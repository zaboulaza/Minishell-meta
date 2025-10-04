/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 20:57:32 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/04 14:24:15 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	exec_cmd(t_cmd *cmd, t_general *g)
{
	int		i;
	int		compt;
	t_files	*tmp_files;

	i = 0;
	tmp_files = cmd->files;
	compt = compt_heredoc(cmd);
	while (tmp_files)
	{
		if (redir_g(tmp_files) == 1)
			return (1);
		compt = redir_heredoc(tmp_files, compt);
		tmp_files = tmp_files->next;
	}
	cmd->args = expand(cmd->args, g);
	cmd->args = removed_quoat(cmd->args);
	while (g->path[i])
	{
		g->path[i] = ft_strjoin(g->path[i], cmd->args[0]);
		i++;
	}
	make_execve(cmd, g);
	return (1);
}

char	**removed_quoat(char **arg)
{
	int		i;
	char	*old_arg;

	i = 0;
	while (arg[i])
	{
		if (find_quote(arg[i]) == 1)
		{
			old_arg = arg[i];
			arg[i] = remove_outer_quotes(arg[i]);
			free(old_arg);
		}
		i++;
	}
	return (arg);
}

int	process_quote_content(char *str, int *i, char *result, int *j, char quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
		result[(*j)++] = str[(*i)++];
	if (str[*i] == quote)
		(*i)++;
	return (*i);
}

char	*remove_outer_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"')
			process_quote_content(str, &i, result, &j, '"');
		else if (str[i] == 39)
			process_quote_content(str, &i, result, &j, 39);
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	waitepid_and_status(pid_t pipes)
{
	int	status;

	waitpid(pipes, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status);
	return (status);
}
