/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_third_utils6.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:50:00 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/14 18:03:53 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*handle_heredoc_error(char *all_content, char *line, char *node)
{
	if (!line)
		printf("bash: warning: here-document delimited by \
end-of-file (wanted `%s')\n", node);
	if (g_signal_status == 130)
	{
		free(all_content);
		ft_signal();
		return (NULL);
	}
	return (all_content);
}

char	*process_heredoc_line(char *all_content, char *line)
{
	all_content = ft_strjoin__(all_content, line);
	free(line);
	if (!all_content)
	{
		ft_signal();
		return (NULL);
	}
	return (all_content);
}

char	*read_all_heredoc_lines(char *node)
{
	char	*all_content;
	char	*line;

	all_content = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (!line || g_signal_status == 130)
		{
			all_content = handle_heredoc_error(all_content, line, node);
			break ;
		}
		if (ft_strcmp(line, node) == 0 && ft_strlen(line) == ft_strlen(node))
		{
			free(line);
			break ;
		}
		all_content = process_heredoc_line(all_content, line);
		if (!all_content)
			return (NULL);
	}
	return (all_content);
}
