/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_first.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:04:26 by nsmail            #+#    #+#             */
/*   Updated: 2025/09/30 21:34:14 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	token_first(t_general *g)
{
	int	i;

	i = 0;
	if (quote(g) == 1)
	{
		printf("quote not good\n");
		return (1);
	}
	else if (bracket(g, i) == 1)
	{
		printf("parents not good\n");
		return (1);
	}
	else if (and_(g) == 1)
	{
		printf("AND not good\n");
		return (1);
	}
	return (0);
}

int	quote(t_general *g)
{
	int		i;
	char	current_quote;

	current_quote = 0;
	i = 0;
	while (g->one_line[i])
	{
		if (g->one_line[i] == '"' || g->one_line[i] == '\'')
		{
			if (current_quote == 0)
				current_quote = g->one_line[i];
			else if (current_quote == g->one_line[i])
				current_quote = 0;
		}
		i++;
	}
	if (current_quote != 0)
		return (1);
	return (0);
}

int	bracket(t_general *g, int i)
{
	int		count;
	char	quote;

	count = 0;
	i = 0;
	while (g->one_line[i])
	{
		if (g->one_line[i] == '"' || g->one_line[i] == 39)
		{
			quote = g->one_line[i++];
			while (g->one_line[i] && g->one_line[i] != quote)
				i++;
			if (g->one_line[i])
				i++;
		}
		if (g->one_line[i] && g->one_line[i] == ')')
			count--;
		else if (g->one_line[i] && g->one_line[i] == '(')
			count++;
		if (count < 0)
			return (1);
		if (g->one_line[i])
			i++;
	}
	return (count != 0);
}

int	and_(t_general *g)
{
	int		i;
	char	quote;

	i = 0;
	while (g->one_line[i])
	{
		if (g->one_line[i] == '"' || g->one_line[i] == 39)
		{
			quote = g->one_line[i++];
			while (g->one_line[i] && g->one_line[i] != quote)
				i++;
			if (g->one_line[i])
				i++;
		}
		if (g->one_line[i] && g->one_line[i] == '&')
		{
			if (g->one_line[i + 1] != '&')
				return (1);
			else
				i++;
		}
		if (g->one_line[i])
			i++;
	}
	return (0);
}
