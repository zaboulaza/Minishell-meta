/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:35:34 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/14 15:36:11 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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
