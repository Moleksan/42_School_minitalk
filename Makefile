# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: moleksan <moleksan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 12:20:36 by moleksan          #+#    #+#              #
#    Updated: 2024/08/06 12:29:32 by moleksan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and compiling flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Project name for the binaries
NAME_CLIENT = client
NAME_SERVER = server

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = library/libft
FT_PRINTF_DIR = library/ft_printf
INC_DIR = include

# Source files and object files
SRC_CLIENT = $(SRC_DIR)/client.c
SRC_SERVER = $(SRC_DIR)/server.c
OBJ_CLIENT = $(SRC_CLIENT:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_SERVER = $(SRC_SERVER:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
LIBS = -L$(LIBFT_DIR) -lft -L$(FT_PRINTF_DIR) -lftprintf

# Header files
HEADERS = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR)

# Rules
all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(LIBFT) $(FT_PRINTF) $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(HEADERS) $(LIBS) -o $(NAME_CLIENT)

$(NAME_SERVER): $(LIBFT) $(FT_PRINTF) $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(HEADERS) $(LIBS) -o $(NAME_SERVER)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minitalk.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	rm -f $(NAME_CLIENT)
	rm -f $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re