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
void write_to_buffer (DESCRIPTOR_DATA *d, const char *txt, int length = 0);

const bool Brain::ProcessOutput( const bool prompt )
{
    if ( prompt && m_connection_state == CON_PLAYING )
    {
        if ( showstr_point )
            write_to_buffer( this, "[Please type (c)ontinue, (r)efresh, (b)ack, (h)elp, (q)uit, or RETURN]:  " );
        else
        {
            CHAR_DATA *ch;

            ch = original ? original : character;
            if ( !IS_NPC(ch) && ch->act.test(ACT_BLANK) && (ch->pcdata->movement <= sysdata.max_move_disp || !ch->act.test(ACT_AUTOBRIEF)) )
                write_to_buffer( this, "\r\n", 2 );
            if ( ch->hunting || ch->hunt_obj )
                char_hunt( ch );
            if ( !IS_NPC(ch) && (ch->pcdata->movement <= sysdata.max_move_disp || !ch->act.test(ACT_AUTOBRIEF)) )
                bust_a_prompt( this );
            if ( ch->act.test(ACT_TELNET_GA) )
                write_to_buffer( this, go_ahead_str );
        }
    }

    if ( outtop == 0 )
        return TRUE;

    if ( snoop_by != NULL )
    {
        char foo[MAX_STRING_LENGTH];
        CHAR_DATA *snoop_ch;

        snoop_ch = original != NULL ? original : character;
        if ( snoop_ch != NULL )
            snprintf( foo, MSL, "[SNOOP:%s] ", snoop_ch->GetName_() );
        write_to_buffer( snoop_by, foo );
        write_to_buffer( snoop_by, outbuf, outtop );
    }

    if ( !Send( outbuf ) )
    {
        outtop = 0;
        return FALSE;
    }
    else
    {
        outtop = 0;
        return TRUE;
    }
}

const bool Brain::Send( const string msg ) const
{
    ssize_t block = 0, length = msg.length(), max_size = MSL, sent = 0, start = 0;

    for ( start = 0; start < length; start += sent )
    {
        block = std::min( length - start, max_size );
        sent = send( m_descriptor, msg.c_str() + start, block, 0 );

        if ( sent == -1 )
        {
            if ( errno == EWOULDBLOCK )
            {
                sent = 0;
                continue;
            }
            else
            {
                perror( "Write_to_descriptor" );
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
    outsize = 2048;
    outtop = 0;
    fcommand = false;
    outbuf = (char*)malloc(outsize);
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
