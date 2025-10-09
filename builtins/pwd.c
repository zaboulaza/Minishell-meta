/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:50:16 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/09 15:15:44 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	has_option(char *line)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_strncmp(line + i, "pwd ", 4))
		{
			i+=4;
			break;
		}
		i++;
	}
	while (line[i + flag] == '-')
		flag++;
	if (ft_isalpha(line[i + flag]) && flag <= 1)
		return (line[i + flag]);
	else if (flag > 1)  //line [i+flag] ne doit pas etre un  " "?
		return ('-');
	else
		return (0); //tt ce qui nest pas "pwd -xx" doit return 0, donc autre quoption attache aux -
}

int	print_pwd(char *line) 
{
	char	*pwd;
	char	result;

	result = has_option(line);
	if (!result)
	{
		pwd = getcwd(NULL, 0); //check retour null
		printf("%s\n", pwd);
		free(pwd);
		return (0); //signal
	}
	else if (ft_isalpha(result))
	{
		printf("pwd: bad option: -%c\n", result);
		return (2);
	}
	else if (result == '-')
	{
		printf("pwd: bad option: --\n");
		return (2);
	}
	return (0);
}