#include "liba.h"

void	viborka(t_env *env, t_parse_data *data, char *buffer, char *command)
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
		sh_open(env, data);
	else
		bin_commands(env, command, data);
}

void	command_parse(char *buffer, t_env *env, t_parse_data *data)
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
	viborka(env, data, buffer, command);
	free_and_errors(data, &command, flag, &buffer);
}

void	pre_parse(char *s, t_env *env, t_parse_data *data)
{
	char	*buffer;

	if (ft_strchr(s, '~'))
	{
		buffer = tilda_parse(env, s);
		command_parse(buffer, env, data);
		free(buffer);
	}
	else
		command_parse(s, env, data);
}

void	read_string(char *str, t_env *env, char *buffer, t_parse_data *data)
{
	while (str[data->i] != '\0')
	{
		if (str[data->i] == '|' && !(data->quotes))
			data->pipe_flag = pipe_ch_parse(&buffer, str, &data->i, &data->b);
		if ((str[data->i] == '<' || str[data->i] == '>' || \
		(str[data->i] == '>' && str[data->i + 1] == '>')) && !(data->quotes))
			data->redirect_type = rdr_parse(&buffer, str, &data->i, &data->b);
		else if (str[data->i] == '\'' || str[data->i] == '"')
		{
			quotes_parse_first(data, str, &data->i);
			buffer[data->b++] = str[data->i++];
		}
		else if (str[data->i] == ';' && !(data->quotes))
		{
			pre_parse(buffer, env, data);
			data->b = semicolon_parse(&data->i, &buffer, str);
		}
		else
			buffer[data->b++] = str[data->i++];
	}
	if (buffer[0] != '\0' || str[data->i - 1] != ';')
		pre_parse(buffer, env, data);
}

void	delete_spaces_and_quotes(char *str, t_env *env, t_hst_data *history)
{
	char			*s;
	char			*buffer;
	char			*tmp;
	t_parse_data	*data;
	char			*ahhh;

	parse_data_struct_init(&data);
	data->status = 0;
	turn_signals(&*history, 1);
	buffer = ft_calloc(1000, sizeof(char));
	tmp = deleteSpaces(str, 0, 0);
	s = ft_strtrim(tmp, " ");
	read_string(s, env, buffer, data);
	free_data_struct(&data);
	turn_signals(&*history, 0);
	free(s);
	free(tmp);
	free(buffer);
}
