#include "../liba.h"

void	bin_commands_modified(t_env *env, char *command, t_parse_data *data)
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
		if (!try_to_open_modified(&*paths, data, -1, 0))
		{
			if (data->args_for_cmd[0] == NULL)
				data->args_for_cmd[0] = ft_strdup("");
			data->isError = print_error(1, 127, data->args_for_cmd[0], "");
		}
		free(val);
		free_double_array(&*paths);
	}
}

void	viborka_modified(t_env *env, t_parse_data *data, \
			char *buffer, char *command)
{
	if (data->quotes)
		printf("multiline command, try again\n");
	else if (data->pipe_flag)
		pipe_check(buffer, env, data);
	else if (data->redirect_type)
		redirecting(buffer, env, data);
	else if (!ft_strcmp(command, "echo") || !cmpp(command, "ECHO"))
		my_echo(data);
	else if (!ft_strcmp(command, "env") || !cmpp(command, "ENV"))
		my_env(env);
	else if (!ft_strcmp(command, "export"))
		my_export(env, data);
	else if (!ft_strcmp(command, "unset"))
		my_unset(env, data);
	else if (!ft_strcmp(command, "pwd") || !cmpp(command, "PWD"))
		my_pwd(env);
	else if (!ft_strcmp(command, "cd"))
		my_cd(env, data);
	else if (!ft_strcmp(command, "exit"))
		my_exit(data);
	else if (ft_strchr(command, '/'))
		sh_open_modified(env, data);
	else
		bin_commands_modified(env, command, data);
}

void	free_and_errors_modified(t_parse_data *data, char **cmd, \
								int flag, char **buf)
{
	if (data->status != 0)
	{
		g_global_error = data->status % 255;
		data->isError = 1;
	}
	if (data->isError != 1)
		g_global_error = 0;
	free(*cmd);
	if (flag)
		free(*buf);
}

void	command_parse_modified(char *buffer, t_env *env, t_parse_data *data)
{
	char	*command;
	int		flag;

	flag = 0;
	if (*buffer == '\0')
	{
		data->isError = print_error(8, 258, "", "");
		return ;
	}
	if (ft_strchr(buffer, '$'))
	{
		flag = 1;
		buffer = env_parse(env, buffer);
	}
	data->args_for_cmd = split_in_args(buffer, -1, 0, 0);
	command = command_cutter(buffer);
	viborka_modified(env, data, buffer, command);
	free_and_errors_modified(data, &command, flag, &buffer);
}

void	pre_parse_modified(char *s, t_env *env, t_parse_data *data)
{
	char	*buffer;

	if (ft_strchr(s, '~'))
	{
		buffer = tilda_parse(env, s);
		command_parse_modified(buffer, env, data);
		free(buffer);
	}
	else
		command_parse_modified(s, env, data);
}
