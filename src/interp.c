/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  Ack 2.2 improvements copyright (C) 1994 by Stephen Dooley              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *       _/          _/_/_/     _/    _/     _/    ACK! MUD is modified    *
 *      _/_/        _/          _/  _/       _/    Merc2.0/2.1/2.2 code    *
 *     _/  _/      _/           _/_/         _/    (c)Stephen Zepp 1998    *
 *    _/_/_/_/      _/          _/  _/             Version #: 4.3          *
 *   _/      _/      _/_/_/     _/    _/     _/                            *
 *                                                                         *
 *                        http://ackmud.nuc.net/                           *
 *                        zenithar@ackmud.nuc.net                          *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/
/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#include "h/globals.h"

#ifndef DEC_ACT_CLAN_H
#include "h/act_clan.h"
#endif

#ifndef DEC_ACT_COMM_H
#include "h/act_comm.h"
#endif

#ifndef DEC_ACT_INFO_H
#include "h/act_info.h"
#endif

#ifndef DEC_ACT_MOVE_H
#include "h/act_move.h"
#endif

#ifndef DEC_ACT_OBJ_H
#include "h/act_obj.h"
#endif

#ifndef DEC_ACT_WIZ_H
#include "h/act_wiz.h"
#endif

#ifndef DEC_BOARD_H
#include "h/board.h"
#endif

#ifndef DEC_BUILD_H
#include "h/build.h"
#endif

#ifndef DEC_BUILDARE_H
#include "h/buildare.h"
#endif

#ifndef DEC_CLUTCH_H
#include "h/clutch.h"
#endif

#ifndef DEC_COMM_H
#include "h/comm.h"
#endif

#ifndef DEC_DB_H
#include "h/db.h"
#endif

#ifndef DEC_EMAIL_H
#include "h/email.h"
#endif

#ifndef DEC_ENCHANT_H
#include "h/enchant.h"
#endif

#ifndef DEC_FIGHT_H
#include "h/fight.h"
#endif

#ifndef DEC_HANDLER_H
#include "h/handler.h"
#endif

#ifndef DEC_HELP_H
#include "h/help.h"
#endif

#ifndef DEC_HUNT_H
#include "h/hunt.h"
#endif

#ifndef DEC_INTERP_H
#include "h/interp.h"
#endif

#ifndef DEC_MAGIC_H
#include "h/magic.h"
#endif

#ifndef DEC_MAPPER_H
#include "h/mapper.h"
#endif

#ifndef DEC_MONEY_H
#include "h/money.h"
#endif

#ifndef DEC_MOUNT_H
#include "h/mount.h"
#endif

#ifndef DEC_MUDINFO_H
#include "h/mudinfo.h"
#endif

#ifndef DEC_PDELETE_H
#include "h/pdelete.h"
#endif

#ifndef DEC_QUEST_H
#include "h/quest.h"
#endif

#ifndef DEC_RULERS_H
#include "h/rulers.h"
#endif

#ifndef DEC_SOCIAL_H
#include "h/social.h"
#endif

#ifndef DEC_SCHECK_H
#include "h/scheck.h"
#endif

#ifndef DEC_SPENDQP_H
#include "h/spendqp.h"
#endif

#ifndef DEC_SYSDATA_H
#include "h/sysdata.h"
#endif

#ifndef DEC_VAMPIRE_H
#include "h/vampire.h"
#endif

#ifndef DEC_WEREWOLF_H
#include "h/werewolf.h"
#endif

#ifndef DEC_WIZUTIL_H
#include "h/wizutil.h"
#endif

#ifndef DEC_WRITE_H
#include "h/write.h"
#endif

/*
 * Command logging types.
 */
#define LOG_NORMAL      0
#define LOG_ALWAYS      1
#define LOG_NEVER       2

/*
 * Log-all switch.
 */
bool fLogAll = FALSE;



/*
 * Command table.
 */
const struct cmd_type cmd_table[] =
{
    /*
     * Common movement commands.
     */



    /*
     * command table modified by Aeria
     */
    {"north", do_north, POS_STANDING, 0, LOG_NORMAL,
        C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"east", do_east, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"south", do_south, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"west", do_west, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"up", do_up, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"down", do_down, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"map", do_mapper, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},

    /*
     * Common other commands.
     * Placed here so one and two letter abbreviations work.
     */
    {"buy", do_buy, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"cast", do_cast, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"exits", do_exits, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"get", do_get, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"gain", do_gain, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"inventory", do_inventory, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, true, false},
    {"kill", do_kill, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"look", do_look, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"order", do_order, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"rest", do_rest, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"sleep", do_sleep, POS_SLEEPING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"stand", do_stand, POS_SLEEPING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"tell", do_tell, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"whisper", do_whisper, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"wield", do_wear, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"wizhelp", do_wizhelp, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"loot", do_loot, POS_STANDING, 20, LOG_ALWAYS,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"remove", do_remove, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},

    /*
     * Informational commands.
     */
    {"abandon", do_abandon, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"affected", do_affected, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"areas", do_areas, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"appraise", do_appraise, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, false, false},
    {"bug", do_bug, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_MISC, C_SHOW_ALWAYS, true, false},
    {"clist", do_clan_list, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"commands", do_commands, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"compare", do_compare, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"consider", do_consider, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"credits", do_credits, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"cwhere", do_cwhere, POS_DEAD, CLAN_ONLY, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"delete", do_delete, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"diagnose", do_diagnose, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"equipment", do_equipment, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"examine", do_examine, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"help", do_help, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"shelp", do_shelp, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"heal", do_heal, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"idea", do_idea, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_MISC, C_SHOW_ALWAYS, true, false},
    {"note", do_note, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_MISC, C_SHOW_ALWAYS, false, false},
    {"report", do_report, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"pagelength", do_pagelen, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"read", do_read, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"rlist", do_race_list, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"score", do_score, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"slist", do_slist, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"socials", do_socials, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"status", do_status, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"time", do_time, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"typo", do_typo, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_MISC, C_SHOW_ALWAYS, true, false},
    {"weather", do_weather, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"who", do_who, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"whois", do_whois, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"wizlist", do_wizlist, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"write", do_write, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"edit", do_edit, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},

    /*
     * Configuration commands.
     */
    {"accept", do_accept, POS_DEAD, CLAN_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"alias", do_alias, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"autobrief", do_autobrief, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"autodig", do_autodig, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"autoexit", do_autoexit, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"autoloot", do_autoloot, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"autosac", do_autosac, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"banish", do_banish, POS_DEAD, CLAN_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"blank", do_blank, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"brief", do_brief, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"channels", do_channels, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"color", do_color, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"colist", do_colist, POS_DEAD, 0, LOG_NORMAL, C_TYPE_CONFIG,
     C_SHOW_ALWAYS, true, false},
    {"combine", do_combine, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"config", do_config, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"description", do_description, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, false, false},
    {"ignore", do_ignore, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"password", do_password, POS_DEAD, 0, LOG_NEVER,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"prompt", do_prompt, POS_DEAD, 0, LOG_ALWAYS,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"title", do_title, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"wimpy", do_wimpy, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"worth", do_worth, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"stance", do_stance, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},

    /*
     * Communication commands.
     */
    {"answer", do_answer, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"ask", do_ask, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"beep", do_beep, POS_RESTING, 0, LOG_NORMAL, C_TYPE_COMM,
     C_SHOW_ALWAYS, true, false},
    {"clan", do_clan, POS_RESTING, CLAN_ONLY, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"creator", do_creator, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {")", do_creator, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    { ".",              do_gossip,      POS_RESTING,     0,  LOG_NORMAL,
      C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    { "gossip", do_gossip, POS_RESTING, 0, LOG_NORMAL,
      C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"pemote", do_pemote, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"emote", do_emote, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {",", do_emote, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"flame", do_flame, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"finger", do_finger, POS_DEAD, 86, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"gtell", do_gtell, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {";", do_gtell, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"music", do_music, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"newbie", do_newbie, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"pose", do_pose, POS_RESTING, 86, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, false, false},
    {"pray", do_pray, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"quest", do_quest, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"question", do_question, POS_SLEEPING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"race", do_race, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"reply", do_reply, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"say", do_say, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"'", do_say, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"shout", do_shout, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"tongue", do_tongue, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"yell", do_yell, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"zzz", do_zzz, POS_SLEEPING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"game", do_game, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"vamp", do_familytalk, POS_RESTING, VAMP_ONLY, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"remort", do_remorttalk, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"{", do_remorttalk, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"diplomat", do_diptalk, POS_RESTING, CLAN_ONLY, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"crusade", do_crusade, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"adept", do_adepttalk, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"ooc", do_ooc, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},

    /*
     * Combat commands.
     */
    {"assist", do_assist, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"backstab", do_backstab, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"bs", do_backstab, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"dirt", do_dirt, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"trip", do_trip, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"smash", do_smash, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"bash", do_bash, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"berserk", do_berserk, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"circle", do_circle, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"disarm", do_disarm, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"feed", do_feed, POS_FIGHTING, VAMP_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"flee", do_flee, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"headbutt", do_headbutt, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"kick", do_kick, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"knee", do_knee, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"murde", do_murde, POS_FIGHTING, 5, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_NEVER, false, false},
    {"murder", do_murder, POS_FIGHTING, 5, LOG_ALWAYS,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"punch", do_punch, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"rescue", do_rescue, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"stake", do_stake, POS_STANDING, 5, LOG_ALWAYS,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"stun", do_stun, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"frenzy", do_frenzy, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"charge", do_charge, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"target", do_target, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},

    /*
     * Object manipulation commands.
     */
    {"adapt", do_adapt, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"auction", do_auction, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"bank", do_bank, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"bid", do_bid, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"brandish", do_brandish, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"cdonate", do_cdonate, POS_RESTING, CLAN_ONLY, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"close", do_close, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"clutch", do_clutch, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"donate", do_donate, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"drink", do_drink, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"drop", do_drop, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"eat", do_eat, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"enter", do_enter, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"fill", do_fill, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"give", do_give, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"hold", do_wear, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"list", do_list, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"lock", do_lock, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"open", do_open, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"make", do_make, POS_DEAD, CLAN_ONLY, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"pick", do_pick, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"put", do_put, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"quaff", do_quaff, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"recite", do_recite, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"sell", do_sell, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"take", do_get, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"sacrifice", do_sacrifice, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"unlock", do_unlock, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"value", do_value, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"wear", do_wear, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"zap", do_zap, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"enchant", do_enchant, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"assemble", do_connect, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_OBJECT, C_SHOW_ALWAYS, false, false},
    {"afk", do_afk, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_MISC, C_SHOW_ALWAYS, true, false},
    {"assassinate", do_assassinate, POS_STANDING, 20, LOG_ALWAYS,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"finger", do_finger, POS_DEAD, 86, LOG_ALWAYS,
     C_TYPE_MISC, C_SHOW_ALWAYS, true, false},
    {"follow", do_follow, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"gold", do_gold, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"group", do_group, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"hide", do_hide, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"hunt", do_hunt, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"dismount", do_dismount, POS_STANDING, 1, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"mount", do_mount, POS_STANDING, 1, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"leav", do_leav, POS_RESTING, CLAN_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_NEVER, false, false},
    {"leave", do_leave, POS_RESTING, CLAN_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"practice", do_practice, POS_SLEEPING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"qui", do_qui, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_MISC, C_SHOW_NEVER, true, false},
    {"quit", do_quit, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_MISC, C_SHOW_ALWAYS, true, false},
    {"recall", do_recall, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"/", do_recall, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"home", do_clan_recall, POS_STANDING, CLAN_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"save", do_save, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_MISC, C_SHOW_ALWAYS, true, false},
    {"scan", do_scan, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"shadowform", do_shadowform, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"sleep", do_sleep, POS_SLEEPING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"sneak", do_sneak, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"spells", do_spells, POS_SLEEPING, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"split", do_split, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"steal", do_steal, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"train", do_train, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"visible", do_visible, POS_SLEEPING, 0, LOG_NORMAL,
     C_TYPE_MISC, C_SHOW_ALWAYS, true, false},
    {"wake", do_wake, POS_SLEEPING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, true, false},
    {"warcry", do_warcry, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"where", do_where, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"disguise", do_disguise, POS_STANDING, 0, LOG_ALWAYS,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"politics", do_politics, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"rulers", do_rulers, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},

    /*
     * AckFUSS additions -Kline
     */
    {"stop", do_stop, POS_FIGHTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"statraise", do_statraise, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"census", do_census, POS_STANDING, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"mquest", do_mquest, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"qstat", do_qstat, POS_STANDING, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"safe", do_safe, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"repair", do_repair, POS_STANDING, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, false, false},
    {"disable", do_disable, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, false, false},
    {"mudinfo", do_mudinfo, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"whitelist", do_whitelist, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, false, false},
    {"logins", do_logins, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, false, false},
    {"setemail", do_set_email, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"everify", do_verify_email, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"email", do_email, POS_RESTING, 20, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"togemail", do_tog_email, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_CONFIG, C_SHOW_ALWAYS, true, false},
    {"history", do_cmd_history, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},

    /*
     *    Vampire and REMORT SKILLS Zen
     */
    {"family", do_family, POS_RESTING, VAMP_ONLY, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"disguise", do_disguise, POS_STANDING, 0, LOG_ALWAYS,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"instruct", do_instruct, POS_STANDING, VAMP_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"scout", do_scout, POS_STANDING, 1, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, true, false},

    /*
     * NEW CLAN COMMANDS Zen
     */
    {"ctoggle", do_ctoggle, POS_RESTING, BOSS_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"negotiate", do_negotiate, POS_RESTING, CLAN_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_ALWAYS, false, false},
    {"council", do_council, POS_RESTING, 0, LOG_NORMAL,
     C_TYPE_MISC, C_SHOW_NEVER, false, false},
    {"qpspend", do_qpspend, POS_STANDING, 1, LOG_NORMAL,
     C_TYPE_MISC, C_SHOW_ALWAYS, false, false},

    /*
     * Immortal commands.
     */
    {"alist", build_arealist, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"alink", do_alink, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"build", do_build, POS_STANDING, L_HER, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"mpcr", do_mpcr, POS_STANDING, L_DEI, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"halls", do_halls, POS_RESTING, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"lhunt", do_lhunt, POS_DEAD, L_SUP, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"sstat", do_sstat, POS_DEAD, L_SUP, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"cset", do_cset, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"whoname", do_whoname, POS_DEAD, L_ANG, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"sysdata", do_sysdata, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"setclass", do_setclass, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"doggy", do_dog, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"togbuild", do_togbuild, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"togleader", do_togleader, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"isnoop", do_isnoop, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"trust", do_trust, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"deathmatc", do_deathmatc, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_NEVER, true, false},
    {"deathmatch", do_deathmatch, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"resetpasswd", do_resetpassword, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"iscore", do_iscore, POS_DEAD, L_DEI, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"iwhere", do_iwhere, POS_DEAD, L_DEI, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"fights", do_fights, POS_DEAD, L_DEI, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"allow", do_allow, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"iban", do_ban, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"deny", do_deny, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"freeze", do_freeze, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"reboo", do_reboo, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_NEVER, true, false},
    {"reboot", do_reboot, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"hotreboo", do_hotreboo, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_NEVER, true, false},
    {"hotreboot", do_hotreboot, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"shutdow", do_shutdow, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_NEVER, true, false},
    {"shutdown", do_shutdown, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"users", do_users, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"wizify", do_wizify, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"wizlock", do_wizlock, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"for", do_for, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"force", do_force, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"log", do_log, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"mload", do_mload, POS_DEAD, L_HER, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"monitor", do_monitor, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"areasave", do_areasave, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"mset", do_mset, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"mgive", do_mgive, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"noemote", do_noemote, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"nopray", do_nopray, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"notell", do_notell, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"oload", do_oload, POS_DEAD, L_HER, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"oset", do_oset, POS_DEAD, L_ANG, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"owhere", do_owhere, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"pardon", do_pardon, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"peace", do_peace, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"pload", do_pload, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"punload", do_punload, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"purge", do_purge, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"iquest", do_iquest, POS_DEAD, L_DEI, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"restore", do_restore, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"rset", do_rset, POS_DEAD, 86, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"silence", do_silence, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"sla", do_sla, POS_DEAD, 86, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"slay", do_slay, POS_DEAD, L_HER, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"snoop", do_snoop, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"sset", do_sset, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"transfer", do_transfer, POS_DEAD, L_HER, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"transdm", do_transdm, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"at", do_at, POS_DEAD, L_DEI, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"bamfin", do_bamfin, POS_DEAD, L_ANG, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"bamfout", do_bamfout, POS_DEAD, L_ANG, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"echo", do_echo, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"goto", do_goto, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"holylight", do_holylight, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"invis", do_invis, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"memory", do_memory, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"mfind", do_mfind, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"mfindlev", do_mfindlev, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"mstat", do_mstat, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"mwhere", do_mwhere, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"ofind", do_ofind, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"ostat", do_ostat, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"recho", do_recho, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"return", do_return, POS_DEAD, L_DEI, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"rstat", do_rstat, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"slookup", do_slookup, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"switch", do_switch, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"immtalk", do_immtalk, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {":", do_immtalk, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"reward", do_reward, POS_DEAD, L_DEI, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"setcouncil", do_togcouncil, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"resetgain", do_gain_stat_reset, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"exlist", do_exlist, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"vlist", do_vlist, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"olmsg", do_olmsg, POS_DEAD, L_HER, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"ofindlev", do_ofindlev, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"prename", do_rename, POS_DEAD, L_GOD, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"pdelete", do_sdelete, POS_DEAD, 2, LOG_ALWAYS,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"scheck", do_scheck, POS_DEAD, L_GOD, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"immbrand", do_immbrand, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"otype", do_otype, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"owear", do_owear, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},
    {"findreset", do_findreset, POS_DEAD, L_HER, LOG_NORMAL,
     C_TYPE_IMM, C_SHOW_ALWAYS, true, false},

    /*
     * Werewolf commands
     */
    {"howl", do_howl, POS_DEAD, WOLF_ONLY, LOG_NORMAL,
     C_TYPE_COMM, C_SHOW_ALWAYS, true, false},
    {"tribe", do_tribe, POS_DEAD, WOLF_ONLY, LOG_NORMAL,
     C_TYPE_INFO, C_SHOW_ALWAYS, true, false},
    {"rage", do_rage, POS_FIGHTING, WOLF_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"imprint", do_imprint, POS_STANDING, WOLF_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},
    {"scent", do_scent, POS_STANDING, WOLF_ONLY, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_SKILL, false, false},

    /*
     * End of list.
     */
    {"", 0, POS_DEAD, 0, LOG_NORMAL,
     C_TYPE_ACTION, C_SHOW_NEVER, false, false}
};

/* Log all commands.. rewrite every 5 mins.. */
void comlog( CHAR_DATA * ch, bool cleanup, int cmd, char *args )
{
    static FILE *fplog;
    static time_t ltime;

    if ( !fplog || ltime + ( 5 * 60 ) <= current_time )
    {
        if ( fplog )
            file_close( fplog );
        if ( !( fplog = file_open( "../log/comlog.txt", "w" ) ) )
            return;
        ltime = current_time;
    }

    if ( cleanup )
    {
        if ( fplog )
            file_close( fplog );
        return;
    }

    fprintf( fplog, "%.24s :: %12.12s (%5d): %s %s\n", ctime( &current_time ),
             ch->getName_(), ( IS_NPC( ch ) ? ch->npcdata->pIndexData->vnum : -1 ), cmd_table[cmd].name,
             ( cmd_table[cmd].log == LOG_NEVER ? "XXX" : args ) );
    fflush( fplog );
}



/*
 * The main entry point for executing commands.
 * Can be recursively called from 'at', 'order', 'force'.
 */
void interpret( CHAR_DATA * ch, const string input )
{
    /*
     * BUG with aliases: they can call themselves, which is
     * * a Bad Thing.  When an alias calls interp, we'll add
     * * a '~' char as the first char.  Checking for this will
     * * tell us if we need to check aliases again. -S-
     */

    bool alias_call;
    char command[MAX_INPUT_LENGTH];
    char logline[MAX_INPUT_LENGTH];
    uint_t cmd;
    alias_call = FALSE;
    char *argument;

    argument = const_cast<char*>( input.c_str() );

    if ( ch->position == POS_WRITING )
        /*
         * if player is writing, pass argument straight to write_interpret
         */
    {
        write_interpret( ch, argument );
        return;
    }

    if ( ch->position == POS_BUILDING )
    {
        if ( argument[0] == ':' )
            argument++;
        else
        {
            build_interpret( ch, argument );
            return;
        }
    }


    /*
     * Strip leading spaces.
     */
    while ( isspace( *argument ) )
        argument++;
    if ( argument[0] == '\0' )
        return;


    if ( argument[0] == '~' )
    {
        argument++;
        alias_call = TRUE;
    }

    /*
     * No hiding.
     */
    REMOVE_BIT( ch->affected_by, AFF_HIDE );


    /*
     * Implement freeze command.
     */
    if ( !IS_NPC( ch ) && ch->act.test(ACT_FREEZE) )
    {
        send_to_char( "@@a@@fYou're totally frozen!@@N\r\n", ch );
        return;
    }

    if ( ch->stun_timer > 0 )
    {
        send_to_char( "You are too@@aSTUNNED@@N to act!\r\n", ch );
        return;
    }

    /*
     * Grab the command word.
     * Special parsing so ' can be a command,
     *   also no spaces needed after punctuation.
     */
    strcpy( logline, argument );
    if ( !isalpha( argument[0] ) && !isdigit( argument[0] ) )
    {
        command[0] = argument[0];
        command[1] = '\0';
        argument++;
        while ( isspace( *argument ) )
            argument++;
    }
    else
    {
        argument = one_argument( argument, command );
    }

    /*
     * Look for command in command table.
     */
    cmd = ch->canInterpret( command );

    /*
     * Log and snoop.
     */
    if ( cmd_table[cmd].log == LOG_NEVER )
        strcpy( logline, "XXXXXXXX XXXXXXXX XXXXXXXX@@N" );

    if ( ( !IS_NPC( ch ) && ch->act.test(ACT_LOG) ) || fLogAll || cmd_table[cmd].log == LOG_ALWAYS )
    {
        snprintf( log_buf, (2 * MIL), "Log %s: %s", ch->getName_(), logline );
        Utils::Logger( 0, "%s", log_buf );
        if ( ch->act.test(ACT_LOG) )
            monitor_chan( log_buf, MONITOR_BAD );
        else if ( cmd_table[cmd].level > LEVEL_HERO )
            monitor_chan( log_buf, MONITOR_GEN_IMM );
        else
            monitor_chan( log_buf, MONITOR_GEN_MORT );

    }

    if ( ch->desc != NULL && ch->desc->snoop_by != NULL ) /* -S- Mod */
    {
        char snp[MAX_STRING_LENGTH];
        snprintf( snp, MSL, "[Snoop:%s] %s\r\n", ch->getName_(), logline );
        ch->desc->snoop_by->Send( snp );
    }

    if ( cmd_table[cmd].log != LOG_NEVER )
        ch->desc->pushCommandHistory( logline );

    if ( cmd == server.total_commands && !IS_NPC( ch ) && ( !alias_call ) )
    {
        int cnt;
        char foo[MAX_STRING_LENGTH];
        /*
         * Check aliases -S-
         */

        for ( cnt = 0; cnt < MAX_ALIASES; cnt++ )
        {
            if ( !str_cmp( ch->pcdata->alias_name[cnt], command ) && str_cmp( ch->pcdata->alias_name[cnt], "<none>@@N" ) )
            {
                snprintf( foo, MSL, "~%s %s", ch->pcdata->alias[cnt], argument );
                interpret( ch, foo );
                return;
            }
        }
    }


    if ( cmd == server.total_commands )
    {
        /*
         * Look for command in socials table.
         */
        if ( !check_social( ch, command, argument )
                && !imc_command_hook( ch, command, argument )
#ifdef I3
                && !I3_command_hook( ch, command, argument )
#endif
           )
            send_to_char( "Huh?\r\n", ch );
        return;
    }

    if ( check_disabled(&cmd_table[cmd]) )
    {
        send_to_char("This command has been temporarily disabled.\r\n", ch);
        return;
    }
    /*
     * Character not in position for command?
     */
    if ( IS_GHOST(ch) && cmd_table[cmd].ghost_cmd == false )
    {
        send_to_char("Not while you're @@R@@fdead@@N!\r\n", ch);
        return;
    }

    if ( ch->position < cmd_table[cmd].position )
    {
        switch ( ch->position )
        {
            case POS_DEAD:
                send_to_char( "Lie still; you are @@dDEAD@@N.\r\n", ch );
                break;

            case POS_MORTAL:
            case POS_INCAP:
                send_to_char( "You are @@Rhurt@@N far too bad for that.\r\n", ch );
                break;

            case POS_STUNNED:
                send_to_char( "You are too @@estunned@@N to do that.\r\n", ch );
                break;

            case POS_SLEEPING:
                send_to_char( "Oh, go back to @@Wsleep!@@N\r\n", ch );
                break;

            case POS_RESTING:
                send_to_char( "Naaaaaah... You feel too @@brelaxed@@N...\r\n", ch );
                break;

            case POS_FIGHTING:
                send_to_char( "Not until you @@Rstop@@N fighting!\r\n", ch );
                break;

        }
        return;
    }

    /*
     * Dispatch the command.
     */
    if ( !IS_NPC( ch )
            && ( ( ch->stance == STANCE_AMBUSH )
                 || ( ch->stance == STANCE_AC_BEST ) )
            && ( ( str_prefix( command, "kill" ) )
                 && ( str_prefix( command, "murder" ) )
                 && ( str_prefix( command, "backstab" ) )
                 && ( str_prefix( command, "bs" ) )
                 && ( str_prefix( command, "whisper" ) )
                 && ( str_prefix( command, "stake" ) ) && ( str_prefix( command, "steal" ) ) ) )


    {
        send_to_char( "You step out of the shadows.\r\n", ch );
        ch->stance = STANCE_WARRIOR;
        ch->setModAC( 0 );
        ch->setModDR( 0 );
        ch->setModHR( 0 );
        act( "$n steps out of the Shadows!", ch, NULL, NULL, TO_ROOM );
    }

    /* Check for movement */
    if ( !IS_NPC(ch) )
    {
        if ( !str_cmp(cmd_table[cmd].name, "north") || !str_cmp(cmd_table[cmd].name, "east") || !str_cmp(cmd_table[cmd].name, "south") || !str_cmp(cmd_table[cmd].name, "west") || !str_cmp(cmd_table[cmd].name, "up") || !str_cmp(cmd_table[cmd].name, "down") )
            ch->pcdata->movement++;
        else
            ch->pcdata->movement = 0;
    }

    comlog( ch, false, cmd, argument );
    ( *cmd_table[cmd].do_fun ) ( ch, argument );

    return;
}



bool check_social( CHAR_DATA * ch, char *command, char *argument )
{
    char arg[MAX_INPUT_LENGTH];
    CHAR_DATA *victim;
    bool found;
    SOCIAL_DATA *soc;

    found = FALSE;
    if( exists_social(command) )
    {
        soc = load_social(command);
        found = TRUE;
    }

    if ( !found )
        return FALSE;

    if ( !IS_NPC( ch ) && ch->act.test(ACT_NO_EMOTE) )
    {
        send_to_char( "You are anti-social!\r\n", ch );
        return TRUE;
    }

    if ( IS_GHOST(ch) )
    {
        send_to_char("Your ghostly form can't seem to convey emotions...\r\n", ch);
        return true;
    }

    switch ( ch->position )
    {
        case POS_DEAD:
            send_to_char( "Lie still; you are @@dDEAD@@N.\r\n", ch );
            return TRUE;

        case POS_INCAP:
        case POS_MORTAL:
            send_to_char( "You are @@Rhurt@@N far too bad for that.\r\n", ch );
            return TRUE;

        case POS_STUNNED:
            send_to_char( "You are too @@estunned@@N to do that.\r\n", ch );
            return TRUE;

        case POS_SLEEPING:
            /*
             * I just know this is the path to a 12" 'if' statement.  :(
             * But two players asked for it already!  -- Furey
             */
            if ( !str_cmp( soc->name, "snore" ) )
                break;
            send_to_char( "In your @@Wdreams@@N, or what?\r\n", ch );
            return TRUE;

    }

    one_argument( argument, arg );
    victim = NULL;
    if ( arg[0] == '\0' )
    {
        act( soc->other_no_arg.c_str(), ch, NULL, victim, TO_ROOM );
        act( soc->char_no_arg.c_str(), ch, NULL, victim, TO_CHAR );
    }
    else if ( ( victim = get_char_room( ch, arg ) ) == NULL )
    {
        send_to_char( "They aren't here.\r\n", ch );
    }
    else if ( victim == ch )
    {
        act( soc->other_auto.c_str(), ch, NULL, victim, TO_ROOM );
        act( soc->char_auto.c_str(), ch, NULL, victim, TO_CHAR );
    }
    else
    {
        act( soc->other_found.c_str(), ch, NULL, victim, TO_NOTVICT );
        act( soc->char_found.c_str(), ch, NULL, victim, TO_CHAR );
        act( soc->vict_found.c_str(), ch, NULL, victim, TO_VICT );

        if ( !IS_NPC( ch ) && IS_NPC( victim ) && !IS_AFFECTED( victim, AFF_CHARM ) && IS_AWAKE( victim ) )
        {
            switch ( number_bits( 4 ) )
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    act( soc->other_found.c_str(), victim, NULL, ch, TO_NOTVICT );
                    act( soc->char_found.c_str(), victim, NULL, ch, TO_CHAR );
                    act( soc->vict_found.c_str(), victim, NULL, ch, TO_VICT );
                    break;

                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                    act( "$n slaps $N.", victim, NULL, ch, TO_NOTVICT );
                    act( "You slap $N.", victim, NULL, ch, TO_CHAR );
                    act( "$n slaps you.", victim, NULL, ch, TO_VICT );
                    break;
            }
        }
    }

    return TRUE;
}

/*
 * Check if that command is disabled
 * Note that we check for equivalence of the do_fun pointers; this means
 * that disabling 'chat' will also disable the '.' command
 */
bool check_disabled( const struct cmd_type *command )
{
    DISABLED_DATA *p;
    list<DISABLED_DATA *>::iterator li;

    for ( li = disabled_list.begin(); li != disabled_list.end(); li++ )
    {
        p = *li;
        if ( p->command->do_fun == command->do_fun )
            return true;
    }

    return false;
}

uint_t count_commands()
{
    uint_t total = 0;

    for ( total = 0; cmd_table[total].name[0] != '\0'; total++ )
        ;

    return total;
}
