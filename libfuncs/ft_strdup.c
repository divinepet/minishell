#include "../liba.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	len = ft_strlen((char *)s1);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (0);
	while (i < len)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
