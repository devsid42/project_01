/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 18:45:04 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/01 23:43:21 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CLIENT_H
# define FT_CLIENT_H

# include "libft.h"
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <signal.h>
# include <ncurses.h>

typedef struct sockaddr		t_sockaddr;
typedef struct sockaddr_in	t_sockaddr_in;
typedef struct addrinfo		t_addrinfo;
typedef struct in_addr		t_in_addr;
typedef struct timeval		t_timeval;

# define USAGE "Usage: %s [<ip> <port>] [nick] [user]\n"
# define GETADDRINFO_OK 0
# define IRC_BUF_SIZE 512
# define MSG_SIZE 512
# define CHAN_SIZE 50
# define NICK_SIZE 10

# define USER "youzeur"
# define NICK "nique"
# define PORT 6667

# define END_OF_MOTD " 376 "
# define END_OF_CHAN_LST " 323 "
# define END_OF_NAME_LST " 366 "
# define UNKNOWN_CMD " 421 "
# define CANNOT_SENDTOCHAN " 404 "

typedef struct		s_chan
{
	char			*name;
	struct s_chan	*prev;
	struct s_chan	*next;
}					t_chan;

typedef struct		s_env
{
	int				connected;
	int				sock;
	char			*ip;
	int				port;
	t_sockaddr_in	sin;
	t_in_addr		addr;
	fd_set			fd_read;
	fd_set			fd_write;
	t_chan			*chans;
	char			*cur_chan;
	char			nick[NICK_SIZE];
	char			user[NICK_SIZE];
	t_timeval		tv;
}					t_env;

void				put_prompt(t_env *e);
int					init_stream_client(t_env *e);
void				init_fd(t_env *e);
int					handle_select(t_env *e);
int					client_read(t_env *e);
int					client_write(t_env *e);
void				send_credential(int sock, char *nick, char *user);
void				get_server_status(char *buf);
void				put_prompt(t_env *e);
void				handle_ctrl_c(int sig);

int					user_write_chan(t_env *e, char **cmds);
int					user_write_nick(t_env *e, char **cmds);
int					user_write_user(t_env *e, char **cmds);
int					user_write_join(t_env *e, char **cmds);
int					user_write_part(t_env *e, char *buf, char **cmds);
int					user_write_msg(t_env *e, char **cmds, char *buf);
int					user_write_connect(t_env *e, char **cmds);
int					user_write_who(t_env *e, char **cmds);
int					user_write_list(t_env *e, char **cmds);
int					user_write_names(t_env *e, char **cmds);
int					user_write_mode(t_env *e, char **cmds);
int					user_write_quit(t_env *e, char **cmds);
int					user_write_help(char **cmds);

int					srv_ping_pong(int sock, char *buf);
int					srv_user_part(t_env *e, char *buf, char **cmds);
int					srv_user_join(t_env *e, char *buf, char **cmds);
int					srv_user_nick(t_env *e, char *buf, char **cmds);

int					init_window(void);

char				*get_channel(char *buf);
t_chan				*lst_chan_create(char *name);
int					lst_chan_add_end(t_chan **chans, t_chan *new_node);
int					lst_chan_del_by_name(t_chan **chans, char *chan_name);
int					lst_chan_is(t_chan *chans, char *name);
void				lst_chan_put(t_chan *chans, char *msg, int dir);
char				*lst_chan_get_last_name(t_chan *chans);
char				*lst_chan_get_name(t_chan *chans, char *name);
int					lst_chan_delete_all(t_chan **chans);

#endif
