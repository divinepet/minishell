#include "../liba.h"

t_history	*ft_up_arrow(char **res, t_hst_data *history, t_history *tmp)
{
	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	SHOW_PROMPT();
	if (*res && !history->flag_hst)
	{
		if (!history->str)
			history->str = ft_strjoin("", *res);
		else
			history->str = ft_strjoin(history->str, *res);
	}
	free(*res);
	*res = NULL;
	if (tmp)
	{
		history->flag_end = 1;
		if (tmp->next && history->flag_hst)
			tmp = tmp->next;
		write(1, tmp->str, ft_strlen(tmp->str));
		history->flag_hst = 1;
		history->flag_next = 1;
	}
	return (tmp);
}

t_history	*ft_down_arrow(char **res, t_hst_data *history, t_history *tmp)
{
	char	*buf;

	tputs(restore_cursor, 1, ft_putchar);
	tputs(tgetstr("cd", NULL), 1, ft_putchar);
	SHOW_PROMPT();
	if (tmp)
	{
		if (*res && !history->flag_hst)
		{
			if (!history->str)
				history->str = ft_strjoin("", *res);
			else
			{
				buf = history->str;
				history->str = ft_strjoin(history->str, *res);
				free(buf);
			}
		}
	}
	return (down_utils(history, tmp, *&res));
}

char	*delete_one_char(char *str, int flag, t_hst_data *history)
{
	char	*buf;
	int		i;
	int		count;

	i = 0;
	count = ft_strlen(str) - 1;
	if (str[count] < 0)
		count -= 1;
	if (count == 0)
	{
		free(str);
		history->flag_end = 0;
		return (NULL);
	}
	buf = ft_calloc(count + 1, sizeof(char));
	while (i < count)
	{
		buf[i] = str[i];
		i++;
	}
	if (str && flag == 2)
		free(str);
	return (buf);
}

char	*delete_char(char *res, t_history *tmp, t_hst_data *history)
{
	char	*buf;

	if (!history->flag_hst && history->str)
		res = live_string(history, *&res);
	if (history->str)
	{
		free(history->str);
		history->str = NULL;
	}
	if (history->flag_hst == 1 && res == NULL)
	{
		delete_symbol();
		history->flag_hst = 0;
		return (delete_one_char(tmp->str, 0, *&history));
	}
	else if (res)
	{
		delete_symbol();
		if (history->flag_hst)
			res = copy_str(*&res, history, tmp);
		return (delete_one_char(res, 2, *&history));
	}
	return (NULL);
}

t_history	*read_from_term(char *str, t_history *tmp, \
						t_hst_data *hst, char **res)
{
	int	l;

	l = read(0, str, 100);
	str[l] = 0;
	if (str[0] == '\0')
		str[0] = '1';
	if (!ft_strcmp(str, "\3"))
		tmp = ctrl_c(hst, *&res);
	else if (!ft_strcmp(str, "\e[A"))
		tmp = ft_up_arrow(res, hst, tmp);
	else if (!ft_strcmp(str, "\e[B"))
		tmp = ft_down_arrow(res, hst, tmp);
	else if (!ft_strcmp(str, "\177") && (*res || hst->flag_hst || hst->str))
	{
		*res = delete_char(*res, tmp, *&hst);
		if (!(*res))
			hst->flag_end = 0;
	}
	else if (ft_strcmp(str, "\e[C") && ft_strcmp(str, "\e[D") && \
						str[0] != '\4' && str[0] != '\177')
	{
		hst->flag_end = 1;
		ft_print_and_save(str, res, l);
	}
	return (tmp);
}
