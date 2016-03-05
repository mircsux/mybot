/* Commands from servers. */

#include "includes.h"


void		parse_ping			(char *line)
{
		/* Return fire with a pong. */
		printf ("parse_ping: line = %s\n", line);
		S ("PONG :%s\n", line);
}