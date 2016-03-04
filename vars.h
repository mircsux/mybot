/* Vars.h */
extern	long	CONNECT_WAIT_TIMEOUT;

extern	char	HOSTNAME		[512];
extern	char	VHOST			[512];

extern	int		alarmed;
extern	int		sockfd;
extern	int		PORT;
extern  int		send_tog;
extern	int		SEND_DELAY;

extern struct		sendq
{
		char	data	[STRING_SHORT];
		struct	sendq 	*next;
}		
*sendqhead, *sendqtail;
