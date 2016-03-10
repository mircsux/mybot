/* Stuff involving config files */

#include "includes.h"

extern	Config *config;

#define		C_UNKNOWN		0
#define		C_MYNICK		1
#define		C_MYUSER		2

struct
{
	const	char	*opt;
	const	int		c_value;
}	cfg_opt [] =
{
	{	"BOTNICK",		C_MYNICK			},
	{   NULL,			0					}
};


int			do_config_set 		(int	opt, 	char *value)
{
	switch (opt)
	{
		case C_MYNICK:
		{
			printf ("value = %s\n", value);
			printf ("Set nick = %s\n", value);
			strncpy (config->MYNICK, value, sizeof (config->MYNICK));
			return (1);
		}
		default:
		{
			printf ("Invalid config setting\n");
			return (0);
		}
	}
}

void		load_config		(char *file)
{
	
	FILE		*fp = NULL;
	int			i = 0;
	char		str 	[STRING_LONG] = { "\0" };
	char		*opt = NULL, *value = NULL;
	
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
	
	/* Run a check here at some point to assure our
	   config file is formatted properly */
	   
	while (fgets (str, STRING_LONG, fp))
	{
		/* NULL lines or lines that don't do us any good?
		   Just ignore them. */
		if ((opt = strtok (str, "=")) == NULL)
			return;
		
		value = strtok (NULL, "");
		if (value != NULL)
			printf ("value = %s\n", value);
		
	
		for (i = 0; cfg_opt[i].opt != NULL; i++)
		{
			if (stricmp (opt, cfg_opt->opt) == 0)
			{
				if (do_config_set (cfg_opt->c_value, value) == 0)
				{
					printf ("Invalid option: %s\n", opt);
				}
			}	
		}
	}   /*End WHILE */
	
}

