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

 //void add_env(t_env **env, char *key, char *value)
 //{
 	//
 //}

 //t_env *find_env(t_env *env, char *key)
 //{
 	//return 0 si pas trouvee 1 si trouvee
 //}

 int is_valid_identifier(char *str)
 {
 	if (!str)
 		return (0); //si pb 
 	return (1); //si ok
 	//doit commencer par isalpha ou is_ puis isalnum ou is_
 }

 char *extract_key(char *new_line)
 {
 	return (new_line);
 }
 char *extract_value(char *new_line)
 {
 	return (new_line);
 }
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

 int	do_export(char *new_line, t_env **envlst) //ptr sur env
 {
 	//si pas arg, affiche les variables differement que env
 	char *key = extract_key(new_line);
 	char *val = extract_value(new_line);

 	if (!ft_strcmp(new_line, "export"))
 		print_export(*envlst); //si pas darg
 	//if (!is_valid_identifier(str))
 	//return (ft_putstr_fd("export: `%s`: not a valid identifier\n", 2),0);
 	//if (find_env(*env, key)) //variable connue dans env
 	//{
 		//if (=) 
 		//{
 		//	free(env->value);
 		//	env->value = ft_strdup(val);
 		//}
 	//}
 	//else
 	//{
 		//add_env(env, key, value);
 	//}
 	free(key);
 	free(val);
 	return (1);
 }
