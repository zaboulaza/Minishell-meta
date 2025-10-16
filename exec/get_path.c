/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:29:54 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/16 19:13:52 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_envsize(t_env *lst)
{
	int	compt;

	if (lst == NULL)
		return (0);
	compt = 0;
	while (lst->next != 0)
	{
		lst = lst->next;
		compt++;
	}
	return (compt);
}

char    *ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
    char    *res;
    size_t  len1;
    size_t  len2;
    size_t  len3;

    if (!s1 || !s2 || !s3)
        return (NULL);
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    len3 = ft_strlen(s3);
    res = malloc(len1 + len2 + len3 + 1);
    if (!res)
        return (NULL);
    ft_strlcpy(res, s1, len1 + 1);
    ft_strlcat(res, s2, (len1 + len2 + 1));
    ft_strlcat(res, s3, (len1 + len2 + len3 + 1));
    return (res);
}

char **lst_to_envp(t_env *lst)
{
    int		i;
    int		size;
    char	**envp;
	
	i = 0;
	size = ft_envsize(lst);
	envp = malloc(sizeof(char *) * (size + 1));
    while (lst)
    {
		envp[i] = ft_strjoin3(lst->key, "=", lst->value);
        lst = lst->next;
        i++;
    }
    envp[i] = NULL;
    return (envp);
}

void	get_path(t_general *g, int i)
{
	char	*path_one_line;
	char	**path;
	char	**env_curr;

	env_curr = lst_to_envp(g->envlst);
	if (!env_curr)
	{
		g->path = NULL;
		return ;
	}
	i = 0;
	while (env_curr[i])
	{
		if (!ft_strncmp("PATH=", env_curr[i], 5))
			path_one_line = env_curr[i];
		i++;
	}
	if (!path_one_line)
		return ;
	path_one_line = ft_substr(path_one_line, 5, ft_strlen(path_one_line) - 5);
	path = ft_split(path_one_line, ':');
	free(path_one_line);
	i = -1;
	while (path[++i])
		path[i] = ft_strjoin(path[i], "/");
	g->path = path;
}
