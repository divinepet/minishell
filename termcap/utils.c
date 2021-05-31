#include "../liba.h"

void	ft_print_and_save(char *str, char **res, int l)
{
	char	*buf;

	if (allowed_characters(str[0]))
	{
		write(1, str, l);
		if (*res)
		{
			buf = *res;
			*res = ft_strjoin(*res, &str[0]);
			free(buf);
		}
		else
			*res = ft_strdup(str);
	}
}

void	turn_signals(t_hst_data *history, int flag)
{
	if (flag == 1)
	{
		history->term = history->old_term;
		tcsetattr(0, TCSANOW, &(history)->term);
		tcgetattr(0, &(history)->term);
		history->term.c_lflag |= ECHO;
		history->term.c_lflag |= ICANON;
		history->term.c_lflag |= ISIG;
	}
	else
	{
		tcgetattr(0, &(history)->term);
		history->term.c_lflag &= ~(ECHO);
		history->term.c_lflag &= ~(ICANON);
		history->term.c_lflag &= ~(ISIG);
	}
	tcsetattr(0, TCSANOW, &(history)->term);
	tgetent(0, "xterm-256color");
}

void	SHOW_PROMPT(void)
{
	write(2, MAGENTA, ft_strlen(MAGENTA));
	write(2, "minishell🔥: ", ft_strlen("minishell🔥: "));
	write(2, RESET, ft_strlen(RESET));
}

void	signal_use(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	allowed_characters(char c)
{
	return (((int)c >= 32 && (int)c <= 126) || c == -47 || c == -48);
}
