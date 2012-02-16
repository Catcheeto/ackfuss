/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#include "h/globals.h"

#ifndef DEC_ACT_OBJ_H
#include "h/act_obj.h"
#endif

#ifndef DEC_THING_H
#include "h/thing.h"
#endif

/*
 * Level Handling
 */

const bool Thing::DecrExperience( const uint_t amount )
{
    if ( amount <= 0 || amount >= uintmax_t )
        return false;

    if ( ( m_experience - amount ) <= 0 )
        m_experience = 0;
    else
        m_experience -= amount;

    return true;
}

const bool Thing::IncrExperience( const uint_t amount )
{
    if ( amount <= 0 || amount >= uintmax_t )
        return false;

    if ( ( m_experience + amount ) >= uintmax_t )
        m_experience = uintmax_t;
    else
        m_experience += amount;

    return true;
}

const bool Thing::SetExperience( const uint_t amount )
{
    if ( amount <= 0 || amount >= uintmax_t )
        return false;

    m_experience = amount;

    return true;
}

/*
 * 'Object' Manipulation
 */

const bool Thing::DropThing( const Thing* what )
{
    char name[MSL];

    strcpy( name, what->GetName().c_str() );
    do_drop( static_cast<CHAR_DATA*>(this), name );
    return true;
}

const bool Thing::EquipThing( const Thing* what )
{
    char name[MSL];

    strcpy( name, what->GetName().c_str() );
    do_wear( static_cast<CHAR_DATA*>(this), name );
    return true;
}

const bool Thing::RemoveThing( const Thing* what )
{
    char name[MSL];

    strcpy( name, what->GetName().c_str() );
    do_remove( static_cast<CHAR_DATA*>(this), name );
    return true;
}

/*
 * Name Handling
 */
/*
bool Thing::IsWithinName( const char* word );
{
    string holder;
    stringstream stream;
    vector<string> tokens;
    vector<string>::iterator it;

    stream << word;
    while( stream >> holder )
        tokens.push_back( holder );

    for ( it = tokens.begin(); it < tokens.end(); it++ )
    {
        if ( m_name.find( *it ) )
            return true;
    }

    return false;
}

bool Thing::IsWithinName( const string word );
{
    string holder;
    stringstream stream;
    vector<string> tokens;
    vector<string>::iterator it;

    stream << word;
    while( stream >> holder )
        tokens.push_back( holder );

    for ( it = tokens.begin(); it < tokens.end(); it++ )
    {
        if ( m_name.find( *it ) )
            return true;
    }

    return false;
}
*/
Thing::Thing()
{
    m_experience = 0;
    m_name.clear();
    m_owner = NULL;
}

Thing::~Thing()
{
}
