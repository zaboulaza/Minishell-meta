/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:21:10 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/09 19:09:57 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../mini.h"

// //int	full_space(char *str)
// //{
// //	int	i;

// //	i = 0;
// //	while (str[i])
// //	{
// //		if (str[i] != 32)
// //			return (0);
// //		i++;
// //	}
// //	return (1);
// //}

// t_satoi	ps_atoi(char *str)
// {
// 	t_satoi	res;
// 	int		i;
// 	int		sign;

// 	res = (t_satoi){0};
// 	sign = 1;
// 	i = 0;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (str[i])
// 	{
// 		//if (str[i] == 32 && full_space(str + i))
// 		//	return (res.val *= sign, res);
// 		if (!ft_isdigit(str[i]))
// 			return (res.err_code = -1, res);
// 		res.val *= 10;
// 		res.val += str[i] - '0';
// 		i++;
// 	}
// 	if ((res.val * sign) > LLONG_MAX || (res.val * sign) < LLONG_MIN)
// 		return (res.err_code = -1, res);
// 	return (res.val *= sign, res);
// }
