/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:52:52 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/14 16:11:52 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	exec(t_cmd *cmd, t_general *g)
{
	int	pid;

	if (cmd == NULL)
		return (1);
	get_path(g, 0);
	if (cmd->type == CMD || cmd->type == SUBSHELL)
	{
		if (is_built_in(cmd) == 1)
			exec_cmd(cmd, g);
		else
		{
			pid = ft_fork();
			if (pid == 0)
				exit(exec_ast(cmd, g));
			g->status = waitepid_and_status(pid, g);
		}
	}
	else
		exec_ast(cmd, g);
	return (0);
}

int	is_built_in(t_cmd *cmd)
{
	if (cmd->args == NULL || cmd->args[0] == NULL)
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (1);
	return (0);
}
