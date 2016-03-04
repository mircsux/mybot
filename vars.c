/* Vars */

long	CONNECT_WAIT_TIMEOUT	= 10;
char	HOSTNAME	[512]			= "punch.wa.us.dal.net";
char	VHOST		[512]			= "0";

int		alarmed					= 0;
int		sockfd					= 0;
int		PORT					= 6667;