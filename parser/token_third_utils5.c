/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_third_utils5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:33:51 by zaboulaza         #+#    #+#             */
/*   Updated: 2025/10/14 18:15:15 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	**cpy_char_tab(char **tab)
{
	int		i;
	char	**new;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	find_arg_norm3(t_cmd *cmd, t_tmp **tmp, t_tmp *cur)
{
	if (cur->heredoc_content == NULL)
	{
		clear_tmp(tmp);
		cmd->type = 10;
	}
	else
	{
		add_tmp_to_list(cmd, tmp);
		cmd->type = 10;
		clear_tmp(tmp);
	}
}

void	handle_tmp_and_set_type(t_cmd *cmd, t_tmp **tmp)
{
	add_tmp_to_list(cmd, tmp);
	clear_tmp(tmp);
	cmd->type = 11;
}

t_node	*process_parent_content(t_node *node, char **arg, int count)
{
	node = node->next;
	while (node && (count > 2))
	{
		arg[0] = ft_strjoin_(arg[0], node->content);
		node = node->next;
		count--;
	}
	return (node->next);
}
