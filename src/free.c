/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:43:02 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/17 17:21:04 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	free_all(t_general *g)
{
	if (!g)
		return ;
	if (g->one_line)
	{
		free(g->one_line);
		g->one_line = NULL;
	}
	if (g->node)
	{
		free_node(g->node);
		g->node = NULL;
	}
	if (g->cmd)
	{
		free_cmd(g->cmd);
		g->cmd = NULL;
	}
	if (g->path)
	{
		free_all_(g->path);
		g->path = NULL;
	}
	if (g->envlst)
	{
		free_envlst(g->envlst);
		g->env = NULL;
	}
	if (g->pwd)
	{
		free_pwd(g->pwd);
		g->pwd = NULL;
	}
}

void	clear_tmp(t_tmp **tmp)
{
	t_tmp	*cur;
	t_tmp	*next;

	cur = *tmp;
	while (cur)
	{
		next = cur->next;
		free(cur->path);
		free(cur);
		cur = next;
	}
	*tmp = NULL;
}

void	free_all_(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
