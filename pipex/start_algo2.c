/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_algo2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 01:55:31 by nsmail            #+#    #+#             */
/*   Updated: 2025/09/27 16:33:52 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <sys/wait.h>

int	here_doc(t_general *g, char **av)
{
	char	*line;

	if (pipe(g->here_fd) == -1)
	{
		free_function(g);
		perror("pipe");
		return (1);
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
		if (!line)
			return (1);
		if (!line || (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0
				&& line[ft_strlen(av[2])] == '\n'))
		{
			free(line);
			break ;
		}
		write(g->here_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(g->here_fd[1]);
	return (0);
}

int	start_algo_here_doc(t_general *g, int ac, char **av)
{
	int		pipefd[4];
	pid_t	*pipes;
	int		nb_av;
	int		i_pipe;

	nb_av = 0;
	i_pipe = 0;
	pipes = malloc(sizeof(pid_t) * (ac - 4));
	if (!pipes)
		return (perror("malloc"), 1);
	if (here_doc(g, av) == 1)
		return (1);
	pipefd[0] = g->here_fd[0];
	while (i_pipe < ac - 5)
	{
		if (pipe(pipefd + 2) == -1)
			return (perror("pipe"), 1);
		child_here(g, pipefd, i_pipe, pipes);
		(close(pipefd[0]), close(pipefd[3]), i_pipe++);
		pipefd[0] = pipefd[2];
	}
	child_last_here(g, pipefd, i_pipe, pipes);
	return (close023(pipefd), waitpid_here(ac, pipes, g), free(pipes), 0);
}

void	child_here(t_general *g, int *pipefd, int i_pipe, pid_t *pipes)
{
	int	nb_av;

	pipes[i_pipe] = fork();
	if (pipes[i_pipe] == 0)
	{
		dup2(pipefd[0], 0);
		dup2(pipefd[3], 1);
		close023(pipefd);
		nb_av = i_pipe + g->i_av;
		if (start_exec(g, nb_av) == 1)
		{
			if (pipes)
				free(pipes);
			free_function(g);
			exit(127);
		}
	}
}

void	child_last_here(t_general *g, int *pipefd, int i_pipe, pid_t *pipes)
{
	int	nb_av;

	pipes[i_pipe] = fork();
	if (pipes[i_pipe] == 0)
	{
		pipefd[3] = open(g->av[g->ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
		dup2(pipefd[0], 0);
		dup2(pipefd[3], 1);
		close023(pipefd);
		nb_av = i_pipe + g->i_av;
		if (start_exec(g, nb_av) == 1)
		{
			if (pipes)
				free(pipes);
			free_function(g);
			exit(127);
		}
	}
}

void	waitpid_here(int ac, pid_t *pipes, t_general *g)
{
	int	i;

	i = 0;
	while (i < ac - 5)
	{
		waitpid(pipes[i], &g->status, 0);
		if (WIFEXITED(g->status))
			g->status = WEXITSTATUS(g->status);
		else if (WIFSIGNALED(g->status))
			g->status = WTERMSIG(g->status);
		i++;
	}
}
