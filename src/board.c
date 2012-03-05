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

#ifndef DEC_BOARD_H
#include "h/board.h"
#endif

#ifndef DEC_BUILD_H
#include "h/build.h"
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

#ifndef DEC_SSM_H
#include "h/ssm.h"
#endif

#ifndef DEC_WRITE_H
#include "h/write.h"
#endif

/**************************************************************************
 *               MAG Modified outline                                     *
 *       Use a directory called boards under area directory.              *
 *       Store a file for each board called board.vnum makes things a lot *
 *       easier, and means files can be transfered easily between boards  *
 *       use a time based means to get rid of messages.                   *
 *                                                    *
 *       Values:                              *
 *          Value0  :  Expiry time for a message in days.                 *
 *          Value1  :  Min level of player to read the board.             *
 *          Value2  :  Max level of player to write to the board.         *
 *          Value3  :  Board number (usually it's vnum for simplicity)    *
 *                                    *
 *       Uses commands in write.c for string editing.                     *
 *       This file does reading files, writing files and managing boards  *
 *                                    *
 **************************************************************************/

/**************************************************************************
 *                        Outline of BOARD.C                              *
 *                        ^^^^^^^^^^^^^^^^^^                              *
 * This code was written for use in ACK! MUD.  It should be easy to       *
 * include it into a Diku Merc 2.0+ Mud.                                  *
 *                                                                        *
 * The following functions are needed:                                    *
 * 1) Show the contents of a board to a player.                           *
 * 2) Show a message to a player                                          *
 * 3) Add to a message & finish writing a message.                        *
 * 4) Start writing a message                                             *
 * 5) Remove a message                                                    *
 * 6) Save the messages                                                   *
 * 7) Load the messages (only used at start-up)                           *
 *                                                                        *
 * Also, the code for the commands write and read are in this file.       *
 * WRITE checks for a board, and calls either 4) or 3) above.             *
 * READ calls 2) above.  The LOOK function was ammended to allow players  *
 * to type 'look board' or 'look at board' which calls 1) above.          *
 *                                                                        *
 * MESSAGE DATA holds the vnum of the board where the message was written *
 * and the message info.  There is no seperate save file or structure for *
 * each board.  Instead, they are all stored together.  I have used       *
 * OBJ_TYPE 23 for boards, with the following values used:                *
 * value 0: max number of messages allowed                                *
 * value 1: min level of player to read the board                         *
 * value 2: min level of player to write on the board                     *
 * value 3: the vnum of the board...NOT the vnum of the room...           *
 **************************************************************************/

board_data::board_data()
{
    clan = -1;
    expiry_time = 0;
    messages.clear();
    min_read_lev = 0;
    min_write_lev = 0;
    vnum = 0;

    board_list.push_back(this);
}

board_data::~board_data()
{
    list<MESSAGE_DATA*>::iterator it = messages.begin();

    while ( it++ != messages.end() )
        delete *it;
}

message_data::message_data()
{
    author.clear();
    board = NULL;
    datetime = 0;
    message.clear();
    title.clear();
}

message_data::~message_data()
{
}

void show_contents( CHAR_DATA * ch, OBJ_DATA * obj )
{
    /*
     * Show the list of messages that are present on the board that ch is
     * * looking at, indicated by board_vnum...
     */

    MESSAGE_DATA *msg = NULL;
    list<BOARD_DATA*>::iterator li;
    list<MESSAGE_DATA*>::iterator mi;
    BOARD_DATA *board = NULL;
    OBJ_INDEX_DATA *pObj;
    char buf[MAX_STRING_LENGTH];
    uint_t board_num, cnt = 0;

    pObj = obj->pIndexData;
    board_num = pObj->value[3];

    /*
     * First find the board, and if not there, create one.
     */
    for ( li = board_list.begin(); li != board_list.end(); li++ )
    {
        board = *li;
        if ( board->vnum == board_num )
            break;
    }

    if ( board == NULL )
        board = load_board( pObj );

    /*
     * check here to see if player allowed to read board
     */

    if ( board->min_read_lev > get_trust( ch ) )
    {
        send_to_char( "You are not allowed to look at this board.\r\n", ch );
        return;
    }

    if ( ( board->clan != 0 ) && !IS_NPC( ch ) && ch->clan != ( board->clan - 1 ) )
    {
        send_to_char( "You are not of the right clan to read this board.\r\n", ch );
        return;
    }


    send_to_char( "This is a notice board.\r\n", ch );
    send_to_char( "Type READ <num> to read message <num>, and WRITE <title> to post.\r\n", ch );
    send_to_char( "Type WRITE to: <player> for a private message.\r\n", ch );
    send_to_char( "Type DELETE <num> to delete message <num> that you have writen.\r\n", ch );
    send_to_char( "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\r\n", ch );


    for ( mi = board->messages.begin(); mi != board->messages.end(); mi++ )
    {
        msg = *mi;
        snprintf( buf, MSL, "[%3lu] %12s : %s", cnt, msg->author.c_str(), msg->title.c_str() );
        send_to_char( buf, ch );

    }

    if ( !board->messages.size() ) /* then there were no messages here */
        send_to_char( "         There are no messages right now!\r\n", ch );

    send_to_char( "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\r\n", ch );

    return;
}

BOARD_DATA *load_board( OBJ_INDEX_DATA * pObj )
{
    FILE *board_file;
    char buf[255];
    char *word;
    char letter;
    time_t message_time;
    time_t expiry_time;
    BOARD_DATA *board;
    MESSAGE_DATA *message;

    board = new BOARD_DATA;

    board->expiry_time = pObj->value[0];
    board->min_read_lev = pObj->value[1];
    board->min_write_lev = pObj->value[2];
    board->vnum = pObj->value[3];

    snprintf( buf, 255, "%s/board.%lu", BOARD_DIR, board->vnum );

    if ( ( board_file = file_open( buf, "r" ) ) != NULL )
    {
        /*
         * Read in Optional board parameters
         */
        for ( ;; )
        {
            if ( feof( board_file ) )
                break;

            word = fread_word( board_file );
            if ( !str_cmp( word, "ExpiryTime" ) )
            {
                board->expiry_time = fread_number( board_file );
                fread_to_eol( board_file );
            }
            if ( !str_cmp( word, "MinReadLev" ) )
            {
                board->min_read_lev = fread_number( board_file );
                fread_to_eol( board_file );
            }
            if ( !str_cmp( word, "MinWriteLev" ) )
            {
                board->min_write_lev = fread_number( board_file );
                fread_to_eol( board_file );
            }
            if ( !str_cmp( word, "Clan" ) )
            {
                board->clan = fread_number( board_file );
                fread_to_eol( board_file );
            }
            if ( !str_cmp( word, "Messages" ) )
            {
                fread_to_eol( board_file );
                break;
            }
        }

        if ( board->expiry_time > 0 )
            expiry_time = time( NULL ) - ( board->expiry_time ) * 3600 * 24;
        else
            expiry_time = 0;

        /*
         * Now read in messages
         */
        for ( ;; )
        {
            if ( feof( board_file ) )
                break;

            letter = fread_letter( board_file );
            if ( letter == 'S' )
                break;

            if ( letter != 'M' )
            {
                bug( "Letter in message file not M", 0 );
                break;
            }

            /*
             * check time
             */
            message_time = ( time_t ) fread_number( board_file );
            if ( feof( board_file ) )
                break;

            if ( message_time < expiry_time )
            {
                char *dumpme;

                dumpme = fread_string( board_file );   /* author  */
                free_string( dumpme );
                dumpme = fread_string( board_file );   /* title   */
                free_string( dumpme );
                dumpme = fread_string( board_file );   /* message */
                free_string( dumpme );
            }
            else
            {
                message = new MESSAGE_DATA;
                message->datetime = message_time;
                message->author = fread_string( board_file );
                message->title = fread_string( board_file );
                message->message = fread_string( board_file );
                message->board = board;
                board->messages.push_back( message );
            }
        }

        /*
         * Now close file
         */
        file_close( board_file );
    }

    return board;
}

void save_board( BOARD_DATA * board, CHAR_DATA * ch )
{
    char buf[MAX_STRING_LENGTH];
    FILE *board_file;
    MESSAGE_DATA *msg = NULL;
    list<MESSAGE_DATA*>::iterator mi;


    snprintf( buf, MSL, "%s/board.%lu", BOARD_DIR, board->vnum );
    if ( ( board_file = file_open( buf, "w" ) ) == NULL )
    {
        send_to_char( "Cannot save board, please contact an immortal.\r\n", ch );
        bug( "Could not save file board.%i.", board->vnum );
        file_close(board_file);
        return;
    }

    fprintf( board_file, "ExpiryTime  %lu\n", board->expiry_time );
    fprintf( board_file, "MinReadLev  %lu\n", board->min_read_lev );
    fprintf( board_file, "MaxWriteLev %lu\n", board->min_write_lev );
    fprintf( board_file, "Clan        %lu\n", board->clan );

    /*
     * Now print messages
     */
    fprintf( board_file, "Messages\n" );

    for ( mi = board->messages.begin(); mi != board->messages.end(); mi++ )
    {
        msg = *mi;
        fprintf( board_file, "M%i\n", ( int )( msg->datetime ) );

        strcpy( buf, msg->author.c_str() );  /* Must do copy, not allowed to change string directly */
        smash_tilde( buf );
        fprintf( board_file, "%s~\n", buf );

        strcpy( buf, msg->title.c_str() );
        smash_tilde( buf );
        fprintf( board_file, "%s~\n", buf );

        strcpy( buf, msg->message.c_str() );
        smash_tilde( buf );
        fprintf( board_file, "%s~\n", buf );

    }

    fprintf( board_file, "S\n" );

    file_close( board_file );

    return;
}

DO_FUN(do_delete)
{
    OBJ_DATA *object;
    BOARD_DATA *board = NULL;
    list<BOARD_DATA*>::iterator li;
    list<MESSAGE_DATA*>::iterator mi;
    MESSAGE_DATA *msg = NULL;
    OBJ_INDEX_DATA *pObj;
    uint_t vnum;
    int mess_num;
    int cnt = 0;

    if ( IS_NPC( ch ) )
    {
        send_to_char( "NPCs may *not* delete messages.  So there.\r\n", ch );
        return;
    }

    if ( argument[0] == '\0' )
    {
        send_to_char( "You need to specify a message number to delete!\r\n", ch );
        return;
    }

    for ( object = ch->in_room->first_content; object != NULL; object = object->next_in_room )
    {
        if ( object->item_type == ITEM_BOARD )
            break;
    }

    if ( object == NULL )
    {
        send_to_char( "Delete on what?\r\n.", ch );
        return;
    }

    pObj = object->pIndexData;
    vnum = pObj->value[3];

    /*
     * First find the board, and if not there, create one.
     */
    for ( li = board_list.begin(); li != board_list.end(); li++ )
    {
        board = *li;
        if ( board->vnum == vnum )
            break;
    }

    if ( board == NULL )
        board = load_board( pObj );

    /*
     * check here to see if player allowed to write to board
     */

    if ( board->min_write_lev > get_trust( ch ) )
    {
        send_to_char( "You are not allowed to delete on this board.\r\n", ch );
        return;
    }

    if ( ( board->clan != 0 ) && ch->clan != ( board->clan - 1 ) )
    {
        send_to_char( "You are not of the right clan to delete on this board.\r\n", ch );
        return;
    }


    cnt = 0;
    mess_num = is_number( argument ) ? atoi( argument ) : 0;

    for ( mi = board->messages.begin(); mi != board->messages.end(); mi++ )
    {
        msg = *mi;
        if ( ++cnt == mess_num )
            break;
    }

    if ( msg == NULL )
    {
        send_to_char( "No such message!\r\n", ch );
        return;
    }

    /*
     * See if person is writer or is recipient
     */
    if ( ( ch->GetName() == msg->author ) && !is_name( ch->GetName_(), msg->title )
            && get_trust( ch ) < MAX_LEVEL && str_cmp( ch->GetName(), clan_table[board->clan].leader ) )
    {
        send_to_char( "Not your message.\r\n", ch );
        return;
    }

    /*
     * Now delete message
     */

    board->messages.remove( msg );
    delete msg;

    save_board( board, ch );

    return;
}

void show_message( CHAR_DATA * ch, int mess_num, OBJ_DATA * obj )
{
    /*
     * Show message <mess_num> to character.
     * * check that message vnum == board vnum
     */

    list<BOARD_DATA*>::iterator li;
    list<MESSAGE_DATA*>::iterator mi;
    BOARD_DATA *board = NULL;
    OBJ_INDEX_DATA *pObj;
    uint_t vnum;
    MESSAGE_DATA *msg = NULL;
    int cnt = 0;
    bool mfound = FALSE;
    char buf[MAX_STRING_LENGTH];
    char to_check[MAX_INPUT_LENGTH];
    char *to_person;
    char private_name[MAX_INPUT_LENGTH];

    pObj = obj->pIndexData;
    vnum = pObj->value[3];

    /*
     * First find the board, and if not there, create one.
     */
    for ( li = board_list.begin(); li != board_list.end(); li++ )
    {
        board = *li;
        if ( board->vnum == vnum )
            break;
    }

    if ( board == NULL )
        board = load_board( pObj );

    /*
     * check here to see if player allowed to read board
     */

    if ( board->min_read_lev > get_trust( ch ) )
    {
        send_to_char( "You are not allowed to look at this board.\r\n", ch );
        return;
    }

    if ( ( board->clan != 0 ) && !IS_NPC( ch ) && ch->clan != ( board->clan - 1 ) )
    {
        send_to_char( "You are not of the right clan to read this board.\r\n", ch );
        return;
    }

    for ( mi = board->messages.begin(); mi != board->messages.end(); mi++ )
    {
        msg = *mi;
        if ( ++cnt == mess_num ) /* then this the message!!! */
        {
            mfound = TRUE;

            to_person = one_argument( msg->title, to_check );
            to_person = one_argument( to_person, private_name );
            if ( !str_cmp( to_check, "to:" ) && str_prefix( private_name, ch->GetName_() ) && ( msg->author == ch->GetName() ) )
            {
                send_to_char( "This is a private message.\r\n", ch );
                break;
            }
            snprintf( buf, MSL, "** [%d] %12s : %s ** \r\n\r\n%s\r\n", cnt, msg->author.c_str(), msg->title.c_str(), msg->message.c_str() );
            send_to_char( buf, ch );
            break;
        }
    }

    if ( !mfound )
    {
        send_to_char( "No such message!\r\n", ch );
    }

    return;
}

DO_FUN(do_write)
{
    OBJ_DATA *object;
    BOARD_DATA *board = NULL;
    list<BOARD_DATA *>::iterator li;
    MESSAGE_DATA *msg;
    OBJ_INDEX_DATA *pObj;
    uint_t vnum;
    char buf[MAX_STRING_LENGTH];

    if ( IS_NPC( ch ) )
    {
        send_to_char( "NPCs may *not* write messages.  So there.\r\n", ch );
        return;
    }

    if ( argument[0] == '\0' )
    {
        send_to_char( "You need to specify a header for your message!\r\n", ch );
        return;
    }

    for ( object = ch->in_room->first_content; object != NULL; object = object->next_in_room )
    {
        if ( object->item_type == ITEM_BOARD )
            break;
    }

    if ( object == NULL )
    {
        send_to_char( "Write on what?\r\n.", ch );
        return;
    }

    pObj = object->pIndexData;
    vnum = pObj->value[3];

    /*
     * First find the board, and if not there, create one.
     */
    for ( li = board_list.begin(); li != board_list.end(); li++ )
    {
        board = *li;
        if ( board->vnum == vnum )
            break;
    }

    if ( board == NULL )
        board = load_board( pObj );

    /*
     * check here to see if player allowed to write to board
     */

    if ( board->min_write_lev > get_trust( ch ) )
    {
        send_to_char( "You are not allowed to write on this board.\r\n", ch );
        return;
    }

    if ( ( board->clan != 0 ) && ch->clan != ( board->clan - 1 ) )
    {
        send_to_char( "You are not of the right clan to write on this board.\r\n", ch );
        return;
    }

    msg = new MESSAGE_DATA;
    msg->datetime = time( NULL ); /* we are sure we can edit.          */
    snprintf( buf, MSL, "%s @@a%s@@N", argument, ( char * )ctime( &current_time ) );
    msg->title = buf;
    msg->author = ch->GetName();
    msg->board = board;

    /*
     * Now actually run the edit prog.
     */
    //FIXME write_start( &msg->message, finished_editing, msg, ch );

    if ( !msg->message.empty() )
    {
        send_to_char( "Editing message. Type .help for help.\r\n", ch );
        board->messages.push_back( msg );
    }
    else
    {
        send_to_char( "Could not add message.\r\n", ch );
        delete msg;
    }
    return;
}


/* Deals with taking message out of list if user aborts... */

void finished_editing( MESSAGE_DATA * msg, char **dest, CHAR_DATA * ch, bool saved )
{
    if ( !saved )
    {
        msg->board->messages.remove( msg );
        delete msg;
    }
    else
    {
        save_board( msg->board, ch );
    }
    return;
}

DO_FUN(do_read)
{
    OBJ_DATA *obj;


    if ( ( argument[0] == '\0' ) || !is_number( argument ) )
    {
        send_to_char( "Read what??\r\n", ch );
        return;
    }

    for ( obj = ch->in_room->first_content; obj != NULL; obj = obj->next_in_room )
    {
        if ( obj->item_type == ITEM_BOARD )
            break;
    }

    if ( obj == NULL )
    {
        send_to_char( "Read What??\r\n", ch );
        return;
    }

    /*
     * Hopefully, by now there should be a board in the room, and the
     * * player should have supplied some sort of argument....
     */

    show_message( ch, atoi( argument ), obj );
    return;
}





void edit_message( CHAR_DATA * ch, int mess_num, OBJ_DATA * obj )
{
    /*
     * Show message <mess_num> to character.
     * * check that message vnum == board vnum
     */

    list<BOARD_DATA*>::iterator li;
    list<MESSAGE_DATA*>::iterator mi;
    BOARD_DATA *board = NULL;
    OBJ_INDEX_DATA *pObj;
    uint_t vnum;
    MESSAGE_DATA *msg = NULL;
    int cnt = 0;
    bool mfound = FALSE;

    pObj = obj->pIndexData;
    vnum = pObj->value[3];

    /*
     * First find the board, and if not there, create one.
     */
    for ( li = board_list.begin(); li != board_list.end(); li++ )
    {
        board = *li;
        if ( board->vnum == vnum )
            break;
    }

    if ( board == NULL )
        board = load_board( pObj );

    /*
     * check here to see if player allowed to read board
     */

    if ( board->min_read_lev > get_trust( ch ) )
    {
        send_to_char( "You are not allowed to even look at this board!\r\n", ch );
        return;
    }

    if ( ( board->clan != 0 ) && !IS_NPC( ch ) && ch->clan != ( board->clan - 1 ) )
    {
        send_to_char( "You are not of the right clan to even read this board!\r\n", ch );
        return;
    }

    for ( mi = board->messages.begin(); mi != board->messages.end(); mi++ )
    {
        msg = *mi;
        if ( ++cnt == mess_num ) /* then this the message!!! */
        {
            mfound = TRUE;

            if ( msg->author == ch->GetName() )
            {
                send_to_char( "Not your message to edit!\r\n", ch );
                return;
            }
            else
            {
                //FIXME build_strdup( &msg->message, "$edit", TRUE, FALSE, ch );
            }

        }
    }
    if ( !mfound )
        send_to_char( "No such message!\r\n", ch );

    return;
}

DO_FUN(do_edit)
{
    OBJ_DATA *obj;


    if ( ( argument[0] == '\0' ) || !is_number( argument ) )
    {
        send_to_char( "Read what??\r\n", ch );
        return;
    }

    for ( obj = ch->in_room->first_content; obj != NULL; obj = obj->next_in_room )
    {
        if ( obj->item_type == ITEM_BOARD )
            break;
    }

    if ( obj == NULL )
    {
        send_to_char( "Read What??\r\n", ch );
        return;
    }

    /*
     * Hopefully, by now there should be a board in the room, and the
     * * player should have supplied some sort of argument....
     */

    edit_message( ch, atoi( argument ), obj );
    return;
}
