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
