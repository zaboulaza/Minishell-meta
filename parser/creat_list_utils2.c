/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:17:31 by nsmail            #+#    #+#             */
/*   Updated: 2025/09/05 17:24:10 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	find_content_norm1(char *line)
{
	int		lenght;
	char	quote;
	char	*special;

	special = "|&()<>";
	lenght = 0;
	while (line[lenght])
	{
		if (line[lenght] == '"' || line[lenght] == 39)
		{
			quote = line[lenght++];
			while (line[lenght] && line[lenght] != quote)
				lenght++;
			if (line[lenght + 1])
				lenght++;
			while (line[lenght] != '\0' && ispacce(line[lenght]) != 1)
				lenght++;
		}
		if (ft_strchr(special, line[lenght]) != NULL
			|| ispacce(line[lenght]) == 1)
			break ;
		lenght++;
	}
	return (lenght);
}
