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
	
	/* Strip the leading ':' off the sender. */
	if (*who == ':')
		who++;
	
	rest = strtok (NULL, "");
	if (rest == NULL)	return;
	
	/* Run through the server command structure in case this 
	 * is a command from the server. */
	
	 if (try_server_command(who, rest) == 1)
		return;
	
	/* Check if originating from a another client, this will
	   will be a ron!ron@ron.com type userhost if so and 
	   contain the ! character, otherwise, pass through to 
	   next check. 
	 */
	 
	if (strstr (who, "!") == NULL)
	{
		cmd = strtok (rest, " ");
		if (cmd == NULL)
			return;
		rest = strtok (NULL, "");
	}
	/* Try again. We get this sometimes, certain messages from
	 * server do not include a trailing sender token. We parse
	 * through and find these messages first, after they are taken
	 * care of, we check for other commands that originate from	
	 * a specific sender. */
	if (try_server_command(who, rest) == 1)
		return;

	printf ("cmd = %s, who = %s, rest = %s\n", cmd, who, rest);
}