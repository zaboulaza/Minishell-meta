/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:09:04 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/04 14:03:00 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	find_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

int	compt_heredoc(t_cmd *cmd)
{
	t_files	*tmp;
	int		compt;

	tmp = cmd->files;
	compt = 0;
	while (tmp != NULL)
	{
		if (tmp->mode == HEREDOC)
			compt++;
		tmp = tmp->next;
	}
	return (compt);
}

int	redir_g(t_files *tmp_files)
{
	if (tmp_files->mode == REDIR_IN)
    {
        if (redir_in(tmp_files) == 1)
            return (1);
    }
	else if (tmp_files->mode == REDIR_OUT)
    {   
        if (redir_out(tmp_files) == 1)
            return (1);
    }
	else if (tmp_files->mode == REDIR_APPEND)
    {
        if (redir_append(tmp_files) == 1)
            return (1);
    }
	return (0);
}

int	redir_in(t_files *tmp_files)
{
	int	fd;

	fd = open(tmp_files->path, O_CREAT | O_RDONLY, 0644);
	if (fd < 0)
		return (perror("open"), 1);
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	redir_out(t_files *tmp_files)
{
	int	fd;

	fd = open(tmp_files->path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (perror("open"), 1);
	dup2(fd, 1);
	close(fd);
	return (0);
}
