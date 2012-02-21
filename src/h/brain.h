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
        uint_t descriptor;
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


        string GetHost() const { return m_host; }
        char* GetHost_() const { return m_host; }
        string setHost( const char* host ) { strcpy( m_host, host ); return m_host; }
        World* setWorld( World* world ) { return m_world = world; }

    private:
        char*  m_host;
        World* m_world;
};
