/*

* ------------------------------ *
|                                |
|   -= Coding Game Server =-     |
|                                |
|       client API in C          |
|                                |
* ------------------------------ *

Authors: T. Hilaire, J. Brajard
Licence: GPL

File: clientAPI.h
	Functions' prototypes for the client API

Copyright 2016-2020 T. Hilaire, J. Brajard
*/



#ifndef __API_CLIENT_GAME__
#define __API_CLIENT_GAME__

#include <stdio.h>


#define MAX_GET_MOVE 128	    	/* maximum size of the string representing a move */
#define MAX_MESSAGE 1024			/* maximum size of the message move */


/* defines a return code, used for playMove and getMove */
typedef enum
{
	NORMAL_MOVE = 0,
	WINNING_MOVE = 1,
	LOSING_MOVE = -1
} t_return_code;


/* --------------------
 * Display Error message and exit
 *
 * Parameters:
 * - fct: name of the function where the error raises (__FUNCTION__ can be used)
 * - msg: message to display
 * - ...: extra parameters to give to printf...
*/
void dispError(const char* fct, const char* msg, ...);



/* ------------------------
 * Display Debug message (only if `debug` constant is set to 1)
 *
 * Parameters:
 * - fct: name of the function where the error raises (__FUNCTION__ can be used)
 * - msg: message to display
 * - level : debug level (print if debug>=level, level=0 always print)
 * - ...: extra parameters to give to printf...
*/
void dispDebug(const char* fct,int level, const char* msg, ...);



/* -------------------------------------
 * Initialize connection with the server
 * Quit the program if the connection to the server cannot be established
 *
 * Parameters:
 * - fct: name of the function that calls connectToCGS (used for the logging)
 * - serverName: (string) address of the server (it could be "localhost" if the server is run in local, or "pc4521.polytech.upmc.fr" if the server runs there)
 * - port: (int) port number used for the connection
 * - name: (string) name of the bot : max 20 characters (checked by the server)
 */
void connectToCGS(const char* fct, const char* serverName, unsigned int port, char* name);



/* ----------------------------------
 * Close the connection to the server
 * to do, because we are polite
 *
 * Parameters:
 * - fct: name of the function that calls closeCGSConnection (used for the logging)
*/
void closeCGSConnection(const char* fct);



/* ------------------------------------------------------------------------------
 * Wait for a Game, and retrieve its name and first data (typically, array sizes)
 *
 * Parameters:
 * - fct: name of the function that calls waitForGame (used for the logging)
 * - training: string (max 50 characters) type of the training player we want to play with (empty string for regular game)
 * - gameName: string (max 50 characters), corresponds to the game name
 * - data: string (max 128 characters), corresponds to the data
 *
 * training is a string like "NAME key1=value1 key2=value1 ..."
 * - NAME can be empty. It gives the type of the training player
 * - key=value pairs are used for options (each training player has its own options)
 *   invalid keys are ignored, invalid values leads to error
 *   the following options are common to every training player (when NAME is not empty):
 *   - timeout: allows an define the timeout when training (in seconds)
 */
void waitForGame(const char* fct, const char* training, char* gameName, char* data);



/* -------------------------------------
 * Get the game data and tell who starts
 * It fills the char* data with the data of the game (it will be parsed by the caller)
 *
 * Parameters:
 * - fct: name of the function that calls getGameData (used for the logging)
 * - data: the array of game (the pointer data MUST HAVE allocated with the right size !!)
 * - ndata : maximum size of the data
 *
 * Returns 0 if the client begins, or 1 if the opponent begins
 */
int getGameData(const char* fct, char* data, size_t ndata);



/* ----------------------
 * Get the opponent move
 *
 * Parameters:
 * - fct: name of the function that calls getCGSMove (used for the logging)
 * - move: a string representing a move (the caller will parse it to extract the move's values)
 * - msg: a string with extra data (or message when the move is not a NORMAL_MOVE)
 *
 * Fill the move and returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move)
 * this code is relative to the opponent (+1 if HE wins, ...)
 */
t_return_code getCGSMove(const char* fct, char* move ,char* msg);



/* -----------
 * Send a move
 *
 * Parameters:
 * - fct: name of the function that calls sendCGSMove (used for the logging)
 * - move: a string representing a move (the caller will parse it to extract the move's values)
 * - answer: a string representing the answer (should be allocated)
 *
 * Returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move
 */
t_return_code sendCGSMove(const char* fct, char* move, char* answer);



/* ----------------------
 * Display the game
 * in a pretty way (ask the server what to print)
 *
 * Parameters:
 * - fct: name of the function that calls sendCGSMove (used for the logging)
 */
void printCGSGame(const char* fct);



/* ----------------------------
 * Send a comment to the server
 *
 * Parameters:
 * - fct: name of the function that calls sendCGSMove (used for the logging)
 * - comment: (string) comment to send to the server (max 100 char.)
 */
void sendCGSComment(const char* fct, const char* comment);

#endif
