/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#include "h/globals.h"

#ifndef ACT_WIZ_H
#include "h/act_wiz.h"
#endif

#ifndef DEC_DB_H
#include "h/db.h"
#endif

#ifndef DEC_COMM_H
#include "h/comm.h"
#endif

#ifndef DEC_HELP_H
#include "h/help.h"
#endif

#ifndef DEC_INTERP_H
#include "h/interp.h"
#endif

#ifndef DEC_MUDINFO_H
#include "h/mudinfo.h"
#endif

#define KEY( literal, field, value )  if ( !str_cmp( word, literal ) ) { field  = value; fMatch = TRUE;  break;}
#define SKEY( literal, field, value )  if ( !str_cmp( word, literal ) ) { if (field!=NULL) free_string(field);field  = value; fMatch = TRUE;  break;}


void load_mudinfo( void )
{
    FILE *fp;
    const char *word;
    bool fMatch;

    Utils::Logger( 0, "Loading " MUDINFO_FILE );

    if ( (fp = file_open(MUDINFO_FILE, "r")) == NULL )
    {
        file_close(fp);
        Utils::Logger( 0, "Failed to load mudinfo data." );
        return;
    }

    for ( ; ; )
    {
        word = feof(fp) ? "End" : fread_word(fp);
        fMatch = FALSE;

        switch ( UPPER(word[0]) )
        {
            case 'E':
                if ( !str_cmp(word, "End") )
                {
                    file_close(fp);
                    Utils::Logger( 0, "Done." );
                    return;
                }
                break;
            case 'F':
                KEY("First_Boot",   server.first_boot,   fread_number(fp));
                break;
            case 'M':
                KEY("Max_Players",  server.max_players,  fread_number(fp));
                KEY("MK_By_NPC",    server.mk_by_npc,    fread_number(fp));
                KEY("MK_By_PC",     server.mk_by_pc,     fread_number(fp));
                break;
            case 'P':
                KEY("PK_By_NPC",    server.pk_by_npc,    fread_number(fp));
                KEY("PK_By_PC",     server.pk_by_pc,     fread_number(fp));
                break;
            case 'T':
                KEY("Total_Pfiles", server.total_pfiles, fread_number(fp));
                break;
        }
        if ( !fMatch )
        {
            snprintf(log_buf, (2 * MIL), "Loading in mudinfo: no match for ( %s ).", word);
            monitor_chan(log_buf, MONITOR_BAD);
            fread_to_eol(fp);
        }
    }

    return;
}

void save_mudinfo( void )
{
    FILE *fp;

    if ( (fp = file_open(MUDINFO_FILE, "w")) == NULL )
    {
        file_close(fp);
        Utils::Logger( 0, "Failed to save mudinfo data." );
        return;
    }

    fprintf(fp, "First_Boot   %lu\n", server.first_boot);
    fprintf(fp, "Max_Players  %lu\n", server.max_players);
    fprintf(fp, "MK_By_NPC    %lu\n", server.mk_by_npc);
    fprintf(fp, "MK_By_PC     %lu\n", server.mk_by_pc);
    fprintf(fp, "PK_By_NPC    %lu\n", server.pk_by_npc);
    fprintf(fp, "PK_By_PC     %lu\n", server.pk_by_pc);
    fprintf(fp, "Total_Pfiles %lu\n", server.total_pfiles);
    fprintf(fp, "End\n\n");

    file_close(fp);

    return;
}


DO_FUN(do_mudinfo)
{
    string str;

    ch->send("      MUD info for " mudnamecolor ":\r\n");
    ch->send("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\r\n");

    str = ctime(&server.first_boot);
    str.erase(str.end() - 1, str.end());
    ch_printf(ch, "The MUD was first booted on: %s.\r\n", str.c_str());

    if ( server.cur_players == 0 )
        ch->send("No players are currently online!\r\n");
    else if ( server.cur_players == 1 )
        ch->send("You are all alone in this world. How lonely :(.\r\n");
    else
        ch_printf(ch, "%lu players are currently online.\r\n", server.cur_players);

    if ( server.max_players == 0 )
        ch->send("No players have ever logged in!\r\n");
    else if ( server.max_players == 1 )
        ch->send("You are the only person to ever log in. How lonely :(.\r\n");
    else
        ch_printf(ch, "The MUD has had %lu players logged in at once.\r\n", server.max_players);

    if ( server.max_players_reboot == 0 )
        ch->send("No players have ever logged in this reboot!\r\n");
    else if ( server.max_players_reboot == 1 )
        ch->send("You are the only person to ever log in this reboot. How lonely :(.\r\n");
    else
        ch_printf(ch, "The MUD has had %lu players logged in this reboot.\r\n", server.max_players_reboot);

    if ( server.mk_by_npc == 0 )
        ch->send("No mobs have died to other mobs yet!\r\n");
    else if ( server.mk_by_npc == 1 )
        ch->send("1 mob has died to another mob. How sad :(.\r\n");
    else
        ch_printf(ch, "%lu mobs have died to other mobs.\r\n", server.mk_by_npc);

    if ( server.mk_by_pc == 0 )
        ch->send("No mobs have died to players yet!\r\n");
    else if ( server.mk_by_pc == 1 )
        ch->send("1 mob has died to a player. How sad :(.\r\n");
    else
        ch_printf(ch, "%lu mobs have died to players.\r\n", server.mk_by_pc);

    if ( server.pk_by_npc == 0 )
        ch->send("No players have died to mobs yet!\r\n");
    else if ( server.pk_by_npc == 1 )
        ch->send("1 player has died to a mob. How sad :(.\r\n");
    else
        ch_printf(ch, "%lu players have died to mobs.\r\n", server.pk_by_npc);

    if ( server.pk_by_pc == 0 )
        ch->send("No players have died to other players yet!\r\n");
    else if ( server.pk_by_pc == 1 )
        ch->send("1 player has died to another player. How sad :(.\r\n");
    else
        ch_printf(ch, "%lu players have died to other players.\r\n", server.pk_by_pc);

    if ( server.total_pfiles == 1 )
        ch->send("There is only a single pfile. How lonely :(.\r\n");
    else
        ch_printf(ch, "There are currently @@W%lu @@Npfiles.\r\n", server.total_pfiles);

    return;
}

void init_mudinfo( void )
{
    server.cur_players = uintmin_t;
    server.descriptor = uintmin_t;
    server.first_boot = uintmin_t;
    server.max_descriptor = uintmin_t;
    server.max_players = uintmin_t;
    server.max_players_reboot = uintmin_t;
    server.mk_by_npc = uintmin_t;
    server.mk_by_pc = uintmin_t;
    server.port = 1234;
    server.pk_by_npc = uintmin_t;
    server.pk_by_pc = uintmin_t;
    server.shutdown = false;
    server.total_commands = count_commands();
    server.total_helpfiles = count_helps();
    server.total_pfiles = uintmin_t;

    return;
}
