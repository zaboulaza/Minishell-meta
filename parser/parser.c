/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:35:38 by nsmail            #+#    #+#             */
/*   Updated: 2025/09/18 12:24:57 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	parsing_general(t_general *g, t_tmp **tmp)
{
	if (token_first(g) == 1)
		return (1);
	if (add_to_liste(&g->node, g->one_line) == 1)
		return (1);
	if (token_second(&g->node) == 1)
		return (1);
	if (token_third(g, tmp) == 1)
		return (1);
	if (last_verif_parent(g->cmd) == 1)
		return (1);
	if (init_ast(g->cmd, false) == NULL)
		return (1);
	return (0);
}
