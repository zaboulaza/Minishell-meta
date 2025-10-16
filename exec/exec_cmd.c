/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:57:32 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/16 19:28:18 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	join_cmd_to_paths(t_general *g, char *cmd_name)
{
	int	i;

	i = 0;
	if (!g->path)
		return ;
	while (g->path[i])
	{
		g->path[i] = ft_strjoin(g->path[i], cmd_name);
		i++;
	}
}

int	exec_cmd(t_cmd *cmd, t_general *g)
{
	int		compt;
	t_files	*tmp_files;

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
	if (is_built_in(cmd) == 1)
		return (exec_built_in(cmd, g), 0);
	join_cmd_to_paths(g, cmd->args[0]);
	if (ft_strchr(cmd->args[0], '/') != NULL)
		make_execve_slash(cmd, g);
	else
		make_execve(cmd, g);
	return (0);
}

void	make_execve_slash(t_cmd *cmd, t_general *g)
{
	// list to char **
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
			return ;
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
	if (g->path)
	{
		while (g->path[i] != 0)
		{
			if (access(g->path[i], F_OK) == 0)
			{
				if (access(g->path[i], X_OK) == 0)
					execve(g->path[i], cmd->args, g->env);
			}
			i++;
		}
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
		return (128 + WTERMSIG(status));
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}
