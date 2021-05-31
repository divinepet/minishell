#include "../liba.h"

void	my_exit(t_parse_data *data)
{
	int		i;

	i = 0;
	write(1, "exit\n", 5);
	if (data->args_for_cmd[1] == NULL)
		exit(0);
	while (data->args_for_cmd[1][i] != '\0')
	{
		if (!isdigit(data->args_for_cmd[1][i]))
		{
			printf("bash: exit: %s: numeric argument required\n", \
											data->args_for_cmd[1]);
			exit(ft_atoi(data->args_for_cmd[1]));
		}
		i++;
	}
	if (data->args_for_cmd[2] != NULL)
		data->isError = print_error(7, 1, "", "exit");
	else
		exit(ft_atoi(data->args_for_cmd[1]));
}
