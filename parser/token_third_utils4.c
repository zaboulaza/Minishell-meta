/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_third_utils4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaboulaza <zaboulaza@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 15:55:59 by nsmail            #+#    #+#             */
/*   Updated: 2025/09/15 22:38:14 by zaboulaza        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	add_tmp_to_list(t_cmd *cmd, t_tmp **tmp)
{
	t_tmp	*tmp_;
	t_files	*new;
	t_files	*last;

	tmp_ = *tmp;
	while (tmp_)
	{
		new = malloc(sizeof(t_files));
		ft_bzero(new, sizeof(t_files));
		new->mode = tmp_->mode;
		new->path = ft_strdup(tmp_->path);
		if (tmp_->mode == HEREDOC)
			new->heredoc_content = cpy_char_tab(tmp_->heredoc_content);
		new->next = NULL;
		if (cmd->files == NULL)
			cmd->files = new;
		else
		{
			last = cmd->files;
			while (last->next)
				last = last->next;
			last->next = new;
		}
		tmp_ = tmp_->next;
	}
}

void	remove_invalid_cmds(t_cmd **cmd_list)
{
	t_cmd	*current;
	t_cmd	*prev;
	t_cmd	*next;

	current = *cmd_list;
	prev = NULL;
	while (current)
	{
		next = current->next;
		if (current->type == 100)
		{
			if (prev)
				prev->next = next;
			else
				*cmd_list = next;
			free(current);
			current = next;
		}
		else
		{
			prev = current;
			current = next;
		}
	}
}

int	find_arg_norm_parent2(t_node *node)
{
	t_node	*size;
	int		count;
	int		counted;

	count = 0;
	counted = 0;
	size = node;
	while (size)
	{
		if (size->type == OPEN_PAREN)
			counted++;
		else if (size->type == CLOSE_PAREN)
			counted--;
		count++;
		if (counted == 0)
			break ;
		size = size->next;
	}
	return (count);
}

char	**heredoc_content(char *node)
{
	char	*all_content;
	char	*line;
	char	**result;

	all_content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("not found end-of file\n");
			break ;
		}
		if (ft_strncmp(line, node) == 0)
		{
			free(line);
			break ;
		}
		all_content = ft_strjoin__(all_content, line);
		if (!all_content)
			return (NULL);
	}
	result = ft_split(all_content, '\n');
	free(all_content);
	return (result);
}

char	*ft_strjoin__(char *s1, char const *s2)
{
	size_t	tailleg;
	int		i;
	size_t	j;
	char	*s3;

	if (!s1)
		return (NULL);
	tailleg = ft_strlen(s1) + ft_strlen(s2);
	i = -1;
	s3 = malloc(tailleg + 2);
	if (!s3)
		return (free(s1), NULL);
	while (s1[++i])
		s3[i] = s1[i];
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\n';
	s3[i + 1] = '\0';
	free(s1);
	return (s3);
}
