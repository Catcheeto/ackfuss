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
        sint_t GetAlignment() const { return m_alignment; }
        sint_t DecrAlignment( const sint_t amount );
        sint_t IncrAlignment( const sint_t amount );
        sint_t SetAlignment( const sint_t amount );

        // Brain
        Brain* AttachBrain( Brain* brain = NULL );
        Brain* GetBrain() const { return m_brain; }

        // Combat Stats
        sint_t GetModAC() const { return m_mod_ac; }
        sint_t DecrModAC( const sint_t amount );
        sint_t IncrModAC( const sint_t amount );
        sint_t SetModAC( const sint_t amount );
        sint_t GetModDR() const { return m_mod_dr; }
        sint_t DecrModDR( const sint_t amount );
        sint_t IncrModDR( const sint_t amount );
        sint_t SetModDR( const sint_t amount );
        sint_t GetModHR() const { return m_mod_hr; }
        sint_t DecrModHR( const sint_t amount );
        sint_t IncrModHR( const sint_t amount );
        sint_t SetModHR( const sint_t amount );

        // Descriptions
        string AppendDescrLong( const string descr ) { return m_descr_long.append( descr ); }
        string AppendDescrShort( const string descr ) { return m_descr_short.append( descr ); }
        uint_t DelDescrExtra( string key ) { return m_descr_extra.erase( key ); }
        string GetDescrExtra( string key ) const;
        char* GetDescrExtra_( string key ) const { return const_cast<char*>( GetDescrExtra( key ).c_str() ); }
        list<string> GetDescrExtraKeys() const;
        uint_t GetDescrExtraSize() const { return m_descr_extra.size(); }
        list<string> GetDescrExtraValues() const;
        pair<map<string,string>::iterator,bool> SetDescrExtra( const string key, string value ) { return m_descr_extra.insert( pair<string,string>( key, value ) ); }
        string GetDescrLong( const Thing* looker = NULL ) const { return m_descr_long; }
        char* GetDescrLong_( const Thing* looker = NULL ) const { return const_cast<char*>( GetDescrLong( looker ).c_str() ); }
        string GetDescrShort( const Thing* looker = NULL ) const { return m_descr_short; }
        char* GetDescrShort_( const Thing* looker = NULL ) const { return const_cast<char*>( GetDescrShort( looker ).c_str() ); }
        string SetDescrLong( const string descr ) { return m_descr_long = descr; }
        string SetDescrShort( const string descr ) { return m_descr_short = descr; }

        // Level
        uint_t GetExperience() const { return m_experience; }
        uint_t DecrExperience( const uint_t amount );
        uint_t IncrExperience( const uint_t amount );
        uint_t SetExperience( const uint_t amount );

        // Name
        string AppendName( const string name ) { return m_name.append( name ); }
        string GetName( const Thing* looker = NULL ) const { return m_name; }
        char* GetName_( const Thing* looker = NULL ) const { return const_cast<char*>( GetName( looker ).c_str() ); }
/*        bool IsWithinName( const char* word );
        bool IsWithinName( const string word );*/
        string PrefixName( const string name ) { return m_name.insert( 0, name ); }
        string SetName( const string name ) { return m_name = name; }

        // 'Object' Manipulation
        bool DropThing( const Thing* what );
        bool EquipThing( const Thing* what );
        bool RemoveThing( const Thing* what );

        // Owner
        Thing* GetOwner() const { return m_owner; }
        Thing* SetOwner( Thing* owner ) { return m_owner = owner; }

    protected:
        // Alignment
        sint_t m_alignment;

        // Brain
        Brain* m_brain;

        // Combat Stats
        sint_t m_mod_ac;
        sint_t m_mod_dr;
        sint_t m_mod_hr;

        // Descriptions
        map<string,string> m_descr_extra;
        string m_descr_long;
        string m_descr_short;

        // Level
        uint_t m_experience;

        // Name
        string m_name;

        // Owner
        Thing* m_owner;
};
