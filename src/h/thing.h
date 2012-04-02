/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#define DEC_THING_H

#ifndef DEC_BRAIN_H
#include "brain.h"
#endif

/*
 * One Thing to rule them all!
 */

class Thing {
    public:
        Thing();
        ~Thing();

        // Alignment
        sint_t getAlignment() const { return m_alignment; }
        sint_t decrAlignment( const sint_t amount );
        sint_t incrAlignment( const sint_t amount );
        sint_t setAlignment( const sint_t amount );

        // Brain
        Brain* attachBrain( Brain* brain = NULL, uint_t brain_type = BRAIN_TYPE_DUMB_NPC );
        Brain* getBrain() const { return m_brain; }

        // Clan
        uint_t getClan() const { return m_clan; }
        uint_t setClan( const uint_t clan = 0 );

        // Combat Stats
        sint_t getModAC() const { return m_mod_ac; }
        sint_t decrModAC( const sint_t amount );
        sint_t incrModAC( const sint_t amount );
        sint_t setModAC( const sint_t amount );
        sint_t getModDR() const { return m_mod_dr; }
        sint_t decrModDR( const sint_t amount );
        sint_t incrModDR( const sint_t amount );
        sint_t setModDR( const sint_t amount );
        sint_t getModHR() const { return m_mod_hr; }
        sint_t decrModHR( const sint_t amount );
        sint_t incrModHR( const sint_t amount );
        sint_t setModHR( const sint_t amount );

        // Command Handling
        uint_t canInterpret( const string cmd ) const;

        // Descriptions
        string appendDescrLong( const string descr ) { return m_descr_long.append( descr ); }
        string appendDescrShort( const string descr ) { return m_descr_short.append( descr ); }
        uint_t delDescrExtra( string key ) { return m_descr_extra.erase( key ); }
        string getDescrExtra( string key ) const;
        #define getDescrExtra_( T ) getDescrExtra( T ).c_str()
        list<string> getDescrExtraKeys() const;
        uint_t getDescrExtraSize() const { return m_descr_extra.size(); }
        list<string> getDescrExtraValues() const;
        pair<map<string,string>::iterator,bool> setDescrExtra( const string key, string value ) { return m_descr_extra.insert( pair<string,string>( key, value ) ); }
        string getDescrLong( const Thing* looker = NULL ) const { return m_descr_long; }
        #define getDescrLong_( T ) getDescrLong( T ).c_str()
        string getDescrShort( const Thing* looker = NULL ) const { return m_descr_short; }
        #define getDescrShort_( T ) getDescrShort( T ).c_str()
        string setDescrLong( const string descr ) { return m_descr_long = descr; }
        string setDescrShort( const string descr ) { return m_descr_short = descr; }

        // Flags
        bool getFlag( const uint_t flag_type, const uint_t flag_value ) const;
        bool setFlag( const uint_t flag_type, const uint_t flag_value, const bool flag_state );

        // Level
        uint_t decrExperience( const uint_t amount );
        uint_t getExperience() const { return m_experience; }
        uint_t incrExperience( const uint_t amount );
        uint_t setExperience( const uint_t amount );
        uint_t decrLevel( const uint_t tier = THING_LEVEL_TIER1, const uint_t tclass = THING_LEVEL_TIER1_CLASS_MAGE, const uint_t amount = 1 );
        uint_t getLevel( const uint_t tier = MAX_THING_LEVEL_TIER, const uint_t tclass = MAX_THING_LEVEL_TIER_CLASS, const bool psuedo = false ) const;
        uint_t incrLevel( const uint_t tier = THING_LEVEL_TIER1, const uint_t tclass = THING_LEVEL_TIER1_CLASS_MAGE, const uint_t amount = 1 );
        uint_t setLevel( const uint_t tier = THING_LEVEL_TIER1, const uint_t tclass = THING_LEVEL_TIER1_CLASS_MAGE, const uint_t amount = 1 );
        uint_t getTrust() const;
        uint_t setTrust( const uint_t level );

        // Misc
        bool isAdept() const;
        bool isCBoss() const { return getFlag( THING_FLAG_ACT, THING_FLAG_ACT_CBOSS ); }
        bool isHero() const { return getTrust() >= LEVEL_HERO; }
        bool isImmortal() const { return getTrust() >= LEVEL_IMMORTAL; }
        bool isNPC() const { return !( getBrain() && getBrain()->getType() == BRAIN_TYPE_HUMAN ); }
        bool isRemortal() const;
        bool isVampire() const { return getFlag( THING_FLAG_ACT, THING_FLAG_ACT_VAMPIRE ); }
        bool isWerewolf() const { return getFlag( THING_FLAG_ACT, THING_FLAG_ACT_WEREWOLF ); }
        const void Send( const string msg ) { if ( getBrain() ) getBrain()->Send( msg ); return; }

        // Name
        string appendName( const string name ) { return m_name.append( name ); }
        string getName( const Thing* looker = NULL ) const { return m_name; }
        #define getName_( T ) getName( T ).c_str()
/*        bool IsWithinName( const char* word );
        bool IsWithinName( const string word );*/
        string prefixName( const string name ) { return m_name.insert( 0, name ); }
        string setName( const string name ) { return m_name = name; }
        string getNameWho() const;
        #define getNameWho_( T ) getNameWho( T ).c_str()
        string setNameWho( const string name = "" ) { if ( name.empty() ) { m_name_who.clear(); return m_name_who; } else return m_name_who = name; }

        // 'Object' Manipulation
        bool dropThing( const Thing* what );
        bool equipThing( const Thing* what );
        bool removeThing( const Thing* what );

        // Owner
        Thing* getOwner() const { return m_owner; }
        Thing* setOwner( Thing* owner ) { return m_owner = owner; }

    protected:
        // Alignment
        sint_t m_alignment;

        // Brain
        Brain* m_brain;

        // Clan
        uint_t m_clan;

        // Combat Stats
        sint_t m_mod_ac;
        sint_t m_mod_dr;
        sint_t m_mod_hr;

        // Descriptions
        map<string,string> m_descr_extra;
        string m_descr_long;
        string m_descr_short;

        // Flags
        bitset<MAX_BITSET> m_flag[MAX_THING_FLAG];

        // Level
        uint_t m_experience;
        uint_t m_level[MAX_THING_LEVEL_TIER][MAX_THING_LEVEL_TIER_CLASS];
        uint_t m_trust;

        // Name
        string m_name;
        string m_name_who;

        // Owner
        Thing* m_owner;
};
