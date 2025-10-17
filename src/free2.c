/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:18:27 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/17 17:38:55 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	free_envlst(t_env *envlst)
{
	t_env *tmp;

	while (envlst)
	{
		tmp = envlst->next;
		free(envlst->key);
		free(envlst->value);
		free(envlst);
		envlst = tmp;
	}
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_node(t_node *node)
{
	t_node	*tmp;

	while (node)
	{
		tmp = node->next;
		free(node->content);
		free(node);
		node = tmp;
	}
}
void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_files	*file_tmp;
	t_files	*file_next;

	while (cmd)
	{
		if (cmd->args)
			free_all_(cmd->args);
		file_tmp = cmd->files;
		while (file_tmp)
		{
			file_next = file_tmp->next;
			if (file_tmp->path)
				free(file_tmp->path);
			if (file_tmp->heredoc_content)
				free_all_(file_tmp->heredoc_content);
			free(file_tmp);
			file_tmp = file_next;
		}
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}

void	free_pwd(t_pwd *pwd)
{
	if (pwd->prev)
		free(pwd->prev);
	if (pwd->tmp)
		free(pwd->tmp);
	if (pwd->new)
		free(pwd->new);
	free(pwd);
}
