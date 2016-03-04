/* Sockets */

#include "includes.h"

/* Send data over socket fd */
int		recv_data		(int sockfd, char *reply)
{
	if (recv (sockfd, reply, STRING_LONG, 0) < 0)
	{
		printf ("receive failed");
	}
	
	printf ("data = %i, %s\n", sockfd, reply);
	return (0);
}

int		send_data		(int sockfd, char *stuff)
{
	if (send (sockfd, stuff, strlen (stuff), 0) < 0)
	{
		printf ("Send failed.\n");
		return (1);
	}
	
	printf ("data send: %i, %s, %i\n", sockfd, stuff, strlen (stuff));
}		

void	parse_message 	(int sockfd, char *line, fd_set *read_fds)
{
	if (FD_ISSET (sockfd, read_fds))
    {
		if (readln (sockfd, line) > 0)
		{
			printf ("%s\n", line);
		}
		else
		{
			close (sockfd);
		}
	}
}

char	*readln 	(int sockfd, char *line)
{
	char ch = 0;
	int	i = 0;
	
	do
	{
		if (read (sockfd, &ch, 1) < 1)
			return (0);
		if (i < 524 - 1)
			line[i++] = ch;
	}
	while (ch != '\n');
	line[i] = '\0';
	return (line);
}

void
prepare_bot ()
{
	int esc = 0;

	while (!esc)
	{
		/* Load servers here */
		
		printf (".: Connecting to %s:%ld\t\r", HOSTNAME, PORT);
		fflush (stdout);
		sleep (2);

		sockfd = create_connection (HOSTNAME, VHOST, PORT);

		switch (sockfd)
		{

			case ERR_TIMED_OUT:
				printf (".: Connection to %s:%ld timed out!\t\r", HOSTNAME, PORT);
				fflush (stdout);
				sleep (2);
				break;

			case ERR_CONN_REFUSED:
				printf (".: Connection to %s:%ld was refused!\t\r", HOSTNAME, PORT);
				fflush (stdout);
				sleep (2);
				break;

			case ERR_NOT_ADDR:
				printf ("Address not in range!\n");
				exit (1);

			case ERR_NO_REACH:
				printf ("Address not reachable!\n");
				exit (1);

			default:
				esc = 1;
				printf
					(".: Connected to %s:%ld! [%ld]\t\r", HOSTNAME, PORT, (long) getpid ());

				fflush (stdout);
				sleep (5);
				break;
		}
	}

	/* set the socket to BLOCK */
	if (fcntl (sockfd, F_SETFL, 0) < 0)
	{
		printf ("\n");
		perror ("fcntl");
		exit (EXIT_FAILURE);
	}
}

int
create_connection (char *server, char *virtualhost, long port)
{
	struct	sockaddr_in		name;
	struct	hostent			*hostname;
	struct	timeval			timeout;
	fd_set					set;
	int						sock = 0, vhost = 1, sockerr = 0,
							optlen = sizeof (sockerr);

	if ((!virtualhost) || (strlen (virtualhost) < 1))
		vhost = 0;

	if ((sock = socket (AF_INET, SOCK_STREAM, 0)) < 0)
		return -1;

	memset (&name, 0, sizeof (struct sockaddr_in));

	setsockopt (sock, SOL_SOCKET, SO_LINGER, 0, 0);
	setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, 0, 0);
	setsockopt (sock, SOL_SOCKET, SO_KEEPALIVE, 0, 0);

	name.sin_family = AF_INET;
	name.sin_addr.s_addr = (vhost ? inet_addr (virtualhost) : INADDR_ANY);

	if ((name.sin_addr.s_addr == -1) && vhost)
	{
		hostname = gethostbyname (virtualhost);
		if (hostname)
		{
			name.sin_addr = *(struct in_addr *) hostname->h_addr;
		}
		else
		{
			name.sin_addr.s_addr = INADDR_ANY;
		}
	}
	if (bind (sock, (struct sockaddr *) &name, sizeof (struct sockaddr_in)) < 0)
	{
		printf ("\n");
		perror ("bind");
		close (sock);
		exit (EXIT_FAILURE);
	}

	memset (&name, 0, sizeof (struct sockaddr_in));
	name.sin_family = AF_INET;
	name.sin_port = htons (port);

	if(!(hostname = gethostbyname (server)))
	{
		printf ("\n");
		herror ("hostname");
		exit (EXIT_FAILURE);
	}

	name.sin_addr = *(struct in_addr *) hostname->h_addr;

	/* set the file descriptor to non blocking mode so that connect()
	   returns immediately.
	 */

	if (fcntl (sock, F_SETFL, O_NONBLOCK) < 0)
	{
		printf ("\n");
		perror ("fcntl");
		exit (EXIT_FAILURE);
	}
	
	if (connect (sock, (struct sockaddr *) &name, sizeof (name)) < 0)
	{
		if ((errno != EINPROGRESS) && (errno != ENOENT))
		{
			printf ("\n");
			perror ("connect");
			return (-1);
		}
	}
	
	alarm (0);

	while (1)
	{
		/* set the timeout */
		timeout.tv_sec = CONNECT_WAIT_TIMEOUT;
		timeout.tv_usec = 0;

		/* set the file descriptor to be empty */
		FD_ZERO (&set);

		/* add our socket to the file descriptor set */
		FD_SET (sock, &set);

		/* select will let us know when our socket is ready (connected) */
		switch (select (FD_SETSIZE, (fd_set *) 0, &set, (fd_set *) 0, &timeout))
		{
				/* if select returns 0, our timeout was reached */
			case 0:
				alarm (AIL);
				return ERR_TIMED_OUT;

				/* -1 means we are not connected */
			case -1:
				break;

				/* we MIGHT be connected */
			default:

				/* get the socket errno so we can check if we are connected */
				switch (getsockopt (sock, SOL_SOCKET, SO_ERROR, &sockerr, &optlen))
				{
					case -1:
						alarm (AIL);
						return ERR_SOCK_OPT;

					case 0:
						switch (sockerr)
						{
							case ECONNREFUSED:
								alarm (AIL);
								return ERR_CONN_REFUSED;

							case EADDRNOTAVAIL:
								alarm (AIL);
								return ERR_NOT_ADDR;

							case ENETUNREACH:
								alarm (AIL);
								return ERR_NO_REACH;

							case SUCCESS:
								alarm (AIL);
								return sock;
						}
				}
		}
	}
}

	