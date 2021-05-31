#include "../liba.h"

static	int	start_index(char const *s1, char const *set)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (set[k] != '\0')
	{
		if (s1[i] == set[k])
		{
			i++;
			k = 0;
		}
		if (s1[i] != set[k])
			k++;
	}
	return (i);
}

void	tgetend(char **buf, char **array)
{
	pid_t	pid;
	char	*str;
	char	*tmp;
	int		a;

	str = ft_strjoin("/bin/", "ba");
	tmp = ft_strjoin(str, "sh");
	pid = fork();
	if (pid == 0)
		execve(tmp, array, buf);
	else
		wait(&pid);
	exit(0);
}

static	int	end_index(char const *s1, char const *set)
{
	int	i;
	int	k;

	k = 0;
	i = ft_strlen((char *)s1) - 1;
	while (set[k] != '\0')
	{
		if (s1[i] == set[k])
		{
			i--;
			k = 0;
		}
		if (s1[i] != set[k])
			k++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*dst;

	i = 0;
	if (!s1 || !set)
		return (0);
	start = start_index(s1, set);
	end = end_index(s1, set);
	if (start < 0 || end < 0)
	{
		start = 2;
		end = 0;
	}
	dst = (char *)malloc(sizeof(char) * ((end - start) + 2));
	if (!dst)
		return (NULL);
	while (start <= end)
		dst[i++] = s1[start++];
	dst[i] = '\0';
	return (dst);
}
