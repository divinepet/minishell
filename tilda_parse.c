#include "liba.h"

static void	free_elements(char **key, char **value, char **after_key)
{
	if (*key)
		free(*key);
	free(*value);
	free(*after_key);
}

static char	*init_elements(char *str, int i, int k, t_env *env)
{
	char	*key;
	char	*value;
	char	*after_key;
	char	*tmp;

	key = NULL;
	value = get_value_for_key(env, "HOME");
	after_key = ft_strdup(str + i + k);
	if (value == NULL)
		value = ft_strdup("");
	if (after_key != NULL)
		str = ft_strjoin(value, after_key);
	else
		str = ft_strdup(value);
	free_elements(&key, &value, &after_key);
	return (str);
}

char	*tilda_parse(t_env *env, char *str)
{
	int		k;
	int		i;
	char	*new_str;
	char	*tmp;
	char	*tmp2;

	k = 0;
	i = -1;
	new_str = ft_substr(str, '~');
	while (str[i] != '~')
		i++;
	if (str[i] == '~')
	{
		tmp = new_str;
		i++;
		while (ft_isalnum(*(str + i + k)))
			k++;
		tmp2 = init_elements(str, i, k, env);
		new_str = ft_strjoin(new_str, tmp2);
		free(tmp);
		free(tmp2);
		return (new_str);
	}
	free(new_str);
	return (str);
}
