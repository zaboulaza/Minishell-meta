/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:49:22 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/14 16:52:11 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	handle_double_quote(char *str, int *i, char *result, int *j)
{
	(*i)++;
	while (str[*i] && str[*i] != '"')
		result[(*j)++] = str[(*i)++];
	if (str[*i] == '"')
		(*i)++;
	return (*i);
}

int	handle_single_quote(char *str, int *i, char *result, int *j)
{
	(*i)++;
	while (str[*i] && str[*i] != 39)
		result[(*j)++] = str[(*i)++];
	if (str[*i] == 39)
		(*i)++;
	return (*i);
}

char	*remove_outer_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"')
			handle_double_quote(str, &i, result, &j);
		else if (str[i] == 39)
			handle_single_quote(str, &i, result, &j);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}
