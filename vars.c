/* Vars */
#include "includes.h"


long	CONNECT_WAIT_TIMEOUT	= 10;
char	HOSTNAME	[512]			= "localhost";
char	VHOST		[512]			= "0";
char	myline		[STRING_SHORT]  = { NULL };
int		alarmed					= 0;
int		sockfd					= 0;
int		PORT					= 6667;
int		send_tog				= 0;
int		SEND_DELAY 				= 1;

struct sendq *sendqhead = NULL, *sendqtail = NULL;


struct	{
		char 	*cmd;
		void	(*function)(char *, char *);
}		parse_server_cmd[] = {

	{	"PING",					parse_ping				},
	{	NULL,					NULL					}

};
