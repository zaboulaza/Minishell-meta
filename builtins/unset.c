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

void	do_unset(t_cmd *cmd, t_general *g) //chaque arg = une val a unset
{
	size_t	i;

	i = 0;
	while (cmds->args[i])
	{
		if (find_variable(g->env, cmds->args[i]))
		{
			ft_putstr_fd("unset_it", 1);
			//exit code 0
		}
		else
		{
			ft_putstr_fd("bash: unset: ", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			//exit code 1
		}
	}
}
