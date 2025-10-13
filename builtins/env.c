/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:53:49 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/13 18:03:23 by lchapot          ###   ########.fr       */
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
t_env *new_env_node(char *key, char *value) //ok
{
	t_env *node;
	
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	//node->key = ft_strdup(key);
	//node->value = ft_strdup(value);
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
	*key = strndup(str, i);
	if (!*key)
		return (1);
	if (str[i] == '=')
		*value = strdup(str + i + 1);
	else
		*value = NULL;
	if (str[i] == '=' && !*value)
		return (free(*key), 1);
	return (0);
}

t_env *env_to_envlst(char **envp)
{
    t_env   *lst;
    t_env   *node;
    char    *key;
    char    *value;
    int     i;

    lst = NULL;
    i = 0;
    while (envp && envp[i])
    {
        if (split_env_line(envp[i], &key, &value))
            return (NULL);
        node = new_env_node(key, value);
        if (!node)
        {
            free(key);
            free(value);
            return (NULL);
        }
        env_add_back(&lst, node);
        i++;
    }
    return (lst);
}
