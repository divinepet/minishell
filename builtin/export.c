#include "../liba.h"

void	add_to_env(t_env **env, char *str, int hidden)
{
	char	*tmp;

	if (hidden == 0)
	{
		tmp = ft_substr(str, '=');
		add_env(&*env, tmp, (ft_strchr(str, '=') + 1), 0);
		free(tmp);
	}
	else if (hidden == 1)
		add_env(&*env, str, "", 1);
}

void	my_export_with_arguments(t_env *env, t_parse_data *data)
{
	int		i;
	int		k;

	i = 1;
	k = 0;
	while (data->args_for_cmd[i] != NULL)
	{
		k = isForbiddenEnviroment(data->args_for_cmd[i]);
		if (!k)
			data->isError = print_error(5, 1, data->args_for_cmd[i], "export");
		else if (k == 1)
			add_to_env(&env, data->args_for_cmd[i], 0);
		else if (k == 2)
			add_to_env(&env, data->args_for_cmd[i], 1);
		i++;
	}
}

void	my_export(t_env *env, t_parse_data *data)
{
	int		i;
	int		row;
	t_env	*env_copy;

	env_copy = sort_export(env);
	row = 0;
	i = 0;
	if (data->args_for_cmd[1] == NULL)
	{
		while (env_copy)
		{
			if (env_copy->hidden == 1)
				printf("declare -x %s\n", env_copy->key);
			else
				printf("declare -x %s=\"%s\"\n", env_copy->key, env_copy->value);
			env_copy = env_copy->next;
		}
	}
	else
		my_export_with_arguments(env, data);
}
