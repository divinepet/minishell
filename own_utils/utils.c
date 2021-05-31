#include "../liba.h"

char	*deleteSpaces(char *str, int i, int j)
{
	char	quotes;
	char	*str_copy;

	quotes = 0;
	str_copy = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && !quotes)
		{
			while (str[i] == ' ')
				i++;
			str_copy[j++] = ' ';
			continue ;
		}
		else if (str[i] == '\'' || str[i] == '"')
		{
			if (!quotes)
				quotes = str[i];
			else if (str[i] == quotes)
				quotes = 0;
		}
		str_copy[j++] = str[i++];
	}
	return (str_copy);
}

char	*command_cutter(char *str)
{
	int		i;
	int		j;
	char	*str_copy;

	str_copy = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	while (str[i] != '\0' && str[i] != ' ')
	{
		str_copy[i] = str[i];
		i++;
	}
	return (str_copy);
}

char	**envp_to_double_array(t_env *env)
{
	t_env	*env_copy;
	char	**env_array;
	int		size;
	int		i;
	char	*tmp;

	size = 0;
	i = 0;
	env_copy = env;
	while (env_copy)
	{
		size++;
		env_copy = env_copy->next;
	}
	env_array = malloc((size + 1) * sizeof(char *));
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		env_array[i++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

int	isForbiddenEnviroment(const char *s)
{
	int	i;

	i = 0;
	if (s[0] <= '9' && s[0] >= '0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (1);
		else if (!((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122) || \
		(s[i] >= '0' && s[i] <= '9')))
			return (0);
		i++;
	}
	return (2);
}

void	level_up(t_env **env)
{
	t_env	*env_copy;
	char	*shlvl_string;
	char	*tmp;
	int		shlvl_num;

	env_copy = *env;
	shlvl_string = get_value_for_key(env_copy, "SHLVL");
	shlvl_num = ft_atoi(shlvl_string) + 1;
	tmp = ft_itoa(shlvl_num);
	if (shlvl_num > 1000)
	{
		SHOW_PROMPT();
		write(2, "warning: shell level (", 22);
		write(2, tmp, ft_strlen(tmp));
		write(2, ") too high, resetting to 1\n", 27);
		free(tmp);
		tmp = ft_strdup("1");
	}
	free(shlvl_string);
	shlvl_string = ft_strjoin("SHLVL=", tmp);
	add_to_env(&env_copy, shlvl_string, 0);
	add_to_env(&env_copy, "OLDPWD", 1);
	free(shlvl_string);
	free(tmp);
}
