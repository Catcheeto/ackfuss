/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#define DEC_BRAIN_H

#ifndef DEC_WORLD_H
#include "world.h"
#endif

class Brain {
    public:
        Brain();
        ~Brain();
        Brain* snoop_by;
        CHAR_DATA *character;
        CHAR_DATA *original;
        char inbuf[4 * MAX_INPUT_LENGTH];
        char incomm[MAX_INPUT_LENGTH];
        char inlast[MAX_INPUT_LENGTH];
        short repeat;
        char *showstr_head;
        char *showstr_point;

        const bool ProcessOutput( const bool prompt = true );
        const bool Read();
        const void Send( const string msg ) { if ( m_output.empty() && !m_command_run ) { m_output += "\r\n"; m_output += msg; } else m_output += msg; return; };

        bool getCommandRun() const { return m_command_run; }
        bool togCommandRun() { return m_command_run = !m_command_run; }

        sint_t getConnectionState( const sint_t state = MSL ) const { return state == MSL ? m_connection_state : m_connection_state == state; }
        sint_t setConnectionState( const sint_t state ) { return m_connection_state = state; }

        bool getCreationCheck( const uint_t check ) const { return m_creation_check.test( check ); }
        bool remCreationCheck( const uint_t check ) { m_creation_check.reset( check ); return m_creation_check.test( check ); }
        bool setCreationCheck( const uint_t check ) { m_creation_check.set( check ); return m_creation_check.test( check ); }

        uint_t getDescriptor() const { return m_descriptor; }
        uint_t setDescriptor( const uint_t descriptor ) { return  m_descriptor = descriptor; }

        string getHost() const { return m_host; }
        char* getHost_() const { return m_host; }
        string setHost( const char* host ) { strcpy( m_host, host ); return m_host; }

        uint_t getPort() const { return m_port; }
        uint_t setPort( const uint_t port ) { return m_port = port; }

        time_t getTimeout() const { return m_timeout; }
        time_t setTimeout( const time_t timeout ) { return m_timeout = timeout; }

        World* getWorld() const { return m_world; }
        World* setWorld( World* world ) { return m_world = world; }

    private:
        const void ProcessColors();
        const bool _Send();

        bool   m_command_run;      // Found a command run, force output to socket
        sint_t m_connection_state; // Connection state
        bitset<MAX_CREATION_CHECK> m_creation_check; // Ensure creation process completed
        uint_t m_descriptor;       // File descriptor channel
        char*  m_host;             // Remote hostname
        string m_output;           // Output buffer
        uint_t m_port;             // Remote port
        time_t m_timeout;          // Idle timeout
        World* m_world;            // Game world
};
