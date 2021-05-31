#include "../liba.h"

void	old_env(t_env *env)
{
	while (env)
	{
		(env)->toSort = 1;
		(env) = (env)->next;
	}
}

void	envpToStruct(t_env **env, char **ev)
{
	int		i;
	char	*tmp;

	i = 1;
	tmp = ft_substr(ev[0], '=');
	*env = create(tmp, (ft_strchr(ev[0], '=') + 1), 0);
	free(tmp);
	while (ev[i] != NULL)
	{
		tmp = ft_substr(ev[i], '=');
		add_env(&*env, tmp, (ft_strchr(ev[i], '=') + 1), 0);
		free(tmp);
		i++;
	}
	old_env(*env);
}

void	redirect_struct_init(t_redirect **re)
{
	*re = malloc(sizeof(t_redirect));
	(*re)->i = 0;
	(*re)->j = 0;
	(*re)->args = ft_calloc(1000, sizeof(char));
	(*re)->files = ft_calloc(1000, sizeof(char));
	(*re)->command = ft_calloc(1000, sizeof(char));
	(*re)->spec_file = NULL;
	(*re)->redirect = 0;
	(*re)->fd = 0;
	(*re)->fd_copy = 0;
}

void	parse_data_struct_init(t_parse_data **data)
{
	*data = malloc(sizeof(t_parse_data));
	(*data)->quotes = 0;
	(*data)->i = 0;
	(*data)->b = 0;
	(*data)->redirect_type = 0;
	(*data)->pipe_flag = 0;
	(*data)->status = 0;
	(*data)->envp_array = NULL;
	(*data)->args_for_cmd = NULL;
}
