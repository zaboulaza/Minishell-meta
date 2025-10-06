/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:52:52 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/06 20:52:58 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int exec(t_cmd *cmd, t_general *g)
{
    if (cmd == NULL)
        return (1);
    get_path(g);
    if (cmd->type == CMD || cmd->type == SUBSHELL) {
        if (/* built-in */ 0 ) {
            
        } else {
            int pid = ft_fork();
            if (pid == 0)
                exit(exec_ast(cmd, g));
            g->status = waitepid_and_status(pid, g);
        }
    }
    else
        exec_ast(cmd, g);
    return (0);
}

// int exec(t_cmd *cmd, t_general *g)
// {
//     get_path(g);
//     if (cmd->type == CMD || cmd->type == SUBSHELL) {
//         if (/* built-in */ 0 ) {
            
//         } else {
//             int pid = fork();
//             if (pid == 0)
//                 exit(exec_ast(init_ast(cmd, false), g));
//             wait(NULL);
//         }
//     }
//     else if (exec_ast(init_ast(cmd, false), g) == 1)
//     {
//         return (1);
//     }
//     return (0);
// }

// #include "../mini.h"

// int exec(t_cmd *cmd, t_general *g)
// {
//     get_path(g);
//     if (cmd->type == CMD) {
//         if (/* built-in */ 0 ) {
            
//         } else {
//             int pid = fork();
//             if (pid == 0)
//                 exit(exec_ast(init_ast(cmd, false), g));
//             wait(NULL);
//         }
//     }
//     else if (exec_ast(init_ast(cmd, false), g) == 1)
//     {
//         return (1);
//     }
//     return (0);
// }

