/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:24:27 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/17 16:43:19 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

volatile sig_atomic_t	g_signal_status = 0;

int	main(int ac, char **av, char **env)
{
	t_general	g;

	creat_struct(&g, ac, av, env);
	g.envlst = env_to_envlst(env);
	while (1)
	{
		g.node = NULL;
		g.cmd = NULL;
		g.signaled = 0;
		g_signal_status = 0;
		ft_signal();
		g.one_line = readline("mini ✗ ");
		if (!g.envlst)
			return (perror("env_to_envlst"), 1);
		if (g_signal_status != 0)
		{
			g.status = g_signal_status;
			continue ;
		}
		if (!g.one_line)
		{
			printf("exit\n");
			free_all(&g);
			break ;
		}
		add_history(g.one_line);
		if (*g.one_line)
		{
			if (parsing_general(&g, &g.tmp) == 1)
				return (free_all(&g), printf("ftg\n"), 1);
			if (exec(init_ast(g.cmd, false), &g) == 1)
				return (free_all(&g), printf("chut\n"), 1);
			if (g.signaled == 128 + SIGINT)
				write(2, "\n", 1);
			else if (g.signaled == 128 + SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			free_all(&g);
		}
	}
	free_all(&g);
	return (0);
}
