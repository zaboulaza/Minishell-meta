/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:05:37 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/10 15:18:07 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../mini.h"

 int	pass_option(char *new_line)
 {
 	int	i;

 	i = 0;
 	while (new_line[i]) //echo -nnn
 	{
 		if (!ft_strncmp(new_line + i, "-n ", 3))
 			i+=3;
 		else
 			break;
 	}
 	return (i);
 }
 int	manage_echo(char *new_line) //en vrai sera split
 {
 	int	i; //echo sans rien = cmd not found ???
 	int	flag;

 	i = 5; 
 	if (ft_strncmp(new_line + 4, " ", 1))
 		return (ft_putstr_fd(new_line, 2), ft_putstr_fd(": command not found\n", 2), 127);
 	else
 	{
 		flag = pass_option(new_line + i); //je passe les -n bien ecrit
 		{
 			printf("%s", new_line + i + flag);
 			if (!flag)
 				printf("\n");
 		}
 	}
 	// +7(l.88) et il faut tous les passer dabord
 	return (0);
 	//l.94? comme dans printf en soit
 }