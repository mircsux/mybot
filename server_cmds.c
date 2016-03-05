/* Commands from servers. */

#include "includes.h"


struct {
	char	*cmd;
	void	(*func)(char *, char *);
}   server_command[] =
{
	{ "PING", 			parse_ping				},
	{  NULL	,			NULL					}
};

int		try_server_command		(char *who, char *rest)
{
	int		i = 0;

	if (*who == ':')
		who++;
	
	for (i = 0; server_command[i].cmd; i++)
	 {
		if (stricmp (who, server_command[i].cmd) == 0)
		{
				server_command[i].func (who, rest);
				/* Success */
				return (1);
		}
	 }
	 return (0);
 }
void		parse_ping			(char *who, char *rest)
{
		/* Return fire with a pong. */
#ifdef	DEBUG
		printf ("parse_ping(who: %s rest: %s\n", who, rest);
#endif
		if (*rest == ':')
			rest++;
		S ("PONG :%s\n", rest);

}