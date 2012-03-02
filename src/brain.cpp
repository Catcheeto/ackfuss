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

#ifndef DEC_DB_H
#include "h/db.h"
#endif

#ifndef DEC_TELOPT_H
#include "h/telopt.h"
#endif

const char go_ahead_str[] = { char(IAC), char(GA), char('\0') };
void bust_a_prompt (DESCRIPTOR_DATA *d);
void char_hunt (CHAR_DATA *ch);

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
    int iStart;

    /*
     * Check for overflow.
     */
    iStart = strlen( inbuf );
    if ( iStart >= (int)sizeof( inbuf ) - 10 )
    {
        snprintf( log_buf, (2 * MIL), "%s input overflow!", getHost_() );
        log_string( log_buf );
        snprintf( log_buf, (2 * MIL), "input overflow by %s (%s)", ( character == NULL ) ? "[login]" : character->GetName_(), getHost_() );
        monitor_chan( log_buf, MONITOR_CONNECT );
        Send( "\r\n SPAMMING IS RUDE, BYE BYE! \r\n" );
        return FALSE;
    }

    /*
     * Snarf input.
     */
    for ( ;; )
    {
        unsigned char tmp[MSL];
        int nRead;

        nRead = read( getDescriptor(), tmp, sizeof( tmp ) - 10 - iStart );
        if ( nRead > 0 )
        {
            iStart += telopt_handler(this, tmp, nRead, (unsigned char *)(inbuf + iStart));
            if ( inbuf[iStart - 1] == '\n' || inbuf[iStart - 1] == '\r' )
            {
                inbuf[iStart - 1] = '\0';
                pushCommandQueue( inbuf );
                inbuf[0] = '\0';
                break;
            }
        }
        else if ( nRead == 0 )
        {
            log_string( "EOF encountered on read." );
            return FALSE;
        }
        else if ( errno == EWOULDBLOCK )
            break;
        else
        {
            perror( "Read_from_descriptor" );
            return FALSE;
        }
    }

    return TRUE;
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
    if ( front )
        m_command_queue.push_front( cmd );
    else
        m_command_queue.push_back( cmd );

    while( m_command_history.size() >= MAX_CMD_HISTORY )
        m_command_history.pop_back();

    return cmd;
}

Brain::Brain()
{
    snoop_by = NULL;
    character = NULL;
    original = NULL;
    showstr_head = NULL;
    showstr_point = NULL;
    inlast[0] = '\0';
    inbuf[0] = '\0';


    m_command_history.clear();
    m_command_queue.clear();
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

/*
 * Transfer one line from input buffer to input line.
void read_from_buffer( DESCRIPTOR_DATA * d )
{
    int i, j, k;

     * Hold horses if pending command already.
    if ( d->incomm[0] != '\0' )
        return;

     * Look for at least one new line.
    for ( i = 0; d->inbuf[i] != '\n' && d->inbuf[i] != '\r'; i++ )
    {
        if ( d->inbuf[i] == '\0' )
            return;
    }

     * Canonical input processing.
    for ( i = 0, k = 0; d->inbuf[i] != '\n' && d->inbuf[i] != '\r'; i++ )
    {
        if ( k >= MAX_INPUT_LENGTH - 2 )
        {
            d->Send( "Line too long.\r\n" );

             * skip the rest of the line
            for ( ; d->inbuf[i] != '\0'; i++ )
            {
                if ( d->inbuf[i] == '\n' || d->inbuf[i] == '\r' )
                    break;
            }
            d->inbuf[i] = '\n';
            d->inbuf[i + 1] = '\0';
            break;
        }

        if ( d->inbuf[i] == '\b' && k > 0 )
            --k;
        else if ( isascii( d->inbuf[i] ) && isprint( d->inbuf[i] ) )
            d->incomm[k++] = d->inbuf[i];
    }

     * Finish off the line.
    if ( k == 0 )
        d->incomm[k++] = ' ';
    d->incomm[k] = '\0';

     * Deal with bozos with #repeat 1000 ...
    if ( k > 1 || d->incomm[0] == '!' )
    {
        if ( d->incomm[0] != '!' && strcmp( d->incomm, d->inlast ) )
        {
            d->repeat = 0;
        }
        else
        {
            if ( ++d->repeat >= 30 )
            {
                if ( d->getConnectionState( CON_PLAYING ) )
                {
                    snprintf( log_buf, (2 * MIL), "%s input spamming!", d->character->GetName_() );
                    log_string( log_buf );
                    monitor_chan( log_buf, MONITOR_CONNECT );
                }
                d->Send( "\r\n***** SHUT UP!! *****\r\n" );
                close_socket( d );
                 * old way: strcpy( d->incomm, "quit" );
            }
        }
    }

     * Do '!' substitution.
    if ( d->incomm[0] == '!' )
        strcpy( d->incomm, d->inlast );
    else
        strcpy( d->inlast, d->incomm );

     * Shift the input buffer.
    while ( d->inbuf[i] == '\n' || d->inbuf[i] == '\r' )
        i++;
    for ( j = 0; ( d->inbuf[j] = d->inbuf[i + j] ) != '\0'; j++ )
        ;
    return;
} */
