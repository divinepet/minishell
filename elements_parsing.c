#include "liba.h"

int	quotes_parse_second(int *quotes, char *str, int i)
{
	if (!*quotes)
	{
		*quotes = str[i];
		return (1);
	}
	else if (str[i] == *quotes)
	{
		*quotes = 0;
		return (1);
	}
	return (0);
}

int	quotes_parse_first(t_parse_data *data, char *str, int *i)
{
	if (!data->quotes)
		data->quotes = str[*i];
	else if (data->quotes == str[*i])
		data->quotes = 0;
	return (0);
}

int	semicolon_parse(int *i, char **buffer, char *str)
{
	*i += 1;
	while (str[*i] == ' ' || str[*i] == '\0')
	{
		if (str[*i] == '\0')
			break ;
		*i += 1;
	}
	ft_memset(*buffer, '\0', 1000);
	return (0);
}

int	rdr_parse(char **buffer, char *str, int *i, int *b)
{
	char	*buf;

	buf = *buffer;
	if (str[*i] == '<')
	{
		buf[*b] = -3;
		*b += 1;
	}
	else if (str[*i] == '>' && str[*i + 1] != '>')
	{
		buf[*b] = -1;
		*b += 1;
	}
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		buf[*b] = -2;
		*i += 1;
		*b += 1;
	}
	*i += 1;
	*buffer = buf;
	return (1);
}

int	pipe_ch_parse(char **buffer, char *str, int *i, int *b)
{
	char	*buf;

	buf = *buffer;
	if (str[*i] == '|')
	{
		buf[*b] = -4;
		*b += 1;
	}
	*i += 1;
	*buffer = buf;
	return (1);
}
