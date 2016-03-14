/* Functions */

#include "includes.h"

void	stripline (char *ptr)
{
        for (; ptr && *ptr; ++ptr)
        {
                if ('\r' == *ptr || '\n' == *ptr)
                {
                        *ptr = 0;
                        return;
                }
        }
}

int
stricmp (const char *s1, const char *s2)
{
        register int c = 0;

        while ((c = tolower (*s1)) == tolower (*s2))
        {
                if (c == 0)
                        return 0;
                s1++;
                s2++;
        }
        if (c < tolower (*s2))
                return -1;
        return 1;
}

char	*get_word		(int num, char *str, int sep)
{
	char 	*ptr = NULL;
	int 	i = 0, j = 0;
	int		sepcount = 0;
	
	if ((ptr = malloc (sizeof (str))) == NULL)
	{
		printf ("Memory allocation failure in get_word\n");
		exit (EXIT_FAILURE);
	}
	
	for (i = 0, j = 0; str[i]; i++, j++)
	{
		if (str[i] == sep)
		{
			sepcount++;
			j = 0;
			i++;
		}

		if (sepcount == num)
			return (ptr);

		ptr[j] = str[i];
	}
	return (ptr);
}


	
	