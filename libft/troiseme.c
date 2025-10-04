/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   troiseme.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:02:31 by nsmail            #+#    #+#             */
/*   Updated: 2025/06/20 22:20:38 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_hexa_pointer(unsigned long nb)
{
	int	nb_len;

	nb_len = 1;
	if (nb < 0)
	{
		nb_len++;
		nb = -nb;
	}
	while (nb > 16)
	{
		nb = nb / 16;
		nb_len++;
	}
	return (nb_len);
}

int	ft_putnbr_hexa_pointer(unsigned long nb, int is_null)
{
	int	i;

	if (is_null == 1)
		i = ft_putstr2("(nil)");
	else
	{
		i = count_hexa_pointer(nb);
		if (nb > 16)
		{
			ft_putnbr_hexa_pointer(nb / 16, 0);
			ft_putnbr_hexa_pointer(nb % 16, 0);
		}
		else
		{
			if (nb == 16)
				i = ft_putstr2("10");
			if (nb >= 10 && nb <= 15)
				(ft_putchar2('a' + (nb % 10)));
			else if (nb != 16)
				(ft_putchar2(nb + '0'));
		}
	}
	return (i);
}

// #include <limits.h>
// int	main(void)
// {
// 	int i = ft_printf(" %p ", (void *)0);
// 	printf("\n");
// 	printf("\n");
// 	printf("%d", i);
//     printf("\n");
// 	printf("\n");
// 	i = printf(" %p ", (void *)0);
// 	printf("%d", i);
// 	// i = ft_putnbr_hexa_pointer(127);

// 	// int c = printf("%p\n", (void *)127);
// }