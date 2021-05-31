#include "../liba.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					ink;
	unsigned long int	num;

	i = 0;
	ink = 1;
	num = 0;
	if (!str[i])
		return (0);
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ' || str[i] == '\r')
		i += 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			ink = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + (str[i++] - '0');
	if (num > 9223372036854775807 && ink > 0)
		return (-1);
	else if (num > 9223372036854775807 && ink < 0)
		return (0);
	return (num * ink);
}
