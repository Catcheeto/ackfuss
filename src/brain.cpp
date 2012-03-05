/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#include "h/globals.h"

#ifndef DEC_ACT_WIZ_H
#include "h/act_wiz.h"
#endif

#ifndef DEC_COMM_H
#include "h/comm.h"
#endif

#ifndef DEC_DB_H
#include "h/db.h"
#endif

#ifndef DEC_TELOPT_H
#include "h/telopt.h"
#endif

const char go_ahead_str[] = { char(IAC), char(GA), char('\0') };
void char_hunt (CHAR_DATA *ch);

const void Brain::Disconnect()
{
    char buf[MSL];
    Brain* b = NULL;
    iterBrain di;
    CHAR_DATA *ch;

    if ( snoop_by != NULL )
        snoop_by->Send( "Your victim has left the game.\r\n" );

    for ( di = brain_list.begin(); di != brain_list.end(); di++)
    {
        b = *di;
        if ( b->snoop_by == this )
            b->snoop_by = NULL;
    }

    if ( original )
    {
        if ( character )
            do_return( character, "" );
        else
        {
            bug( "Brain::Disconnect: original without ch", 0 );
            character = original;
            original = NULL;
        }
    }

    if ( ( ch = character ) != NULL )
    {
        snprintf( buf, MSL, "Closing link to %s.", ch->GetName_() );
        Utils::Logger( 0, buf );
        monitor_chan( buf, MONITOR_CONNECT );
        if ( m_connection_state == CON_PLAYING )
        {
            act( "$n has lost $s link.", ch, NULL, NULL, TO_ROOM );
            ch->desc = NULL;
        }
        else
            delete character;
    }

    server.mudNextDesc = brain_list.erase( find( brain_list.begin(), brain_list.end(), this ) );
    close( m_descriptor );
    update_player_cnt();

    delete this;

    return;
}

const void Brain::ProcessColors()
{
    size_t loc = 0;
    uint_t i = 0, k = 0;

    if ( m_output.empty() )
        return;

    for ( i = 0; i < MAX_ANSI; i++ )
    {
        while ( ( loc = m_output.find( ansi_table[i].key ) ) != string::npos )
        {
            if ( CH( this ) && IS_GHOST( CH( this ) ) ) // No color for ghosts
            {
                switch( number_range( 1, 3 ) )
                {
                    case 1: k = col_pos( "white" );     break;
                    case 2: k = col_pos( "gray" );      break;
                    case 3: k = col_pos( "dark_gray" ); break;
                }
                m_output.replace( loc, ansi_table[k].key.length(), ansi_table[k].value );
                continue;
            }
            if ( ansi_table[i].name == "random_fg" ) // Random foreground color
            {
                k = number_range( 0, 16 );
                m_output.replace( loc, ansi_table[k].key.length(), ansi_table[k].value );
            }
            else if ( ansi_table[i].name == "random_bg" ) // Random background color
            {
                k = number_range( 20, 27 );
                m_output.replace( loc, ansi_table[k].key.length(), ansi_table[k].value );
            }
            else // Process color without modification
                m_output.replace( loc, ansi_table[i].key.length(), ansi_table[i].value );
        }
    }

    return;
}

const bool Brain::ProcessOutput( const bool prompt )
{
    if ( m_output.empty() )
        return true;

    if ( prompt && m_connection_state == CON_PLAYING )
    {
        if ( showstr_point )
            Send( "[Please type (c)ontinue, (r)efresh, (b)ack, (h)elp, (q)uit, or RETURN]:  " );
        else
        {
            CHAR_DATA *ch;

            ch = original ? original : character;
            if ( !IS_NPC( ch ) && ( ch->act.test( ACT_BLANK ) && ( ch->pcdata->movement <= sysdata.max_move_disp || !ch->act.test( ACT_AUTOBRIEF ) ) ) )
                Send( "\r\n" );
            if ( ch->hunting || ch->hunt_obj )
                char_hunt( ch );
            if ( !IS_NPC( ch ) && ( ch->pcdata->movement <= sysdata.max_move_disp || !ch->act.test( ACT_AUTOBRIEF ) ) )
                bust_a_prompt( this );
            if ( ch->act.test( ACT_TELNET_GA ) )
                Send( go_ahead_str );
        }
    }

    if ( snoop_by != NULL )
    {
        char foo[MAX_STRING_LENGTH];
        CHAR_DATA *snoop_ch;

        snoop_ch = original ? original : character;
        if ( snoop_ch != NULL )
            snprintf( foo, MSL, "[SNOOP:%s] ", snoop_ch->GetName_() );
        snoop_by->Send( foo );
    }

    ProcessColors();

    if ( !_Send() )
        return false;
    else
        return true;
}

const bool Brain::Read()
{
    char buf[MSL], tmp[MSL];
    ssize_t recvd = 0, start = 0;

    start = strlen( inbuf );
    if ( start >= MSL )
    {
        snprintf( buf, MSL, "Input overflow by %s (%s)", ( character == NULL ) ? "[login]" : character->GetName_(), getHost_() );
        Utils::Logger( 0, buf );
        monitor_chan( buf, MONITOR_CONNECT );
        Send( "\r\n SPAMMING IS RUDE, BYE BYE! \r\n" );
        return false;
    }

    for ( ;; )
    {
        recvd = read( m_descriptor, tmp, sizeof( inbuf ) - start );
        if ( recvd > 0 )
        {
            start += telopt_handler(this, (unsigned char*)tmp, recvd, (unsigned char *)(inbuf + start)); //TODO: improve this
            if ( inbuf[start - 1] == '\n' || inbuf[start - 1] == '\r' )
            {
                inbuf[start - 1] = '\0';
                pushCommandQueue( inbuf );
                break;
            }
        }
        else if ( recvd == 0 )
        {
            Utils::Logger( 0, "EOF encountered on read." );
            return false;
        }
        else if ( errno == EWOULDBLOCK )
            break;
        else
        {
            perror( "Brain::Read" );
            return false;
        }
    }

    inbuf[0] = '\0';

    return true;
}

const void Brain::Send( const string msg )
{
    if ( m_output.empty() && !m_command_run )
    {
        m_output += "\r\n";
        m_output += msg;
    }
    else
        m_output += msg;

    return;
}

const bool Brain::_Send()
{
    ssize_t block = 0, length = m_output.length(), max_size = MSL, sent = 0, start = 0;

    for ( start = 0; start < length; start += sent )
    {
        block = std::min( length - start, max_size );
        sent = send( m_descriptor, m_output.c_str() + start, block, 0 );

        if ( sent == -1 )
        {
            if ( errno == EWOULDBLOCK )
            {
                sent = 0;
                continue;
            }
            else
            {
                perror( "Brain::Send" );
                return false;
            }
        }
    }
    m_output.clear();

    return true;
}

string Brain::pushCommandQueue( const string cmd, const bool front )
{
    char buf[MSL];
    string push = cmd;

    if ( !push.compare( m_command_history.front() ) ) // Kick the repeat spammers
    {
        if ( m_command_repeat++ >= MAX_CMD_HISTORY )
        {
            if ( m_connection_state == CON_PLAYING )
            {
                snprintf( buf, MSL, "%s input spamming!", character->GetName_() );
                Utils::Logger( 0, buf );
                monitor_chan( buf, MONITOR_CONNECT );
            }
            Send( "\r\n ***** SHUT UP!! ***** \r\n" );
            Disconnect();
            return push;
        }
    }
    else
        m_command_repeat = 0;

    if ( !push.compare( "!" ) && !m_command_history.empty() ) // Repeat previous cmd
        push = m_command_history.front();
    if ( front )
        m_command_queue.push_front( push );
    else
        m_command_queue.push_back( push );

    while( m_command_history.size() >= MAX_CMD_HISTORY )
        m_command_history.pop_back();

    return push;
}

Brain::Brain()
{
    snoop_by = NULL;
    character = NULL;
    original = NULL;
    showstr_head = NULL;
    showstr_point = NULL;
    inbuf[0] = '\0';


    m_command_history.clear();
    m_command_queue.clear();
    m_command_repeat = 0;
    m_command_run = false;
    m_connection_state = CON_GET_NAME;
    m_creation_check.reset();
    m_descriptor = uintmin_t;
    m_host = new char[256];
    m_output = "";
    m_port = uintmin_t;
    m_timeout = current_time + MAX_IDLE_TIME;
    m_world = NULL;
}

Brain::~Brain()
{
    delete[] m_host;
}
