#include "../liba.h"

void	free_and_errors(t_parse_data *data, char **cmd, int flag, char **buf)
{
	if (data->status != 0)
	{
		g_global_error = data->status % 255;
		data->isError = 1;
	}
	if (data->isError != 1)
		g_global_error = 0;
	free(*cmd);
	if (flag)
		free(*buf);
}
