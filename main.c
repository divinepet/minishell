#include "liba.h"

void	print_some(t_hst_data history)
{
	tputs(save_cursor, 1, ft_putchar);
	if (history.flag_end == 0)
	{
		SHOW_PROMPT();
	}
}

void	init_hst(t_hst_data *history, char **av)
{
	char		*term_name;

	term_name = "xterm-256color";
	history->flag_hst = 0;
	history->flag_next = 0;
	history->count_hst = 0;
	history->flag_end = 0;
	tcgetattr(0, &(history)->term);
	tcgetattr(0, &(history)->old_term);
	history->term.c_lflag &= ~(ECHO);
	history->term.c_lflag &= ~(ICANON);
	history->term.c_lflag &= ~(ISIG);
	tcsetattr(0, TCSANOW, &(history)->term);
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	ft_signal();
	tgetent(0, term_name);
	load_from_file(&history);
}

void	reload_flags(t_hst_data *history, char **res)
{
	history->flag_end = 0;
	history->flag_hst = 0;
	history->flag_next = 0;
	if (*res != NULL)
	{
		free(*res);
		*res = NULL;
	}
}

void	main_cycle(t_hst_data *history, t_env *env)
{
	t_history	*tmp;
	int			flag;
	char		str[2000];
	char		*res;

	flag = 1;
	tmp = history->hst;
	res = NULL;
	while (ft_strcmp(str, "\4") || history->flag_end)
	{
		print_some(*history);
		while (flag)
		{
			tmp = read_from_term(str, tmp, &*history, &res);
			flag = (ft_strcmp(str, "\4") && ft_strcmp(str, "\n"));
		}
		if (!ft_strcmp(str, "\n"))
		{
			tmp = create_history(str, &res, &*history, tmp);
			if (history->flag_hst || res != NULL)
				delete_spaces_and_quotes(tmp->str, env, &*history);
			reload_flags(*&history, &res);
		}
		flag = 1;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_hst_data	history;
	t_history	*tmp;
	t_env		*env;
	int			flag;

	flag = 1;
	g_global_error = 0;
	envpToStruct(&env, envp);
	level_up(&env);
	init_hst(&history, av);
	tmp = history.hst;
	main_cycle(&history, env);
	history.term.c_lflag |= ECHO;
	history.term.c_lflag |= ICANON;
	history.term.c_lflag |= ISIG;
	tcsetattr(0, TCSANOW, &(history).term);
	free_struct(&env);
	write(1, "exit\n", 6);
	return (0);
}
