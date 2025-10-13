/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 21:54:11 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/13 20:52:00 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	**expand(char **arg, t_general *g)
{
	int		i;
	int		j;
	char	*old_arg;

	j = 0;
	i = 0;
	while (arg[i])
	{
		if (check_if_need_to_expand(arg[i], j) == 0)
		{
			old_arg = arg[i];
			arg[i] = expand_line(arg[i], g);
			free(old_arg);
			// printf("arg = %s\n", arg[i]);
		}
		i++;
	}
	return (arg);
}

int	check_if_need_to_expand(char *arg, int j)
{
	j = 0;
	while (arg[j])
	{
		if (arg[j] == '"')
		{
			j++;
			while (arg[j] && arg[j] != '"')
			{
				if (arg[j] == '$')
					return (0);
				j++;
			}
		}
		else if (arg[j] == 39)
		{
			j++;
			while (arg[j] && arg[j] != 39)
				j++;
		}
		else if (arg[j] == '$')
			return (0);
		j++;
	}
	return (1);
}

char	*find_in_path(char *arg, t_general *g)
{
	int		j;
	int		len;
	char	*tmp;
	char	*one_line;

	one_line = NULL;
	j = 1;
	if (arg[1] == '?')
		return (ft_itoa(g->status));
	while (arg[j] && (ft_isalnum(arg[j]) || arg[j] == '_'))
		j++;
	if (j == 1)
		return (ft_strdup("$"));
	tmp = ft_substr(arg, 1, j - 1);
	tmp = ft_strjoin(tmp, "=");
	len = ft_strlen(tmp);
	j = 0;
	while (g->env[j])
	{
		if (ft_strncmp(tmp, g->env[j], len) == 0)
			one_line = g->env[j];
		j++;
	}
	if (!one_line)
		return (free(tmp), ft_strdup(""));
	one_line = ft_substr(one_line, len, ft_strlen(one_line) - len);
	return (free(tmp), one_line);
}

char	*ft_strjoin_one_char(char *s1, char s2)
{
	size_t	tailleg;
	int		i;
	char	*s3;

	if (!s1)
		return (NULL);
	tailleg = ft_strlen(s1) + 1;
	i = -1;
	s3 = malloc(tailleg + 1);
	if (!s3)
		return (free(s1), NULL);
	while (s1[++i])
		s3[i] = s1[i];
	s3[i++] = s2;
	s3[i] = '\0';
	free(s1);
	return (s3);
}

char	*expand_line(char *line, t_general *g)
{
	char	*res;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && (line[i + 1] == '"' || line[i + 1] == 39))
			i++;
		else if (line[i] == '"')
			process_double_quote(line, &i, &res, g);
		else if (line[i] == 39)
			process_single_quote(line, &i, &res);
		else if (line[i] == '$')
			process_variable(line, &i, &res, g);
		else
			res = ft_strjoin_one_char(res, line[i++]);
	}
	return (res);
}
