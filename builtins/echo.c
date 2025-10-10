/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:05:37 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/10 20:25:22 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../mini.h"

 int	manage_echo(t_cmd *cmd)
 {
 	int	i;
 	int	flag;

 	i = 1;
	if (!cmd->args[1])
		return (printf("\n"), 0);
	while (cmd->args[i] && !ft_strcmp(cmd->args[i], "-n"))
		i++;
	flag = i;
	if (!cmd->args[i])
		return (0);
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
 	if (flag == 1)
 		printf("\n");
 	return (0);
 }