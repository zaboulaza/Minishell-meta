/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_third.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:56:31 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/02 15:33:21 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	token_third(t_general *g, t_tmp **tmp)
{
	if (add_to_cmd_liste(&g->cmd, g->node, tmp) == 1)
		return (1);
	remove_invalid_cmds(&g->cmd);
	return (0);
}

int	add_to_cmd_liste(t_cmd **cmd, t_node *node, t_tmp **tmp)
{
	t_cmd	*new;
	t_cmd	*tmp_;

	if (!node)
		return (0);
	while (node != NULL)
	{
		new = new_cmd(node, tmp);
		if (!new)
			return (1);
		if (!*cmd)
			*cmd = new;
		else
		{
			tmp_ = *cmd;
			while (tmp_->next != NULL)
				tmp_ = tmp_->next;
			tmp_->next = new;
		}
		node = next_step_cmd(node);
	}
	return (0);
}

t_cmd	*new_cmd(t_node *node, t_tmp **tmp)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->type = find_cmd_type(node);
	cmd->args = find_arg(cmd, node, tmp);
	cmd->next = NULL;
	return (cmd);
}

t_node	*next_step_cmd(t_node *node)
{
	if (node->type >= REDIR_IN && node->type <= HEREDOC)
	{
		while (node && (node->type >= REDIR_IN && node->type <= HEREDOC))
			node = node->next->next;
	}
	else if (node->type == WORD)
	{
		while (node != NULL && node->type == WORD)
		{
			node = node->next;
			while (node != NULL && (node->type >= REDIR_IN
					&& node->type <= HEREDOC))
				node = node->next;
		}
	}
	else if (node->type == OPEN_PAREN)
		node = next_step_norm_cmd(node);
	else if (node->type >= PIPE && node->type <= AND)
	{
		node = node->next;
	}
	return (node);
}
