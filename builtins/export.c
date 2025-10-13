// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   export.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/10/03 13:20:04 by lchapot           #+#    #+#             */
// /*   Updated: 2025/10/09 15:15:33 by lchapot          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

 #include "../mini.h"

void print_export(t_env *env)
{
	// trie ta liste si besoin
	while (env)
	{
		printf("declare -x %s", env->key);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
}

int	do_export(t_cmd *cmd, t_general *g) //ptr sur env
{
 	//si pas arg, affiche les variables differement que env
 	//char *key = extract_key(cmd->args);
 	//char *val = extract_value(cmd->args);

	if (!cmd->args[1])
		print_export(g->envlst);
	//if (!is_valid_identifier(cmd->args[1]))
	//return (ft_putstr_fd("export: `%s`: not a valid identifier\n", 2),0);
	//if (find_env(g->*env, key)) //variable connue dans env
	//{
	//	if (ft_strchr(cmd->args[1], '=')) //found
	//	{
	//		free(env->value);
	//		env->value = ft_strdup(val);
	//	}
	//}
	//else
	//{
	//	add_env(env, key, value);
	//}
	//free(key);
	//free(val);
	return (1);
}

