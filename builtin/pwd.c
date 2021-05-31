#include "../liba.h"

void	my_pwd(t_env *env)
{
	char	*error;
	char	dir[1001];

	ft_memset(dir, '\0', 1000);
	error = getcwd(dir, 1000);
	if (error == NULL)
		printf("%s\n", get_value_for_key(env, "OLDPWD"));
	else
		printf("%s\n", dir);
}
