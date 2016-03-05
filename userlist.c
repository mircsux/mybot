/* Anything pertaining to the Internet User List (IUL) */

#include "includes.h"


void	add_user		(char *chan, char *nick, char *uh, long tog)
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
