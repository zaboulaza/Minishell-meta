/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:31:30 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/04 21:09:33 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	exec_ast(t_cmd *cmd, t_general *g)
{
	int	type;

	type = cmd->type;
	if (type == AND)
		exec_and(cmd, g);
	else if (type == OR)
		exec_or(cmd, g);
	else if (type == PIPE)
		exec_pipe(cmd, g);
	else if (type == CMD)
		exec_cmd(cmd, g);
	else if (type == SUBSHELL)
		exec_subshell(cmd, g);
	free_all(g);
	return (0);
}

void	exec_and(t_cmd *cmd, t_general *g)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == 0)
	{
		exec_ast(cmd->left, g);
		exit(g->status);
	}
	g->status = waitepid_and_status(pid1);
	if (g->status != 0)
	{
		free_all(g);
		exit(g->status);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		exec_ast(cmd->right, g);
		exit(g->status);
	}
	g->status = waitepid_and_status(pid2);
}

void	exec_or(t_cmd *cmd, t_general *g)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == 0)
	{
		exec_ast(cmd->left, g);
		free_all(g);
		exit(g->status);
	}
	g->status = waitepid_and_status(pid1);
	if (g->status == 0)
	{
		free_all(g);
		exit(g->status);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		exec_ast(cmd->right, g);
		free_all(g);
		exit(g->status);
	}
	g->status = waitepid_and_status(pid2);
}

void	exec_pipe(t_cmd *cmd, t_general *g)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(pipefd);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(pipefd[0]);
		(dup2(pipefd[1], 1), close(pipefd[1]));
		exec_ast(cmd->left, g);
		(free_node(g->node), free_cmd(g->cmd));
		exit(g->status);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(pipefd[1]);
		(dup2(pipefd[0], 0), close(pipefd[0]));
		exec_ast(cmd->right, g);
		(free_node(g->node), free_cmd(g->cmd));
		exit(g->status);
	}
	(close(pipefd[0]), close(pipefd[1]), waitpid(pid1, NULL, 0));
	g->status = waitepid_and_status(pid2);
}

void	exec_subshell(t_cmd *cmd, t_general *g)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{	
		g->one_line = ft_strdup(cmd->args[0]);
		(free_node(g->node), free_cmd(g->cmd));
		g->node = NULL;
		g->cmd = NULL;
		if (parsing_general(g, &g->tmp) == 1)
		{
			g->one_line = NULL;
			free_all(g);
			exit(1);
		}
		free(g->one_line);
		g->one_line = NULL;
		exec_ast(init_ast(g->cmd, false), g);
		exit(g->status);
	}
	g->status = waitepid_and_status(pid);
	// free_all(g);
}
