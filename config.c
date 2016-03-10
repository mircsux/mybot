/* Stuff involving config files */

#include "includes.h"

extern	Config *config;

void		load_config		(char *file)
{
	
	FILE		*fp = NULL;
	
	config = malloc (sizeof (Config));
	
	if (config == NULL)
	{
		printf ("Out of memory in load_config()\n");
		exit (EXIT_FAILURE);
	}
	/* Exit out if we can't open the file, no use in 
	   lollygagging around. */
	if ((fp = fopen (file, "r")) == NULL)
	{
		printf ("Failed to load config file (%s)", file);
		return;
	}
	
	strncpy (config->MYNICK, MYNICK, sizeof (config->MYNICK));
	
	printf ("config_array: MYNICK = %s\n", config->MYNICK);
}


