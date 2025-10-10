/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 13:20:13 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/10 15:18:13 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../mini.h"

 t_pwd	*move_cd(char *new_line, t_pwd *pwds, t_env *envlst) //cd tt seul marche pas grr
 {
 	char	**arg;
 	int	i;
 	char	*home;

 	i = 0;
 	arg = ft_split(new_line, ' ');
 	if (!arg)
 		return (NULL);
 	while (arg[i])
 		i++;
 	//if (pwds->tmp)
 	//	free(pwds->tmp); ?
 	pwds->tmp = getcwd(NULL, 0); //pwd a free?
 	if (i > 2)
 		return (free_double(arg), ft_putstr_fd("cd: too many arguments\n", 2), pwds);
 	if (i == 1 || !ft_strcmp(arg[1], "--") || !ft_strcmp(arg[1], "~"))
 	{
 		home = get_env_value(envlst, "HOME");
 		if (!home)
 			return (ft_putstr_fd("cd: HOME not set\n", 2), pwds);
 		printf("i go HOME\n");
 		chdir(home); //free(home);
 		pwds->prev = pwds->tmp;
 		pwds->new = pwds->prev;
 	}
 	else if (!ft_strcmp(arg[1], "-"))
 	{
 		if (!chdir(pwds->prev))
 		{
 			printf("%s\n", pwds->prev);
 			//free(pwds->prev)
 			pwds->prev = pwds->tmp;
 			pwds->new = pwds->prev;
 		}
 		else
 		{
 			if (!pwds->prev)
 				ft_putstr_fd("cd: OLDPWD not set\n", 2);
 			else
 				perror("cd:"); //si pwdprev est suppr
 		}
 	}
 	else
 	{
 		if (!chdir(arg[1])) //est ok acces<
 		{
 			printf("i go at [%s]\n", arg[1]);
 			pwds->prev = pwds->tmp; 
 			pwds->new = getcwd(NULL, 0);//mettre a jour newpwd prevwd
 		}
 		else
 		{
 			ft_putstr_fd("cd: no such file or directory: ", 2);
 			ft_putstr_fd(arg[1], 2);
 			ft_putstr_fd("\n", 2);
 		}	
 	}
 	return(free_double(arg), pwds); // printf("RETURN LAST\n"), 
 	//free(pwds->tmp);
 }
