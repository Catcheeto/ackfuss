/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#define DEC_ENUM_H

// Negative states are used to track who to boot during copyover
// sint_t    Brain->m_connection_state
#define CON_RESET_PASSWORD          -16 // was -17
#define CON_CONFIRM_RESET_PASSWORD  -15 // was -18
#define CON_QUITTING                -14 // was -15
#define CON_RECONNECTING            -13 // was -16
#define CON_COPYOVER_RECOVER        -12 // was -14
#define CON_GET_NAME                -11 // was -1
#define CON_CONFIRM_NEW_NAME        -10 // was -3
#define CON_GET_NEW_PASSWORD        -9  // was -4
#define CON_CONFIRM_NEW_PASSWORD    -8  // was -5
#define CON_CREATION_MENU           -7  // was -13
#define CON_CREATION_GET_SEX        -6
#define CON_CREATION_GET_RACE       -5  // was -9
#define CON_CREATION_GET_STATS      -4  // was -11
#define CON_CREATION_GET_CLASS      -3  // was -7
#define CON_GET_OLD_PASSWORD        -2
#define CON_READ_MOTD               -1  // was -10
#define CON_SETTING_STATS            0  // was 1 -- cast spells
#define CON_PLAYING                  1  // was 0

// bitset<MAX_CREATION_CHECK>    Brain->m_creation_check
enum bitsBrain_m_creation_check {
    CREATION_RACE_DONE  = 0,
    CREATION_CLASS_DONE = 1,
    CREATION_SEX_DONE   = 2,
    CREATION_STATS_DONE = 3,
    MAX_CREATION_CHECK  = 4
};

// uint_t    Brain->m_type
enum uintBrain_m_type {
    BRAIN_TYPE_DUMB_NPC  = 0,
    BRAIN_TYPE_SMART_NPC = 1,
    BRAIN_TYPE_HUMAN     = 2,
    MAX_BRAIN_TYPE       = 3
};

// bitset<MAX_BITSET>[MAX_THING_FLAG]    Thing->m_flag
enum bitsThing_m_flag {
    THING_FLAG_ACT = 0,
    MAX_THING_FLAG = 1
};

// uint_t[MAX_THING_LEVEL_TIER][MAX_THING_LEVEL_CLASS]
enum uintThing_m_level_tier {
    THING_LEVEL_TIER1    = 0,
    THING_LEVEL_TIER2    = 1,
    THING_LEVEL_TIER3    = 2,
    MAX_THING_LEVEL_TIER = 3
};

enum uintThing_m_level_tier1_class {
    THING_LEVEL_TIER1_CLASS_MAGE       = 0,
    THING_LEVEL_TIER1_CLASS_CLERIC     = 1,
    THING_LEVEL_TIER1_CLASS_THIEF      = 2,
    THING_LEVEL_TIER1_CLASS_WARRIOR    = 3,
    THING_LEVEL_TIER1_CLASS_PSIONICIST = 4,
    MAX_THING_LEVEL_TIER1_CLASS        = 5
};

enum uintThing_m_level_tier2_class {
    THING_LEVEL_TIER2_CLASS_SORCERER    = THING_LEVEL_TIER1_CLASS_MAGE,
    THING_LEVEL_TIER2_CLASS_MONK        = THING_LEVEL_TIER1_CLASS_CLERIC,
    THING_LEVEL_TIER2_CLASS_ASSASSIN    = THING_LEVEL_TIER1_CLASS_THIEF,
    THING_LEVEL_TIER2_CLASS_KNIGHT      = THING_LEVEL_TIER1_CLASS_WARRIOR,
    THING_LEVEL_TIER2_CLASS_NECROMANCER = THING_LEVEL_TIER1_CLASS_PSIONICIST,
    MAX_THING_LEVEL_TIER2_CLASS         = MAX_THING_LEVEL_TIER1_CLASS
};

enum uintThing_m_level_tier3_class {
    THING_LEVEL_TIER3_CLASS_ADEPT = THING_LEVEL_TIER2_CLASS_SORCERER,
    MAX_THING_LEVEL_TIER3_CLASS   = MAX_THING_LEVEL_TIER2_CLASS
};

#define MAX_THING_LEVEL_TIER_CLASS MAX_THING_LEVEL_TIER3_CLASS

// uint_t    THING_FLAG_ACT
enum uintThing_flag_act {
    THING_FLAG_ACT_CBOSS      = 0,
    THING_FLAG_ACT_VAMPIRE    = 1,
    THING_FLAG_ACT_WEREWOLF   = 2,
    THING_FLAG_ACT_AMBASSADOR = 3,
    MAX_THING_FLAG_ACT        = 4
};

// bitset<MAX_BITSET>    Utils
enum bitsUtils {
    UTILS_DEBUG       = 0,
    UTILS_IGNORE_CASE = 1,
    UTILS_RAW         = 2,
    UTILS_TYPE_ERROR  = 3,
    MAX_UTILS         = 4
};
