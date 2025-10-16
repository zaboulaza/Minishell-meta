/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:20:13 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/15 15:47:29 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../mini.h"

void	err_cd(t_cmd *cmd, t_general *g, int flag)
{
	if (flag == 1)
	{
		if (!g->pwd->prev)
			ft_putstr_fd("cd: OLDPWD not set\n", 2);
		else
			perror("cd"); 	
	}
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("\n", 2);
	}	
}

void	change_cd(t_general *g, int flag)
{
	if (flag == 1)
	{
		printf("%s\n", g->pwd->prev);
		g->pwd->prev = g->pwd->tmp;
		g->pwd->new = g->pwd->prev;
	}
	if (flag == 2)
	{
		g->pwd->prev = g->pwd->tmp; 
		g->pwd->new = getcwd(NULL, 0);
	}
}

void	cd_home(t_general *g)
{
	char	*home;

	home = get_env_value(g, "HOME");
	if (!home)
		ft_putstr_fd("cd: HOME not set\n", 2);
	chdir(home); //free(home);
	g->pwd->prev = g->pwd->tmp;
	g->pwd->new = g->pwd->prev;
	free (home);
}

void	move_cd(t_cmd *cmd, t_general *g)
{
	int		i;
	
	i = 0;
	while (cmd->args[i])
		i++;
	if (i > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	g->pwd->tmp = getcwd(NULL, 0);
	if (i == 1 || !ft_strcmp(cmd->args[1], "--") || !ft_strcmp(cmd->args[1], "~"))
		cd_home(g);
	else if (i <= 2 && !ft_strcmp(cmd->args[1], "-"))
	{
		if (!chdir(g->pwd->prev))
			change_cd(g, 1);
		else
			err_cd(cmd, g, 1);
	}
	else if (i <= 2)
	{
		if (!chdir(cmd->args[1]))
			change_cd(g, 2);
		else
			err_cd(cmd, g, 2);
	}
}
