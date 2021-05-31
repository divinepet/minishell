#include "../liba.h"

void	my_env(t_env *env)
{
	while (env)
	{
		if (!env->hidden)
		{
			printf("%s=", env->key);
			printf("%s\n", env->value);
		}
		env = env->next;
	}
}
