/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_verif_parent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:58:24 by nsmail            #+#    #+#             */
/*   Updated: 2025/09/17 15:49:27 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	last_verif_parent(t_cmd *cmd)
{
	t_cmd	*cmd_;

	cmd_ = cmd;
	while (cmd_)
	{
		if (cmd_->next && cmd_->type == CMD && cmd_->next->type == SUBSHELL)
		{
			printf("error: CMD cannot be followed by SUBSHELL\n");
			return (1);
		}
		else if (cmd_->next && cmd_->type == SUBSHELL
			&& cmd_->next->type == CMD)
		{
			printf("error: SUBSHELL cannot be followed by CMD\n");
			return (1);
		}
		cmd_ = cmd_->next;
	}
	return (0);
}
