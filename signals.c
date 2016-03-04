/* Signals */

#include "includes.h"


void		sig_alrm (int unused)
{
	alarmed = 1;
	alarm (AIL);
}

void		sig_segv (int unused)
{
	long	p = 0;
	
	/* Grab our pid number */
	p = getpid ();
	
	printf (".: Aborting process %ld, SIG_SEGV.\n", p);
	
	if (fork () > 0)
	{
		kill (p, 3); /* SIGQUIT - terminate process and dump core. */
		kill (p, 9); /* SIGKILL */
	}
	exit (0);
}

void	sig_hup 	(int unused)
{
	printf (".: SIGHUP - Restarting the program.\n");
	exit (0);
}