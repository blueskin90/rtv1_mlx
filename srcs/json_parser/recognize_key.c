
#include "json_parser.h"

char	*recognize_key(int *i, t_elem *current, char *line)
{
	int		quote;
	int		len;

	len = 0;
	quote = 0;
	if (line[*i] != "\"")
		return (0);
	else
		quote = 1;
	while (len != '\0' && len != '\"')
			len++;

	
}
