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

File: clientAPI.c
	Functions for the Game API (connexion to the Coding Game Server)

Copyright 2016-2020 T. Hilaire, J. Brajard
*/

/* TODO: allows to try to connect to a list of servers? Or just returns 0 if the connection fails */


#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>

#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#include "clientAPI.h"

#define h_addr h_addr_list[0] /* for backward compatibility */

#define HEAD_SIZE 6 			/*number of bytes to code the size of the message (header)*/
#define MAX_LENGTH 20000 		/* maximum size of the buffer expected for print_Game */



/* global variables about the connection
 * we use them just to hide all the connection details to the user
 * so no need to know about them, or give them when we use the functions of this API
*/
int sockfd = -1;		        /* socket descriptor, equal to -1 when we are not yet connected */
char buffer[MAX_LENGTH];		/* global buffer used to send message (global so that it is not allocated/desallocated for each message) */
int debug=0;			        /* debug constant; we do not use here a #DEFINE, since it allows the client to declare 'extern int debug;' set it to 1 to have debug information, without having to re-compile labyrinthAPI.c */
char playerName[21] = {};       /* name of the player, stored to display it in debug */


/* Display Error message and exit
 *
 * Parameters:
 * - fct: name of the function where the error raises (__FUNCTION__ can be used)
 * - msg: message to display
 * - ...: extra parameters to give to printf...
*/
void dispError(const char* fct, const char* msg, ...) {
	va_list args;
	va_start(args, msg);
	fprintf(stderr, "\e[5m\e[31m\u2327\e[2m [%s] (%s)\e[0m ", playerName, fct);
	vfprintf(stderr, msg, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(EXIT_FAILURE);
}


/* Display Debug message (only if `debug` constant is set to 1)
 *
 * Parameters:
 * - fct: name of the function where the error raises (__FUNCTION__ can be used)
 * - level : debug level (print if debug>=level, level=0 always print)
 * - msg: message to display
 * - ...: extra parameters to give to printf...
*/
void dispDebug(const char* fct, int level, const char* msg, ...) {
  if (debug>=level)	{
		printf("\e[35m\u26A0\e[0m [%s] (%s) ", playerName, fct);

		/* print the msg, using the varying number of parameters */
		va_list args;
		va_start(args, msg);
		vprintf(msg, args);
		va_end(args);

		printf("\n");
	}
}

/* Read the message and fill the buffer
* Parameters:
* - fct : name of the calling function
* - buf: pointer to the buffer variable (already allocated)
* - nbuf : size of the buffer
*
* Return the remaining length of the message (0 is the message is completely read)
*/
size_t read_inbuf(const char *fct, char *buf, size_t nbuf) {
	static char stream_size[HEAD_SIZE];		/* size of the message to be received, static to avoid allocate memory at each call*/
	ssize_t r;
	static size_t length=0 ; 				/* static because some length has to be read again */
	if (!length) {
		bzero(stream_size, HEAD_SIZE);
		r = read(sockfd, stream_size, HEAD_SIZE);
		if (r < 0)
			dispError (fct, "Cannot read message's length (server has failed?)");
		r = sscanf (stream_size, "%lu", &length);
		if (r != 1)
			dispError (fct, "Cannot read message's length (server has failed?)");
		dispDebug (fct, 3, "prepare to receive a message of length :%lu",length);
	}
	size_t mini = length > nbuf ? nbuf: length;
	int read_length = 0;
	bzero(buf, nbuf);
	do {
		r = read(sockfd, buf + read_length, mini-read_length);
		if (r < 0)
			dispError(fct, "Cannot read message (called by : %s)");
		read_length += r;
	} while (read_length < mini);
  
	length -= mini; // length to be read again
	return length;
}


/* Send a string through the open socket and get acknowledgment (OK)
 * Manage connection problems
 *
 * Parameters:
 * - fct: name of the function that calls sendString (used for the logging)
 * - str: string to send
 * - ...:  accept extra parameters for str (string expansion)
 */
void sendString(const char* fct, const char* str, ...) {
	va_list args;
	va_start(args, str);
	bzero(buffer, MAX_LENGTH);
	vsprintf(buffer, str, args);
	/* check if the socket is open */
	if (sockfd < 0)
		dispError( fct, "The connection to the server is not established. Call 'connectToServer' before !");

	/* send our message */
	ssize_t r = write(sockfd, buffer, strlen(buffer));
	dispDebug(fct,2, "Send '%s' to the server", buffer);
	if (r < 0)
		dispError(fct, "Cannot write to the socket (%s)", buffer);

	/* get acknowledgment */
	size_t rr = read_inbuf(fct, buffer, MAX_LENGTH);
	if (rr > 0)
	  dispError(fct, "Acknowledgement message too long (sending:%s,receive:%s)", str,buffer);

	if (strcmp(buffer, "OK") != 0)
		dispError(fct, "Error: The server does not acknowledge, but answered:\n%s",buffer);

	dispDebug(fct, 3, "Receive acknowledgment from the server");
}



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
void connectToCGS(const char* fct, const char* serverName, unsigned int port, char* name) {
	struct sockaddr_in serv_addr;
	struct hostent *server;

	/* copy the name */
	strncpy(playerName, name, 20);

	dispDebug(fct,2, "Initiate connection with %s (port: %d)", serverName, port);

	/* Create a socket point, TCP/IP protocol, connected */
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		dispError(fct, "Impossible to open socket");

	/* Get the server */
	server = gethostbyname(serverName);
	if (server == NULL)
		dispError(fct, "Unable to find the server by its name");
	dispDebug(fct,1, "Open connection with the server %s", serverName);

	/* Allocate sockaddr */
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy(server->h_addr, &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port);

	/* Now connect to the server */
	if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		dispError(fct, "Connection to the server '%s' on port %d impossible.", serverName, port);

	/* Sending our name */
	sendString(fct, "CLIENT_NAME %s",name);
}


/* ----------------------------------
 * Close the connection to the server
 * to do, because we are polite
 *
 * Parameters:
 * - fct: name of the function that calls closeCGSConnection (used for the logging)
*/
void closeCGSConnection(const char* fct) {
	if (sockfd<0)
		dispError(fct,"The connection to the server is not established. Call 'connectToServer' before !");
	close(sockfd);
}



/* ------------------------------------------------------------------------------
 * Wait for a Game, and retrieve its name and first data (typically, array sizes)
 *
 * Parameters:
 * - fct: name of the function that calls waitForGame (used for the logging)
 * - gameType: string (max 200 characters) type of the game we want to play (empty string for regular game)
 * - gameName: string (max 50 characters), game name filled by the function
 * - data: string (max 128 characters), corresponds to the data returns by the server
 *
 * gameType is a string like "GAME key1=value1 key2=value1 ..."
 * - GAME can be empty (wait for a game). It gives the type of the game
 *   it could be "TRAINING xxxx" to play against bot xxxx
 *   or "TOURNAMENT xxxx" to join the tournament xxxx
 * - key=value pairs are used for options (each training player has its own options)
 *   invalid keys are ignored, invalid values leads to error
 *   the following options are common to every training player:
 *     - 'timeout': allows an define the timeout when training (in seconds)
 *     - 'seed': allows to set the seed of the random generator
 *     - 'start': allows to set who starts ('0' or '1')
 */
void waitForGame(const char* fct, const char* gameType, char* gameName, char* data) {
	size_t r;
	if (gameType)
	    sendString(fct,"WAIT_GAME %s", gameType);
	else
	    sendString(fct,"WAIT_GAME ");

	/* read Labyrinth name
	 If the name send is "NOT_READY", then we need to wait again
	 This (stupid) polling is here to allow the server to dectect (at least at the polling sampling period)
	 if we have disconnected or not
	 (that's the only way for the server to detect disconnection, ie sending something and check if the socket is still open)*/
	do {
        bzero(buffer,MAX_LENGTH);
        r = read_inbuf(fct,buffer,MAX_LENGTH);
        if (r>0)
            dispError( fct, "Too long answer from 'WAIT_GAME' command (sending:%s)");
    }
    while (strcmp(buffer,"NOT_READY")==0);

	dispDebug(fct,1, "Receive Game name=%s", buffer);
	strcpy(gameName, buffer);

	/* read Labyrinth size */
	bzero(buffer,MAX_LENGTH);
	r = read_inbuf(fct,buffer,MAX_LENGTH);
	if (r>0)
	  dispError(fct, "Answer from 'WAIT_GAME' too long");

	dispDebug(fct,2, "Receive Game sizes=%s", buffer);
	strcpy(data, buffer);
}



/* -------------------------------------
 * Get the game data and tell who starts
 * It fills the char* data with the data of the game (it will be parsed by the caller)
 * 1 if there's a wall, 0 for nothing
 *
 * Parameters:
 * - fct: name of the function that calls gameGetData (used for the logging)
 * - data: the array of game (the pointer data MUST HAVE allocated with the right size !!)
 *
 * Returns 0 if the client begins, or 1 if the opponent begins
 */
int getGameData(const char* fct, char* data, size_t ndata) {
	sendString(fct, "GET_GAME_DATA");

	/* read game data */
	size_t r = read_inbuf(fct, data, ndata);
	if (r > 0)
		dispError(fct, "too long answer from 'GET_GAME_DATA' command");

	dispDebug(fct,2, "Receive game's data:%s", data);


	/* read if we begin (0) or if the opponent begins (1) */
	bzero(buffer,MAX_LENGTH);
	r = read_inbuf(fct,buffer,MAX_LENGTH);
	if (r > 0)
		dispError(fct, "too long answer from 'GET_GAME_DATA' ");

	dispDebug(fct,2, "Receive these player who begins=%s", buffer);

	return buffer[0] - '0';
}



/* ----------------------
 * Get the opponent move
 *
 * Parameters:
 * - fct: name of the function that calls getCGSMove (used for the logging)
 * - move: a string representing a move (the caller will parse it to extract the move's values)
 * - msg: a string with extra data (or message when the move is not a NORMAL_MOVE), max 256 char.
 *
 * move and msg are already allocated, with at least MAX_MOVE and MAX_MESSAGE chars
 * Fill the move  and string, and returns a return_code (0 for normal move, 1 for a winning move, -1 for a losing (or illegal) move)
 * this code is relative to the opponent (+1 if HE wins, ...)
 */
t_return_code getCGSMove(const char* fct, char* move ,char* msg) {
	t_return_code result;
	sendString(fct, "GET_MOVE");
	*move = *msg = 0;

	/* read move */
	size_t r = read_inbuf(fct, move, MAX_GET_MOVE);
	if (r>0)
		dispError(fct, "too long answer from 'GET_MOVE' command");
	dispDebug(__FUNCTION__,1, "Receive that move:%s", move);

	/* read the message */
	r = read_inbuf(fct, msg, MAX_MESSAGE);
	if (r>0)
		dispError(fct, "Too long answer from 'GET_MOVE' command");
	dispDebug(__FUNCTION__,2, "Receive that return code:%s", buffer);

	/* read the return code*/
	bzero(buffer, MAX_LENGTH);
	r = read_inbuf(fct,buffer, MAX_LENGTH);
	if (r>0)
		dispError(fct, "Too long answer from 'GET_MOVE' command");
	dispDebug(__FUNCTION__,2, "Receive that return code:%s", buffer);
	sscanf(buffer, "%d", &result);

	if (result != NORMAL_MOVE)
		printf("[%s] %s\n", __FUNCTION__, msg);

	return result;
}



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
t_return_code sendCGSMove( const char* fct, char* move, char* answer) {
	t_return_code result;
	sendString(fct, "PLAY_MOVE %s", move);

	/* read the associated answer */
	bzero(buffer, MAX_LENGTH);
	size_t r = read_inbuf(fct, buffer, MAX_LENGTH);
	if (r>0)
		dispError(fct, "Too long answer from 'PLAY_MOVE' command ");
	dispDebug(fct,1, "Receive that message: %s", buffer);
	if (answer)
		strcpy(answer, buffer);

	/* read return code */
	bzero(buffer, MAX_LENGTH);
	r = read_inbuf(fct, buffer, MAX_LENGTH);
	if (r>0)
		dispError(fct, "Too long answer from 'PLAY_MOVE' command");
	dispDebug(fct,2, "Receive that return code: %s", buffer);
	sscanf(buffer, "%d", &result);

	/* display the message if the move is not a NORMAL_MOVE */
	if (result != NORMAL_MOVE)
		printf("[%s] %s\n", __FUNCTION__, answer);

	return result;
}



/* ----------------------
 * Display the game
 * in a pretty way (ask the server what to print)
 *
 * Parameters:
 * - fct: name of the function that calls sendCGSMove (used for the logging)
 */
void printCGSGame(const char* fct) {
  dispDebug(fct,2, "Try to get string to display Game");

	/* send command */
	sendString(fct, "DISP_GAME");

	/* get string to print */
	size_t r ;
	do {
	  r = read_inbuf(fct,buffer,MAX_LENGTH);
	  printf("%s",buffer);
	}
    while (r>0);
}



/* ----------------------------
 * Send a comment to the server
 *
 * Parameters:
 * - fct: name of the function that calls sendCGSMove (used for the logging)
 * - comment: (string) comment to send to the server (max 100 char.)
 */
void sendCGSComment(const char* fct, const char* comment) {
  dispDebug(fct,2, "Try to send a comment");

	/* max 100. car */
	if (strlen(comment)>100)
		dispError(fct, "The Comment is more than 100 characters.");

	/* send command */
	sendString(fct, "SEND_COMMENT %s", comment);
}
