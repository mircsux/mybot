/* Vars */
#include "includes.h"


long	CONNECT_WAIT_TIMEOUT	= 10;
long	AIL666 					= 0;
long	AIL8					= 0;

char	HOSTNAME[STRING_SHORT]	= "localhost";
char	VHOST	[STRING_SHORT]	= "0";
char	MYNICK	[STRING_SHORT] 	= "mybot";

char	myline		[STRING_SHORT]  = { "\0" };
int		alarmed					= 0;
int		sockfd					= 0;
int		PORT					= 6667;
int		send_tog				= 0;
int		SEND_DELAY 				= 1;

struct sendq *sendqhead = NULL, *sendqtail = NULL;
