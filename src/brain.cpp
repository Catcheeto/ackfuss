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
