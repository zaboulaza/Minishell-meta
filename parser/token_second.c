/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 17:38:12 by nsmail            #+#    #+#             */
/*   Updated: 2025/09/24 15:40:54 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	token_second(t_node **node)
{
	t_node	*tmp;

	if (!node || !*node)
		return (1);
	tmp = *node;
	while (tmp != NULL)
	{
		if (tmp->type >= REDIR_IN && tmp->type <= HEREDOC)
		{
			if (team_redir(tmp) == 1)
				return ((printf("type after redir not good\n")), 1);
		}
		else if (tmp->type >= PIPE && tmp->type <= AND)
		{
			if (team_and_or(tmp) == 0)
				return ((printf("type after and / or not good\n")), 1);
		}
		else if (token_second_norme(tmp) == 1)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	token_second_norme(t_node *tmp)
{
	if (tmp->type == OPEN_PAREN)
	{
		if (team_open_parent(tmp) == 1)
			return ((printf("type after open_parent not good\n")), 1);
	}
	if (tmp->type == CLOSE_PAREN)
	{
		if (team_close_parent(tmp) == 1)
			return ((printf("type after close_parent not good\n")), 1);
	}
	return (0);
}
