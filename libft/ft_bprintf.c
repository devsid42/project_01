/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/02 08:48:56 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:10:47 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		null_case(char *fmt, int fd)
{
	if (!fmt)
	{
		ft_putstr_fd("(null)\n", fd);
		return (-1);
	}
	return (0);
}

static int		string_decimal_args(char *buf, size_t bsize, char *fmt, va_list *args)
{
	char	*s;

	s = NULL;
	if (ft_strncmp((fmt), "%s", 2) == 0)
	{
		s = va_arg(*args, char *);
		if (ft_strlen(buf) + ft_strlen(s) >= bsize)
			return (-1);
		ft_strcat(buf, s);
	}
	else if (ft_strncmp((fmt), "%d", 2) == 0)
	{
		if (!(s = ft_itoa(va_arg(*args, int))))
			return (-1);
		else if (ft_strlen(buf) + ft_strlen(s) >= bsize)
			return (-1);
		ft_strcat(buf, s);
		ft_strdel(&s);
	}
	else
		return (0);
	return (2);
}

static int		commun_args(char *buf, size_t bsize, char *fmt, va_list *args)
{
	char	*s;

	s = NULL;
	if (string_decimal_args(buf, bsize, fmt, args) == 2)
		;
	else if (ft_strncmp((fmt), "%c", 2) == 0)
	{
		if (ft_strlen(buf) + 1 >= bsize)
			return (-1);
		buf[ft_strlen(buf)] = (char)va_arg(*args, int);
	}
	else
		return (0);
	return (2);
}

static int		run(char *fmt, char *buf, size_t bsize, va_list *args)
{
	int			res;

	while (*fmt && ft_strlen(buf) < bsize)
	{
		res = commun_args(buf, bsize, fmt, args);
		if (res == -1)
			break ;
		if (!res)
		{
			buf[ft_strlen(buf)] = *fmt;
			res = 1;
		}
		fmt += res;
	}
	return (0);
}

int				ft_bprintf(int fd, size_t bsize, char *fmt, ...)
{
	va_list		args;
	char		*buf;

	if (null_case(fmt, fd) == -1)
		return (-1);
	if (!(buf = (char *)ft_memalloc(sizeof(char) * (bsize + 1))))
		return (-1);
	va_start(args, fmt);
	run(fmt, buf, bsize, &args);
	write(fd, buf, ft_strlen(buf));
	va_end(args);
	ft_strdel(&buf);
	return (1);
}
