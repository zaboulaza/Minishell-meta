/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:29:54 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/14 16:29:04 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	get_path(t_general *g, int i)
{
	char	*path_one_line;
	char	**path;

	if (g->env == NULL)
	{
		g->path = NULL;
		return ;
	}
	i = 0;
	while (g->env[i])
	{
		if (ft_strncmp("PATH=", g->env[i], 5) == 0)
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
