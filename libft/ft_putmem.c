/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 19:35:45 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 16:39:31 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		put_deci_end(char *addr, size_t cols, size_t i, size_t rest)
{
	size_t	j;
	size_t	len;

	len = i;
	i -= rest;
	j = cols - rest;
	while (j--)
		ft_printf(1, "  ");
	ft_printf(1, "\t[");
	j = 0;
	while (j < cols && i < len)
	{
		if (ft_isprint(addr[i]))
			ft_printf(1, "%c", addr[i]);
		else
			ft_printf(1, ".");
		if (j + 1 != cols)
			ft_printf(1, " ");
		i += 1;
		j += 1;
	}
	ft_printf(1, "]\n");
	return (0);
}

static int		put_deci(char *addr, size_t cols, size_t i)
{
	size_t	j;

	j = 0;
	ft_printf(1, "\t[");
	i -= cols;
	while (j < cols)
	{
		if (ft_isprint(addr[i]))
			ft_printf(1, "%c", addr[i]);
		else
			ft_printf(1, ".");
		if (j + 1 != cols)
			ft_printf(1, " ");
		i += 1;
		j += 1;
	}
	ft_printf(1, "]\n");
	return (0);
}

static int		put_hexa(char *addr, size_t cols, size_t i)
{
	if (i % cols == 0)
		ft_printf(1, "[0x%p]\t", addr + i);
	if ((unsigned char)addr[i] < 0xf)
		ft_printf(1, "0");
	ft_printf(1, "%x ", (unsigned char)addr[i]);
	return (0);
}

int				ft_putmem(char *addr, size_t cols, size_t len)
{
	size_t	i;
	size_t	rest;

	if (!cols || !cols)
		return (-1);
	if (!addr)
	{
		ft_printf(1, "(null)");
		return (-1);
	}
	i = 0;
	rest = 0;
	while (i < len)
	{
		if (i > 0 && i % cols == 0)
			put_deci(addr, cols, i);
		put_hexa(addr, cols, i);
		i++;
	}
	put_deci_end(addr, cols, i, len % cols);
	ft_printf(1, "\n");
	return (i);
}
