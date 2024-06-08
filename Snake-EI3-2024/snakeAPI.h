/* --------------------------------------------- *
 |                                               |
 |                                               |
 |   ░░░░░░░ ░░░    ░░  ░░░░░  ░░   ░░ ░░░░░░░   |
 |   ▒▒      ▒▒▒▒   ▒▒ ▒▒   ▒▒ ▒▒  ▒▒  ▒▒        |
 |   ▒▒▒▒▒▒▒ ▒▒ ▒▒  ▒▒ ▒▒▒▒▒▒▒ ▒▒▒▒▒   ▒▒▒▒▒     |
 |        ▓▓ ▓▓  ▓▓ ▓▓ ▓▓   ▓▓ ▓▓  ▓▓  ▓▓        |
 |   ███████ ██   ████ ██   ██ ██   ██ ███████   |
 |                                               |
 |                                               |
 |   Based on CodingGameServer                   |
 |                                               |
 * --------------------------------------------- *

Authors: T. Hilaire
Licence: GPL

File: snkaeAPI.h
	Contains the client API for the Snake game
	-> based on clientAPI.h

Copyright 2024 T. Hilaire
*/


#ifndef __API_CLIENT_SNAKE__
#define __API_CLIENT_SNAKE__
#include "clientAPI.h"


/* Definition of a move */
typedef enum {
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3
} t_move;


/* -------------------------------------
 * Initialize connection with the server
 * Quit the program if the connection to the server
 * cannot be established
 *
 * Parameters:
 * - serverName: (char*) address of the server
 *   (it could be "localhost" if the server is run in local,
 *   or "pc5039.polytech.upmc.fr" if the server runs there)
 * - port: (int) port number used for the connection
 * - name: (char*) name of your bot : max 20 characters
 */
void connectToServer(char* serverName, int port, char* name);



/* ----------------------------------
 * Close the connection to the server
 * Has to be done, because we are polite
 */
void closeConnection();


/* -------------------------------------------------------------------------
 * Wait for a Game, and retrieve its name, its sizes and the number of walls
 *
 * Parameters:
 * - gameType: (string, max 150 char) type of the game we want to play (empty string for regular game)
 * - gameName: (string, max 50 char), corresponds to the game name (filled by the server)
 * - sizeX, sizeY: (int*) pointers to the dimension of the game (filled by the server)
 * - nbWalls: (int*) pointer to the number of walls
 *
* gameType is a string like "GAME key1=value1 key2=value1 ..."
 * - It indicates the type of the game you want to plys
 *   it could be "TRAINING <BOT>" to play against bot <BOT>
 *   or "TOURNAMENT xxxx" to join the tournament xxxx
 *   or "" (empty string) to wait for an opponent (decided by the server)
 * - key=value pairs are used for options (each training player has its own options)
 *   invalid keys are ignored, invalid values leads to error
 *   the following options are common to every training player
  *        - 'timeout': allows and define the timeout when training (in seconds)
 *        - 'seed': allows to set the seed of the random generator
 *        - 'start': allows to set who starts (0 or 1)
 *        - 'difficulty': between 0 (no walls) and 3 (a lot of walls); 2 is the default value
 *
 * The bots <BOT> available are :
 * - "RANDOM_PLAYER": player that makes random (but legal) moves
 * - "SUPER_PLAYER": not so good player, but maybe a little bit better than RANDOM_PLAYER...
 */
void waitForSnakeGame(char* gameType, char* gameName, int* sizeX, int* sizeY, int* nbWalls);


/* -------------------------------------
 * Get the data and tell who starts
 *
 * Parameters:
  * - walls: (int*) array of nbWalls*4 integers (x1, y1, x2 , y2 for a wall between (x1,y1) and (x2,y2))
 *   (the pointer data MUST HAVE allocated, the size if given with `waitForSnakeGame`)
 *
 * Returns 0 if you begin, or 1 if the opponent begins
 */
int getSnakeArena(int* walls);



/* ----------------------
 * Get the opponent move
 *
 * Parameters:
 * - move: a move
 *
 * Returns a return_code
 * NORMAL_MOVE for normal move,
 * WINNING_MOVE for a winning move, -1
 * LOSING_MOVE for a losing (or illegal) move
 * this code is relative to the opponent (WINNING_MOVE if HE wins, ...)
 */
t_return_code getMove(t_move* move );



/* -----------
 * Send a move
 *
 * Parameters:
 * - move: a move
 *
 * Returns a return_code
 * NORMAL_MOVE for normal move,
 * WINNING_MOVE for a winning move, -1
 * LOSING_MOVE for a losing (or illegal) move
 * this code is relative to your programm (WINNING_MOVE if YOU win, ...)
 */
t_return_code sendMove(t_move move);



/* ----------------------
 * Display the Game
 * in a pretty way (ask the server what to print)
 */
void printArena();



/* ----------------------------
 * Send a comment to the server
 *
 * Parameters:
 * - comment: (string) comment to send to the server (max 100 char.)
 */
void sendComment(char* comment);



#endif
