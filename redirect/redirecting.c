#include "../liba.h"

void	output(t_redirect *re, t_env *env, t_parse_data *data)
{
	char	*buffer;

	buffer = ft_strjoin(re->command, re->args);
	if (!fork())
	{
		if (re->fd_copy != 0)
			dup2(re->fd_copy, 0);
		if (re->fd != 0)
			dup2(re->fd, 1);
		if (*buffer != '\0')
			pre_parse(buffer, env, data);
		close(re->fd);
		exit(0);
	}
	wait(&data->status);
	free(buffer);
}

/*
*	Функция для чтения из файла в поток
*/
void	redirecting_output(t_redirect *re, t_env *env, t_parse_data *data)
{
	char	**array_of_files;
	int		i;

	i = 0;
	array_of_files = ft_split(re->files, ' ');
	while (array_of_files[i] != NULL)
	{
		re->fd_copy = open(array_of_files[i++], O_RDONLY);
		if (re->fd_copy < 0)
		{
			re->spec_file = ft_strdup(array_of_files[i - 1]);
			break ;
		}
	}
	free_double_array(&*array_of_files);
}

void	fill_data(t_redirect *re, char *str, t_env *env, t_parse_data *data)
{
	int	k;

	k = get_command(re, str, k);
	while (str[k] != '\0')
	{
		while (str[k] != -1 && str[k] != -2 && str[k] != -3 && str[k] != '\0')
			re->args[re->i++] = str[k++];
		if (str[k] == -1 || str[k] == -2 || str[k] == -3)
		{
			if (re->redirect == -3 && re->files)
				redirecting_output(re, env, data);
			re->redirect = str[k];
		}
		k += 1;
		while (str[k] != ' ' && str[k] != '\0' && str[k] != -1 \
							&& str[k] != -2 && str[k] != -3)
			re->files[re->j++] = str[k++];
		re->files[re->j++] = ' ';
		if (re->command[0] == '\0')
			k = get_command(re, str, k + 1);
	}
	if (re->redirect == -3 && re->files)
		redirecting_output(re, env, data);
}

void	redirecting(char *str, t_env *env, t_parse_data *data)
{
	t_redirect	*re;
	char		*s;
	int			a1;
	int			a2;

	data->redirect_type = 0;
	redirect_struct_init(&re);
	s = new_str(str, 0, 0);
	fill_data(re, s, env, data);
	a1 = search_errors_in_args(re, data);
	a2 = search_errors_in_fd(re, data);
	if (!a1 && !a2)
		output(re, env, data);
	else
		g_global_error = 1;
	if (s)
		free(s);
	free_redirect_struct(&re);
}
