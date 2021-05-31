/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_in_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elaronda <elaronda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 15:58:10 by rlinkfen          #+#    #+#             */
/*   Updated: 2021/05/29 01:17:49 by elaronda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../liba.h"

static	void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_global_error = 130;
}

static	void	ft_signal_quit(int sig)
{
	write(1, "\b\b  \b\b", 6);
	write(1, "^\\Quit: ", 8);
	ft_putnbr_fd(sig, 1);
	write(1, "\n", 1);
	g_global_error = 131;
}

void	ft_signal_child_process(void)
{
	signal(SIGINT, ft_signal_cltr_c);
	signal(SIGQUIT, ft_signal_quit);
}
