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

void		parse_join			(int fs, char *cmd, char *who, char *rest)
{
	/* Do the add_user in here somewhere */
	

}

void		parse_who			(int fs, char *cmd, char *who, char *rest)
{
	/* Do the add_user in here somewhere too. */
}