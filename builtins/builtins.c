/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:09:45 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/17 17:41:54 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

void	exec_built_in(t_cmd *cmd, t_general *g)
{
	if (!ft_strcmp(cmd->args[0], "pwd"))
		print_pwd(cmd);
	if (!ft_strcmp(cmd->args[0], "env")) //commande dapres bug
		print_env(g);
	if (!ft_strcmp(cmd->args[0], "exit")) // revoir le atoi
		manage_exit(cmd, g);
	if (!ft_strcmp(cmd->args[0], "echo"))
		manage_echo(cmd);
	if (!ft_strcmp(cmd->args[0], "cd"))
		move_cd(cmd, g);
	 if (!ft_strcmp(cmd->args[0], "export"))
		do_export(cmd, g);
	 if (!ft_strcmp(cmd->args[0], "unset"))
		do_unset(cmd, g);
}
