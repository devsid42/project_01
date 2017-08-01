/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 19:54:19 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 17:26:58 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SERVER_H
# define FT_SERVER_H

# include "libft.h"
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <signal.h>

typedef struct sockaddr		t_sockaddr;
typedef struct sockaddr_in	t_sockaddr_in;
typedef struct timeval		t_timeval;

# define RBUF_SIZE 1024
# define BUF_COEF 5
# define RBUF_LIMIT RBUF_SIZE / BUF_COEF
# define IP_BUF_SIZE 50
# define MAX_FD FD_SETSIZE
# define MAX_USER MAX_FD - 1
# define MSG_SIZE 512
# define CHAN_SIZE 50
# define NICK_SIZE 10
# define SRV_NAME "SERVER_NAME"
# define STR_NO_CHAN ":%s This channel does not exist (%s)\n"

typedef struct		s_chan
{
	char			name[CHAN_SIZE];
	struct s_chan	*prev;
	struct s_chan	*next;
}					t_chan;

typedef struct		s_client
{
	int				connected;
	int				sock;
	char			rbuf[RBUF_SIZE];
	int				buflen;
	char			*start_rbuf;
	char			*stop_rbuf;
	char			ip[IP_BUF_SIZE];
	int				port;
	char			nick[NICK_SIZE];
	char			user[NICK_SIZE];
	t_chan			*chans;
	struct s_client	*prev;
	struct s_client	*next;
}					t_client;

typedef struct		s_env
{
	int				srv_sock;
	int				srv_port;
	t_sockaddr_in	sin;
	t_sockaddr_in	addr;
	socklen_t		sock_len;
	fd_set			fd_read;
	fd_set			fd_write;
	int				*socks;
	t_chan			*chans;
	t_chan			*nicks;
	t_client		*cnt;
	t_timeval		tv;
	int				dbg;
}					t_env;

int					init_stream_server(t_env *serv);
int					init_fd(t_env *e);
int					handle_fd(t_env *e);
void				handle_signal(void);

int					add_sock_in_socks(t_env *e, int sock);
int					del_sock_in_socks(t_env *e, int sock);
t_client			*rotate_read(t_env *e, int sock);
int					client_quit(t_env *e, int sock);
void				put_srv_info(t_env *e);
void				put_rotate_buf(void *addr, size_t col, t_client *node);
int					srv_is_known_cmd(int sock, char *buf, char **cmds);
int					srv_quit(t_env *e, int sock, char *buf);
int					srv_join_part(t_env *e, char *buf, char **cmds, int sock);
int					srv_user_nick(t_env *e, int sock, char **cmds);
int					srv_names(t_env *e, int sock, char **cmds);
int					srv_list(t_env *e, int sock, char **cmds);
int					srv_who(t_env *e, int sock, char **cmds);
int					srv_mode(t_env *e, int sock, char **cmds);
int					srv_ping_pong(int sock, char *buf);
int					srv_speak_msg(t_env *e,\
						int src_sock, char *buf, char **cmds);
int					srv_speak_general(t_env *e, int src_sock, char *buf);

t_client			*lst_client_create(int sock, t_sockaddr_in *addr);
int					lst_client_add_end(t_client **cnt, t_client *new_node);
int					lst_client_set_nick(t_client *cnt, int sock, char *nick);
int					lst_client_set_user(t_client *cnt, int sock, char *user);
int					lst_client_is_reg(t_client *cnt, int sock);
void				lst_client_put(t_client *cnt);
int					lst_put_client_chan_nicks(\
								t_env *e, int sock, char *chan, char *nick);
int					lst_client_del_node(t_client **cnt, int sock);
char				*lst_client_get_nick(t_client *cnt, int sock);
char				*lst_client_get_user(t_client *cnt, int sock);
char				*lst_client_get_rbuf(t_client *cnt, int sock);
t_client			*lst_client_get_node(t_client *cnt, int sock);
int					lst_client_get_sock(t_client *cnt, char *nick);
int					lst_client_channel_user_nb(t_client *cnt, char *chan);
int					lst_client_is_user_in_channel(\
						t_client *cnt, int sock, char *chan);

char				*get_channel(char *buf);
t_chan				*lst_chan_create(char *chan_name);
int					lst_chan_add_end(t_chan **chans, t_chan *new_node);
int					lst_chan_del_by_name(t_chan **chans, char *name);
int					lst_chan_is(t_chan *chans, char *name);
void				lst_chan_put(t_chan *chans, char *msg, int dir);
char				*lst_chan_get_last_name(t_chan *chans);
char				*lst_chan_get_name(t_chan *chans, char *name);
int					lst_chan_delete_all(t_chan **chans);

#endif
