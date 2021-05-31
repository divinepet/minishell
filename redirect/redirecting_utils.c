#include "../liba.h"

int	get_command(t_redirect *re, char *str, int k)
{
	int	i;

	i = 0;
	k = 0;
	while (ft_isalnum(str[k]) && str[k] != '\0')
		re->command[i++] = str[k++];
	return (k);
}

char	*new_str(char *str, int i, int k)
{
	char	*s;

	s = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i] != '\0')
	{
		if (str[i] == -1 || str[i] == -2 || str[i] == -3)
		{
			if (str[i + 1] == ' ')
			{
				s[k++] = str[i];
				i += 2;
				continue ;
			}
		}
		if (str[i + 1] == -1 || str[i + 1] == -2 || str[i + 1] == -3)
		{
			if (str[i] == ' ')
			{
				i++;
				continue ;
			}
		}
		s[k++] = str[i++];
	}
	return (s);
}

int	fd_cycle(char **array_of_files, int a, t_redirect *re)
{
	int	i;

	i = 0;
	while (array_of_files[i] != NULL)
		i++;
	if (re->redirect == -1)
		re->fd = open(array_of_files[i - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (re->redirect == -2)
		re->fd = open(array_of_files[i - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (re->fd < 0)
	{
		SHOW_PROMPT();
		printf("%s: %s\n", array_of_files[i - 1], strerror(errno));
		a = 2;
	}
	return (a);
}

int	search_errors_in_args(t_redirect *re, t_parse_data *data)
{
	int		i;

	i = 0;
	while (re->command[i] == ' ')
		i++;
	if (re->command[i] == '\0')
		free_redirect_args(&re->command);
	i = 0;
	while (re->args[i] == ' ')
		i++;
	if (re->args[i] == '\0')
		free_redirect_args(&re->args);
	i = 0;
	while (re->files[i] == ' ')
		i++;
	if (re->files[i] == '\0')
	{
		data->isError = print_error(6, 258, "", "");
		return (1);
	}
	return (0);
}

int	search_errors_in_fd(t_redirect *re, t_parse_data *data)
{
	char	**array_of_files;
	int		a;

	array_of_files = ft_split(re->files, ' ');
	a = 0;
	if (re->fd_copy < 0)
	{
		data->isError = print_error_r(re->spec_file, 1);
		a = 1;
	}
	if (re->redirect == -1 || re->redirect == -2)
		fd_cycle(array_of_files, a, re);
	free_double_array(&*array_of_files);
	if (a == 1)
		close(re->fd_copy);
	if (a == 2)
		close(re->fd);
	return (a);
}
