/*
 * Original mquest code kindly donated by Abel@StormHunters. Thanks!
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "globals.h"
#include "mquest.h"

#ifndef DEC_MONEY_H
#include "money.h"
#endif

extern int top_mob_index;
extern int top_obj_index;

/* locals */
void      mquest_info              args( ( CHAR_DATA *ch ) );
void      mquest_complete_message  args( ( CHAR_DATA *ch ) );
void      mquest_calc_rewards      args( ( CHAR_DATA *ch ) );
void      mquest_clear             args( ( CHAR_DATA *ch ) );
void      generate_killing_quest   args( ( CHAR_DATA *ch ) );
CHAR_DATA *get_quest_kill          args( ( int min_lev, int max_lev, CHAR_DATA *ch ) );
void      generate_retrieval_quest args( ( CHAR_DATA *ch ) );
OBJ_DATA  *get_quest_item          args( ( int min_lev, int max_lev, CHAR_DATA *ch ) );

void do_mquest( CHAR_DATA *ch, char *argument )
{
 sh_int i;
 CHAR_DATA *mob;
 OBJ_DATA *obj;
 OBJ_DATA *obj_next;
 char buf[MSL];

 if( IS_NPC(ch) )
  return;
 if( get_psuedo_level(ch) < 20 )
 {
  send_to_char("You must be level 20 to request quests from the questmaster.\n\r",ch);
  return;
 }
 if( argument[0] == '\0' )
 {
  send_to_char("Mquest what? Syntax: mquest <giveup|request|info|handin|complete|hint>\n\r",ch);
  return;
 }
 if( !str_prefix(argument,"request") )
 {
  for( mob = ch->in_room->first_person; mob; mob = mob->next_in_room )
   if( IS_NPC(mob) && IS_SET(mob->pIndexData->act,ACT_QUESTMASTER) )
    break;
  if( mob == NULL )
  {
   send_to_char("You have to be at a questmaster!\n\r",ch);
   return;
  }
  if( ch->pcdata->quest_info->is_questing )
  {
   send_to_char("You are already on a quest! Give up on it first if you'd like a new one.\n\r",ch);
   return;
  }
  if( ch->pcdata->quest_info->wait_time > 0 )
  {
   xprintf(buf,"You must wait %d more minute%s before taking another quest.\n\r",ch->pcdata->quest_info->wait_time,ch->pcdata->quest_info->wait_time > 1 ? "s" : "");
   send_to_char(buf,ch);
   return;
  }
  if( ch->pcdata->quest_info->quest_type == QUEST_ASSAULT )
  {
   send_to_char("@@dYou must complete your @@eassault@@d quest before you can continue questing!\n\r",ch);
   return;
  }/*
  if( number_percent() < 6 )
  {
   send_to_char("@@dYour next assigned quest is an @@eassault@@d quest!\n\r",ch);
   send_to_char("@@dThese quests are mandatory if you wish to keep questing!\n\r",ch);
   ch->pcdata->quest_info->quest_type = QUEST_ASSAULT;
   generate_assault_quest(ch);
  }*/
  if( number_percent () < 51 )
  {
   send_to_char("Your next available quest is an @@eitem retrieval quest@@N!\n\r",ch);
   if( number_percent() < 70 )
    ch->pcdata->quest_info->quest_type = QUEST_MULTI_RETRIEVE;
   else
    ch->pcdata->quest_info->quest_type = QUEST_RETRIEVAL;
   generate_retrieval_quest(ch);
   ch->pcdata->quest_info->is_questing = TRUE;
  }
  else
  {
   send_to_char("Your next available quest is a @@ecreature killing@@N quest!\n\r",ch);
   if( number_percent() < 70 )
    ch->pcdata->quest_info->quest_type = QUEST_MULTI_KILL;
   else
    ch->pcdata->quest_info->quest_type = QUEST_KILLING;
   generate_killing_quest(ch);
   ch->pcdata->quest_info->is_questing = TRUE;
  }
  mquest_calc_rewards(ch);
  mquest_info(ch);
  do_save(ch,"auto");
  return;
 }
 else if( !str_prefix(argument,"giveup") )
 {
  int pqp = 0, pgold = 0, pexp = 0;

  if( !ch->pcdata->quest_info->is_questing )
  {
   send_to_char("You are not currently on a quest!\n\r",ch);
   return;
  }
  if( ch->pcdata->quest_info->quest_type == QUEST_ASSAULT )
  {
   send_to_char("Your current quest is an @@eassault@@N quest. It must be completed before you can continue questing.\n\r",ch);
   return;
  }

  pqp = UMAX(1,ch->pcdata->quest_info->quest_reward[0]/3);
  pgold = UMAX(1,ch->pcdata->quest_info->quest_reward[1]/4);
  pexp = UMAX(1,ch->pcdata->quest_info->quest_reward[2]/4);

  if( (ch->pcdata->quest_points - pqp) < 0 )
  {
   send_to_char("You do not have enough quest points to give up on this quest!\n\r",ch);
   return;
  }
  if( (money_value(ch->money) - pgold) < 0 )
  {
   send_to_char("You do not have enough gold to give up on this quest!\n\r",ch);
   return;
  }
  if( (ch->exp - pexp) < 0 )
  {
   send_to_char("You do not have enough experience to give up on this quest!\n\r",ch);
   return;
  }

  ch->pcdata->quest_points -= pqp;
  join_money(round_money(pgold * -1,TRUE),ch->money);
  ch->exp -= pexp;

  xprintf(buf,"Giving up on this quest has cost you %d qp, %s and %d exp.\n\r",pqp,cost_to_money(pgold),pexp);
  send_to_char(buf,ch);
  ch->pcdata->records->mquest_f++;
  ch->pcdata->quest_info->wait_time = number_range(10,15); /* higher wait time on giveup */
  xprintf(buf,"You must wait %d minutes before your next quest.\n\r",ch->pcdata->quest_info->wait_time);
  send_to_char(buf,ch);
  mquest_clear(ch);
  do_save(ch,"auto");
  return;
 }
 else if( !str_prefix(argument,"hint") )
 {
  sh_int hint;

  if( !ch->pcdata->quest_info->is_questing )
  {
   send_to_char("You are not currently on a quest!\n\r",ch);
   return;
  }
  if( !isdigit(hint = atoi(argument)) )
  {
   send_to_char("You must select a task number for which you want a hint.\n\r",ch);
   return;
  }
  if( hint < 1 || hint > 5 )
  {
   send_to_char("You must choose the number of a task that you currently have!\n\r",ch);
   return;
  }
  if( ch->pcdata->quest_info->amount[hint-1] == -1 )
  {
   send_to_char("You do not currently have a task with that number.\n\r",ch);
   return;
  }
  if( ch->pcdata->quest_info->amount[hint-1] == 0 )
  {
   send_to_char("You have already completed that task!\n\r",ch);
   return;
  }
  if( ch->pcdata->quest_info->quest_hint[hint-1] )
  {
   send_to_char("You've already got your hint for that task!\n\r",ch);
   return;
  }
  if( ch->pcdata->quest_info->quest_type == QUEST_MULTI_KILL || ch->pcdata->quest_info->quest_type == QUEST_KILLING )
  {
   MOB_INDEX_DATA *mob = get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[hint-1]);
   xprintf(buf,"%s can be found somewhere in %s.\n\r",mob->short_descr,mob->area->name);
   send_to_char(buf,ch);
  }
  else if( ch->pcdata->quest_info->quest_type == QUEST_MULTI_RETRIEVE || ch->pcdata->quest_info->quest_type == QUEST_RETRIEVAL )
  {
   OBJ_INDEX_DATA *ob = get_obj_index(ch->pcdata->quest_info->quest_item_vnum[hint-1]);
   xprintf(buf,"%s can be found somewhere in %s.\n\r",ob->short_descr,ob->area->name);
   send_to_char(buf,ch);
  }
  ch->pcdata->quest_info->quest_hint[hint-1] = TRUE;
  send_to_char("Your quest rewards have been reduced for using a hint.\n\r",ch);
  do_save(ch,"auto");
  return;
 }
 else if( !str_prefix(argument,"info") )
 {
  if( !ch->pcdata->quest_info->is_questing )
  {
   send_to_char("You are not currently on a quest!\n\r",ch);
   if( ch->pcdata->quest_info->wait_time > 0 )
   {
    xprintf(buf,"You must wait %d more minute%s before taking another quest.\n\r",ch->pcdata->quest_info->wait_time,ch->pcdata->quest_info->wait_time > 1 ? "s" : "");
    send_to_char(buf,ch);
   }
   return;
  }
  if( ch->pcdata->quest_info->quest_type != 0 )
  {
   mquest_info(ch);
   return;
  }
  if( ch->pcdata->quest_info->assault_type != 0 )
  {
   switch( ch->pcdata->quest_info->assault_type )
   {
    default:
     send_to_char("ERROR!\n\r",ch);
     return;
    case ASSAULT_STEALTH:
     send_to_char("You are on a STEALTH quest!\n\r",ch);
     return;
    case ASSAULT_SLAUGHTER:
     send_to_char("You are on a SLAUGHTER quest!\n\r",ch);
     return;
    case ASSAULT_INVASION:
     send_to_char("You are on an INVASION quest!\n\r",ch);
     return;
    case ASSAULT_PROTECT:
     send_to_char("You are on a PROTECT quest!\n\r",ch);
     return;
    case ASSAULT_PRISONER:
     send_to_char("You are on a PRISONER quest!\n\r",ch);
     return;
    case ASSAULT_STOP:
     send_to_char("You are on a STOP quest!\n\r",ch);
     return;
   }
  }
  return;
 }
 else if( !str_prefix(argument,"handin") )
 {
  CHAR_DATA *mob;
  int x = 0;

  for( mob = ch->in_room->first_person; mob; mob = mob->next_in_room )
  {
   if( IS_NPC(mob) && IS_SET(mob->pIndexData->act,ACT_QUESTMASTER) )
    break;
   if( mob == NULL )
   {
    send_to_char("You have to be at a questmaster!\n\r",ch);
    return;
   }
   if( !ch->pcdata->quest_info->is_questing )
   {
    send_to_char("You aren't even on a quest! Request one first.\n\r",ch);
    return;
   }
   if( ch->pcdata->quest_info->quest_type != QUEST_RETRIEVAL && ch->pcdata->quest_info->quest_type != QUEST_MULTI_RETRIEVE )
   {
    send_to_char("You aren't on an item retrieval quest, so you have nothing to hand in!\n\r",ch);
    return;
   }
   for( i = 0; i < 5; i++) /* take objects */
   {
    if( ch->pcdata->quest_info->quest_item_vnum[i] != 0 )
    {
     for( obj = ch->first_carry; obj != NULL && ch->pcdata->quest_info->amount[i] > 0; obj = obj_next )
     {
      obj_next = obj->next_in_carry_list;
      if( ch->pcdata->quest_info->quest_item_vnum[i] == obj->pIndexData->vnum && obj->wear_loc == WEAR_NONE && !IS_SET(obj->extra_flags,ITEM_UNIQUE) )
      {
       extract_obj(obj);
       x++;
       ch->pcdata->quest_info->amount[i]--;
       if( ch->pcdata->quest_info->amount[i] == 0 )
       {
        xprintf(buf,"You have now handed in all the %s you needed for your quest.\n\r",get_obj_index(ch->pcdata->quest_info->quest_item_vnum[i])->short_descr);
        send_to_char(buf,ch);
       }
      }
     }
     if( x > 0 && ch->pcdata->quest_info->amount[i] != 0 )
     {
      xprintf(buf,"%s (%d) was handed into the questmaster.\n\r",get_obj_index(ch->pcdata->quest_info->quest_item_vnum[i])->short_descr,x);
      send_to_char(buf,ch);
     }
    }
   }
   ch->pcdata->quest_info->quest_complete = TRUE;
   for( i = 0; i < 5; i++ )
    if( ch->pcdata->quest_info->quest_item_vnum[i] != 0 && ch->pcdata->quest_info->amount[i] > 0 )
     ch->pcdata->quest_info->quest_complete = FALSE;
   mquest_complete_message(ch);
   do_save(ch,"auto");
  }
 }
 else if( !str_prefix(argument,"complete") )
 {
  CHAR_DATA *mob;
  sh_int x = 0;

  for( mob = ch->in_room->first_person; mob; mob = mob->next_in_room )
  {
   if( IS_NPC(mob) && IS_SET(mob->pIndexData->act,ACT_QUESTMASTER) )
    break;
   if( mob == NULL )
   {
    send_to_char("You have to be at a questmaster!\n\r",ch);
    return;
   }
   if( !ch->pcdata->quest_info->is_questing )
   {
    send_to_char("You aren't even on a quest! Request one first.\n\r",ch);
    return;
   }
   if( ch->pcdata->quest_info->quest_type != QUEST_KILLING && ch->pcdata->quest_info->quest_type != QUEST_MULTI_KILL )
   {
    send_to_char("You aren't on a creature killing quest, so you have nothing to complete!\n\r",ch);
    return;
   }
   for( i = 0; i < 5; i++ )
   {
    if( ch->pcdata->quest_info->quest_mob_vnum[i] != 0 )
    {
     if( ch->pcdata->quest_info->amount[i] > 0 )
     {
      x += ch->pcdata->quest_info->amount[i];
      xprintf(buf,"You are seeking out the creature known as %s.\n\r",get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[i])->short_descr);
      send_to_char(buf,ch);
      xprintf(buf,"Your quest contract states that you must slay %d more of them.\n\r",ch->pcdata->quest_info->amount[i]);
      send_to_char(buf,ch);
     }
    }
   }
   if( x > 0 )
    return;
   ch->pcdata->quest_info->quest_complete = TRUE;
   mquest_complete_message(ch);
   do_save(ch,"auto");
  }
 }
 else
  do_mquest(ch,"");
 return;
}

void do_qstat( CHAR_DATA *ch, char *argument )
{
 CHAR_DATA *victim;
 char buf[MSL];
 sh_int i = 0;

 if( argument[0] == '\0' )
 {
  send_to_char("Qstat whom?\n\r",ch);
  return;
 }
 if( (victim = get_char_world(ch,argument)) == NULL )
 {
  send_to_char("They aren't here.\n\r",ch);
  return;
 }
 if( IS_NPC(victim) )
 {
  send_to_char("Not on mobiles.\n\r",ch);
  return;
 }

 xprintf(buf,"@@y%s@@b's current quest status:@@N\n\r",victim->name);
 send_to_char(buf,ch);

 switch( victim->pcdata->quest_info->quest_type )
 {
  default:
   send_to_char("No active quest.\n\r",ch);
   return;
  case QUEST_RETRIEVAL:
   if( victim->pcdata->quest_info->quest_item_vnum[0] != 0 )
   {
    xprintf(buf,"%s is seeking item %d-%s...\n\r",PERS(victim,ch),victim->pcdata->quest_info->quest_item_vnum[0],get_obj_index(victim->pcdata->quest_info->quest_item_vnum[0])->short_descr);
    send_to_char(buf,ch);

    if( victim->pcdata->quest_info->amount[0] > 0 )
    {
     xprintf(buf,"...and must retrieve %d more of them.\n\r",victim->pcdata->quest_info->amount[0]);
     send_to_char(buf,ch);
    }
   }
   else
    send_to_char("Invalid quest item.\n\r",ch);
   break;
  case QUEST_KILLING:
   if( victim->pcdata->quest_info->quest_mob_vnum[0] != 0 )
   {
    xprintf(buf,"%s is seeking mob %d-%s...\n\r",PERS(victim,ch),victim->pcdata->quest_info->quest_mob_vnum[0],get_mob_index(victim->pcdata->quest_info->quest_mob_vnum[0])->short_descr);
    send_to_char(buf,ch);

    if( victim->pcdata->quest_info->amount[0] > 0 )
    {
     xprintf(buf,"...and must slay %d more of them.\n\r",victim->pcdata->quest_info->amount[0]);
     send_to_char(buf,ch);
    }
   }
   else
    send_to_char("Invalid quest mob.\n\r",ch);
   break;
  case QUEST_MULTI_KILL:
   send_to_char("Kill the following creatures (# of times).\n\r",ch);
   for( i = 0; i < 5; i++ )
   {
    if( victim->pcdata->quest_info->quest_mob_vnum[i] != 0 )
    {
     xprintf(buf,"Target #%d: %5d-%s (%d)\n\r",i+1,victim->pcdata->quest_info->quest_mob_vnum[i],get_mob_index(victim->pcdata->quest_info->quest_mob_vnum[i])->short_descr,victim->pcdata->quest_info->amount[i]);
     send_to_char(buf,ch);
    }
   }
   break;
  case QUEST_MULTI_RETRIEVE:
   send_to_char("Retrieve the following items (# of times).\n\r",ch);
   for( i = 0; i < 5; i++ )
   {
    if( victim->pcdata->quest_info->quest_item_vnum[i] != 0 )
    {
     xprintf(buf,"Item #%d: %5d-%s (%d)\n\r",i+1,victim->pcdata->quest_info->quest_item_vnum[i],get_obj_index(victim->pcdata->quest_info->quest_item_vnum[i])->short_descr,victim->pcdata->quest_info->amount[i]);
     send_to_char(buf,ch);
    }
   }
   break;
 }
 xprintf(buf,"QP:   %d\n\rGold: %s\n\rExp:  %d\n\r",victim->pcdata->quest_info->quest_reward[0],cost_to_money(victim->pcdata->quest_info->quest_reward[1]),victim->pcdata->quest_info->quest_reward[2]);
 send_to_char(buf,ch);
 return;
}

void mquest_info( CHAR_DATA *ch )
{
 char buf[MSL];
 sh_int i =0 ;

 switch( ch->pcdata->quest_info->quest_type )
 {
  default:
   send_to_char("Your current quest is an @@eassault@@N quest!\n\r",ch);
   break;
  case QUEST_RETRIEVAL:
   if( ch->pcdata->quest_info->quest_item_vnum[0] != 0 )
   {
    xprintf(buf,"You are seeking the item known as %s.\n\r",get_obj_index(ch->pcdata->quest_info->quest_item_vnum[0])->short_descr);
    send_to_char(buf,ch);

    if( ch->pcdata->quest_info->amount[0] > 0 )
    {
     xprintf(buf,"Your quest contract states that you must retrieve %d more of them.\n\r",ch->pcdata->quest_info->amount[0]);
     send_to_char(buf,ch);
     xprintf(buf,"@@eHint:@@N They can be found in %s@@N!\n\r",get_obj_index(ch->pcdata->quest_info->quest_item_vnum[i])->area->name);
     send_to_char(buf,ch);
    }
   }
   else
    send_to_char("Invalid quest item.\n\r",ch);
   break;
  case QUEST_KILLING:
   if( ch->pcdata->quest_info->quest_mob_vnum[0] != 0 )
   {
    xprintf(buf,"You are seeking out the creature known as %s.\n\r",get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[0])->short_descr);
    send_to_char(buf,ch);

    if( ch->pcdata->quest_info->amount[0] > 0 )
    {
     xprintf(buf,"Your quest contract states that you must slay %d more of them.\n\r",ch->pcdata->quest_info->amount[0]);
     send_to_char(buf,ch);
     xprintf(buf,"@@eHint:@@N They can be found in %s@@N!\n\r",get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[i])->area->name);
     send_to_char(buf,ch);
    }
    else
     send_to_char("You have fulfilled the kill requirements outlined in your contract.\n\r",ch);
   }
   else
    send_to_char("Invalid quest mob.\n\r",ch);
   break;
  case QUEST_MULTI_KILL:
   send_to_char("You must hunt down and destroy the following creatures (# of times).\n\r",ch);
   for( i = 0; i < 5; i++ )
   {
    if( ch->pcdata->quest_info->quest_mob_vnum[i] != 0 )
    {
     xprintf(buf,"Target #%d: %s (%d)",i+1,get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[i])->short_descr,ch->pcdata->quest_info->amount[i]);
     send_to_char(buf,ch);
     xprintf(buf," [%s]\n\r",get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[i])->area->name);
     send_to_char(buf,ch);
    }
   }
   break;
  case QUEST_MULTI_RETRIEVE:
   send_to_char("You must retrieve the following items from across the land (# of times).\n\r",ch);
   for( i = 0; i < 5; i++ )
   {
    if( ch->pcdata->quest_info->quest_item_vnum[i] != 0 )
    {
     xprintf(buf,"Item #%d: %s (%d)",i+1,get_obj_index(ch->pcdata->quest_info->quest_item_vnum[i])->short_descr,ch->pcdata->quest_info->amount[i]);
     send_to_char(buf,ch);
     xprintf(buf," [%s]\n\r",get_obj_index(ch->pcdata->quest_info->quest_item_vnum[i])->area->name);
     send_to_char(buf,ch);
    }
   }
   break;
  }
 return;
}

void mquest_complete_message( CHAR_DATA *ch )
{
 char buf[MSL];
 sh_int hint = 0, i, x;

 if( IS_NPC(ch) )
  return;
 if( ch->pcdata->quest_info->quest_complete )
 {
  for( i = 0; i < 5; i++ )
   if( ch->pcdata->quest_info->quest_hint[i] )
    hint++;
  if( hint > 0 )
  {
   if( ch->pcdata->quest_info->quest_type == QUEST_MULTI_KILL || ch->pcdata->quest_info->quest_type == QUEST_KILLING )
    for( x = 0; ch->pcdata->quest_info->quest_mob_vnum[x] !=0 && x < 5; x++);
   else if( ch->pcdata->quest_info->quest_type == QUEST_MULTI_RETRIEVE || ch->pcdata->quest_info->quest_type == QUEST_RETRIEVAL )
    for( x = 0; ch->pcdata->quest_info->quest_item_vnum[x] != 0 && x < 5; x++);
   else
   {
    send_to_char("Error calculating mquest reward. This should not happen.\n\r",ch);
    return;
   }
   ch->pcdata->quest_info->quest_reward[0] *= (float)(1-((float)hint/(float)x));
   ch->pcdata->quest_info->quest_reward[1] *= (float)(1-((float)hint/(float)x));
   ch->pcdata->quest_info->quest_reward[2] *= (float)(1-((float)hint/(float)x));
   xprintf(buf,"Quest reward reduced for the use of %d hints (%d).\n\r",hint,x);
   send_to_char(buf,ch);
  }

  xprintf(buf,"Quest Complete. You have earned %d qp, %s and %d experience!\n\r",ch->pcdata->quest_info->quest_reward[0],cost_to_money(ch->pcdata->quest_info->quest_reward[1]),ch->pcdata->quest_info->quest_reward[2]);
  send_to_char(buf,ch);

  ch->pcdata->quest_points += ch->pcdata->quest_info->quest_reward[0];
  join_money(round_money(ch->pcdata->quest_info->quest_reward[1],TRUE),ch->money);
  ch->exp += ch->pcdata->quest_info->quest_reward[2];

  ch->pcdata->records->mquest_c++;
  ch->pcdata->records->qp_tot += ch->pcdata->quest_info->quest_reward[0];

  if( ch->pcdata->records->mquest_c %50 == 0 )   /* every time a person completes 50 quests */
  {
   send_to_char("@@eCongratulations! You've succesfully completed 50 questmaster quests!\n\r",ch);
   send_to_char("@@eYou have been rewarded a bonus 25 practices and 40 quest points!\n\r",ch);
   ch->practice += 25;
   ch->pcdata->quest_points += 40;
   ch->pcdata->records->qp_tot += 40;
  }
  if( ch->pcdata->quest_points > ch->pcdata->records->qp )
  {
   send_to_char("@@yYou've broken your quest point record!@@N\n\r",ch);
   ch->pcdata->records->qp = ch->pcdata->quest_points;
  }
  mquest_clear(ch);
 }
 else
  send_to_char("You haven't completed the quest's requirements yet.\n\r",ch);
 return;
}

void mquest_calc_rewards( CHAR_DATA *ch )
{
 sh_int clev, tot_amt, tot_tsk;
 float mod = 1.00;

 if( IS_NPC(ch) )
  return;

 tot_amt = 0;
 tot_tsk = 0;
 clev = get_psuedo_level(ch);

 if( is_adept(ch) )
 {
  ch->pcdata->quest_info->quest_reward[0] = number_range(4,5);
  ch->pcdata->quest_info->quest_reward[1] = number_range(5000,7000);
  ch->pcdata->quest_info->quest_reward[2] = number_range(exp_to_level_adept(ch) * 0.04,exp_to_level_adept(ch) * 0.08);
 }
 else if( is_remort(ch) )
 {
  ch->pcdata->quest_info->quest_reward[0] = number_range(3,4);
  ch->pcdata->quest_info->quest_reward[1] = number_range(3000,5000);
  ch->pcdata->quest_info->quest_reward[2] = number_range(exp_to_level(ch,clev,5) * 0.04,exp_to_level(ch,clev,5) * 0.08);
 }
 else
 {
  ch->pcdata->quest_info->quest_reward[0] = number_range(2,3);
  ch->pcdata->quest_info->quest_reward[1] = number_range(1000,3000);
  ch->pcdata->quest_info->quest_reward[2] = number_range(exp_to_level(ch,clev,1) * 0.04,exp_to_level(ch,clev,1) * 0.08);
 }

 /* Add some randomness */
 ch->pcdata->quest_info->quest_reward[1] += number_range(-1,1);
 ch->pcdata->quest_info->quest_reward[2] = number_range(ch->pcdata->quest_info->quest_reward[2] * 0.9,ch->pcdata->quest_info->quest_reward[2] * 1.1);
 ch->pcdata->quest_info->quest_reward[3] = number_range(ch->pcdata->quest_info->quest_reward[3] * 0.9,ch->pcdata->quest_info->quest_reward[3] * 1.1);

 for( tot_tsk = 0; tot_tsk < 5; tot_tsk++ )
 {
  if( ch->pcdata->quest_info->amount[tot_tsk] == -1 )
   break;
  else
   tot_amt += ch->pcdata->quest_info->amount[tot_tsk];
 }

 if( ch->pcdata->quest_info->quest_type == QUEST_MULTI_RETRIEVE )
 {
  if( tot_tsk >= 3 )
   mod += ((tot_tsk - 3) * 0.1);
  else
   mod -= 0.2;
 }
 else if( ch->pcdata->quest_info->quest_type == QUEST_RETRIEVAL )
 {
  if( tot_amt >= 3 )
   mod += ((tot_amt - 3) * 0.1);
  else
   mod -= 0.2;
 }
 else if( ch->pcdata->quest_info->quest_type == QUEST_KILLING )
 {
  if( tot_amt >= 3 )
   mod += ((tot_amt - 4) * 0.1);
  else
   mod -= 0.2;
 }
 else if( ch->pcdata->quest_info->quest_type == QUEST_MULTI_KILL )
 {
  if( tot_tsk >= 3 )
   mod += ((tot_tsk - 3 ) * 0.1);
  else
   mod -= 0.2;
  mod += ((tot_amt - 10) * 0.02);
 }
 else
 {
  send_to_char("An error has occured calculating rewards. This should not happen.\n\r",ch);
  return;
 }

 ch->pcdata->quest_info->quest_reward[0] *= mod;
 ch->pcdata->quest_info->quest_reward[1] *= mod;
 ch->pcdata->quest_info->quest_reward[2] *= mod;
       
 /* Bonus! */
 if( number_percent() < 5 )
  ch->pcdata->quest_info->quest_reward[0] += 2;
 if( number_percent() < 5 )
  ch->pcdata->quest_info->quest_reward[1] *= 1.5;
 if( number_percent() < 5 )
  ch->pcdata->quest_info->quest_reward[2] *= 1.5;

 /* No negative rewards */
 if( ch->pcdata->quest_info->quest_reward[0] < 0 )
  ch->pcdata->quest_info->quest_reward[0] = 0;
 if( ch->pcdata->quest_info->quest_reward[1] < 0 )
  ch->pcdata->quest_info->quest_reward[1] = 0;
 if( ch->pcdata->quest_info->quest_reward[2] < 0 )
  ch->pcdata->quest_info->quest_reward[2] = 0;

 return;
}

void mquest_clear( CHAR_DATA *ch )
{
 int i = 0;
 char buf[MSL];

 if( IS_NPC(ch) )
  return;

 for( i = 0; i < 5; i++ )
  ch->pcdata->quest_info->amount[i] = -1;
 ch->pcdata->quest_info->assault_type = 0;
 ch->pcdata->quest_info->is_questing = FALSE;
 ch->pcdata->quest_info->quest_complete = FALSE;
 for( i = 0; i < 5; i++ )
  ch->pcdata->quest_info->quest_hint[i] = FALSE;
 for( i = 0; i < 5; i++ )
  ch->pcdata->quest_info->quest_item_vnum[i] = 0;
 for( i = 0; i < 5; i++ )
  ch->pcdata->quest_info->quest_mob_vnum[i] = 0;
 for( i = 0; i < 3; i++ )
  ch->pcdata->quest_info->quest_reward[i] = 0;
 ch->pcdata->quest_info->quest_type = 0;
 ch->pcdata->quest_info->time_left = 0;
 if( ch->pcdata->quest_info->wait_time == 0 )
 {
  ch->pcdata->quest_info->wait_time = 5;
  xprintf(buf,"You must wait %d minutes before your next quest.\n\r",ch->pcdata->quest_info->wait_time);
  send_to_char(buf,ch);
 }
 do_save(ch,"auto");
 return;
}

void generate_killing_quest( CHAR_DATA *ch )
{
 CHAR_DATA *mob;
 sh_int max, i, x;
 bool redo = FALSE;
 sh_int min_lev, max_lev;
 sh_int clev;

 if( IS_NPC(ch) )
  return;

 clev = get_psuedo_level(ch);
 min_lev = (clev * 0.7);
 max_lev = (clev * 1.1);

 if( ch->pcdata->quest_info->quest_type == QUEST_MULTI_KILL )
  max = number_range(3,5);
 else
  max = 1;

 if( clev <= 80 && max_lev > 80 )
  max_lev = 80;
 else if( clev < 110 && max_lev > 110 )
  max_lev = 110;
 else if( clev == 120 && min_lev <110 )
  min_lev = 110;
 else
 {
  send_to_char("Mquest error. Unable to calculate levels.\n\r",ch);
  return;
 }

 min_lev = UMAX(0,min_lev);
 max_lev = UMIN(140,max_lev);

 for( i = 0; i < max; i++ )
 {
  mob = NULL;
  mob = get_quest_kill(min_lev,max_lev,ch);

  if( !mob )
  {
   max--; /* If it was entirely ineligible, reduce the tasks by 1. */
   i--;
   if( max < 1 ) /* Ensure we find something */
    max = 1;

   continue;
  }

  ch->pcdata->quest_info->quest_mob_vnum[i] = mob->pIndexData->vnum;
 
  if( redo ) /* If it just failed the same-area check, don't check again, check vnums. */
  {
   redo = FALSE; /* Prevent crashing due to infinite loop. */

   for( x = 0; x < i; x++ )
    if( (ch->pcdata->quest_info->quest_mob_vnum[i] == ch->pcdata->quest_info->quest_mob_vnum[x]) && (x != i) )
     redo = TRUE; /* Same vnum, don't allow it. Don't redo same-area check though. */
  }
  else
  {
   for( x = 0; x < i; x++ )
    if( !str_cmp(get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[i])->area->name,get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[x])->area->name) && (x != i) )
     redo = TRUE;
  }
  if( !redo )
  {
   if( ch->pcdata->quest_info->quest_type == QUEST_MULTI_KILL )
    ch->pcdata->quest_info->amount[i] = 1;
   else
   {
    if( IS_SET(get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[i])->act,ACT_SENTINEL) )
     ch->pcdata->quest_info->amount[i] = 1;
    else
     ch->pcdata->quest_info->amount[i] = (2 + number_range(0,4));
   }
  }
  else
  { /* Same area detected. Run it again. */
   ch->pcdata->quest_info->quest_mob_vnum[i] = 0;
   ch->pcdata->quest_info->amount[i] = -1;
   i--;
  }
 }
 return;
}

CHAR_DATA *get_quest_kill( int min_lev, int max_lev, CHAR_DATA *ch )
{
 CHAR_DATA *mob;
 int i = number_range(0,top_mob_index-1);

 for( mob = first_char; mob != NULL; mob  = mob->next )
 {
  i--;

  if( i > 0 )  /* Add some variety to where we start in the ch_list */
   continue;
  if( !IS_NPC(mob) )
   continue;

  if( (get_psuedo_level(mob) < min_lev || get_psuedo_level(mob) > max_lev)
   || (mob->in_room->area->min_level > get_psuedo_level(ch) || mob->in_room->area->max_level < get_psuedo_level(ch))
   || (IS_SET(mob->in_room->area->flags,AREA_NOSHOW) || IS_SET(mob->in_room->area->flags,AREA_NO_QUEST))
   || (!str_cmp(rev_spec_lookup(mob->spec_fun),"spec_cast_adept"))
   || (!str_cmp(rev_spec_lookup(mob->spec_fun),"spec_executioner"))
   || (mob->pIndexData->vnum > mob->in_room->area->max_vnum || mob->pIndexData->vnum < mob->in_room->area->min_vnum)
   || (IS_SET(mob->in_room->room_flags,ROOM_SAFE))
   || (IS_AFFECTED(mob,AFF_CHARM))
   || (IS_SET(mob->act,ACT_PET))
   || (IS_SET(mob->act,ACT_NO_QUEST)))
    continue;

  if( number_percent() < 5 ) /* Add variety to actually selecting the first ch we find in the ch_list */
   return mob;
 }
 return mob;
}

void generate_retrieval_quest( CHAR_DATA *ch )
{
 OBJ_DATA *obj;
 sh_int max, i, x;
 bool redo=FALSE;
 sh_int min_lev, max_lev;
 sh_int clev;
 

 if( IS_NPC(ch) )
  return;

 clev = get_psuedo_level(ch);
 min_lev = (clev * 0.7);
 max_lev = (clev * 1.1);

 if(ch->pcdata->quest_info->quest_type == QUEST_MULTI_RETRIEVE )
  max = number_range(3,5);
 else
  max = 1;

 if( clev <= 80 && max_lev > 80 )
  max_lev = 80;
 else if( clev < 110 && max_lev > 110 )
  max_lev = 110;
 else if( clev == 120 && min_lev <110 )
  min_lev = 110;
 else
 {
  send_to_char("Mquest error. Unable to calculate levels.\n\r",ch);
  return;
 }

 min_lev = UMAX(0,min_lev);
 max_lev = UMIN(140,max_lev);

 for( i = 0; i < max; i++ )
 {
  obj = NULL;
  obj = get_quest_item(min_lev,max_lev,ch);

  if( !obj )
  {
   max--; /* If it was entirely ineligible, reduce the tasks by 1. */
   i--;
   if( max < 1 ) /* Ensure we find something */
    max = 1;

   continue;
  }

  ch->pcdata->quest_info->quest_item_vnum[i] = obj->pIndexData->vnum;

  if( redo ) /* If it just failed the same-area check, don't check again, check vnums. */
  {
   redo = FALSE; /* Prevent crashing due to infinite loop. */

   for( x = 0; x < i; x++ )
    if( (ch->pcdata->quest_info->quest_item_vnum[i] == ch->pcdata->quest_info->quest_item_vnum[x]) && (x != i) )
     redo = TRUE; /* Same vnum, don't allow it. Don't redo same-area check though. */
  }
  else
  {
   for( x = 0; x < i; x++ )
    if( !str_cmp(get_obj_index(ch->pcdata->quest_info->quest_item_vnum[i])->area->name,get_obj_index(ch->pcdata->quest_info->quest_item_vnum[x])->area->name) && (x != i) )
     redo = TRUE;
  }
  if( !redo )
  {
   if( ch->pcdata->quest_info->quest_type == QUEST_MULTI_RETRIEVE )
    ch->pcdata->quest_info->amount[i] = 1;
   else
    ch->pcdata->quest_info->amount[i] = (2 + number_range(0,4));
  }
  else
  { /* Same area detected. Run it again. */
   ch->pcdata->quest_info->quest_item_vnum[i] = 0;
   ch->pcdata->quest_info->amount[i] = -1;
   i--;
  }
 }
 return;
}

OBJ_DATA *get_quest_item( int min_lev, int max_lev, CHAR_DATA *ch )
{
 OBJ_DATA *obj;
 int i = number_range(0,top_obj_index-1);

 for( obj = first_obj; obj != NULL; obj = obj->next )
 {
  i--;

  if( i > 0 ) /* Add some variety to where we start in the obj_list */
   continue;

  if( obj->in_room )
  {
   if( (IS_SET(obj->in_room->area->flags,AREA_NO_QUEST) || IS_SET(obj->in_room->area->flags,AREA_NOSHOW)) /* Hide places we don't want to use. */
    || (obj->in_room->area->min_level > get_psuedo_level(ch) || obj->in_room->area->max_level < get_psuedo_level(ch))
    || (obj->pIndexData->vnum > obj->in_room->area->max_vnum || obj->pIndexData->vnum < obj->in_room->area->min_vnum) /* outside obj's own area */
    || (!IS_SET(obj->wear_flags,ITEM_TAKE)) /* ensure we can pick it up */
    || (IS_SET(obj->extra_flags,ITEM_RARE)) /* don't waste rares */
    || (obj->item_type == ITEM_QUEST) /* no autoquest items */
    || (obj->item_type == ITEM_MONEY)
    || (IS_SET(obj->extra_flags,ITEM_NO_QUEST))
    || (obj->item_type == ITEM_PIECE)
    || (IS_SET(obj->extra_flags,ITEM_UNIQUE))
    || (obj->carried_by != NULL && (!IS_NPC(obj->carried_by)
    || (IS_NPC(obj->carried_by) && obj->carried_by->pIndexData->pShop != NULL)))  /* held by PC or held by NPC that is a shopkeeper */
    || (obj->weight > 15)
    || (obj->level > max_lev)
    || (obj->level < min_lev))
     continue;

   if( number_percent() < 5 ) /* Add variety to actually selecting the first obj we find in the obj_list */
    return obj;
  }
  else if( obj->carried_by && obj->carried_by->in_room )
  {
   if( (IS_SET(obj->carried_by->in_room->area->flags,AREA_NO_QUEST) || IS_SET(obj->carried_by->in_room->area->flags,AREA_NOSHOW)) /* Hide places we don't want to use. */
    || (obj->carried_by->in_room->area->min_level > get_psuedo_level(ch) || obj->carried_by->in_room->area->max_level < get_psuedo_level(ch))
    || (obj->pIndexData->vnum > obj->carried_by->in_room->area->max_vnum || obj->pIndexData->vnum < obj->carried_by->in_room->area->min_vnum) /* outside obj's own area */
    || (!IS_SET(obj->wear_flags,ITEM_TAKE)) /* ensure we can pick it up */
    || (IS_SET(obj->extra_flags,ITEM_RARE)) /* don't waste rares */
    || (obj->item_type == ITEM_QUEST) /* no autoquest items */
    || (obj->item_type == ITEM_MONEY)
    || (IS_SET(obj->extra_flags,ITEM_NO_QUEST))
    || (obj->item_type == ITEM_PIECE)
    || (IS_SET(obj->extra_flags,ITEM_UNIQUE))
    || (obj->carried_by != NULL && (!IS_NPC(obj->carried_by)
    || (IS_NPC(obj->carried_by) && obj->carried_by->pIndexData->pShop != NULL))) /* held by PC or held by NPC that is a shopkeeper */
    || (obj->weight > 15)
    || (obj->level > max_lev)
    || (obj->level < min_lev))
     continue;

   if( number_percent() < 5 ) /* Add variety to actually selecting the first obj we find in the obj_list */
    return obj;
  }
 }
 return obj;
}

char *display_mob_target( CHAR_DATA *ch, CHAR_DATA *victim )
{
 if( IS_NPC(ch) || !IS_NPC(victim) )
  return "";
 if( ch->pcdata->quest_info->is_questing && (ch->pcdata->quest_info->quest_type == QUEST_MULTI_KILL || ch->pcdata->quest_info->quest_type == QUEST_KILLING) )
 {
  sh_int i = 0;

  /* Ugly to workaround same-descr mobs with different vnums for repop purposes */
  for( i = 0; i < 5; i++ )
   if( ch->pcdata->quest_info->amount[i] > 0
    && (ch->pcdata->quest_info->quest_mob_vnum[i] == victim->pIndexData->vnum
    || (!str_cmp(get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[i])->short_descr,victim->short_descr) 
    && get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[i])->area == victim->in_room->area)) )
     return "@@e[@@yTARGET@@e] @@N";
 }
 return "";
}

char *display_obj_target( CHAR_DATA *ch, OBJ_DATA *obj )
{
 if( IS_NPC(ch) )
  return "";
 if( ch->pcdata->quest_info->is_questing && (ch->pcdata->quest_info->quest_type == QUEST_MULTI_RETRIEVE || ch->pcdata->quest_info->quest_type == QUEST_RETRIEVAL) )
 {
  sh_int i = 0;

  for( i = 0; i < 5; i++ )
   if( ch->pcdata->quest_info->quest_item_vnum[i] == obj->pIndexData->vnum && ch->pcdata->quest_info->amount[i] > 0 )
    return "@@e[@@yTARGET@@e] @@N";
 }
 return "";
}

void update_mquest_wait_time( CHAR_DATA *ch )
{
 if( IS_NPC(ch) )
  return;
 if( !ch->pcdata->quest_info->is_questing && ch->pcdata->quest_info->wait_time > 0 && ch->desc != NULL )
 {
  ch->pcdata->quest_info->wait_time--;
  if( ch->pcdata->quest_info->wait_time == 0 )
   send_to_char("You can now get another quest from the questmaster!\n\r",ch);
 }
 return;
}

void update_mquest_kill( CHAR_DATA *ch, CHAR_DATA *victim )
{
 sh_int i, tot = 0;

 if( IS_NPC(ch) || !IS_NPC(victim) )
  return;
 if( ch->pcdata->quest_info->is_questing && (ch->pcdata->quest_info->quest_type == QUEST_KILLING || ch->pcdata->quest_info->quest_type == QUEST_MULTI_KILL) && !ch->pcdata->quest_info->quest_complete )
 {
  for( i = 0; i < 5; i++ )
  {
   if( ch->pcdata->quest_info->quest_mob_vnum[i] < 1 )
    continue;
   if( ch->pcdata->quest_info->amount[i] > 0
    && (ch->pcdata->quest_info->quest_mob_vnum[i] == victim->pIndexData->vnum
    || (!str_cmp(get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[i])->short_descr,victim->short_descr)
    && get_mob_index(ch->pcdata->quest_info->quest_mob_vnum[i])->area == victim->in_room->area)) )
   {
    ch->pcdata->quest_info->amount[i]--;
    send_to_char("You have completed a quest kill!\n\r",ch);
    if( ch->pcdata->quest_info->amount[i] == 0 )
     send_to_char("You have completed the kill requirement for this creature!\n\r",ch);
   }
   if( ch->pcdata->quest_info->amount[i] > -1 )
    tot += ch->pcdata->quest_info->amount[i];
  }
  if( tot == 0 ) /* If the total is 0 after checking through the whole loop, then they've completed their quest. */
  {
   ch->pcdata->quest_info->quest_complete = TRUE;
   send_to_char("You have completed your quest! Return to the quest master.\n\r",ch);
  }
 }
 return;
}