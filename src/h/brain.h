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
        short connected;
        bool fcommand;
        char inbuf[4 * MAX_INPUT_LENGTH];
        char incomm[MAX_INPUT_LENGTH];
        char inlast[MAX_INPUT_LENGTH];
        short repeat;
        char *showstr_head;
        char *showstr_point;
        char *outbuf;
        int outsize;
        int outtop;
        uint_t remote_port;
        int check;
        int flags;
        int childpid;
        time_t timeout;


        uint_t getDescriptor() const { return m_descriptor; }
        string getHost() const { return m_host; }
        char* getHost_() const { return m_host; }
        uint_t setDescriptor( const uint_t descriptor ) { return  m_descriptor = descriptor; }
        string setHost( const char* host ) { strcpy( m_host, host ); return m_host; }
        World* setWorld( World* world ) { return m_world = world; }

    private:
        uint_t m_descriptor;
        char*  m_host;
        World* m_world;
};
