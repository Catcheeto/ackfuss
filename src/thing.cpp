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

#ifndef DEC_BRAIN_H
#include "h/brain.h"
#endif

#ifndef DEC_THING_H
#include "h/thing.h"
#endif

// Alignment
sint_t Thing::decrAlignment( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    if ( ( m_alignment - amount ) <= sintmin_t )
        return m_alignment = sintmin_t;
    else
        return m_alignment -= amount;
}

sint_t Thing::incrAlignment( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    if ( ( m_alignment + amount ) >= sintmax_t )
        return m_alignment = sintmax_t;
    else
        return m_alignment += amount;
}

sint_t Thing::setAlignment( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    return m_alignment = amount;
}

// Brain
Brain* Thing::attachBrain( Brain* brain )
{
    if ( brain )
        return m_brain = brain;
    else
    {
        m_brain = new Brain();
        CoreWorld->pushListBrain( m_brain );
        return m_brain;
    }
}

// Combat Stats
sint_t Thing::decrModAC( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    if ( ( m_mod_ac - amount ) <= sintmin_t )
        return m_mod_ac = sintmin_t;
    else
        return m_mod_ac -= amount;
}

sint_t Thing::incrModAC( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    if ( ( m_mod_ac + amount ) >= sintmax_t )
        return m_mod_ac = sintmax_t;
    else
        return m_mod_ac += amount;
}

sint_t Thing::setModAC( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    return m_mod_ac = amount;
}

sint_t Thing::decrModDR( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    if ( ( m_mod_dr - amount ) <= sintmin_t )
        return m_mod_dr = sintmin_t;
    else
        return m_mod_dr -= amount;
}

sint_t Thing::incrModDR( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    if ( ( m_mod_dr + amount ) >= sintmax_t )
        return m_mod_dr = sintmax_t;
    else
        return m_mod_dr += amount;
}

sint_t Thing::setModDR( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    return m_mod_dr = amount;
}

sint_t Thing::decrModHR( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    if ( ( m_mod_hr - amount ) <= sintmin_t )
        return m_mod_hr = sintmin_t;
    else
        return m_mod_hr -= amount;
}

sint_t Thing::incrModHR( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    if ( ( m_mod_hr + amount ) >= sintmax_t )
        return m_mod_hr = sintmax_t;
    else
        return m_mod_hr += amount;
}

sint_t Thing::setModHR( const sint_t amount )
{
    if ( amount <= sintmin_t || amount >= sintmax_t )
        return 0;

    return m_mod_hr = amount;
}

// Descriptions
string Thing::getDescrExtra( const string key ) const
{
    map<string,string>::const_iterator it = m_descr_extra.find( key );
    string value = it->second;

    return value;
}

list<string> Thing::getDescrExtraKeys() const
{
    map<string,string>::const_iterator it;
    list<string> value;;

    for ( it =  m_descr_extra.begin(); it != m_descr_extra.end(); it++ )
        value.push_back( it->first );

    return value;
}

list<string> Thing::getDescrExtraValues() const
{
    map<string,string>::const_iterator it;
    list<string> value;

    for ( it =  m_descr_extra.begin(); it != m_descr_extra.end(); it++ )
        value.push_back( it->second );

    return value;
}

// Level
uint_t Thing::decrExperience( const uint_t amount )
{
    if ( amount <= uintmin_t || amount >= uintmax_t )
        return 0;

    if ( ( m_experience - amount ) <= 0 )
        return m_experience = uintmin_t;
    else
        return m_experience -= amount;
}

uint_t Thing::incrExperience( const uint_t amount )
{
    if ( amount <= uintmin_t || amount >= uintmax_t )
        return 0;

    if ( ( m_experience + amount ) >= uintmax_t )
        return m_experience = uintmax_t;
    else
        return m_experience += amount;
}

uint_t Thing::setExperience( const uint_t amount )
{
    if ( amount <= 0 || amount >= uintmax_t )
        return 0;

    return m_experience = amount;
}

// 'Object' Manipulation
bool Thing::dropThing( const Thing* what )
{
    char name[MSL];

    strcpy( name, what->getName().c_str() );
    do_drop( static_cast<CHAR_DATA*>(this), name );
    return true;
}

bool Thing::equipThing( const Thing* what )
{
    char name[MSL];

    strcpy( name, what->getName().c_str() );
    do_wear( static_cast<CHAR_DATA*>(this), name );
    return true;
}

bool Thing::removeThing( const Thing* what )
{
    char name[MSL];

    strcpy( name, what->getName().c_str() );
    do_remove( static_cast<CHAR_DATA*>(this), name );
    return true;
}

// Name
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
    // Alignment
    m_alignment = uintmin_t;

    // Brain
    m_brain = NULL;

    // Combat Stats
    m_mod_ac = uintmin_t;
    m_mod_dr = uintmin_t;
    m_mod_hr = uintmin_t;

    // Descriptions
    m_descr_extra.clear();
    m_descr_long.clear();
    m_descr_short.clear();

    // Level
    m_experience = uintmin_t;

    // Name
    m_name.clear();

    // Owner
    m_owner = NULL;
}

Thing::~Thing()
{
    if ( m_brain )
        delete m_brain;
}
