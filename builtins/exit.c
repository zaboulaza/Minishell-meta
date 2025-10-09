/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:13:08 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/09 15:15:30 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	manage_exit(char *new_line)
{
	char	**options;
	t_satoi	res;

	options = ft_split(new_line, ' ');
	if (!options[1]) //ptt a check avant split
	{
		free_double(options);
		printf("exit (0)\n");
		exit(0);
	}
	res = ps_atoi(options[1]);
	if (ft_isalpha(options[1][0]) || res.err_code == -1)
	{
		free_double(options);
		printf("exit\nbash: exit: %s: numeric argument required\n", options[1]);
		exit(2);
	}
	if (res.err_code != -1)
	{
		if (options[2])
		{
			free_double(options);
			printf("exit\nbash: exit: too many argument\n");
			exit(1);
		}
		else
		{
			printf("%lli > exit(%i)", res.val, ((unsigned char)res.val % 256));
			free_double(options);
			exit((unsigned char)res.val % 256);
		}
	}
	//free_double(options); !!!!!!!!
}
