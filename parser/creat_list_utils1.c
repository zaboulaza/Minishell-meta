/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:17:00 by nsmail            #+#    #+#             */
/*   Updated: 2025/09/25 23:25:17 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	find_type(char *line)
{
	if (*line == '|' && *(line + 1) != '|')
		return (PIPE);
	if (*line == '|' && *(line + 1) == '|')
		return (OR);
	if (*line == '&' && *(line + 1) == '&')
		return (AND);
	if (*line == '(')
		return (OPEN_PAREN);
	if (*line == ')')
		return (CLOSE_PAREN);
	if (*line == '<' && *(line + 1) != '<')
		return (REDIR_IN);
	if (*line == '>' && *(line + 1) != '>')
		return (REDIR_OUT);
	if (*line == '<' && *(line + 1) == '<')
		return (HEREDOC);
	if (*line == '>' && *(line + 1) == '>')
		return (REDIR_APPEND);
	return (WORD);
}

char	*find_content(char *line)
{
	int		lenght;
	char	*special;
	char	*result;
	char	*trimmed;

	special = "|&()<>";
	lenght = 0;
	if (line[lenght] == '"' || line[lenght] == 39)
		lenght += find_content_norm1(line);
	else if (ft_strchr(special, *line) != NULL)
		return (ft_substr(line, 0, find_content_norm(line)));
	else
	{
		lenght += find_content_norm1(line);
		result = ft_substr(line, 0, lenght);
		trimmed = ft_strtrim(result, " \t\n\r\v\f");
		free(result);
		return (trimmed);
	}
	return (ft_substr(line, 0, lenght));
}

int	find_content_norm(char *line)
{
	if (*line == '|' && *(line + 1) != '|')
		return (1);
	if ((*line == '|' && *(line + 1) == '|') || (*line == '&' && *(line
				+ 1) == '&'))
		return (2);
	if ((*line == '(') || (*line == ')'))
		return (1);
	if ((*line == '<' && *(line + 1) != '<') || (*line == '>' && *(line
				+ 1) != '>'))
		return (1);
	if ((*line == '<' && *(line + 1) == '<') || (*line == '>' && *(line
				+ 1) == '>'))
		return (2);
	return (0);
}

int	ispacce(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	list_size(t_node *node)
{
	int	i;

	i = 0;
	while (node != NULL)
	{
		node->id = i;
		i++;
		node = node->next;
	}
	return (0);
}
