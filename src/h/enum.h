/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#define DEC_ENUM_H

// Negative states are used to track who to boot during copyover
enum ConnectionState {
 CON_RESET_PASSWORD         = -16,
 CON_CONFIRM_RESET_PASSWORD = -15,
 CON_QUITTING               = -14,
 CON_RECONNECTING           = -13,
 CON_COPYOVER_RECOVER       = -12,
 CON_GET_NAME               = -11,
 CON_CONFIRM_NAME           = -10,
 CON_GET_PASSWORD           = -9,
 CON_CONFIRM_PASSWORD       = -8,
 CON_CREATION_MENU          = -7,
 CON_CREATION_GET_SEX       = -6,
 CON_CREATION_GET_RACE      = -5,
 CON_CREATION_GET_STATS     = -4,
 CON_CREATION_GET_CLASS     = -3,
 CON_GET_OLD_PASSWORD       = -2,
 CON_READ_MOTD              = -1,
 CON_SETTING_STATS          =  0, // cast spells
 CON_PLAYING                =  1
};
