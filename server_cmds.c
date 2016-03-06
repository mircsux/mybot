/* Commands from servers. */

#include "includes.h"


struct {
	char	*cmd;
	void	(*func)(int, char *, char *, char *);
}   server_command[] =
{
	{ "001", 			parse_001				},
	{ "JOIN", 			parse_join				},
	{ "MODE", 			parse_mode				},
	{ "PING", 			parse_ping				},
	{ "PRIVMSG",		parse_privmsg			},
	{  NULL	,			NULL					}
};

int		register_bot		(void)
{
	get_sendq_count (1);
	Snow ("NICK %s\n", MYNICK);
	Snow ("USER mybot %d %d :%s\n", time(NULL), time(NULL), PACKAGE_VERSION);
	return (1);
}

int		try_server_command		(int from_server, char *cmd, char *who, char *rest)
{
	int		i = 0;

	for (i = 0; server_command[i].cmd; i++)
	 {
		if (stricmp (cmd, server_command[i].cmd) == 0)
		{
				server_command[i].func (from_server, cmd, who, rest);
				/* Success */
				return (1);
		}
	 }
	 /* No match */
	 return (0);
}

void		parse_mode			(int from_server, char *cmd, char *who, char *rest)
{
	
} 

void		parse_privmsg		(int from_server, char *cmd, char *who, char *rest)
{
	printf ("hi\n");
}

void		parse_ping			(int from_server, char *cmd, char *who, char *rest)
{
		/* Return fire with a pong. */

		if (*rest == ':')
			rest++;
		S ("PONG :%s\n", rest);

}

void		parse_nick			(int fs, char *cmd, char *who, char *rest)
{
	printf ("hi(nick)\n");
}

void		parse_001			(int fs, char *cmd, char *who, char *rest)
{
	/* Use this to determine if we are successfully connected
	   to a server.*/
	   
	   S ("JOIN #poop\n");
}

void		parse_error			(int fs, char *cmd, char *who, char *rest)
{
	printf ("error\n");
}

void		parse_join			(int fs, char *cmd, char *who, char *rest)
{
	char	*chan = NULL;
	char	*nick = NULL;
	char	*uh = NULL;
	
	
	if (fs == NO)
	{
		if ((nick = strchr (who, '!')) != NULL)
			*nick++ = '\0';
		
		strlwr (nick);
		
		if ((uh = strtok (NULL, " ")) == NULL)
			return;
		
		if ((chan = strtok (rest, " ")) == NULL)
			return;
		/* This should be NULL, and is probably unnecessary. */
		rest = strtok (NULL, "");
		
		/* Check to see if this is ME joining, if it is not, 
		   update the internal user list with this user's
		   information. If this is me joining, retrieve a list
		   of channel users and update the internet user list
		   through parse_who. */
		   
		if (stricmp (nick, MYNICK) != 0)
		{	
			add_user (chan, nick, uh, 1);
		}
		else
		{
				S ("WHO %s\n", chan);
		}
		printf ("nick = %s, uh = %s, chan = %s, rest = %s\n",
					nick, uh, chan, rest);
					
	}
}

void		parse_who			(int fs, char *cmd, char *who, char *rest)
{
	/* Do the add_user in here somewhere too. */
}