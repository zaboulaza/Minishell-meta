/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:57:32 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/11 18:50:25 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	exec_cmd(t_cmd *cmd, t_general *g)
{
	int		i;
	int		compt;
	t_files	*tmp_files;

	i = 0;
	tmp_files = cmd->files;
	compt = compt_heredoc(cmd);
	while (tmp_files)
	{
		if (redir_g(tmp_files) == 1)
			return (1);
		compt = redir_heredoc(tmp_files, compt);
		tmp_files = tmp_files->next;
	}
	cmd->args = expand(cmd->args, g);
	cmd->args = removed_quoat(cmd->args);
	// printf("cmd->args[1] = %s\n", cmd->args[1]);
	if (is_built_in(cmd) == 1)
	{
		exec_built_in(cmd, g);
		return (0);
	}
	while (g->path[i])
	{
		g->path[i] = ft_strjoin(g->path[i], cmd->args[0]);
		i++;
	}
	i = 0;
	if (ft_strchr(cmd->args[0], '/') != NULL)
		make_execve_slash(cmd, g);
	else
		make_execve(cmd, g);
	return (0);
}

void	make_execve_slash(t_cmd *cmd, t_general *g)
{
	if (access(cmd->args[0], F_OK) == 0)
	{
		if (access(cmd->args[0], X_OK) == 0)
		{
			execve(cmd->args[0], cmd->args, g->env);
		}
		else
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			g->status = 126;
			return;
		}
	}
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g->status = 127;
}

void	make_execve(t_cmd *cmd, t_general *g)
{
	int	i;

	i = 0;
	while (g->path[i] != 0)
	{
		if (access(g->path[i], F_OK) == 0)
		{
			if (access(g->path[i], X_OK) == 0)
			{
				execve(g->path[i], cmd->args, g->env);
			}
		}
		i++;
	}
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	g->status = 127;
}

int	waitepid_and_status(pid_t pipes, t_general *g)
{
	int	status;
	
	(void)g;
	waitpid(pipes, &status, 0);
	if (WIFSIGNALED(status))
	{
		g->signaled = 128 + WTERMSIG(status);
		return 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		return WEXITSTATUS(status);
	return status;
}
