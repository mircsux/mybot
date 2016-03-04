/*  Main() */

#include "includes.h"


int			main			(int argc, char **argv)
{
	FILE	*fp = NULL;

	int		errcode = 0, sockfd = 0, i = 0;
	
	char	*hostname = "localhost";
	char	ip 			[100] = { "0" };
	char	REPLY_LINE	[STRING_LONG] = { "0" };
	int	port 		= 6667;
	
	fd_set	fdvar;
		
	struct	hostent 	*he;
	struct	in_addr 	**addr_list;
	struct 	sockaddr_in server;
	struct 	timeval 	timeout;
#ifdef		SA_NOCLDSTOP
	struct	sigaction	newact;
#endif
	

/* This is the best way to deternmine if sigaction() can be used.
 * sigaction() is more portable than signal(), so use it if we can. */

 #ifdef 	SA_NOCLDSTOP
        newact.sa_handler = sig_alrm;
        sigemptyset (&newact.sa_mask);
        newact.sa_flags = 0;
        sigaction (SIGALRM, &newact, NULL);
        newact.sa_handler = sig_segv;
        sigemptyset (&newact.sa_mask);
        newact.sa_flags = 0;
        sigaction (SIGSEGV, &newact, NULL);
        newact.sa_handler = sig_hup;
        sigemptyset (&newact.sa_mask);
        newact.sa_flags = 0;
        sigaction (SIGHUP, &newact, NULL);
#else
        signal (SIGALRM, sig_alrm);
        signal (SIGSEGV, sig_segv);
        signal (SIGHUP, sig_hup);
#endif

	printf ("[*** Ron's IRC Bot %s ***]\r\n", PACKAGE_VERSION);

	printf ("\n");
	printf ("Connecting to %s\n", hostname);
	
	/* Open the past results file. */
	if	((fp = fopen (PAST_RESULT_FILE, "r")) == NULL)
	{
		printf	(":. Failed to open past results file (%s)\t\r", PAST_RESULT_FILE);
		exit	(EXIT_FAILURE);
	}

	// Create socket.
	sockfd = socket (AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
	{	
		printf ("Could not create socket.\n");
	}
	/* Get the IP for our connect host. */
	if ((he = gethostbyname (hostname)) == NULL)
	{
		/* gethostbyname failure. */
		herror ("gethostbyname");
		return (1);
	}
	
	 /* Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only */
    addr_list = (struct in_addr **) he->h_addr_list;
	for (i = 0; addr_list[i] != NULL; i++)
	{
		/* return the first one. */
		strcpy (ip, inet_ntoa (*addr_list[i]));
	}
	
	server.sin_addr.s_addr = inet_addr (ip);
	server.sin_family = AF_INET;
	server.sin_port = htons (port);
	
	// Connect to remote server
	if (connect (sockfd, (struct sockaddr *)&server, sizeof (server)) <0)
	{
		printf ("Error connecting.\n");
		return (1);
	}

	printf ("Connected.\n");

	while (1)
	{
		timeout.tv_sec = WSEC;
		timeout.tv_usec = USEC;
		
		FD_ZERO (&fdvar);
	        FD_SET (sockfd, &fdvar);
		
		switch (select (NFDBITS, &fdvar, (fd_set *) NULL, (fd_set *) NULL, &timeout))
		{
			case 0:
			   break;
			case -1:
			   break;
			default:
			   parse_message (sockfd, REPLY_LINE, &fdvar);
			   break;
	    }
	}
	
	/* Close socket */
	close (sockfd);
	return (0);
	
}
