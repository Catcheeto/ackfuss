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

        /*
         * 'Object' Manipulation
         */
        virtual bool DropThing( const Thing* what );
        virtual bool EquipThing( const Thing* what );
        virtual bool RemoveThing( const Thing* what );

        /*
         * Name Handling
         */
        virtual void AppendName( const char* name ) { m_name.append( name ); };
        virtual void AppendName( const string name ) { m_name.append( name ); };
        virtual const char* GetName_( Thing* looker = NULL ) const { return m_name.c_str(); };
        virtual string GetName( Thing* looker = NULL ) const { return m_name; };
        bool IsWithinName( const char* word );
        bool IsWithinName( const string word );
        virtual void PrefixName( const char* name ) { m_name.insert( 0, name ); };
        virtual void PrefixName( const string name ) { m_name.insert( 0, name ); };
        virtual void SetName( const char* name ) { m_name = name; };
        virtual void SetName( const string name ) { m_name = name; };

        /*
         * Owner Handling
         */
        Thing* GetOwner() const { return m_owner; };
        void SetOwner( Thing* owner ) { m_owner = owner; };

    protected:
        string m_name;
        Thing* m_owner;
};
