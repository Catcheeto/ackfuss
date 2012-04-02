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

#define DEC_LISTS_H

/*
 * All of the global linked lists, in one clump.  Declarations here,
 * actual variables in lists.c
 * -- Altrag
 */
extern list<AFFECT_DATA*> affect_list;
extern list<CHAR_DATA*> aggro_list;
extern list<AREA_DATA*> area_list;
extern list<BAN_DATA*> ban_list;
extern list<BOARD_DATA*> board_list;
extern list<BRAND_DATA*> brand_list;
extern list<Brain*> brain_list;
extern list<BUILD_DATA_LIST*> build_dat_list;
extern list<CHAR_DATA*> cast_list;
extern list<CHAR_DATA*> char_list;
extern list<OBJ_DATA*> corpse_list;
extern list<DISABLED_DATA*> disabled_list;
extern list<EXIT_DATA*> exit_list;
extern list<CHAR_DATA*> fight_list;
extern list<FILE*> file_list;
extern list<MOB_INDEX_DATA*> mob_index_list;
extern list<NOTE_DATA*> note_list;
extern list<NPC_GROUP_DATA*> npc_group_list;
extern list<OBJ_DATA*> obj_list;
extern list<OBJ_INDEX_DATA*> obj_index_list;
extern list<DESCRIPTOR_DATA*> pload_list;
extern list<RESET_DATA*> reset_list;
extern list<ROOM_INDEX_DATA*> room_index_list;
extern list<RULER_DATA*> ruler_list;
extern list<SHOP_DATA*> shop_list;
extern multimap<Brain*,Brain*> snoop_list;
extern list<SOCIAL_DATA*> social_list;
extern list<HELP_DATA*> help_list;
extern list<World*> world_list;

extern BUILD_DATA_LIST* first_build;
extern BUILD_DATA_LIST* last_build;
extern BUF_DATA_STRUCT* first_buf;
extern BUF_DATA_STRUCT* last_buf;
