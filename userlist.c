/* Anything pertaining to the Internet User List (IUL) 
 * or the Internal Server List (ISL) or any other 
   list that is kept in memory for further use. */

#include "includes.h"


void	add_iul_user		(char *chan, char *nick, char *uh, long tog)
{
	/* If 0 tog, just unidle the client */
	struct	IUL 	*n, *c;
	
	c = iulhead;
	
	if (strlen (uh) > 399)
		uh[399] = '\0';
	
	while (c)
	{
		if (tog == 0)
		{
			if (stricmp (c->nick, nick) == 0 && stricmp (c->chan, chan) == 0)
			{
				c->idle = time (NULL);
			}
		}
		else
		if (tog == 1)
		{
			if (stricmp (c->nick, nick) == 0 && stricmp (c->chan, chan) == 0)
			{
				/* If user is already here, overwrite him */
				strncpy (c->chan, chan, sizeof (c->chan));
				strncpy (c->uh, uh, sizeof (c->uh));
				strlwr  (c->uh);
				strncpy (c->nick, nick, sizeof (c->nick));
				c->idle = time (NULL);
				c->level = 0;
				return;
			}
		}
		c = c->next;
	}
	if (tog == 0)
	{
		/* NO need to do anything. */
	}
	
	n = malloc (sizeof (struct IUL));
	if (n == NULL)
	{
		printf ("No RAM left!\n");
		return;
	}
	
	memset (n, 0, sizeof (struct IUL));
    if (n != NULL)
    {
		strncpy (n->chan, chan, sizeof (n->chan));
        strncpy (n->uh, uh, sizeof (n->uh));
        strlwr (n->uh);
        strncpy (n->nick, nick, sizeof (n->nick));
        n->idle = time (NULL);
        n->level = 0;
        n->next = iulhead;
        iulhead = n;
        }
}

void		del_iul_user (const char *nick, char *chan)
{
	struct IUL *pNode, *pPrev;

	pNode = iulhead;
	pPrev = NULL;

	while (pNode)
	{
		if (stricmp (pNode->nick, nick) == 0 && stricmp (pNode->chan, chan) == 0)
		{
/*			save_seen (pNode->nick, pNode->uh, pNode->chan); */
			if (pPrev != NULL)
			{
				pPrev->next = pNode->next;
			}
			else
			{
				iulhead = pNode->next;
			}
			free (pNode);
			pNode = NULL;
			break;
		}
		pPrev = pNode;
		pNode = pNode->next;
	}
}

void	add_isl_server 		(char *line)
{
	struct	ISL  *isl;
	
	if (line == NULL)
		return;
	
	if ((isl = malloc (sizeof (struct ISL))) == NULL)
	{
		printf ("Out of memory in add_isl_server().\n");
		return;
	}
	
	memset (isl, 0, sizeof (struct ISL));
	
	if (isl != NULL)
	{
		char 	*server = NULL, *pass = NULL;
		char	*ptr = NULL;
		long 	port = 0;
		
		/* Set server var, followed by others */
		if ((server = strtok (line, ":")) == NULL)
			return;
		/* Port */
		if ((ptr = strtok (NULL, ":")) == NULL)
			return;
		if ((port = strtol (ptr, (char **) NULL, port)) < 1)
			return;
		/* Pass */
		pass = strtok (NULL, "");

		strncpy (isl->server, server, sizeof (isl->server));
		isl->port = port;
		if (pass != NULL)
			strncpy (isl->pass, pass, sizeof (isl->pass));
		isl->next = isl;
	}
}

void	do_add_servers 		(char *line)
{
	char 	*server = NULL, *pass = NULL;
	char 	*ptr = NULL, *ptr2 = NULL;
	long	port = 0;
	int i = 0;

	if ((ptr = malloc (STRING_LONG)) == NULL)
		return;
	if ((pass = malloc (STRING_LONG)) == NULL)
		return;
	if ((ptr2 = malloc (STRING_LONG)) == NULL)
		return;
	
	do
	{
		i++;
		if ((ptr = get_word (i, line, ',')) != NULL)
		{
			if ((server = get_word (1, ptr, ':')) == NULL)
				return;
			ptr2 = get_word(2, ptr, ':');
			pass = get_word(3, ptr, ':');
			printf ("server = %s\n", server);
			printf ("ptr2 = %s\n", ptr2);
			printf ("pass = %s\n", pass);
			
			
		}
	}
	while (ptr != NULL);
}
