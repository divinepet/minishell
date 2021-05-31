#include "liba.h"

int	tryToOpen(char **paths, t_parse_data *data, int i, int flag)
{
	char		*tmp;
	char		*path;
	struct stat	buf;

	while (paths[++i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, data->args_for_cmd[0]);
		stat(path, &buf);
		if ((buf.st_mode == 33261 || buf.st_mode == 33133) && flag == 0)
		{
			flag = 1;
			if (!fork())
			{
				ft_signal_child_process();
				signal_use();
				execve(path, data->args_for_cmd, data->envp_array);
			}
			wait(&data->status);
		}
		free(path);
		free(tmp);
	}
	return (flag);
}

void	bin_commands(t_env *env, char *command, t_parse_data *data)
{
	char	**paths;
	char	*val;

	if (data->args_for_cmd[0] == NULL)
		data->isError = print_error(1, 127, "", "");
	else
	{
		val = get_value_for_key(env, "PATH");
		if (val == NULL)
		{
			data->isError = print_error(2, 127, command, "");
			return ;
		}
		data->envp_array = envp_to_double_array(env);
		paths = ft_split(val, ':');
		if (!tryToOpen(&*paths, data, -1, 0))
		{
			if (data->args_for_cmd[0] == NULL)
				data->args_for_cmd[0] = ft_strdup("");
			data->isError = print_error(1, 127, data->args_for_cmd[0], "");
		}
		free(val);
		free_double_array(&*paths);
	}
}

void	sh_open(t_env *env, t_parse_data *data)
{
	struct stat	buf;

	data->envp_array = envp_to_double_array(env);
	if (stat(data->args_for_cmd[0], &buf) != 0)
		data->isError = print_error(2, 127, data->args_for_cmd[0], "");
	else
	{
		if (buf.st_mode == 33261 || buf.st_mode == 33133)
		{
			if (!fork())
				execve(data->args_for_cmd[0], data->args_for_cmd, \
						data->envp_array);
			wait(&data->status);
		}
		else if (S_ISDIR(buf.st_mode))
			data->isError = print_error(3, 126, data->args_for_cmd[0], "");
		else
			data->isError = print_error(4, 126, data->args_for_cmd[0], "");
	}
}
