#include "../liba.h"

void	my_unset(t_env *env, t_parse_data *data)
{
	int		i;
	char	*tmp;

	while (data->args_for_cmd[i] != NULL)
	{
		if (!isForbiddenEnviroment(data->args_for_cmd[i]))
			data->isError = print_error(5, 1, data->args_for_cmd[i], "unset");
		else
			deleteKey(&env, data->args_for_cmd[i]);
		i++;
	}
}
