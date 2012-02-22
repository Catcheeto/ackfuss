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

#define DESC_FLAG_PASSTHROUGH 1

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
        int check;
        int flags;
        int childpid;


        const bool ProcessOutput( const bool prompt = true );
        const void Send( const string msg ) { m_output += msg; return; };

        sint_t getConnectionState( const sint_t state = MSL ) const { return state == MSL ? m_connection_state : m_connection_state == state; }
        uint_t setConnectionState( const uint_t state ) { return m_connection_state = state; }

        uint_t getDescriptor() const { return m_descriptor; }
        uint_t setDescriptor( const uint_t descriptor ) { return  m_descriptor = descriptor; }

        string getHost() const { return m_host; }
        char* getHost_() const { return m_host; }
        string setHost( const char* host ) { strcpy( m_host, host ); return m_host; }

        uint_t getPort() const { return m_port; }
        uint_t setPort( const uint_t port ) { return m_port = port; }

        uint_t getTimeout() const { return m_timeout; }
        uint_t setTimeout( const time_t timeout ) { return m_timeout = timeout; }

        World* setWorld( World* world ) { return m_world = world; }

    private:
        const void ProcessColors();
        const bool _Send();

        sint_t m_connection_state; // Connection state
        uint_t m_descriptor;       // File descriptor channel
        char*  m_host;             // Remote hostname
        string m_output;           // Output buffer
        uint_t m_port;             // Remote port
        time_t m_timeout;          // Idle timeout
        World* m_world;            // Game world
};
