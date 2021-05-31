#include "../liba.h"

void	ft_bzero(void *s, size_t n)
{
	char	*src;
	int		i;

	i = 0;
	src = s;
	while (i < (int)n)
		src[i++] = '\0';
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*p;

	p = malloc(size * num);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, (size * num));
	return (p);
}

void	*ft_memset(void *dst, int c, size_t n)
{
	int		i;
	char	*src;

	i = 0;
	src = dst;
	while (i < (int)n)
	{
		src[i] = c;
		i++;
	}
	return (src);
}
