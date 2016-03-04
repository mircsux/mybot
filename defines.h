/* Defines */

/* File that contains past lottery results */
#define	PAST_RESULT_FILE		"past.txt"


#define	AIL						1
#define	USEC					0
#define	WSEC					10
#define	RECHECK					45
#define ERR_SOCK_OPT			-1
#define ERR_TIMED_OUT           -1
#define ERR_CANT_MALLOC         -1
#define ERR_OPEN_SOCKET         -2
#define ERR_CONN_REFUSED        -2
#define ERR_NOT_ADDR            -3
#define ERR_WRITE_SOCKET        -3
#define ERR_NO_REACH            -4
#define ERR_CANT_CONNECT        -5
#define ERR_READ_SOCKET         -5
#define ERR_SERVER_BUSY         -6
#define ERR_NO_DOCUMENTS        -6
#define ERR_NO_DATA             -7
#define SUCCESS                 0

#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
#endif

#define	STRING_LONG		4096
#define STRING_SHORT	512