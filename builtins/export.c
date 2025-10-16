// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   export.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/03 13:20:04 by lchapot           #+#    #+#             */
// /*   Updated: 2025/10/09 15:15:33 by lchapot          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

 #include "../mini.h"

static t_env	*new_env_node(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	node->value = NULL;
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (free(node->key), free(node), NULL);
	}
	node->next = NULL;
	return (node);
}

/* === Cherche une variable existante === */
static t_env	*find_env(t_env *envlst, const char *key)
{
	while (envlst)
	{
		if (ft_strcmp(envlst->key, key) == 0)
			return (envlst);
		envlst = envlst->next;
	}
	return (NULL);
}

static int	set_env_var(t_env **envlst, const char *key, const char *value)
{
	t_env	*found;
	t_env	*tmp;

	found = find_env(*envlst, key);
	if (found)
	{
		free(found->value);
		found->value = NULL;
		if (value)
		{
			found->value = ft_strdup(value);
			if (!found->value)
				return (1);
		}
		return (0);
	}
	tmp = new_env_node(key, value);
	if (!tmp)
		return (1);
	tmp->next = *envlst;
	*envlst = tmp;
	return (0);
}

static int	parse_export_arg(const char *arg, char **key, char **value)
{
	char	*eq;

	eq = ft_strchr(arg, '=');
	if (eq) //si ==
	{
		*key = strndup(arg + 1, eq - arg); //ft_strndup
		if (!*key)
			return (1);
		*value = ft_strdup(eq + 1);
		if (!*value)
			return (free(*key), 1);
	}
	else
	{
		*key = ft_strdup(arg);
		if (!*key)
			return (1);
		*value = NULL;
	}
	return (0);
}

void	do_export(t_cmd *cmd, t_general *g)
{
	int		i;
 	char	*key;
 	char	*value;

	if (!cmd || !cmd->args || !g)
		return ;
	if (!cmd->args[1])//export != env
		print_export(g->envlst);
	i = 1;
	while (cmd->args[i])
	{
		key = NULL;
		value = NULL;
		if (!parse_export_arg(cmd->args[i], &key, &value))
		{
			set_env_var(&g->envlst, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}
