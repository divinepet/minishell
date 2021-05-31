#include "../liba.h"

void	sh_open_modified(t_env *env, t_parse_data *data)
{
	char		**args;
	struct stat	buf;

	data->envp_array = envp_to_double_array(env);
	if (stat(data->args_for_cmd[0], &buf) != 0)
		data->isError = print_error(2, 127, data->args_for_cmd[0], "");
	else
	{
		if (buf.st_mode == 33261 || buf.st_mode == 33133)
			execve(args[0], data->args_for_cmd, data->envp_array);
		else if (S_ISDIR(buf.st_mode))
			data->isError = print_error(3, 126, data->args_for_cmd[0], "");
		else
			data->isError = print_error(4, 126, data->args_for_cmd[0], "");
	}
}

int	try_to_open_modified(char **paths, t_parse_data *data, int i, int flag)
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
			signal_use();
			execve(path, data->args_for_cmd, data->envp_array);
		}
		free(path);
		free(tmp);
	}
	return (flag);
}
