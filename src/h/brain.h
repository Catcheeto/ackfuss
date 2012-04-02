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
//        ~Brain();
        CHAR_DATA *character;
        CHAR_DATA *original;
        char inbuf[4 * MAX_INPUT_LENGTH];
        char *showstr_head;
        char *showstr_point;

        const void Disconnect();
        const bool ProcessOutput( const bool prompt = true );
        const bool Read();
        const void Send( const string msg );

        list<string> getCommandHistory() const { return m_command_history; }
        string pushCommandHistory( const string cmd ) { m_command_history.push_front( cmd ); return cmd; }

        list<string> getCommandQueue() const { return m_command_queue; }
        bool preCommandQueue( const string cmd );
        string popCommandQueue() { string cmd = m_command_queue.front(); m_command_queue.pop_front(); return cmd; }
        string pushCommandQueue( const string cmd, const bool front = false );

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
        #define getHost_() getHost().c_str()
        string setHost( const char* host ) { strcpy( m_host, host ); return m_host; }

        uint_t getPort() const { return m_port; }
        uint_t setPort( const uint_t port ) { return m_port = port; }

        CHAR_DATA* getThing() const { return original ? original : character; } //FIXME: move to Thing*
        CHAR_DATA* setThing( CHAR_DATA* thing ) { return character = thing; } //FIXME: move to Thing*

        time_t getTimeout() const { return m_timeout; }
        time_t setTimeout( const time_t timeout ) { return m_timeout = timeout; }

        uint_t getType() const { return m_type; };
        uint_t setType( const uint_t type );

        World* getWorld() const { return m_world; }
        World* setWorld( World* world ) { return m_world = world; }

    private:
        const void ProcessColors();
        const bool _Send();

        list<string> m_command_history; // Prev command history
        list<string> m_command_queue;   // Command queue for processing
        uint_t m_command_repeat;   // # of command repititions
        bool   m_command_run;      // Found a command run, force output to socket
        sint_t m_connection_state; // Connection state
        bitset<MAX_CREATION_CHECK> m_creation_check; // Ensure creation process completed
        uint_t m_descriptor;       // File descriptor channel
        char*  m_host;             // Remote hostname
        string m_output;           // Output buffer
        uint_t m_port;             // Remote port
        time_t m_timeout;          // Idle timeout
        uint_t m_type;             // Brain type: dumb NPC, player, smart NPC, etc
        World* m_world;            // Game world
};
