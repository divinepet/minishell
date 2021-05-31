/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaronda <elaronda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 15:10:10 by rlinkfen          #+#    #+#             */
/*   Updated: 2021/05/29 01:41:56 by elaronda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../liba.h"

void	delete_symbol(void)
{
	tputs(cursor_left, 1, ft_putchar);
	tputs(tgetstr("dc", 0), 1, ft_putchar);
	tputs(tgetstr("cd", 0), 1, ft_putchar);
}

char	*live_string(t_hst_data *history, char *res)
{
	char	*buf;

	if (!history->flag_hst && history->str)
	{
		buf = res;
		if (!res)
			res = ft_strdup(history->str);
		else
			res = ft_strjoin(history->str, res);
		free(buf);
	}
	return (res);
}

char	*copy_str(char *res, t_hst_data *history, t_history *tmp)
{
	char	*buf;

	buf = res;
	res = ft_strjoin(tmp->str, res);
	history->flag_hst = 0;
	free(buf);
	return (res);
}

t_history	*ctrl_c(t_hst_data *history, char **res)
{
	history->flag_end = 0;
	tputs(cursor_down, 1, ft_putchar);
	tputs(save_cursor, 1, ft_putchar);
	SHOW_PROMPT();
	free(history->str);
	history->str = NULL;
	free(*res);
	*res = NULL;
	return (history->hst);
	g_global_error = 1;
}

t_history	*down_utils(t_hst_data *history, t_history *tmp, char **res)
{
	history->flag_end = 1;
	free(*res);
	*res = NULL;
	if (tmp->prev)
	{
		tmp = tmp->prev;
		history->flag_hst = 1;
	}
	else
	{
		history->flag_end = 0;
		history->flag_hst = 0;
	}
	history->flag_next = 0;
	if (history->flag_hst)
		write(1, tmp->str, ft_strlen(tmp->str));
	else if (history->str)
		write(1, history->str, ft_strlen(history->str));
	return (tmp);
}
