/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conconbre.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:41:45 by nsmail            #+#    #+#             */
/*   Updated: 2025/06/20 22:20:28 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_hexa(unsigned int nb)
{
	unsigned long long	nb_len;

	nb_len = 1;
	while (nb > 16)
	{
		nb = nb / 16;
		nb_len++;
	}
	return (nb_len);
}

int	ft_putnbr_hexa(char c, unsigned int nb)
{
	unsigned int	i;

	i = count_hexa(nb);
	if (nb > 16)
	{
		ft_putnbr_hexa(c, nb / 16);
		ft_putnbr_hexa(c, nb % 16);
	}
	else
	{
		if (nb == 16)
		{
			ft_putchar2('1');
			ft_putchar2('0');
			i++;
		}
		if (nb >= 10 && nb <= 15)
		{
			ft_putchar_maj_min('A' + (nb % 10), c);
		}
		else if (nb != 16)
			ft_putchar2(nb + '0');
	}
	return (i);
}

int	count_unsigned(int nb)
{
	int				nb_len;
	unsigned int	n;

	n = (unsigned)nb;
	nb_len = 1;
	while (n > 9)
	{
		n = n / 10;
		nb_len++;
	}
	return (nb_len);
}

int	ft_putnbr_unsigned(int nb)
{
	unsigned int	n;
	int				i;

	n = (unsigned)nb;
	i = count_unsigned(n);
	if (n > 9)
	{
		ft_putnbr_unsigned(n / 10);
		ft_putnbr_unsigned(n % 10);
	}
	else
	{
		ft_putchar2(n + '0');
	}
	return (i);
}

// int	main(void)
// {
// 	unsigned	i;

// 	i = ft_putnbr_unsigned(-5481);
// 	printf("\n");
// 	ft_printf("%u\n", i);
// }

// int	main(void)
// {
// 	int	i;

// 	i = ft_putnbr_hexa('x', -1);
// 	printf("\n");
// 	ft_printf("%d\n", i);
// }

// int	main(void)
// {
// 	// int i = ft_putnbr2(-1234);
// 	int i = ft_putstr2("-1234abcd");
// 	printf("\n");
// 	ft_printf("taille g % = %d\n", i);
// 	// printf("\n");
// }
