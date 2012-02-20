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

World::World()
{
    bi = m_list_brain.begin();
    m_list_brain.clear();
    m_name.clear();

    world_list.push_back( this );
}

World::~World()
{
    m_list_brain.clear();
    m_name.clear();
    log_string("world dtor");
}
