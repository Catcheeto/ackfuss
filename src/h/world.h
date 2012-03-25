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

    Brain* getFirstBrain( const uint_t brain_type ) const { return *m_list_brain[brain_type].begin(); }
    Brain* getNextBrain( const uint_t brain_type ) { return ++bi[brain_type] != m_list_brain[brain_type].end() ? *bi[brain_type] : NULL; }
    const void pushListBrain( Brain* brain );
    const void removeListBrain( Brain* brain );
    string setName( const string name ) { return m_name = name; }

    private:
        list<Brain*>::const_iterator bi[MAX_BRAIN_TYPE];
        list<Brain*> m_list_brain[MAX_BRAIN_TYPE];
        string m_name;
};
