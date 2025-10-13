// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   unset.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/03 13:20:16 by lchapot           #+#    #+#             */
// /*   Updated: 2025/10/09 15:15:47 by lchapot          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

 #include "../mini.h"


static void	unset_one(t_env **envlst, const char *key)
{
	t_env	*cur;
	t_env	*prev;

	if (!envlst || !*envlst || !key)
		return ;
	cur = *envlst;
	prev = NULL;
	while (cur)
	{
		if (strcmp(cur->key, key) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*envlst = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
	ft_putstr_fd((char *)key, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}

void	do_unset(t_cmd *cmd, t_general *g)
{
	int	i;

	if (!cmd || !cmd->args || !g || !g->envlst)
		return ;
	i = 1;
	while (cmd->args[i])
	{
		unset_one(&g->envlst, cmd->args[i]);
		i++;
	}
}
