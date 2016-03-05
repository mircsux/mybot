/* Parse.c */

#include "includes.h"

void
parse_server_message (int sockfd, char *line, fd_set * read_fds)
{
        if (FD_ISSET (sockfd, read_fds))
        {
                if ((readln (sockfd, line)) != NULL)
                {
                        parse (line);
                }
                else
				{
					close (sockfd);
				}
		}
}

void		parse		(char	*line)
{	
	
	printf ("line = %s\n", line);
}