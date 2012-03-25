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
Brain* Thing::attachBrain( Brain* brain, uint_t brain_type )
{
    if ( brain )
        return m_brain = brain;
    else
    {
        m_brain = new Brain();
        m_brain->setType( brain_type );
        CoreWorld->pushListBrain( m_brain );
        return m_brain;
    }
}

// Clan
uint_t Thing::setClan( const uint_t clan )
{
    if ( clan <= uintmin_t || clan >= MAX_CLAN )
        return m_clan = 0;
    else
        return m_clan = clan;
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

// Command Handling
uint_t Thing::canInterpret( const string cmd ) const
{
    uint_t value = 0;

    for ( value = 0; value < server.total_commands; value++ )
    {
        if ( cmd_table[value].level == CLAN_ONLY && m_clan == uintmin_t )
            continue;

        if ( cmd_table[value].level == BOSS_ONLY && !isCBoss() )
            continue;

        if ( cmd_table[value].level == VAMP_ONLY && !isVampire() && getTrust() < L_GOD )
            continue;

        if ( cmd_table[value].level == WOLF_ONLY && !isWerewolf() && getTrust() < L_GOD  )
            continue;

        if ( cmd.c_str()[0] == cmd_table[value].name[0] )
            Utils::Logger( 0, "trust: %lu -- npc: %d -- btype: %lu -- cmd: %s -- table: %s (%lu)", getTrust(), isNPC(), getBrain()->getType(), cmd.c_str(), cmd_table[value].name, cmd_table[value].level );
        if ( !str_prefix( cmd.c_str(), cmd_table[value].name ) && cmd_table[value].level <= getTrust() )
            break;
    }

    return value;
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

// Flags
bool Thing::getFlag( const uint_t flag_type, const uint_t flag_value ) const
{
    if ( flag_type <= uintmin_t || flag_type >= MAX_THING_FLAG )
        return false;

    if ( flag_value <= uintmin_t || flag_value >= MAX_BITSET )
        return false;

    return m_flag[flag_type].test( flag_value );
}

bool Thing::setFlag( const uint_t flag_type, const uint_t flag_value, const bool flag_state )
{
    if ( flag_type <= uintmin_t || flag_type >= MAX_THING_FLAG )
        return false;

    if ( flag_value <= uintmin_t || flag_value >= MAX_BITSET )
        return false;

    m_flag[flag_type].set( flag_value, flag_state );

    return true;
}

// Level
uint_t Thing::decrExperience( const uint_t amount )
{
    if ( amount <= uintmin_t || amount >= uintmax_t )
        return 0;

    if ( ( m_experience - amount ) <= uintmin_t )
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
    if ( amount <= uintmin_t || amount >= uintmax_t )
        return 0;

    return m_experience = amount;
}

uint_t Thing::getLevel() const
{
    return MAX_LEVEL;
}

uint_t Thing::getTrust() const
{
    if ( !isNPC() && getFlag( THING_FLAG_ACT, THING_FLAG_ACT_AMBASSADOR ) )
        return ( LEVEL_HERO + 1 );

    if ( m_trust != uintmin_t )
        return m_trust;

    if ( isNPC() && getLevel() >= LEVEL_HERO )
        return ( LEVEL_HERO - 1 );
    else
        return getLevel();
}

uint_t Thing::setTrust( const uint_t level )
{
    if ( level <= uintmin_t || level >= MAX_LEVEL )
        return 0;

    return m_trust = level;
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

    // Clan
    m_clan = uintmin_t;

    // Combat Stats
    m_mod_ac = uintmin_t;
    m_mod_dr = uintmin_t;
    m_mod_hr = uintmin_t;

    // Descriptions
    m_descr_extra.clear();
    m_descr_long.clear();
    m_descr_short.clear();

    // Flags
    for ( uint_t i = 0; i < MAX_THING_FLAG; i++ )
        m_flag[i].reset();

    // Level
    m_experience = uintmin_t;
    m_trust = uintmin_t;

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
