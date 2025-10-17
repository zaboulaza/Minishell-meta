/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:53:49 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/17 16:50:26 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	print_env(t_general *g)
{
	while (g->envlst)
	{
		printf("%s=%s\n", g->envlst->key, g->envlst->value);
		g->envlst = g->envlst->next;
	}
	return (0);
}