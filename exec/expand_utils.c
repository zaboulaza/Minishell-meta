/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 21:11:41 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/13 20:51:41 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	process_double_quote(char *line, int *i, char **res, t_general *g)
{
	char	*tmp_expand;

	*res = ft_strjoin_one_char(*res, line[(*i)++]);
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$')
		{
			tmp_expand = find_in_path(&line[*i], g);
			*res = ft_strjoin(*res, tmp_expand);
			free(tmp_expand);
			/* advance past '$' */
			(*i)++;
			/* if it's $? advance past '?' as well */
			if (line[*i] == '?')
				(*i)++;
			else
			{
				while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
					(*i)++;
			}
		}
		else
			*res = ft_strjoin_one_char(*res, line[(*i)++]);
	}
	if (line[*i] == '"')
		*res = ft_strjoin_one_char(*res, line[(*i)++]);
	return (*i);
}

int	process_single_quote(char *line, int *i, char **res)
{
	*res = ft_strjoin_one_char(*res, line[(*i)++]);
	while (line[*i] && line[*i] != 39)
		*res = ft_strjoin_one_char(*res, line[(*i)++]);
	if (line[*i] == 39)
		*res = ft_strjoin_one_char(*res, line[(*i)++]);
	return (*i);
}

int	process_variable(char *line, int *i, char **res, t_general *g)
{
	char	*tmp_expand;

	tmp_expand = find_in_path(&line[*i], g);
	*res = ft_strjoin(*res, tmp_expand);
	free(tmp_expand);
	/* advance past '$' */
	(*i)++;
	/* if it's $? advance past '?' as well */
	if (line[*i] == '?')
		(*i)++;
	else
	{
		while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
			(*i)++;
	}
	return (*i);
}
