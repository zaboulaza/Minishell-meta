// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   pwd.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/02 14:50:16 by lchapot           #+#    #+#             */
// /*   Updated: 2025/10/09 15:15:44 by lchapot          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

 #include "../mini.h"

 char	has_option(char *line)
 {
 	int	i;

 	i = 0;
	if (!line)
		return (0);
 	while (line[i] == '-')
 		i++;
 	if (ft_isalpha(line[i]) && i == 1)
 		return (line[i]);
 	else if (i > 1)
 		return ('-');
 	return (0);
 }

int	print_pwd(t_cmd *cmd)

 {
 	char	*pwd;
 	char	result;

 	result = has_option(cmd->args[1]);
 	if (!result)
 	{
 		pwd = getcwd(NULL, 0); //check retour null
 		printf("%s\n", pwd);
 		free(pwd);
 		return (0); //signal
 	}
	else
 		return (printf("pwd: bad option: -%c\n", result), 2);
 	return (0);
 }