/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:42:55 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/17 16:47:58 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	creat_struct(t_general *g, int ac, char **av, char **env)
{
	ft_memset(g, 0, sizeof(t_general));
	g->ac = ac;
	g->av = av;
	g->env = env;
	g->node = NULL;
	g->pwd = malloc(sizeof(t_pwd));
	if (!g->pwd)
		exit(1);
}

t_env *new_env_node(char *key, char *value)
{
	t_env *node;
	
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void env_add_back(t_env **lst, t_env *new)
{
	t_env *tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static int split_env_line(char *str, char **key, char **value)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	*key = strndup(str, i); //ft_strndup
	if (!*key)
		return (1);
	if (str[i] == '=')
		*value = ft_strdup(str + i + 1);
	else
		*value = NULL;
	if (str[i] == '=' && !*value)
		return (free(*key), 1);
	return (0);
}

t_env *env_to_envlst(char **envp)
{
	t_env	*lst;
	t_env	*node;
	char	*key;
	char	*value;
	int		i;

	lst = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (split_env_line(envp[i], &key, &value))
			return (NULL);
		node = new_env_node(key, value);
		if (!node)
			return (free(key), free(value), NULL);
		env_add_back(&lst, node);
		i++;
	}
	return (lst);
}
