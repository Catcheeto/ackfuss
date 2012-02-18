/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#include "h/globals.h"

#ifndef DEC_ACT_WIZ_H
#include "h/act_wiz.h"
#endif

#ifndef DEC_COMM_H
#include "h/comm.h"
#endif

#ifndef DEC_DB_H
#include "h/db.h"
#endif

#ifndef DEC_HANDLER_H
#include "h/handler.h"
#endif

#ifndef DEC_HASH_H
#include "h/hash.h"
#endif

#ifndef DEC_MONEY_H
#include "h/money.h"
#endif

#ifndef DEC_SSM_H
#include "h/ssm.h"
#endif

affect_data::~affect_data()
{
}

area_data::~area_data()
{
    free_string(can_read);
    free_string(can_write);
    free_string(filename);
    free_string(keyword);
    free_string(level_label);
    free_string(name);
    free_string(owner);
    free_string(reset_msg);
}

ban_data::~ban_data()
{
    free_string(name);
    free_string(banned_by);
}

brand_data::~brand_data()
{
}

buf_data_struct::~buf_data_struct()
{
    free_string(buf);
}

build_data_list::~build_data_list()
{
}

cast_data::~cast_data()
{
    free_string(arg);
}

char_data::~char_data()
{
    while ( first_carry != NULL )
        extract_obj(first_carry);

    while ( first_affect != NULL )
        affect_remove(this, first_affect);

    imc_freechardata(this);
#ifdef I3
    free_i3chardata(this);
#endif

    if ( npcdata )
        delete npcdata;
    if ( pcdata )
        delete pcdata;
    delete money;
    delete casting;

    aggro_list.remove(this);
}

council_data::~council_data()
{
}

descriptor_data::~descriptor_data()
{
}

disabled_data::~disabled_data()
{
}

email_data::~email_data()
{
}

exit_data::~exit_data()
{
    free_string(description);
    free_string(keyword);
}

hash_entry_tp::~hash_entry_tp()
{
}

help_data::~help_data()
{
}

lookup_data::~lookup_data()
{
    free_string(buf);
}

magic_shield::~magic_shield()
{
    free_string(absorb_message_room);
    free_string(absorb_message_victim);
    free_string(absorb_message_self);
    free_string(name);
    free_string(wearoff_room);
    free_string(wearoff_self);
}

mark_data::~mark_data()
{
    free_string(message);
    free_string(author);
}

mob_index_data::~mob_index_data()
{
    free_string(description);
    free_string(long_descr);
    free_string(short_descr);
}

money_type::~money_type()
{
}

note_data::~note_data()
{
    free_string(date);
    free_string(subject);
    free_string(text);
}

npc_data::~npc_data()
{
    free_string(short_descr);
}

npc_group_data::~npc_group_data()
{
}

obj_data::~obj_data()
{
    AFFECT_DATA *a, *a_next;

    for ( a = first_apply; a != NULL; a = a_next )
    {
        a_next = a->next;
        delete a;
    }

    free_string(short_descr);
    free_string(long_descr);
    delete money;
}

obj_index_data::~obj_index_data()
{
    free_string(name);
    free_string(short_descr);
    free_string(long_descr);
}

pc_data::~pc_data()
{
    for ( short i = 0; i < MAX_ALIASES; i++ )
    {
        free_string(alias[i]);
        free_string(alias_name[i]);
    }
    free_string(assist_msg);
    free_string(bamfin);
    free_string(bamfout);
    delete bank_money;
    if ( current_brand )
        delete current_brand;
    delete email;
    free_string(header);
    for ( short i = 0; i < MAX_HOSTS; i++ )
        free_string(host[i]);
    for ( short i = 0; i < MAX_IGNORES; i++ )
        free_string(ignore_list[i]);
    free_string(lastlogin);
    free_string(load_msg);
    free_string(message);
    free_string(pedit_state);
    for ( short i = 0; i < MAX_PEDIT; i++ )
        free_string(pedit_string[i]);
    if ( pnote )
        delete pnote;
    free_string(pwd);
    delete quest_info;
    delete records;
    free_string(room_enter);
    free_string(room_exit);
    delete super;
    free_string(title);
    for ( short i = 0; i < MAX_HOSTS; i++ )
        free_string(whitelist[i]);
    free_string(who_name);
}

quest_info::~quest_info()
{
}

record_data::~record_data()
{
}

reset_data::~reset_data()
{
    free_string(notes);
}

room_affect_data::~room_affect_data()
{
}

room_index_data::~room_index_data()
{
    ROOM_AFFECT_DATA *raf, *raf_next;

    for ( raf = this->first_room_affect; raf != NULL; raf = raf_next )
    {
        raf_next = raf->next;
        r_affect_remove(this, raf);
    }

    for_each( mark_list.begin(), mark_list.end(), DeleteObject() );
    free_string(name);
    free_string(description);
    delete treasure;
}

ruler_data::~ruler_data()
{
    free_string(name);
    free_string(affiliation_name);
    free_string(keywords);
}

shop_data::~shop_data()
{
}

social_data::~social_data()
{
}

super_data::~super_data()
{
}
