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

	