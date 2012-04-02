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

uint_t Thing::decrLevel( const uint_t tier, const uint_t tclass, const uint_t amount )
{
    if ( tier < uintmin_t || tier >= MAX_THING_LEVEL_TIER )
        return 0;

    if ( tclass < uintmin_t || tclass >= MAX_THING_LEVEL_TIER_CLASS )
        return 0;

    if ( amount <= uintmin_t || amount >= uintmax_t )
        return 0;

    if ( ( m_level[tier][tclass] - amount ) <= uintmin_t )
        return m_level[tier][tclass] = uintmin_t;
    else
        return m_level[tier][tclass] -= amount;
}

uint_t Thing::getLevel( const uint_t tier, const uint_t tclass, const bool psuedo ) const
{
    uint_t i = 0, x = 0, value = 0;

    if ( tier < uintmin_t || tier > MAX_THING_LEVEL_TIER )
        return value = getLevel();

    if ( tclass < uintmin_t || tclass > MAX_THING_LEVEL_TIER_CLASS )
        return value = getLevel();

    if ( psuedo )
    {
        for ( i = 0; i < MAX_THING_LEVEL_TIER2_CLASS; i++ )
            value += m_level[THING_LEVEL_TIER2][i];
        value /= 4;

        return value += getLevel();
    }

    if ( tier == MAX_THING_LEVEL_TIER && tclass == MAX_THING_LEVEL_TIER_CLASS && !psuedo ) // return the highest value of all classes
    {
        for ( i = 0; i < MAX_THING_LEVEL_TIER; i++ )
            for ( x = 0; x < MAX_THING_LEVEL_TIER_CLASS; x++ )
                if ( m_level[i][x] > value )
                   value = m_level[i][x];

        return value;
    }

    return value = m_level[tier][tclass];
}

uint_t Thing::incrLevel( const uint_t tier, const uint_t tclass, const uint_t amount )
{
    if ( tier < uintmin_t || tier >= MAX_THING_LEVEL_TIER )
        return 0;

    if ( tclass < uintmin_t || tclass >= MAX_THING_LEVEL_TIER_CLASS )
        return 0;

    if ( amount <= uintmin_t || amount >= uintmax_t )
        return 0;

    if ( ( m_level[tier][tclass] + amount ) >= MAX_LEVEL )
        return m_level[tier][tclass] = MAX_LEVEL;
    else
        return m_level[tier][tclass] += amount;
}

uint_t Thing::setLevel( const uint_t tier, const uint_t tclass, const uint_t amount )
{
Utils::Logger( 0, Utils::FormatString( 0, "tier: %lu -- tclass: %lu -- amount: %lu", tier, tclass, amount ) );
    if ( tier < uintmin_t || tier >= MAX_THING_LEVEL_TIER )
        return 0;

    if ( tclass < uintmin_t || tclass >= MAX_THING_LEVEL_TIER_CLASS )
        return 0;

    if ( amount <= uintmin_t || amount >= uintmax_t )
        return 0;

    if ( amount >= MAX_LEVEL )
        return m_level[tier][tclass] = MAX_LEVEL;
    else
        return m_level[tier][tclass] = amount;
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

// Misc
bool Thing::isAdept() const
{
    uint_t i = 0;

    for ( i = 0; i < MAX_THING_LEVEL_TIER3_CLASS; i++ )
        if ( m_level[THING_LEVEL_TIER3][i] > uintmin_t )
            return true;

    return false;
}

bool Thing::isRemortal() const
{
    uint_t i = 0;

    for ( i = 0; i < MAX_THING_LEVEL_TIER2_CLASS; i++ )
        if ( m_level[THING_LEVEL_TIER2][i] > uintmin_t )
            return true;

    return false;
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
string Thing::getNameWho() const
{
    string output;

    if ( isNPC() )
        return output = "";
    else if ( isImmortal() )
    {
        if ( !m_name_who.empty() )
            return output = m_name_who;

        switch ( getLevel() )
        {
            case MAX_LEVEL - 0: output = "@@l~* CREATOR *~@@N ";
            case MAX_LEVEL - 1: output = "@@B-* SUPREME *-@@N ";
            case MAX_LEVEL - 2: output = "@@a-=MAJOR GOD=-@@N ";
            case MAX_LEVEL - 3: output = "@@a--MINOR GOD--@@N ";
            case MAX_LEVEL - 4: output = "@@c - IMMORTAL -@@N ";
        }

        return output;
    }
    else if ( isAdept() )
    {
        if ( !m_name_who.empty() )
            return output = m_name_who;

        switch ( getLevel( THING_LEVEL_TIER3, THING_LEVEL_TIER3_CLASS_ADEPT ) )
        {
            case 1:  output = "@@W    Mystic    @@N";
            case 2:  output = "@@a   Templar    @@N";
            case 3:  output = "@@l Illusionist  @@N";
            case 4:  output = "@@e   Crusader   @@N";
            case 5:  output = "@@d   Warlock    @@N";
            case 6:  output = "@@a   Paladin    @@N";
            case 7:  output = "@@r    Ranger    @@N";
            case 8:  output = "@@c  Gladiator   @@N";
            case 9:  output = "@@l    Shogun    @@N";
            case 10: output = "@@e    Shamen    @@N";
            case 11: output = "@@r    Druid     @@N";
            case 12: output = "@@b  Conjurer    @@N";
            case 13: output = "@@l Elementalist @@N";
            case 14: output = "@@m  Runemaster  @@N";
            case 15: output = "@@d Shadowmaster @@N";
            case 16: output = "@@b Beastmaster  @@N";
            case 17: output = "@@R   Warlord    @@N";
            case 18: output = "@@e  Dragonlord  @@N";
            case 19: output = "@@d  Demonlord   @@N";
            case 20: output = "@@m  Realm Lord  @@N";
        }

        return output;
    }
    else if ( isRemortal() )
    {
        return output = Utils::FormatString( 0, "@@m%2lu %2lu %2lu %2lu %2lu@@N",
            getLevel( THING_LEVEL_TIER2, THING_LEVEL_TIER2_CLASS_SORCERER ),
            getLevel( THING_LEVEL_TIER2, THING_LEVEL_TIER2_CLASS_MONK ),
            getLevel( THING_LEVEL_TIER2, THING_LEVEL_TIER2_CLASS_ASSASSIN ),
            getLevel( THING_LEVEL_TIER2, THING_LEVEL_TIER2_CLASS_KNIGHT ),
            getLevel( THING_LEVEL_TIER2, THING_LEVEL_TIER2_CLASS_NECROMANCER ) );
    }
    else
    {
        return output = Utils::FormatString( 0, "@@b%2lu %2lu %2lu %2lu %2lu@@N",
            getLevel( THING_LEVEL_TIER1, THING_LEVEL_TIER1_CLASS_MAGE ),
            getLevel( THING_LEVEL_TIER1, THING_LEVEL_TIER1_CLASS_CLERIC ),
            getLevel( THING_LEVEL_TIER1, THING_LEVEL_TIER1_CLASS_THIEF ),
            getLevel( THING_LEVEL_TIER1, THING_LEVEL_TIER1_CLASS_WARRIOR ),
            getLevel( THING_LEVEL_TIER1, THING_LEVEL_TIER1_CLASS_PSIONICIST ) );
    }
}

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
    for ( uint_t i = 0; i < MAX_THING_LEVEL_TIER; i++ )
        for ( uint_t x = 0; x < MAX_THING_LEVEL_TIER_CLASS; x++ )
            m_level[i][x] = uintmin_t;
    m_trust = uintmin_t;

    // Name
    m_name.clear();
    m_name_who.clear();

    // Owner
    m_owner = NULL;
}

Thing::~Thing()
{
    if ( m_brain )
        delete m_brain;
}
