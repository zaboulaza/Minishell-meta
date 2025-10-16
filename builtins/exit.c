// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   exit.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/02 15:13:08 by lchapot           #+#    #+#             */
// /*   Updated: 2025/10/09 15:15:30 by lchapot          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

 #include "../mini.h"

void	freeandexit(t_general *g, unsigned char n)
{
	free_all(g);
	exit(n);
}

void	manage_exit(t_cmd *cmd, t_general *g)
{
	t_satoi	res;

	if (!cmd->args[1]) //ptt a check avant split
		freeandexit(g, 0);
	res = ps_atoi(cmd->args[1]);
	if (ft_isalpha(cmd->args[1][0]) || res.err_code == -1)
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", cmd->args[1]);
		freeandexit(g, 2);
	}
	if (res.err_code != -1)
	{
		if (cmd->args[2])
		{
			printf("exit\nbash: exit: too many argument\n");
			freeandexit(g, 1);
		}
		else
			freeandexit(g, (unsigned char)res.val % 256);
	}
}
