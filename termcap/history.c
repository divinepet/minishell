#include "../liba.h"

t_history	*create_elem(char *str)
{
	t_history	*temp;

	temp = malloc(sizeof(t_history));
	temp->str = ft_strdup(str);
	temp->next = NULL;
	temp->prev = NULL;
	return (temp);
}

void	add_elem(char *str, t_history **hst)
{
	t_history	*current;
	t_history	*temp;

	current = *hst;
	if (!current)
	{
		*hst = create_elem(str);
		return ;
	}
	temp = create_elem(str);
	temp->next = current;
	current->prev = temp;
	*hst = temp;
}

void	add_to_history(t_hst_data *hst, char **res, t_history *tmp)
{
	char	*buf;
	int		fd;

	if (hst->flag_hst)
	{
		buf = *res;
		*res = ft_strjoin(tmp->str, *res);
		free(buf);
	}
	if (!hst->count_hst++)
		hst->hst = create_elem(*res);
	else
		add_elem(*res, &hst->hst);
	free(hst->str);
	fd = open("./termcap/history", O_CREAT | O_RDWR | O_APPEND, \
									S_IRWXO | S_IRWXG | S_IRWXU);
	write(fd, hst->hst->str, ft_strlen(hst->hst->str) + 1);
	write(fd, "\n", 2);
	close(fd);
}

t_history	*create_history(char *str, char **res, \
					t_hst_data *hst, t_history *tmp)
{
	char	*temp;

	if (!hst->flag_hst && hst->str)
	{
		temp = *res;
		if (!*res)
			*res = ft_strdup(hst->str);
		else
			*res = ft_strjoin(hst->str, *res);
		free(temp);
	}
	if (hst->str)
	{
		free(hst->str);
		hst->str = NULL;
	}
	write(1, "\n", 2);
	if (!ft_strcmp(str, "\n") && *res != NULL)
		add_to_history(hst, &*res, tmp);
	else if (hst->flag_hst && *res == NULL)
		add_elem(tmp->str, &hst->hst);
	return (hst->hst);
}

void	load_from_file(t_hst_data **hst)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open("./termcap/history", O_RDWR, S_IREAD);
	while (get_next_line(fd, &line) > 0)
	{
		if ((*hst)->count_hst++ == 0)
			(*hst)->hst = create_elem(line);
		else
			add_elem(line, &(*hst)->hst);
		free(line);
		line = 0;
	}
	free(line);
	line = 0;
	close (fd);
}
