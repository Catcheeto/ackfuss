/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#include "h/globals.h"

#ifndef DEC_DB_H
#include "h/db.h"
#endif

const char go_ahead_str[] = { char(IAC), char(GA), char('\0') };
void bust_a_prompt (DESCRIPTOR_DATA *d);
void char_hunt (CHAR_DATA *ch);

const string Brain::ProcessColors( const string msg ) const
{
    string output = msg;
    size_t loc = 0;
    uint_t i = 0, k = 0;

    for ( i = 0; i < MAX_ANSI; i++ )
    {
        while ( ( loc = output.find( ansi_table[i].key ) ) != string::npos )
        {
            if ( CH( this ) && IS_GHOST( CH( this ) ) ) // No color for ghosts
            {
                switch( number_range( 1, 3 ) )
                {
                    case 1: k = col_pos( "white" );     break;
                    case 2: k = col_pos( "gray" );      break;
                    case 3: k = col_pos( "dark_gray" ); break;
                }
                output.replace( loc, ansi_table[k].key.length(), ansi_table[k].value );
                continue;
            }
            if ( ansi_table[i].name == "random_fg" ) // Random foreground color
            {
                k = number_range( 0, 16 );
                output.replace( loc, ansi_table[k].key.length(), ansi_table[k].value );
            }
            else if ( ansi_table[i].name == "random_bg" ) // Random background color
            {
                k = number_range( 20, 27 );
                output.replace( loc, ansi_table[k].key.length(), ansi_table[k].value );
            }
            else // Process color without modification
                output.replace( loc, ansi_table[i].key.length(), ansi_table[i].value );
        }
    }

    return output;
}

const bool Brain::ProcessOutput( const bool prompt )
{
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
    string output;
    output = "";
    if ( !Send( output ) )
        return false;
    else
        return true;
}

const bool Brain::Send( const string msg ) const
{
    string _msg = ProcessColors( msg );
    ssize_t block = 0, length = _msg.length(), max_size = MSL, sent = 0, start = 0;

    for ( start = 0; start < length; start += sent )
    {
        block = std::min( length - start, max_size );
        sent = send( m_descriptor, _msg.c_str() + start, block, 0 );

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

    return true;
}


Brain::Brain()
{
    snoop_by = NULL;
    character = NULL;
    original = NULL;
    showstr_head = NULL;
    showstr_point = NULL;
    flags = 0;
    childpid = 0;
    incomm[0] = '\0';
    inlast[0] = '\0';
    inbuf[0] = '\0';


    m_connection_state = CON_GET_NAME;
    m_descriptor = uintmin_t;;
    m_host = new char[256];
    m_port = uintmin_t;
    m_timeout = current_time + MAX_IDLE_TIME;
    m_world = NULL;
}

Brain::~Brain()
{
    delete[] m_host;
}
