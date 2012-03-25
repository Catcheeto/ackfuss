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

const void World::pushListBrain( Brain* brain )
{
    bitset<MAX_BITSET> flags;

    brain->setWorld( this );

    if ( brain->getType() < uintmin_t || brain->getType() >= MAX_BRAIN_TYPE )
    {
        flags.set(UTILS_TYPE_ERROR);
        Utils::Logger( flags, "Invalid Brain type (%lu). Unable to add to any Brain list. This may cause a memory leak.", brain->getType() );
        return;
    }

    m_list_brain[brain->getType()].push_back( brain );

    return;
}

const void World::removeListBrain( Brain* brain )
{
    bitset<MAX_BITSET> flags;

    if ( brain->getType() < uintmin_t || brain->getType() >= MAX_BRAIN_TYPE )
    {
        flags.set(UTILS_TYPE_ERROR);
        Utils::Logger( flags, "Invalid Brain type (%lu). Unable to remove from any Brain list. This may cause a memory leak.", brain->getType() );
        return;
    }

    m_list_brain[brain->getType()].remove( brain );

    return;
}

World::World()
{
    for ( uint_t i = 0; i < MAX_BRAIN_TYPE; i++ )
    {
        bi[i] = m_list_brain[i].begin();
        m_list_brain[i].clear();
    }
    m_name.clear();
}

World::~World()
{
    for ( uint_t i = 0; i < MAX_BRAIN_TYPE; i++ )
        m_list_brain[i].clear();
    m_name.clear();
}
