/* Commands from servers. */

#include "includes.h"


struct {
	char	*cmd;
	void	(*func)(int, char *, char *, char *);
}   server_command[] =
{
	{ "001", 			parse_001				},
	{ "315", 			parse_end_of_who		},
	{ "352",			parse_who				},
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
	Snow ("USER mybot %d %d :test bot %s\n", time(NULL), time(NULL), PACKAGE_VERSION);
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
		/* This will mostly initiate the chanserv() function */
		
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

void		parse_end_of_who	(int fs, char *cmd, char *who, char *rest)
{
	BurstingWho = NO;
}

void		parse_join			(int fs, char *cmd, char *who, char *rest)
{
	char *uh = NULL, *nick = NULL;
	
	if (fs == NO)
	{
		if ((nick = strtok (who, "!")) == NULL)
			return;
		if ((uh = strtok (NULL, " ")) == NULL)
			return;
		printf ("uh = %s\n", uh);
		printf ("nick = %s\n", nick);
		/* Check to see if this is ME joining, if it is not, 
		   update the internal user list with this user's
		   information. If this is me joining, retrieve a list
		   of channel users and update the internet user list
		   through parse_who. */
		   
		if (stricmp (nick, MYNICK) != 0)
		{	
			/* Add this user to the internal user list if 
			   it's not me. And then return so we don't
			   /who the whole room, which may be unnecessary,
			   we shall see. */
        
			add_iul_user (rest, nick, uh, 1);
			return;
		}

		printf ("who the room\n");
		
		BurstingWho = YES;
		S ("WHO %s\n", rest);
	}
}

void		parse_who			(int fs, char *cmd, char *who, char *rest)
{
	char	*chan = NULL, *nick = NULL, *host = NULL, *ptr = NULL;
	char	str[STRING_SHORT] = {0};

	/* Sanity check for this var, probably not necessary */
	if (BurstingWho != YES)
		BurstingWho = YES;
	
	printf ("who: rest = %s\n", rest);
	/* Trap my nickname, we will update our nickname variable
	   incase our default name was rejected on connect, or 
	   another nickname was set. Maybe some other scenarios?
	   Check for NULL is probably unecessary. */
	nick = strtok (rest, " "); 
	if (nick == NULL) return;
	strncpy (MYNICK, nick, sizeof (MYNICK));
	chan = strtok (NULL, " ");
	if (chan == NULL) return;
	if ((ptr = strtok (NULL, " ")) == NULL) return;
	if ((host = strtok (NULL, " ")) == NULL) return;
	snprintf (str, sizeof (str), "%s@%s", ptr, host);
	nick = strtok (NULL, " "); /*server */
	nick = strtok (NULL, " ");
	/* Add user information to the internal user list, */
	add_iul_user (chan, nick, str, 1);
	
}