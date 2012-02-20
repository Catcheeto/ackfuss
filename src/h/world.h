/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#define DEC_WORLD_H

#ifndef DEC_BRAIN_H
#include "brain.h"
#endif

class World {
    public:
        World();
        ~World();

    Brain* getFirstBrain() const { return *m_list_brain.begin(); }
    Brain* getNextBrain() { return ++bi != m_list_brain.end() ? *bi : NULL; }
    const void pushListBrain( Brain* brain ) { brain->setWorld( this ); m_list_brain.push_back( brain ); return; }
    const void removeListBrain( Brain* brain ) { m_list_brain.remove( brain ); return; }
    const string &setName( const string name ) { return m_name = name; }

    private:
        list<Brain*>::const_iterator bi;
        list<Brain*> m_list_brain;
        string m_name;
};
