/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaronda <elaronda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 12:26:09 by rlinkfen          #+#    #+#             */
/*   Updated: 2021/05/29 01:45:10 by elaronda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../liba.h"

char	*new_str_for_pipe(char *str, int i, int k)
{
	char	*output;
	int		save_index;

	save_index = 0;
	output = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			if (str[i - 1] == -4)
			{
				while (str[i] == ' ')
					i++;
				continue ;
			}
			save_index = i;
			while (str[i] == ' ')
				i++;
			if (str[i] != -4)
				i = save_index;
		}
		output[k++] = str[i++];
	}
	return (output);
}

int 	**create_pipes(char **av)
{
	int	i;
	int	**pipes;
	int	j;

	i = 0;
	j = 0;
	while (av[i])
		i++;
	pipes = ft_calloc(i + 1, sizeof(int *));
	while (j < i)
		pipes[j++] = ft_calloc(3, sizeof(int));
	return (pipes);
}

void	close_other_fd(int **fd, int k, int j)
{
	int	i;

	i = 0;
	while (fd[i])
	{
		if (fd[i][0] != k)
			close(fd[i][0]);
		if (fd[i][1] != j)
			close(fd[i][1]);
		i++;
	}
}

void	wait_close(pid_t *pid, char **av, int **pipes, t_parse_data *data)
{
	int	i;

	i = 0;
	while (av[i] != NULL)
	{
		waitpid(pid[i], &data->status, WUNTRACED);
		if (i == 0)
			close(pipes[i][1]);
		else if (av[i + 1] == NULL)
			close(pipes[i - 1][0]);
		else
		{
			close(pipes[i - 1][0]);
			close(pipes[i][1]);
		}
		i++;
	}
	dup2(dup(0), 0);
	dup2(dup(1), 1);
	free_double_array(&*av);
	free_double_array((char **)&*pipes);
	free(pid);
}

void	pipe_check(char *buf, t_env *env, t_parse_data *data)
{
	char	**av;
	char	*new_string;
	pid_t	*pid;
	int		**pipes;
	int		count;

	av = str_prepare(buf, data);
	pipes = create_pipes(av);
	count = last_prepare(av, *&new_string);
	pid = ft_calloc(count + 1, sizeof(pid));
	while (++data->j < count)
	{
		pipe(pipes[data->j]);
		pid[data->j] = fork();
		if (pid[data->j] == 0 && data->j == 0)
			first_child(pipes, env, av, data);
		else if (pid[data->j] == 0 && data->j == (count - 1))
			last_child(pipes, env, av, data);
		else if (pid[data->j] == 0 && data->j < (count - 1) && data->j > 0)
			middle_child(pipes, env, av, data);
		dup2(dup(0), 0);
		dup2(dup(1), 1);
	}
	wait_close(pid, *&av, pipes, data);
}
