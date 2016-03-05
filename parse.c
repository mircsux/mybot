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
	int		from_server = 0;
	
	stripline (line); /* Strip junk we don't need */

	/* If we have nothing for the first token?? wtf? return. */
	if ((who = strtok (line, " ")) == NULL)
		return;
	
	/* Strip the leading ':' off the sender. */
	if (*who == ':')
		who++;
	
	rest = strtok (NULL, "");
	if (rest == NULL)	return;
	
	from_server = YES;
	/* Run through the server command structure in case this 
	 * is a command from the server. */
	
	 if (try_server_command(from_server, who, who, rest) == 1)
		return;
	
	/* If this check is true, the message came from either
	   ourselves or a server. */
	if (strstr (who, "!") == NULL)
	{
		cmd = strtok (rest, " ");
		if (cmd == NULL)
			return;
		rest = strtok (NULL, "");
		if (strstr (who, ".") == NULL)
			from_server = 0;
		else from_server = 1;
		
		if (try_server_command(from_server, cmd, who, rest) == 1)
		return;
	}
	else
	{
		cmd = strtok (rest, " ");
		if (cmd == NULL)
			return;
		rest = strtok (NULL, "");
		if (try_server_command(NO, cmd, who, rest) == 1)
			return;
	}
	
	printf ("cmd = %s, who = %s, rest = %s\n", cmd, who, rest);
}