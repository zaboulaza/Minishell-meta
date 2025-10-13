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

int	find_variable(char **env, char *arg)
{
	size_t i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], arg, ft_strlen(arg)))
			return (1);
		i++;
	}
	return (0);
}
//faire ca dans mon envlst
void	do_unset(t_cmd *cmd, t_general *g) //chaque arg = une val a unset
{
	size_t	i;

	i = 1;
	while (cmd->args[i])
	{
		if (find_variable(g->env, cmd->args[i]))
		{
			ft_putstr_fd("unset_it\n", 1);
			//ft_lstdelone(*envlst, del());
			//exit code 0
		}
		else
		{
			ft_putstr_fd("bash: unset: ", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			//g->status = 1; = //exit code 1
		}
		i++;
	}
}
