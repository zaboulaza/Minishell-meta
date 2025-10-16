/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:54:01 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/16 16:54:33 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../mini.h"

void print_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

int	print_env(t_general *g)
{
	while (g->envlst)
	{
		printf("%s=%s\n", g->envlst->key, g->envlst->value);
		g->envlst = g->envlst->next;
	}
	return (0);
}
