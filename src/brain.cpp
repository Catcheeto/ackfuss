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
