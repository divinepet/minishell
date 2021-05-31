#include "../liba.h"

void	my_echo(t_parse_data *data)
{
	int	flag_n;
	int	i;

	i = 1;
	flag_n = 0;
	while (data->args_for_cmd[i] != NULL && \
			!ft_strcmp(data->args_for_cmd[i], "-n"))
	{
		flag_n = 1;
		i++;
	}
	while (data->args_for_cmd[i] != NULL)
	{
		write(1, data->args_for_cmd[i], ft_strlen(data->args_for_cmd[i]));
		if (data->args_for_cmd[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (!flag_n)
		write(1, "\n", 1);
}
