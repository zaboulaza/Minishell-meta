/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:20:13 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/13 18:38:37 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../mini.h"

void	move_cd(t_cmd *cmd, t_general *g) //cd tt seul marche pas grr
{
	int		i;
	char	*home;
	
	i = 0;
	while (cmd->args[i])
		i++;
	g->pwd->tmp = getcwd(NULL, 0);
	if (i > 2)
		ft_putstr_fd("cd: too many arguments\n", 2);
	else if (i == 2 && (!cmd->args[1] || !ft_strcmp(cmd->args[1], "--") || !ft_strcmp(cmd->args[1], "~")))
	{
		home = get_env_value(g, "HOME");
		if (!home)
			ft_putstr_fd("cd: HOME not set\n", 2);
		printf("i go HOME\n");
		chdir(home); //free(home);
		g->pwd->prev = g->pwd->tmp;
		g->pwd->new = g->pwd->prev;
	}
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		if (!chdir(g->pwd->prev))
		{
			printf("%s\n", g->pwd->prev);
			//free(pwd->prev)
			g->pwd->prev = g->pwd->tmp;
			g->pwd->new = g->pwd->prev;
		}
		else
		{
			if (!g->pwd->prev)
				ft_putstr_fd("cd: OLDPWD not set\n", 2);
			else
				perror("cd"); //si pwdprev est suppr
		}
	}
	else
	{
		if (!chdir(cmd->args[1])) //est ok acces<
		{
			printf("i go at [%s]\n", cmd->args[1]);
			g->pwd->prev = g->pwd->tmp; 
			g->pwd->new = getcwd(NULL, 0);//mettre a jour newpwd prevwd
		}
		else
		{
			ft_putstr_fd("cd: no such file or directory: ", 2);
			ft_putstr_fd(cmd->args[1], 2);
			ft_putstr_fd("\n", 2);
		}	
	}
}

