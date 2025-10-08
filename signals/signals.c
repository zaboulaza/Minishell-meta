/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:34:36 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/08 19:31:41 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	set_signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_done = 1;
		g_signal_status = sig + 128;
	}
}

void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_status = sig + 128;
		rl_done = 1;
		write(STDOUT_FILENO, "\n", 1);
	}
}

void	ft_signal_heredoc(void)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	ft_signal(void)
{
	rl_event_hook = sig_event;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
