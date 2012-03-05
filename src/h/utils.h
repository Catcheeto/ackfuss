/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#define DEC_UTILS_H

namespace Utils {
    const string FormatString( const bitset<MAX_BITSET> flags, const string fmt, ... );
    const string FormatString( const bitset<MAX_BITSET> flags, const string fmt, va_list val );
    const void _Logger( const bitset<MAX_BITSET> flags, const string caller, const string fmt, ... );
    #define Logger( flags, fmt, ... ) _Logger( flags, _caller, fmt, ##__VA_ARGS__ )
    const bool PatternMatch( const bitset<MAX_BITSET> flags, const string pat, const string str );
    const vector<string> StrTokens( const string input );
    template <class T> inline const string toLower( const T& t )  { stringstream ss; ss << nouppercase << t; return ss.str(); }
    #define toLower_( T ) toLower( T ).c_str()
    template <class T> inline const string toString( const T& t ) { stringstream ss; ss << t; return ss.str(); }
    #define toString_( T ) toString( T ).c_str()
    template <class T> inline const string toUpper( const T& t )  { stringstream ss; ss << uppercase << t; return ss.str(); }
    #define toUpper_( T ) toUpper( T ).c_str()
};

// Thanks to Laurent Deniau @ https://groups.google.com/d/msg/comp.std.c/d-6Mj5Lko_s/5R6bMWTEbzQJ
#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
         _0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0



// Soon to be deprecated and removed
#define     BIT_0       0
#define     BIT_1       1
#define     BIT_2       2
#define     BIT_3       4
#define     BIT_4       8
#define     BIT_5       16
#define     BIT_6       32
#define     BIT_7       64
#define     BIT_8       128
#define     BIT_9       256
#define     BIT_10      512
#define     BIT_11      1024
#define     BIT_12      2048
#define     BIT_13      4096
#define     BIT_14      8192
#define     BIT_15      16384
#define     BIT_16      32768
#define     BIT_17      65536
#define     BIT_18      131072
#define     BIT_19      262144
#define     BIT_20      524288
#define     BIT_21      1048576
#define     BIT_22      2097152
#define     BIT_23      4194304
#define     BIT_24      8388608
#define     BIT_25      16777216
#define     BIT_26      33554432
#define     BIT_27      67108864
#define     BIT_28      134217728
#define     BIT_29      268435456
#define     BIT_30      536870912
#define     BIT_31      1073741824
#define     BIT_32      2147483648

#define STR(x) #x
#define SX(x) STR(x)
#define _caller __FILE__ ":" SX(__LINE__)

/*
 * Utility macros.
 */
#define UMIN(a, b)              ((a) < (b) ? (a) : (b))
#define UMAX(a, b)              ((a) > (b) ? (a) : (b))
#define URANGE(a, b, c)         ((b) < (a) ? (a) : ((b) > (c) ? (c) : (b)))
#define LOWER(c)                ((c) >= 'A' && (c) <= 'Z' ? (c)+'a'-'A' : (c))
#define UPPER(c)                ((c) >= 'a' && (c) <= 'z' ? (c)+'A'-'a' : (c))
#define IS_SET(flag, bit)       ((flag) & (bit))
#define SET_BIT(var, bit)       ((var) |= (bit))
#define REMOVE_BIT(var, bit)    ((var) &= ~(bit))
#define IS_LETTER(c)            ( ((c) >= 'A' && (c) <= 'Z' ) \
                                  ||((c) >= 'a' && (c) <= 'z' ) )
/*
 * Character macros.
 */
#define IS_NPC(ch)              ( (ch)->npc )
#define IS_IMMORTAL(ch)         (get_trust(ch) >= LEVEL_IMMORTAL)
#define IS_HERO(ch)             (get_trust(ch) >= LEVEL_HERO)
#define IS_ADEPT(ch)            ( !IS_NPC(ch) && ch->get_level("adept") > 0 )
#define IS_REMORT(ch)           ( !IS_NPC(ch) && ch->get_level("remort") > 0 )
#define IS_AFFECTED(ch, sn)     ( IS_SET((ch)->affected_by, (sn)))
#define IS_HUNGRY(ch)           ( !IS_NPC(ch) && ch->pcdata->condition[COND_FULL] <= 0 )
#define IS_THIRSTY(ch)          ( !IS_NPC(ch) && ch->pcdata->condition[COND_THIRST] <= 0 )
#define IS_DRUNK(ch)            ( !IS_NPC(ch) && ch->pcdata->condition[COND_DRUNK] > 10 )

#define HAS_COOLDOWN(ch)        ( ch->cooldown[COOLDOWN_OFF] > 0 || ch->cooldown[COOLDOWN_DEF] > 0 )
#define IS_CASTING(ch)          ( ch->casting->time > 0 )
#define IS_GHOST(ch)            ( ch->act.test(ACT_GHOST) )
#define IS_GOOD(ch)             ( (ch)->GetAlignment() >= 350)
#define IS_EVIL(ch)             ( (ch)->GetAlignment() <= -350)
#define IS_NEUTRAL(ch)          (!IS_GOOD(ch) && !IS_EVIL(ch))
#define IS_AWAKE(ch)            (ch->position > POS_SLEEPING)
#define GET_AC(ch)              ( REAL_AC( ch ) + (ch)->GetModAC() )
#define REAL_AC(ch)             ((ch)->armor  + ( IS_AWAKE(ch) \
                                 ? ( IS_NPC( ch ) \
                                     ? ( dex_app[get_curr_dex(ch)].defensive * ch->get_level("psuedo") / 20 ) \
                                     : ( dex_app[get_curr_dex(ch)].defensive * ch->get_level("psuedo") / 10 ) ): 0 ))
/* Super macros */
#define IS_VAMP(ch)    ( ch->act.test(ACT_VAMPIRE)  )
#define IS_UNDEAD(ch)  ( ch->act.test(ACT_UNDEAD)   )
#define IS_WOLF(ch)    ( ch->act.test(ACT_WEREWOLF) )
#define IS_SHIFTED(ch) ( ch->act.test(ACT_SHIFTED)  )
#define IS_RAGED(ch)   ( ch->act.test(ACT_RAGED)    )
#define IS_HUNTER(ch)  ( ch->act.test(ACT_SHUNTER)  )

/* Added bonus to hit and dam for higher levl players */
/* High level naked players should still be able to fight ok */

#define GET_HITROLL(ch)         ( REAL_HITROLL(ch) + ch->GetModHR() + (ch->get_level("psuedo") / 4 ) )
#define REAL_HITROLL(ch)        ((ch)->hitroll+ (str_app[get_curr_str(ch)].tohit * ch->get_level("psuedo") / 10) )
#define GET_DAMROLL(ch)         ( REAL_DAMROLL(ch) + ch->GetModDR() + (ch->get_level("psuedo") / 4 ) )
#define REAL_DAMROLL(ch)        ((ch)->damroll+( str_app[get_curr_str(ch)].todam * ch->get_level("psuedo") / 10 ) )
#define IS_OUTSIDE(ch)          (!(ch)->in_room->room_flags.test(RFLAG_INDOORS))
#define WAIT_STATE(ch, npulse)  ((ch)->wait = UMAX((ch)->wait, (npulse)))
#define MANA_COST(ch, sn)       (IS_NPC(ch) ? 0 : UMAX ( skill_table[sn].min_mana, 100 / (2 + ch->level - skill_table[sn].skill_level[ch->class] ) ) )
#define IS_RIDING(ch)           (!IS_NPC(ch) && ((ch)->riding))
#define MAGIC_STANCE(ch)        ( IS_NPC(ch) ? FALSE : \
                                  ( (ch)->stance == STANCE_CASTER ) \
                                  || ( (ch)->stance == STANCE_WIZARD ) \
                                  || ( (ch)->stance == STANCE_MAGI ) )
#define PLAYTESTER(ch)          ( !IS_NPC(ch) && IS_SET((ch)->pcdata->pflags, PFLAG_TESTER )  )
#define HAS_BODY(ch)            ( !IS_NPC(ch) || (ch)->act.test(ACT_NO_BODY) )
#define HAS_MIND(ch)            ( !IS_NPC(ch) || (ch)->act.test(ACT_NO_MIND) )
#define IS_WEAPON(eq)           ( (eq) != NULL ? (eq)->item_type == ITEM_WEAPON : FALSE )
#define IS_SHIELD(eq)           ( (eq) != NULL ? (eq)->item_type == ITEM_ARMOR : FALSE )

/*
 * Object macros.
 */
#define CAN_WEAR(obj, part)     ((obj)->wear_flags.test((part)))
#define IS_OBJ_STAT(obj, stat)  ((obj)->extra_flags.test((stat)))


/* Added stuff - Flar */
#define CH(descriptor)  ((descriptor)->original ? \
                         (descriptor)->original : (descriptor)->character)

/*
 * Linked list macros, -- Altrag
 */
/* Regular linking of double-linked list */
#define LINK(link, first, last, next, prev) \
    do { \
        if ( (link)->prev || (link)->next ) hang("LINK: link already in list?"); \
        if ( (last) && (last)->next ) hang("LINK: last->next NON-NULL!"); \
        if ( !(first) ) \
            (first) = (link); \
        else \
            (last)->next = (link); \
        (link)->next = NULL; \
        (link)->prev = (last); \
        (last) = (link); \
    } while(0)

/* Link at the head of the list rather than the tail.  Double linked */
#define TOPLINK(link, first, last, next, prev) \
    do { \
        if ( (link)->prev || (link)->next ) hang("TOPLINK: link already in list?"); \
        if ( (first) && (first)->prev ) hang("TOPLINK: first->prev NON-NULL!"); \
        if ( !(last) ) \
            (last) = (link); \
        else \
            (first)->prev = (link); \
        (link)->prev = NULL; \
        (link)->next = (first); \
        (first) = (link); \
    } while(0)

/* Unlink a double linked list */
#define UNLINK(link, first, last, next, prev) \
    do { \
        if ( (link)->prev && (((link)->prev)->next != (link)) ) \
            hang("UNLINK: link->prev->next corrupted!"); \
        if ( (link)->next && (((link)->next)->prev != (link)) ) \
            hang("UNLINK: link->next->prev corrupted!"); \
        if ( !(link)->next ) \
            (last) = (link)->prev; \
        else \
            (link)->next->prev = (link)->prev; \
        if ( !(link)->prev ) \
            (first) = (link)->next; \
        else \
            (link)->prev->next = (link)->next; \
        (link)->prev = NULL; \
        (link)->next = NULL; \
    } while(0)

/* Link to the end of a single-linked list */
#define SING_LINK(link, first, next, DATA_TYPE) \
    do { \
        if ( !(first) ) \
            (first) = (link); \
        else \
        { \
            DATA_TYPE *last; \
            for ( last = (first); last->next; last = last->next ) \
                ; \
            last->next = (link); \
        } \
        (link)->next = NULL; \
    } while(0)

/* Link to head of a single-linked list (normal linking) */
#define SING_TOPLINK(link, first, next) \
    do { \
        (link)->next = (first); \
        (first) = (link); \
    } while(0)

/* Unlink a single linked list */
#define SING_UNLINK(link, first, next, DATA_TYPE) \
    do { \
        if ( (link) == (first) ) \
            (first) = (link)->next; \
        else \
        { \
            DATA_TYPE *prev; \
            for ( prev = (first); prev; prev = prev->next ) \
                if ( prev->next == (link) ) \
                    break; \
            if ( prev != NULL ) \
                prev->next = (link)->next; \
            else \
                bug("Sing_unlink: link not in list.", 0); \
        } \
    } while(0)

/* Link to end of a half-linked list */
/* Half linked lists have a LAST pointer, but not a PREV pointer, making
   them approximately halfway between a single linked list and a double
   linked list. -- Altrag */
#define HALF_LINK(link, first, last, next) \
    do { \
        if ( !(last) ) \
            (first) = (link); \
        else \
            (last)->next = (link); \
        (link)->next = NULL; \
        (last) = (link); \
    } while(0)

/* Link to head of a half-linked list. */
#define HALF_TOPLINK(link, first, last, next) \
    do { \
        if ( (last) == (first) ) \
            (last) = (link); \
        (link)->next = (first); \
        (first) = (link); \
    } while(0)

/* Unlink a half-linked list. */
#define HALF_UNLINK(link, first, last, next, DATA_TYPE) \
    do { \
        if ( (link) == (first) ) \
        { \
            (first) = (link)->next; \
            if ( (link) == (last) ) \
                (last) = NULL; \
        } \
        else \
        { \
            DATA_TYPE *prev; \
            for ( prev = (first); prev; prev = prev->next ) \
                if ( prev->next == (link) ) \
                    break; \
            if ( prev != NULL ) \
            { \
                prev->next = (link)->next; \
                if ( (link) == (last) ) \
                    (last) = prev; \
            } \
            else \
                bug("Half_unlink: link not in list.", 0); \
        } \
    } while(0)

/*
 * Miscellaneous macros.
 */

/* spec: macro-ised getmem as a wrapper around _getmem for mem_log handling */
#define getmem(size) _getmem(size,_caller,1)
#define qgetmem(size) _getmem(size,_caller,0)

/* This one goes as a #define in merc.h.. dont worry.. itll work.. :) */
/* spec: log all dispose's if mem_log==TRUE - also nuke trailing ; */
/* spec: add dispose override, too */
#define _dispose(mem,size,log) \
    do { \
        if ( ! (mem) ) \
        { \
            bug("Disposing NULL memory",0); \
            return; \
        } \
        if (log&&mem_log) Utils::Logger( 0, "dispose(%p) from %s:%d", (mem), __FILE__, __LINE__); \
        free((mem)); \
        (mem) = NULL; \
    } while(0)

#define dispose(mem,size) _dispose(mem,size,1)
#define qdispose(mem,size) _dispose(mem,size,0)
