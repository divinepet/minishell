#include "../liba.h"

char	*check_memmory(char **memmory, char **line)
{
	char	*pointer;

	pointer = NULL;
	if (*memmory)
	{
		pointer = ft_strchr(*memmory, '\n');
		if (pointer)
		{
			*pointer = '\0';
			*line = ft_strdup(*memmory);
			ft_strcpy(*memmory, ++pointer);
		}
		else
			*line = ft_strdup(*memmory);
	}
	else
	{
		*line = ft_strdup("");
	}
	return (pointer);
}

int	ft_errors(int res, char **pointer, char **memmory)
{
	if (res >= 1 && !(*memmory) && !(*pointer))
	{
		free(*memmory);
		*memmory = NULL;
		return (-1);
	}
	if (res)
		return (1);
	else
	{
		free(*memmory);
		*memmory = NULL;
		return (0);
	}
}

void	free_line(char **line, char **buf)
{
	char	*temp;

	temp = *line;
	*line = ft_strjoin(*line, *buf);
	free(temp);
}

void	help_function(char **pointer, char **memmory)
{
	char	*temp;

	**pointer = '\0';
	temp = ft_strdup(++*pointer);
	free(*memmory);
	*memmory = temp;
}

int	get_next_line(int fd, char **line)
{
	static char		*memmory;
	char			*pointer;
	char			*buf;
	int				res;

	buf = (char *)malloc(BUFFER_SIZE + 1);
	pointer = check_memmory(&memmory, &*line);
	if (BUFFER_SIZE < 1 || fd < 0 || \
			(read(fd, buf, 0) == -1))
		return (-1);
	if (buf == NULL)
		return (-1);
	res = 1;
	while (!pointer && res > 0)
	{
		res = read(fd, buf, BUFFER_SIZE);
		buf[res] = '\0';
		pointer = ft_strchr(buf, '\n');
		if (pointer)
			help_function(&pointer, &memmory);
		free_line(&*line, &buf);
	}
	free(buf);
	buf = NULL;
	return (ft_errors(res, &pointer, &memmory));
}
