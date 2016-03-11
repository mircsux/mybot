/* Stuff involving config files */

#include "includes.h"

#define		C_UNKNOWN		0
#define		C_BOTNICK		1
#define		C_BOTUSER		2
#define		C_BOTNAME		3
struct
{
	const	char	*opt;
	const	int		c_value;
}	cfg_opt [] =
{
	{	"BOTNICK",		C_BOTNICK			},
	{   "BOTUSER",		C_BOTUSER			},
	{   "BOTNAME",		C_BOTNAME			},
	{   NULL,			0					}
};

int			do_config_set 		(const  int	opt, 	char *value)
{
	switch (opt)
	{
		case C_BOTNICK:
		{
			Config *c = config;
			
			if (value == NULL)
				return (0);
			strncpy (c->BOTNICK, value, sizeof (config->BOTNICK));
			return (1);
		}
		
		case C_BOTUSER:
		{
			if (value == NULL)
			{
				printf ("NULL\n");
				return (1);
			}
			printf ("botuser val %s", value);
			strncpy (config->BOTUSER, value, sizeof (config->BOTUSER));
			return (1);
		}
		
		default:
		{
			printf ("Invalid config setting\n");
			return (0);
		}
	}
	return (0);
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
		stripline (str);
		/* NULL lines or lines that don't do us any good?
		   Just ignore them. */
		if ((opt = strtok (str, "=")) == NULL)
			return;
		
		value = strtok (NULL, "");
		if (value == NULL)
			return;
		
		for (i = 0; cfg_opt[i].opt; i++)
		{
			int	retval = 0;
			
			if (stricmp (opt, cfg_opt[i].opt) == 0)
			{
				retval = do_config_set (cfg_opt[i].c_value, value);
				printf ("retval = %d\n", retval);
			}	
		}
	}   /*End WHILE */
	
}

