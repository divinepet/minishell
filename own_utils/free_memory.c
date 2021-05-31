#include "../liba.h"

void	free_struct(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		free((*env)->key);
		free((*env)->value);
		*env = (*env)->next;
		free(tmp);
	}
	free(*env);
}

void	free_redirect_struct(t_redirect **re)
{
	free((*re)->args);
	free((*re)->files);
	free((*re)->command);
	free((*re)->spec_file);
	free(*re);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}

void	free_data_struct(t_parse_data **data)
{
	int	i;

	i = 0;
	if ((*data)->envp_array)
		free_double_array(&*((*data)->envp_array));
	if ((*data)->args_for_cmd)
		free_double_array(&*((*data)->args_for_cmd));
	free(*data);
}

void	free_redirect_args(char **s)
{
	char	*tmp;

	tmp = *s;
	*s = ft_calloc(1000, sizeof(char));
	free(tmp);
}
