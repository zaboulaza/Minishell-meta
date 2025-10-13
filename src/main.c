/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:24:27 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/13 18:07:34 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

volatile sig_atomic_t	g_signal_status = 0;

int	main(int ac, char **av, char **env)
{
	t_general	g;

	creat_struct(&g, ac, av, env);
	while (1)
	{
		g.node = NULL;
		g.cmd = NULL;
		g.signaled = 0;
		g_signal_status = 0;
		ft_signal();
		g.one_line = readline("mini> ");
		g.envlst = env_to_envlst(env);
		if (!g.envlst)
			return (perror("env_to_envlst"), 1);
		if (g_signal_status != 0) //?
			continue ;
		if (!g.one_line)
		{
			printf("exit\n");
			free_all(&g);
			break ;
		}
		add_history(g.one_line);
		if (*g.one_line)
		{
			if (parsing_general(&g, &g.tmp) == 1)
			{
				free_all(&g);
				printf("ftg\n");
				return (1);
			}
			if (exec(init_ast(g.cmd, false), &g) == 1)
			{
				free_all(&g);
				printf("chut\n");
				return (1);
			}
			if (g.signaled == 128 + SIGINT)
				write(2, "\n", 1);
			else if (g.signaled == 128 + SIGQUIT)
				write(2, "Quit (core dumped)\n", 19);
			// print_list(g.node);
			// print_ast(init_ast(g.cmd, false), 0);
			// print_AST_test(init_ast(g.cmd, false));
			// print_list_cmd(g.cmd);
			free_all(&g);
		}
	}
	free_all(&g);
	return (0);
}

void	creat_struct(t_general *g, int ac, char **av, char **env)
{
	ft_memset(g, 0, sizeof(t_general));
	g->ac = ac;
	g->av = av;
	g->env = env;
	g->node = NULL;
	g->pwd = malloc(sizeof(t_pwd));
	if (!g->pwd)
		exit(1);
}

void	free_all(t_general *g)
{
	if (g)
	{
		if (g->one_line)
		{
			free(g->one_line);
			g->one_line = NULL;
		}
		if (g->node)
		{
			free_node(g->node);
			g->node = NULL;
		}
		if (g->cmd)
		{
			free_cmd(g->cmd);
			g->cmd = NULL;
		}
		if (g->path)
		{
			free_all_(g->path);
			g->path = NULL;
		}
	}
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
			free(file_tmp);
			file_tmp = file_next;
		}
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
}

void	clear_tmp(t_tmp **tmp)
{
	t_tmp	*cur;
	t_tmp	*next;

	cur = *tmp;
	while (cur)
	{
		next = cur->next;
		free(cur->path);
		free(cur);
		cur = next;
	}
	*tmp = NULL;
}

// void	print_list_cmd(t_cmd *cmd)
// {
// 	int		i;
// 	t_files	*tmp_files;
// 	int		j;

// 	while (cmd != NULL)
// 	{
// 		printf("type = %d\n", cmd->type);
// 		i = 0;
// 		if (cmd->args != NULL)
// 		{
// 			while (cmd->args[i] != NULL)
// 			{
// 				printf("{cmd} // arg = %s\n", cmd->args[i]);
// 				i++;
// 			}
// 		}
// 		tmp_files = cmd->files;
// 		while (tmp_files != NULL)
// 		{
// 			printf("{files} // path = %s\n", tmp_files->path);
// 			printf("{files} // mode = %d\n", tmp_files->mode);
// 			if (tmp_files->heredoc_content != NULL)
// 			{
// 				j = 0;
// 				printf("{heredoc} content:\n");
// 				while (tmp_files->heredoc_content[j] != NULL)
// 				{
// 					printf("  [%d] %s\n", j, tmp_files->heredoc_content[j]);
// 					j++;
// 				}
// 			}
// 			tmp_files = tmp_files->next;
// 		}
// 		printf("\n");
// 		cmd = cmd->next;
// 	}
// }

// void    print_indent(int depth)
// {
//     for (int i = 0; i < depth; i++)
//         printf("    "); // indentation (4 espaces)
// }

// void    print_ast(t_cmd *node, int depth)
// {
//     if (!node)
//         return ;

//     // Indentation + affichage du type
//     print_indent(depth);
//     if (node->type == PIPE)
//         printf("PIPE\n");
//     else if (node->type == AND)
//         printf("AND\n");
//     else if (node->type == OR)
//         printf("OR\n");
//     else if (node->type == CMD)
//     {
//         printf("CMD");
//         if (node->args && node->args[0])
//             printf(" (%s)", node->args[0]); // affiche la commande
//         printf("\n");
//     }
//     else
//         printf("UNKNOWN(%d)\n", node->type);

//     // Appel récursif sur left et right
//     if (node->left)
//     {
//         print_indent(depth);
//         printf("├── left:\n");
//         print_ast(node->left, depth + 1);
//     }
//     if (node->right)
//     {
//         print_indent(depth);
//         printf("└── right:\n");
//         print_ast(node->right, depth + 1);
//     }
// }

// void	print_list(t_node *node)
// {
// 	while (node != NULL)
// 	{
// 		printf("{LIST} type = %d\n", node->type);
// 		printf("{LIST} content = %s\n", node->content);
// 		printf("\n");
// 		node = node->next;
// 	}
// }