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

#ifndef DEC_MAGIC_H
#include "h/magic.h"
#endif

#ifndef DEC_SSM_H
#include "h/ssm.h"
#endif

bool char_data::check_cooldown( const char *skill )
{
    int sn = skill_lookup(skill);

    if ( sn < 0 )
        return false;

    if ( skill_table[sn].cooldown <= COOLDOWN_NONE )
        return false;

    if ( cooldown[skill_table[sn].cooldown] > 0 )
    {
        switch ( skill_table[sn].cooldown )
        {
            case COOLDOWN_OFF: send("@@eYour offensive abilities are on cooldown right now.\r\n"); break;
            case COOLDOWN_DEF: send("@@lYour defensive abilities are on cooldown right now.\r\n"); break;
        }
        return true;
    }

    return false;
}

bool char_data::check_cooldown( int pos )
{
    if ( pos <= COOLDOWN_NONE )
        return false;

    if ( cooldown[pos] > 0 )
    {
        switch ( pos )
        {
            case COOLDOWN_OFF: send("@@eYour offensive abilities are on cooldown right now.\r\n"); break;
            case COOLDOWN_DEF: send("@@lYour defensive abilities are on cooldown right now.\r\n"); break;
        }
        return true;
    }

    return false;
}

const char *char_data::get_name( CHAR_DATA *looker )
{
    if ( looker != NULL )
    {
        if ( can_see(looker, this) )
        {
            if ( IS_NPC(this) )
                return getDescrShort_();
            else
            {
                if ( IS_WOLF(this) && (IS_SHIFTED(this) || IS_RAGED(this)) )
                    return "A Large @@bWolf@@N";
                else
                    return getName_();
            }
        }
        else
        {
            if ( isImmortal() )
                return "A Mystical Being";
            else
                return "Someone";
        }
    }
    else
    {
        if ( IS_NPC(this) )
            return getDescrShort_();
        else
            return getName_();
    }

    return "Unknown!";
}

const char *char_data::get_title( )
{
    if ( IS_NPC(this) )
        return "";
    else
        return pcdata->title;
}

const char *char_data::get_whoname( )
{
    char buf[MSL] = {'\0'};
    short s1, s2, s3, s4, s5;
    const char *output;

    if ( IS_NPC(this) )
        return "";

    if ( isImmortal() )
    {
        if ( strcmp(pcdata->who_name,"off") )
            return pcdata->who_name;

        switch ( get_level() )
        {
            case MAX_LEVEL - 0: return "@@l~* CREATOR *~@@N ";
            case MAX_LEVEL - 1: return "@@B-* SUPREME *-@@N ";
            case MAX_LEVEL - 2: return "@@a-=MAJOR GOD=-@@N ";
            case MAX_LEVEL - 3: return "@@a--MINOR GOD--@@N ";
            case MAX_LEVEL - 4: return "@@c - IMMORTAL -@@N ";
        }
    }

    if ( IS_ADEPT(this) )
    {
        if ( strcmp(pcdata->who_name,"off") )
            return pcdata->who_name;

        switch ( get_level("adept") )
        {
            case 1:  return "@@W    Mystic    @@N";
            case 2:  return "@@a   Templar    @@N";
            case 3:  return "@@l Illusionist  @@N";
            case 4:  return "@@e   Crusader   @@N";
            case 5:  return "@@d   Warlock    @@N";
            case 6:  return "@@a   Paladin    @@N";
            case 7:  return "@@r    Ranger    @@N";
            case 8:  return "@@c  Gladiator   @@N";
            case 9:  return "@@l    Shogun    @@N";
            case 10: return "@@e    Shamen    @@N";
            case 11: return "@@r    Druid     @@N";
            case 12: return "@@b  Conjurer    @@N";
            case 13: return "@@l Elementalist @@N";
            case 14: return "@@m  Runemaster  @@N";
            case 15: return "@@d Shadowmaster @@N";
            case 16: return "@@b Beastmaster  @@N";
            case 17: return "@@R   Warlord    @@N";
            case 18: return "@@e  Dragonlord  @@N";
            case 19: return "@@d  Demonlord   @@N";
            case 20: return "@@m  Realm Lord  @@N";
        }
    }

    if ( IS_REMORT(this) )
    {
        s1 = get_level("sor"); s2 = get_level("mon"); s3 = get_level("ass"); s4 = get_level("kni"); s5 = get_level("nec");
        snprintf( buf, MSL, "@@m%2d %2d %2d %2d %2d@@N", s1 <= 0 ? 0 : s1, s2 <= 0 ? 0 : s2, s3 <= 0 ? 0 : s3, s4 <= 0 ? 0 : s4, s5 <= 0 ? 0 : s5 );
        output = str_dup( buf );

        return output;
    }
    else
    {
        s1 = get_level("mag"); s2 = get_level("cle"); s3 = get_level("thi"); s4 = get_level("war"); s5 = get_level("psi");
        snprintf( buf, MSL, "@@b%2d %2d %2d %2d %2d@@N", s1 <= 0 ? 0 : s1, s2 <= 0 ? 0 : s2, s3 <= 0 ? 0 : s3, s4 <= 0 ? 0 : s4, s5 <= 0 ? 0 : s5 );
        output = str_dup( buf );

        return output;
    }

    return "";
}

void char_data::rsend( string txt, ... )
{
    DESCRIPTOR_DATA *d = NULL;
    iterBrain di;

    if ( this->in_room == NULL )
        return;

    for ( di = brain_list.begin(); di != brain_list.end(); di++ )
    {
        d = *di;
        if ( d->getConnectionState( CON_PLAYING ) && d->character->in_room == this->in_room )
            d->character->send(txt);
    }

    return;
}

void char_data::send( string txt, ... )
{
    char buf[MSL];
    va_list args;

    if ( this == NULL || desc == NULL )
        return;

    if ( txt.empty() )
        return;

    va_start(args, txt);
    vsprintf(buf, txt.c_str(), args);
    va_end(args);

    if ( desc->showstr_head != NULL )
    {
        char *ssh;

        ssh = (char *)qgetmem( strlen( desc->showstr_head ) + strlen( buf ) + 1 );
        strcpy( ssh, desc->showstr_head );
        strcat( ssh, buf );

        if ( desc->showstr_point )
            desc->showstr_point += ( ssh - desc->showstr_head );
        else
            desc->showstr_point = ssh;

        free(desc->showstr_head);
        desc->showstr_head = ssh;
    }
    else
    {
        desc->showstr_head = (char *)malloc( strlen( buf ) + 1);
        strcpy( desc->showstr_head, buf );
        desc->showstr_point = desc->showstr_head;
    }
    if ( desc->showstr_point == desc->showstr_head )
        show_string( desc, "" );
    return;
}

/* Use for passing any strings to escape vsprintf formatting, such as lists of objects with %s, %d, etc in them.
   Value of the bool doesn't matter, just something to differentiate the func for overloading. --Kline */
void char_data::send( bool raw, string txt )
{
    if ( this == NULL || desc == NULL )
        return;

    if ( txt.empty() )
        return;

    if ( desc->showstr_head != NULL )
    {
        char *ssh;

        ssh = (char *)qgetmem( strlen( desc->showstr_head ) + txt.length() + 1 );
        strcpy( ssh, desc->showstr_head );
        strcat( ssh, txt.c_str() );

        if ( desc->showstr_point )
            desc->showstr_point += ( ssh - desc->showstr_head );
        else
            desc->showstr_point = ssh;

        free(desc->showstr_head);
        desc->showstr_head = ssh;
    }
    else
    {
        desc->showstr_head = (char *)malloc( txt.length() + 1);
        strcpy( desc->showstr_head, txt.c_str() );
        desc->showstr_point = desc->showstr_head;
    }
    if ( desc->showstr_point == desc->showstr_head )
        show_string( desc, "" );

    return;
}

void char_data::set_cooldown( const char *skill )
{
    int sn = skill_lookup(skill);

    if ( sn < 0 )
        return;

    if ( skill_table[sn].cooldown <= COOLDOWN_NONE )
        return;

    cooldown[skill_table[sn].cooldown] += skill_table[sn].beats;

    return;
}

void char_data::set_cooldown( int pos, float duration )
{
    if ( pos <= COOLDOWN_NONE )
        return;

    cooldown[pos] += duration;

    return;
}

void char_data::set_title( const char *title )
{
    if ( IS_NPC(this) )
        return;

    free_string(pcdata->title);
    pcdata->title = str_dup(title);

    return;
}
