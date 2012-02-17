/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#define DEC_THING_H

/*
 * One Thing to rule them all!
 */

class Thing {
    public:
        Thing();
        ~Thing();

        // Alignment
        const uint_t GetAlignment() const { return m_alignment; };
        const uint_t DecrAlignment( const uint_t amount );
        const uint_t IncrAlignment( const uint_t amount );
        const uint_t SetAlignment( const uint_t amount );

        // Level
        const uint_t GetExperience() const { return m_experience; };
        const uint_t DecrExperience( const uint_t amount );
        const uint_t IncrExperience( const uint_t amount );
        const uint_t SetExperience( const uint_t amount );

        // Name
        const string AppendName( const char* name ) { return m_name.append( name ); };
        const string AppendName( const string name ) { return m_name.append( name ); };
        const char* GetName_( Thing* looker = NULL ) const { return m_name.c_str(); };
        const string GetName( Thing* looker = NULL ) const { return m_name; };
/*        bool IsWithinName( const char* word );
        bool IsWithinName( const string word );*/
        const string PrefixName( const char* name ) { return m_name.insert( 0, name ); };
        const string PrefixName( const string name ) { return m_name.insert( 0, name ); };
        const string SetName( const char* name ) { return m_name = name; };
        const string SetName( const string name ) { return m_name = name; };

        // 'Object' Manipulation
        const bool DropThing( const Thing* what );
        const bool EquipThing( const Thing* what );
        const bool RemoveThing( const Thing* what );

        // Owner
        const Thing* GetOwner() const { return m_owner; };
        const Thing* SetOwner( Thing* owner ) { return m_owner = owner;};

    protected:
        // Alignment
        uint_t m_alignment;

        // Level
        uint_t m_experience;

        // Name
        string m_name;

        // Owner
        Thing* m_owner;
};
