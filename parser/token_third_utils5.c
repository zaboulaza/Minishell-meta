/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_third_utils5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaboulaza <zaboulaza@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:33:51 by zaboulaza         #+#    #+#             */
/*   Updated: 2025/09/15 22:05:47 by zaboulaza        ###   ########.fr       */
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
