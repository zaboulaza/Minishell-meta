/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:53:49 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/10 20:50:28 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../mini.h"

char *get_env_value(t_general *g, const char *key)
{	 
	(void)g;
	(void)key;
	//while (g->envlst)
	//{		 
	//	if (ft_strcmp(g->envlst->key, key) == 0)
	//		return (g->envlst->value);		 
	//	g->envlst = g->envlst->next;	 
	//}	 
	return (NULL);
}
int	get_env(t_general *g)
{
	int	i;
	i = 0;
	while (g->env[i])
		printf("%s\n", g->env[i++]);
	return (0);
}
t_env *new_env_node(char *key, char *value)
{
	t_env *node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}
void env_add_back(t_env **lst, t_env *new)
{
	if (!*lst)
	{
		*lst = new;
		return;
	}
	t_env *tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
void	init_env(t_env **env_list, char **env)
{
	int		i;
	char	*sep;
	char	*key;
	char	*value;
	int		key_len;
	t_env	*node;
	i = 0;
	*env_list = NULL; //useless?
	while (env[i] && i < 1)
	{
		sep = ft_strchr(env[i], '=');
		if (sep)
		{
			key_len = sep - env[i];
			key = ft_substr(env[i], 0, key_len);
			value = ft_strdup(sep + 1);
			node = new_env_node(key, value);
			env_add_back(env_list, node);
			free(key);
			free(value);
		}
		i++;
	}
}
