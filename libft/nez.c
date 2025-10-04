/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nez.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:16:40 by nsmail            #+#    #+#             */
/*   Updated: 2025/06/20 22:20:10 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar2(int c)
{
	int	i;

	i = 1;
	write(1, &c, 1);
	return (i);
}

int	ft_putstr2(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr2("(null)");
		return (6);
	}
	while (str[i])
	{
		ft_putchar2(str[i]);
		i++;
	}
	return (i);
}

int	count_int(long nb)
{
	int	nb_len;

	nb_len = 1;
	if (nb < 0)
	{
		nb_len++;
		nb = -nb;
	}
	while (nb > 9)
	{
		nb = nb / 10;
		nb_len++;
	}
	return (nb_len);
}

int	ft_putchar_maj_min(int a, char c)
{
	if (c == 'x')
	{
		ft_putchar2(a + 32);
	}
	else
	{
		ft_putchar2(a);
	}
	return (0);
}

int	ft_putnbr2(int nb)
{
	long	n;
	int		i;

	i = count_int(nb);
	n = nb;
	if (n < 0)
	{
		ft_putchar2('-');
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr2(n / 10);
		ft_putnbr2(n % 10);
	}
	else
	{
		ft_putchar2(n + '0');
	}
	return (i);
}

// #include <stdio.h>

// int	main(void)
// {
// 	// int i = ft_putnbr2(-1234);
// 	int i = ft_putstr2("-1234abcd");
// 	printf("\n");
// 	ft_printf("taille g % = %d\n", i);
// 	// printf("\n");
// }