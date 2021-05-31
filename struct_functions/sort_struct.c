#include "../liba.h"

int	size_list(t_env *env)
{
	t_env	*buf;
	int		i;

	i = 0;
	buf = env;
	while (buf)
	{
		buf = buf->next;
		i++;
	}
	return (i);
}

int	sumcode(char *str)
{
	int	sum;
	int	i;

	sum = 0;
	while (str[i])
		sum += (int)str[i++];
	return (sum);
}

void	change_values(t_env *env)
{
	int		key;
	char	*str;
	t_env	*buf;

	buf = env;
	key = buf->hidden;
	buf->hidden = buf->next->hidden;
	buf->next->hidden = key;
	str = buf->key;
	buf->key = buf->next->key;
	buf->next->key = str;
	str = buf->value;
	buf->value = buf->next->value;
	buf->next->value = str;
}

t_env	*sort_export(t_env *env)
{
	t_env	*buf;
	int		count;
	char	*str;
	int		key;

	count = size_list(env);
	buf = env;
	while (count > 1)
	{
		while (buf->next)
		{
			if (ft_strcmp(buf->key, buf->next->key) > 0 && buf->toSort)
				change_values(buf);
			buf = buf->next;
		}
		count--;
		buf = env;
	}
	return (buf);
}
