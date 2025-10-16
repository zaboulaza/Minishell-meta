/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:21:10 by lchapot           #+#    #+#             */
/*   Updated: 2025/10/16 16:52:52 by lchapot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_satoi	ps_atoi(char *str)
{
	t_satoi	res;
	int		i;
	int		sign;

	res = (t_satoi){0};
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (res.err_code = -1, res);
		res.val *= 10;
		res.val += str[i] - '0';
		i++;
	}
	if ((res.val * sign) > LLONG_MAX || (res.val * sign) < LLONG_MIN)
		return (res.err_code = -1, res);
	return (res.val *= sign, res);
}
