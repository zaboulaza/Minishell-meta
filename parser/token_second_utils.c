/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_second_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 19:34:07 by nsmail            #+#    #+#             */
/*   Updated: 2025/09/22 20:19:44 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	team_redir(t_node *tmp)
{
	if (tmp->next == NULL)
		return (1);
	if (tmp->next != NULL)
	{
		if (tmp->next->type != WORD)
			return (1);
	}
	return (0);
}

int	team_and_or(t_node *tmp)
{
	if (tmp->id == 0)
		return (0);
	if (tmp->next == NULL)
		return (0);
	if (tmp->next != NULL)
	{
		if (tmp->next->type != WORD && tmp->next->type != OPEN_PAREN
			&& tmp->next->type != REDIR_IN && tmp->next->type != HEREDOC
			&& tmp->next->type != REDIR_OUT && tmp->next->type != REDIR_APPEND)
			return (0);
	}
	return (1);
}

int	team_open_parent(t_node *tmp)
{
	if (tmp->next != NULL)
	{
		if (tmp->next->type != WORD && tmp->next->type != OPEN_PAREN)
			return (1);
	}
	return (0);
}

int	team_close_parent(t_node *tmp)
{
	if (tmp->next != NULL)
	{
		if (tmp->next->type == WORD)
			return (1);
	}
	return (0);
}

int	team_word(t_node *tmp)
{
	if (tmp->next != NULL)
	{
		if (tmp->next->type == OPEN_PAREN)
			return (1);
	}
	return (0);
}
