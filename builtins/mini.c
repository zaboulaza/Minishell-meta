/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:09:45 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/09 15:26:46 by lchapot          ###   ########.fr       */
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


int	main(int ac, char **av, char **env)
{
	char 	*new_line;
	int		b = 0;
	(void)ac;
	(void)av;
	t_env	**envlst = NULL;
	t_pwd	pwds;

	pwds = (t_pwd){0}; //san*
	init_env(envlst, env);
	b = isatty(STDIN_FILENO);
	if (b == 1)
	{
		while (1)
		{
			new_line = readline("minishell$ ");
			if (newline)
				add_history(new_line);
			if (!ft_strncmp("pwd", new_line, 3))
				print_pwd(new_line);
			if (!ft_strncmp("env", new_line, 3))
				get_env(env);
			if (!ft_strncmp("exit", new_line, 4))
				manage_exit(new_line);
			if (!ft_strncmp("echo", new_line, 4))
				manage_echo(new_line);
			if (!ft_strncmp("cd", new_line, 2))
				move_cd(new_line, &pwds, *envlst);
			if (!ft_strncmp("export", new_line, 6))
				do_export(new_line, envlst);
			if (!ft_strncmp("unset", new_line, 5))
				do_unset(new_line, env);
			free(new_line);
		}
	}
	////rl_replace_line("...", 0);
	////rl_on_new_line();
	////rl_redisplay();
	////rl_clear_history();
	return (0);
}
