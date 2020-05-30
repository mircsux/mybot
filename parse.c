/* Parse.c */

#include "includes.h"
#include "prototypes.h"

void
parse_server_message (int sockfd, fd_set * read_fds)
{
        if (FD_ISSET (sockfd, read_fds))
        {
                if (readln (sockfd))
                {
                        parse (sockfd, myline);
                }
                else
				{
					close (sockfd);
				}
		}
}

void		parse(int sockfd, char	*line)
{
	char	*who = NULL;
	char	*cmd = NULL;
	char	*rest = NULL;
	int		from_server = YES;

	printf("line = %s\n", line);

	stripline(line); /* Strip junk we don't need */

	/* If we have nothing for the first token?? wtf? return. */
	if ((who = strtok(line, " ")) == NULL)
		return;

	/* Strip the leading ':' off the sender. */
	if (*who == ':')	who++;

	if ((rest = strtok(NULL, "")) == NULL)
		return;
	
	if ((cmd = strtok(rest, " ")) == NULL)
		return;
	
	if (strstr(who, "!") == NULL)
		from_server = YES;

	if ((rest = strtok(NULL, "")) == NULL)
		return;

	/* Check and see if we can execute this message as a server
	   command, drop through if not. */
	if (from_server == YES)
	{
	   	 if (try_server_command(from_server, cmd, who, rest) == 1)
			return;
	}
	
	/* Not from server, or command not found? */

}
