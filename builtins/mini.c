/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:09:45 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/11 18:43:31 by nsmail           ###   ########.fr       */
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
	(void)g;
	if (!ft_strcmp(cmd->args[0], "pwd"))
		print_pwd(cmd);
	if (!ft_strcmp(cmd->args[0], "env"))
		get_env(g);                       // ou le env recup
	if (!ft_strcmp(cmd->args[0], "exit")) // revoir le atoi
		manage_exit(cmd);
	if (!ft_strcmp(cmd->args[0], "echo"))
		manage_echo(cmd);
	if (!ft_strcmp(cmd->args[0], "cd"))
		move_cd(cmd, g);
	// if (!ft_strcmp(cmd->args[0], "export"))
	//	do_export(cmd, g);
	// if (!ft_strcmp(cmd->args[0], "unset"))
	//	do_unset(cmd, g);
}
// int	main(int ac, char **av, char **env)
// {
// 	char 	*new_line;make

// 	int		b = 0;
// 	(void)ac;
// 	(void)av;
// 	t_env	**envlst = NULL;
// 	t_pwd	pwds;

// 	pwds = (t_pwd){0}; //san*
// 	init_env(envlst, env);
// 	b = isatty(STDIN_FILENO);
// 	if (b == 1)
// 	{
// 		while (1)
// 		{
// 			new_line = readline("minishell$ ");
// 			if (newline)
// 				add_history(new_line);
// 			if (!ft_strncmp("pwd", new_line, 3))
// 				print_pwd(new_line);
// 			if (!ft_strncmp("env", new_line, 3))
// 				get_env(env);
// 			if (!ft_strncmp("exit", new_line, 4))
// 				manage_exit(new_line);
// 			if (!ft_strncmp("echo", new_line, 4))
// 				manage_echo(new_line);
// 			if (!ft_strncmp("cd", new_line, 2))
// 				move_cd(new_line, &pwds, *envlst);
// 			if (!ft_strncmp("export", new_line, 6))
// 				do_export(new_line, envlst);
// 			if (!ft_strncmp("unset", new_line, 5))
// 				do_unset(new_line, env);
// 			free(new_line);
// 		}
// 	}
// 	////rl_replace_line("...", 0);
// 	////rl_on_new_line();
// 	////rl_redisplay();
// 	////rl_clear_history();
// 	return (0);
// }
