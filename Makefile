# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/10 15:08:30 by avasseur          #+#    #+#              #
#    Updated: 2017/06/01 23:43:50 by avasseur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREY = "\033[30m"
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
PURPLE = "\033[35m"
CYAN = "\033[36m"
WHITE = "\033[37m"
ENDCOLOR = "\033[0m"

SERVER = serveur
CLIENT = client

CC = gcc

NCURSES = -lncurses

PATH_LFT = libft

HDR = -I src_server/inc/ -I src_client/inc/ -I $(PATH_LFT)

SRV_DIR = src_server/src/
CLI_DIR = src_client/src/

COMMON = commun/

LFT = -L $(PATH_LFT) -lft

COMMON_SRC =\
	  $(COMMON)get_channel.c\
	  $(COMMON)lst_chan_add_end.c\
	  $(COMMON)lst_chan_create.c\
	  $(COMMON)lst_chan_del_by_name.c\
	  $(COMMON)lst_chan_is.c\
	  $(COMMON)lst_chan_put.c\
	  $(COMMON)lst_chan_get_last_name.c\
	  $(COMMON)lst_chan_get_name.c\
	  $(COMMON)lst_chan_delete_all.c

SRV_SRC = $(SRV_DIR)main.c\
	  $(SRV_DIR)init_stream_server.c\
	  $(SRV_DIR)add_del_sock_in_socks.c\
	  $(SRV_DIR)init_fd.c\
	  $(SRV_DIR)handle_fd.c\
	  $(SRV_DIR)signal.c\
	  $(SRV_DIR)rotate_read.c\
	  $(SRV_DIR)client_quit.c\
	  $(SRV_DIR)put_stuff.c\
	  $(SRV_DIR)srv_speak.c\
	  $(SRV_DIR)srv_is_known_cmd.c\
	  $(SRV_DIR)srv_join_part.c\
	  $(SRV_DIR)srv_user_nick.c\
	  $(SRV_DIR)srv_quit_mode_ping.c\
	  $(SRV_DIR)srv_names_who_list.c\
	  $(SRV_DIR)lst_client_create.c\
	  $(SRV_DIR)lst_client_add_end.c\
	  $(SRV_DIR)lst_client_set_nick_user.c\
	  $(SRV_DIR)lst_client_is_reg.c\
	  $(SRV_DIR)lst_client_put.c\
	  $(SRV_DIR)lst_client_del_node.c\
	  $(SRV_DIR)lst_client_get.c\
	  $(SRV_DIR)lst_client_channel_user.c\
	  $(COMMON_SRC)

CLI_SRC = $(CLI_DIR)main.c\
	  $(CLI_DIR)init_stream_client.c\
	  $(CLI_DIR)client_write.c\
	  $(CLI_DIR)client_read.c\
	  $(CLI_DIR)put_prompt.c\
	  $(CLI_DIR)handle_ctrlc.c\
	  $(CLI_DIR)send_credential.c\
	  $(CLI_DIR)srv_cmd_read.c\
	  $(CLI_DIR)user_write_nick_user.c\
	  $(CLI_DIR)user_write_chan.c\
	  $(CLI_DIR)user_write_join_part.c\
	  $(CLI_DIR)user_write_msg.c\
	  $(CLI_DIR)user_write_connect.c\
	  $(CLI_DIR)user_write_who_names_mode_quit_list.c\
	  $(CLI_DIR)user_write_help.c\
	  $(CLI_DIR)get_server_status.c\
	  $(CLI_DIR)window.c\
	  $(COMMON_SRC)

CCFLAGS = -Wall -Werror -Wextra -g

SRV_OBJ = $(SRV_SRC:.c=.o)
CLI_OBJ = $(CLI_SRC:.c=.o)

all: libft.a $(SERVER) $(CLIENT)
	
libft.a:
	@make -C $(PATH_LFT)

$(SERVER): $(SRV_OBJ)
	@$(CC) $(SRV_OBJ) -o $(SERVER) $(LFT)
	@echo $(SERVER) compiled

$(CLIENT): $(CLI_OBJ)
	@$(CC) $(CLI_OBJ) -o $(CLIENT) $(LFT) $(NCURSES)
	@echo $(CLIENT) compiled

%.o: %.c
	@$(CC) $(CCFLAGS) -c $< -o $@ $(HDR)

clean:
	@make clean -C $(PATH_LFT)
	@/bin/rm -f $(SRV_OBJ)
	@/bin/rm -f $(CLI_OBJ)

fclean: clean
	@make fclean -C $(PATH_LFT)
	@/bin/rm -f $(SERVER)
	@/bin/rm -f $(CLIENT)

re: fclean all

popo:
	/bin/rm -f $(SERVER)
	@/bin/rm -f $(SRV_OBJ)
	/bin/rm -f $(CLIENT)
	@/bin/rm -f $(CLI_OBJ)

po: popo all

.PHONY: all clean fclean re popo po
