/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaboulaza <zaboulaza@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:29:54 by nsmail            #+#    #+#             */
/*   Updated: 2025/09/26 17:08:35 by zaboulaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_strncmp_(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (i < n)
	{
		if (s1[i] == '\0' || s2[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	get_path(t_general *g)
{
	char	*path_one_line;
	char	**path;
	int		i;

	if (g->env == NULL)
	{
		g->path = NULL;
		return ;
	}
	i = 0;
	while (g->env[i])
	{
		if (ft_strncmp_("PATH=", g->env[i], 5) == 0)
			path_one_line = g->env[i];
		i++;
	}
	path_one_line = ft_substr(path_one_line, 5, ft_strlen(path_one_line) - 5);
	path = ft_split(path_one_line, ':');
	free(path_one_line);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	g->path = path;
}
