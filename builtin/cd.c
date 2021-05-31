#include "../liba.h"

void	my_cd(t_env *env, t_parse_data *data)
{
	char	*path;
	int		res;
	char	oldpwd[1001];
	char	dir[1001];

	if (data->args_for_cmd[1] == NULL)
		path = get_value_for_key(env, "HOME");
	else
		path = ft_strdup(data->args_for_cmd[1]);
	getcwd(oldpwd, 1000);
	add_env(&env, "OLDPWD", oldpwd, 0);
	if (path == NULL)
		data->isError = print_error(10, 1, "", "cd");
	else
	{
		res = chdir(path);
		if (getcwd(dir, 1000) == NULL)
			write(2, "cd: error retrieving current directory: \
					getcwd: cannot access parent directories: \
					No such file or directory\n", 108);
		if (!res)
			add_env(&env, "PWD", dir, 0);
		else
			data->isError = print_error(2, 1, data->args_for_cmd[1], "cd");
		free(path);
	}
}
