/***************************************************************************
 * _/_/_/_/  _/    _/  _/_/_/_/ _/_/_/_/ AckFUSS is modified ACK!MUD 4.3.1 *
 * _/        _/    _/  _/       _/       copyright Matt Goff (Kline) 2008  *
 * _/_/      _/    _/  _/_/_/_/ _/_/_/_/                                   *
 * _/        _/    _/        _/       _/ Support for this code is provided *
 * _/        _/_/_/_/  _/_/_/_/ _/_/_/_/ at www.ackmud.net -- check it out!*
 ***************************************************************************/

#define DEC_BOARD_H

#if __STDC__ || defined(__cplusplus)
#define P_(s) s
#else
#define P_(s) ()
#endif

typedef struct board_data BOARD_DATA;
typedef struct message_data MESSAGE_DATA;

class board_data
{
    public:
        board_data();
        ~board_data();

        sint_t clan;
        uint_t expiry_time;
        list<MESSAGE_DATA*> messages;
        uint_t min_read_lev;
        uint_t min_write_lev;
        uint_t vnum;
};

class message_data
{
    public:
        message_data();
        ~message_data();

        string author;
        BOARD_DATA *board;
        time_t datetime;
        string message;
        string title;
};

/* board.c */
void show_contents P_((CHAR_DATA *ch, OBJ_DATA *obj));
BOARD_DATA *load_board P_((OBJ_INDEX_DATA *pObj));
void save_board P_((BOARD_DATA *board, CHAR_DATA *ch));
DECLARE_DO_FUN(do_delete);
void show_message P_((CHAR_DATA *ch, int mess_num, OBJ_DATA *obj));
DECLARE_DO_FUN(do_write);
void finished_editing P_((MESSAGE_DATA *msg, char **dest, CHAR_DATA *ch, bool saved));
DECLARE_DO_FUN(do_read);
void edit_message P_((CHAR_DATA *ch, int mess_num, OBJ_DATA *obj));
DECLARE_DO_FUN(do_edit);

#undef P_

#define T2000 -1  /* Terminator for files... */
