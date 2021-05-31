#include "../liba.h"

t_env	*create(char *key, char *value, int hidden)
{
	t_env	*list;

	list = malloc(sizeof(t_env));
	(*list).key = ft_strdup(key);
	(*list).value = ft_strdup(value);
	(*list).hidden = hidden;
	(*list).toSort = 0;
	(*list).next = NULL;
	return (list);
}

void	add_env(t_env **list, char *key, char *value, int hidden)
{
	t_env	*list_copy;
	t_env	*list_copy_copy;

	list_copy_copy = *list;
	if (list)
	{
		if (*list == NULL)
			*list = create(key, value, hidden);
		else
		{
			list_copy = (*list);
			while ((*list_copy).next != NULL)
				list_copy = (*list_copy).next;
			if (isKeyExist(&list_copy_copy, key, value, hidden))
				return ;
			else
				(*list_copy).next = create(key, value, hidden);
		}
	}
}

int	isKeyExist(t_env **env, char *key, char *value, int hidden)
{
	char	*tmp;

	while (*env)
	{
		if (!ft_strcmp((*env)->key, key))
		{
			tmp = (*env)->value;
			(*env)->value = ft_strdup(value);
			free(tmp);
			(*env)->hidden = hidden;
			return (1);
		}
		*env = (*env)->next;
	}
	return (0);
}

char	*get_value_for_key(t_env *lst, char *key)
{
	char	*s;

	while (lst)
	{
		if (!ft_strcmp(lst->key, key))
		{
			s = ft_strdup(lst->value);
			return (s);
		}
		lst = lst->next;
	}
	return (NULL);
}

void	deleteKey(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*buffer;

	tmp = *env;
	while (tmp)
	{
		if (tmp->next != NULL && !ft_strcmp(tmp->next->key, key))
		{
			buffer = tmp->next;
			free(tmp->next->key);
			free(tmp->next->value);
			tmp->next = tmp->next->next;
			free(buffer);
			return ;
		}
		else if (tmp->next == NULL && !ft_strcmp(tmp->key, key))
		{
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		tmp = tmp->next;
	}
}
