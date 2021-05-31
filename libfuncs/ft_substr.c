#include "../liba.h"

char	*ft_substr(char const *s, char end)
{
	int		i;
	char	*sub;

	i = 0;
	sub = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	while (s[i] != end && s[i] != '\0')
	{
		sub[i] = s[i];
		i++;
	}
	return (sub);
}
