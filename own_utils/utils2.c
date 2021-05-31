#include "../liba.h"

char	**split_in_args(char *str, int i, int k, int quotes)
{
	char	**array;
	char	*buf;

	buf = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[++i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (quotes_parse_second(&quotes, str, i) == 1)
				continue ;
			else
				buf[k] = str[i];
		}
		if (str[i] == '\\')
			buf[k] = str[++i];
		else if (str[i] == ' ' && !quotes)
			buf[k] = -5;
		else
			buf[k] = str[i];
		k++;
	}
	array = ft_split(buf, -5);
	free(buf);
	return (array);
}
