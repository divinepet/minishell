#include "../liba.h"

static	int	word_count(char *s, char c)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
	z = 0;
	while (s[i] != 0)
	{
		while (s[i] != c && s[i] != 0)
			i++;
		if (i != j)
			z++;
		j = i;
		while (s[j] == c && s[j] != 0)
		{
			j++;
			i++;
		}
		j = i;
	}
	return (z);
}

static	int	start_find(char const *s, char c, int pos)
{
	while (s[pos])
	{
		if (s[pos] == c)
			pos++;
		if (s[pos] != c)
			return (pos);
	}
	return (0);
}

static	int	end_find(char const *s, char c, int pos, int start)
{
	pos = start + 1;
	while (s[pos])
	{
		if (s[pos] != c)
			pos++;
		if (s[pos] == c)
			return (pos);
	}
	if (s[pos] == '\0')
		return (pos);
	return (0);
}

static	char	*test(char const *s, char c, int *pos)
{
	int		start;
	int		end;
	int		j;
	char	*tmp;

	j = 0;
	start = start_find(s, c, *pos);
	end = end_find(s, c, *pos, start);
	tmp = malloc(((end - start) + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	while (start < end)
		tmp[j++] = s[start++];
	tmp[j] = '\0';
	*pos = end;
	return (tmp);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**arr;
	int		k;
	int		pos;

	pos = 0;
	k = 0;
	if (!s)
		return (NULL);
	words = word_count((char *)s, c);
	arr = malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (words--)
	{
		arr[k] = test(s, c, &pos);
		if (arr[k] == NULL)
		{
			free_double_array(&*arr);
			return (NULL);
		}
		k++;
	}
	arr[k] = NULL;
	return (arr);
}
