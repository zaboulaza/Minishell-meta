/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:53:49 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/17 18:53:51 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	print_env(t_cmd *cmds, t_general *g)
{
	char	**env_curr;
	int		i;

	i = 0;
	if (cmds->args[1] && ft_strcmp(cmds->args[1], "env"))
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(cmds->args[1], 2);
		ft_putstr_fd(": no such file or directory\n", 2);
		//return (127);
		return ;
	}
	env_curr = lst_to_envp(g->envlst);
	while (env_curr[i])
	{
		printf("%s\n", env_curr[i]);
		i++;
		//return (0);
	}
	//free_all_(env_curr);
}