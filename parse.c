/* Parse.c */

#include "includes.h"

void
parse_server_message (fd_set * read_fds)
{
        if (FD_ISSET (sockfd, read_fds))
        {
                if (readln ())
                {
                        parse (myline);
                }
                else
				{
					close (sockfd);
				}
		}
}

void		parse		(char	*line)
{	
	char	*who = NULL;
	char	*cmd = NULL;
	char	*rest = NULL;
	int		i = 0;

	stripline (line); /* Strip junk we don't need */

	/* If we have nothing for the first token?? wtf? return. */
	if ((who = strtok (line, " ")) == NULL)
		return;
	
	rest = strtok (NULL, "");
	if (rest == NULL)	return;
	
	/* Run through the server command structure in case this 
	 * is a command from the server. */
	
	 if (try_server_command(who, rest) == 1)
		return;
	
	if (*who == ':')
		*who++;
	
	if (strstr (who, "!") == NULL)
	{
		cmd = strtok (rest, " ");
		if (cmd == NULL)
			return;
		rest = strtok (NULL, "");
		printf ("parse(cmd = %s, rest = %s\n", cmd, rest);
	}
	/* Try again */
	if (try_server_command(who, rest) == 1)
		return;

	printf ("cmd = %s, who = %s, rest = %s\n", cmd, who, rest);
}