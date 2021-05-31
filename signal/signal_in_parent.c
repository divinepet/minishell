/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_in_parent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaronda <elaronda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 15:51:15 by rlinkfen          #+#    #+#             */
/*   Updated: 2021/05/29 01:18:13 by elaronda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../liba.h"

void	ft_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	SHOW_PROMPT();
}

static void	ft_ctrl_backslash(int sig)
{
	write(1, "\b\b  \b\b", 6);
	write(1, "^\\Quit: ", 8);
	ft_putnbr_fd(sig, 1);
	write(1, "\n", 1);
	g_global_error = 131;
}

static void	ft_sig_term(int sig)
{
	(void)sig;
}

static void	ft_sig_chld(int sig)
{
	(void)sig;
}

void	ft_signal(void)
{
	signal(SIGQUIT, ft_ctrl_backslash);
	signal(SIGCHLD, ft_sig_chld);
	signal(SIGTERM, ft_sig_term);
}
