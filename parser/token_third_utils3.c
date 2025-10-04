/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_third_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 23:48:31 by nsmail            #+#    #+#             */
/*   Updated: 2025/09/25 23:43:00 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	add_to_files_liste(t_cmd *cmd, t_node *node, t_tmp **tmp)
{
	t_files	*new;
	t_files	*tmp_;

	(void)tmp;
	new = new_files(node);
	if (!new)
		return (1);
	if (cmd->files == NULL)
		cmd->files = new;
	else
	{
		tmp_ = cmd->files;
		while (tmp_->next != NULL)
			tmp_ = tmp_->next;
		tmp_->next = new;
	}
	return (0);
}

t_files	*new_files(t_node *node)
{
	t_files	*file;

	file = malloc(sizeof(t_files));
	if (!file)
		return (NULL);
	ft_bzero(file, sizeof(t_files));
	file->mode = node->type;
	file->path = ft_strdup(node->next->content);
	if (node->type == HEREDOC)
		file->heredoc_content = heredoc_content(node->next->content);
	file->next = NULL;
	return (file);
}

char	**find_arg_norm(t_cmd *cmd, t_node *node, t_tmp **tmp)
{
	char	*tmp_;
	char	**arg;

	tmp_ = ft_strdup("");
	while (node != NULL && node->type == WORD)
	{
		tmp_ = ft_strjoin_(tmp_, node->content);
		node = node->next;
		if (tmp)
		{
			add_tmp_to_list(cmd, tmp);
			cmd->type = 10;
			clear_tmp(tmp);
		}
		while (node && (node->type >= REDIR_IN && node->type <= HEREDOC))
		{
			add_to_files_liste(cmd, node, tmp);
			node = node->next->next;
		}
	}
	arg = ft_split_(tmp_, ' ');
	if (!arg)
		return (free(tmp_), NULL);
	free(tmp_);
	return (arg);
}

int	add_to_tmp_liste(t_node *node, t_tmp **tmp)
{
	t_tmp	*new;
	t_tmp	*temp;

	new = new_tmp(node);
	if (!new)
		return (1);
	if (*tmp == NULL)
		*tmp = new;
	else
	{
		temp = *tmp;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

t_tmp	*new_tmp(t_node *node)
{
	t_tmp	*file;

	file = malloc(sizeof(t_tmp));
	if (!file)
		return (NULL);
	ft_bzero(file, sizeof(t_tmp));
	file->mode = node->type;
	file->path = ft_strdup(node->next->content);
	if (node->type == HEREDOC)
		file->heredoc_content = heredoc_content(node->next->content);
	file->next = NULL;
	return (file);
}
