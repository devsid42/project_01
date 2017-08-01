/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 13:05:05 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 13:09:39 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putbase_fd(int fd, unsigned long n, int base)
{
	char	c;

	if (n / base > 0)
	{
		ft_putbase_fd(fd, (n / base), base);
		n = n % base;
	}
	c = n < 10 ? '0' : 'a' - 10;
	ft_putchar_fd(c + n, fd);
}