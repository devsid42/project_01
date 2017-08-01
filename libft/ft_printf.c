/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 08:48:56 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 13:05:13 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_make_args_plus(int fd, char *fmt, va_list *args)
{
	if (ft_strncmp((fmt), "%ld", 3) == 0)
		ft_putnbr_fd(va_arg(*args, long), fd);
	else if (ft_strncmp((fmt), "%lx", 3) == 0)
		ft_putbase_fd(fd, va_arg(*args, t_ulong), 16);
	else
		return (0);
	return (3);
}

static int		ft_make_args(int fd, char *fmt, va_list *args)
{
	if (ft_strncmp((fmt), "%s", 2) == 0)
		ft_putstr_fd(va_arg(*args, char *), fd);
	else if (ft_strncmp((fmt), "%d", 2) == 0)
		ft_putnbr_fd(va_arg(*args, int), fd);
	else if (ft_strncmp((fmt), "%c", 2) == 0)
		ft_putchar_fd((char)va_arg(*args, int), fd);
	else if (ft_strncmp((fmt), "%o", 2) == 0)
		ft_putbase_fd(fd, va_arg(*args, t_uint), 8);
	else if (ft_strncmp((fmt), "%x", 2) == 0)
		ft_putbase_fd(fd, va_arg(*args, t_ulong), 16);
	else if (ft_strncmp((fmt), "%p", 2) == 0)
		ft_putbase_fd(fd, va_arg(*args, t_ulong), 16);
	else
		return (0);
	return (2);
}

int				ft_printf(int fd, char *fmt, ...)
{
	va_list		args;
	int			res;

	if (!fmt)
	{
		ft_putstr_fd("(null)\n", fd);
		return (0);
	}
	va_start(args, fmt);
	while (fmt && *fmt)
	{
		if (!(res = ft_make_args(fd, fmt, &args)))
			res = ft_make_args_plus(fd, fmt, &args);
		if (!res)
		{
			ft_putchar_fd(*fmt, fd);
			res = 1;
		}
		fmt += res;
	}
	va_end(args);
	return (1);
}
