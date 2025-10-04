/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:32:25 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/01 15:02:44 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	redir_append(t_files *tmp_files)
{
	int	fd;

	fd = open(tmp_files->path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		return (perror("open"), 1);
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	redir_heredoc(t_files *tmp_files, int compt)
{
	int	heredoc_fd[2];
	int	i;

	i = 0;
	if (tmp_files->mode == HEREDOC)
	{
		compt--;
		if (compt == 0)
		{
			pipe(heredoc_fd);
			while (tmp_files->heredoc_content[i])
			{
				ft_putstr_fd(tmp_files->heredoc_content[i], heredoc_fd[1]);
				ft_putstr_fd("\n", heredoc_fd[1]);
				free(tmp_files->heredoc_content[i]);
				i++;
			}
			close(heredoc_fd[1]);
			dup2(heredoc_fd[0], 0);
			close(heredoc_fd[0]);
		}
	}
	return (compt);
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
				execve(g->path[i], cmd->args, g->env);
		}
		i++;
	}
	perror("execve");
	g->status = 127;
}
