/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaronda <elaronda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 12:26:28 by rlinkfen          #+#    #+#             */
/*   Updated: 2021/05/29 01:44:41 by elaronda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../liba.h"

void	first_child(int **pipes, t_env *env, char **av, t_parse_data *data)
{
	if (ft_strchr(av[data->j], -1) || ft_strchr(av[data->j], -2) \
								|| ft_strchr(av[data->j], -3))
		data->redirect_type = 1;
	dup2(pipes[data->j][1], 1);
	pre_parse_modified(av[data->j], env, data);
	exit(0);
}

void	last_child(int **pipes, t_env *env, char **av, t_parse_data *data)
{
	if (ft_strchr(av[data->j], -1) || ft_strchr(av[data->j], -2) \
								|| ft_strchr(av[data->j], -3))
		data->redirect_type = 1;
	close_other_fd(pipes, pipes[data->j - 1][0], -1);
	dup2(pipes[data->j - 1][0], 0);
	pre_parse_modified(av[data->j], env, data);
	exit(0);
}

void	middle_child(int **pipes, t_env *env, char **av, t_parse_data *data)
{
	if (ft_strchr(av[data->j], -1) || ft_strchr(av[data->j], -2) \
								|| ft_strchr(av[data->j], -3))
		data->redirect_type = 1;
	close_other_fd(pipes, pipes[data->j - 1][0], pipes[data->j][1]);
	dup2(pipes[data->j - 1][0], 0);
	dup2(pipes[data->j][1], 1);
	pre_parse_modified(av[data->j], env, data);
	exit(0);
}

int	last_prepare(char **av, char *new_string)
{
	int	count;

	count = 0;
	while (av[count])
		count++;
	return (count);
}

char	**str_prepare(char *buf, t_parse_data *data)
{
	char	*new_string;
	char	**av;

	data->j = -1;
	data->pipe_flag = 0;
	data->redirect_type = 0;
	new_string = new_str_for_pipe(buf, 0, 0);
	av = ft_split(new_string, -4);
	if (av[0] == NULL)
		data->isError = print_error(9, 258, "", "");
	free(new_string);
	return (av);
}
