/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#define DEC_BRAIN_H

#ifndef DEC_WORLD_H
#include "world.h"
#endif

class Brain {
    public:
        Brain();
        ~Brain();
        DESCRIPTOR_DATA *d;


        string GetHost() const { return m_host; }
        char* GetHost_() const { return m_host; }
        string setHost( const char* host ) { strcpy( m_host, host ); return m_host; }
        World* setWorld( World* world ) { return m_world = world; }

    private:
        char*  m_host;
        World* m_world;
};
