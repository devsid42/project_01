/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 19:16:53 by avasseur          #+#    #+#             */
/*   Updated: 2017/05/24 22:43:19 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

#define BUF_NCURSES 128
#define CHAT_SIZE (LINES / 10) * 9
#define CONSOLE_SIZE (LINES / 10) * 1

static void	draw_border(WINDOW *w_chat, WINDOW *w_console)
{
	box(w_chat, ACS_VLINE, ACS_HLINE);
	box(w_console, ACS_VLINE, ACS_HLINE);
	wrefresh(w_chat);
	wrefresh(w_console);
}

static void	draw_console(WINDOW *w_console, char *buf)
{
	int		x;
	int		i;
	char	c;

	x = 1;
	i = 0;
	move(CHAT_SIZE + 2, 2);
	while (x < BUF_NCURSES - 1)
	{
		c = getch();
		buf[i] = c;
		if (c == '\n')
			return ;
		i += 1;
		mvwprintw(w_console, CHAT_SIZE, x, "%c", c);
		x += 1;
	}
}

static void	draw_chat(WINDOW *w_chat, char *buf, int h)
{
	mvwprintw(w_chat, h, 2, "%s", buf);
}

int			init_window(void)
{
	WINDOW		*w_chat;
	WINDOW		*w_console;
	char		buf[BUF_NCURSES];
	int			h;

	initscr();
	ft_memset(buf, 0, BUF_NCURSES);
	w_chat = subwin(stdscr, CHAT_SIZE, COLS, 0, 0);
	w_console = subwin(stdscr, CONSOLE_SIZE, COLS, CHAT_SIZE, 0);
	h = 2;
	while (42)
	{
		draw_border(w_chat, w_console);
		draw_chat(w_chat, buf, h);
		draw_console(w_console, buf);
		h += 1;
		if (h == CHAT_SIZE - 1)
			h = 2;
	}
	endwin();
	free(w_chat);
	free(w_console);
	return (0);
}
