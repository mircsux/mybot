/* Vars */
#include "defines.h"
#include <stdio.h>

long	CONNECT_WAIT_TIMEOUT	= 10;
char	HOSTNAME	[512]			= "punch.wa.us.dal.net";
char	VHOST		[512]			= "0";

int		alarmed					= 0;
int		sockfd					= 0;
int		PORT					= 6667;
int		send_tog				= 0;
int		SEND_DELAY 				= 1;

struct		sendq
{
		char	data	[STRING_SHORT];
		struct	sendq 	*next;
}		*sendqhead = NULL, *sendqtail = NULL;
