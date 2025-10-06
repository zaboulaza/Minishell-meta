# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/21 12:55:13 by nsmail            #+#    #+#              #
#    Updated: 2025/10/06 18:35:27 by nsmail           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = MINI

# Fichiers source
SRCS = src/main.c \
       src/print_ast.c \
       parser/parser.c \
       parser/token_first.c \
       parser/token_second.c \
       parser/token_third.c \
       parser/token_third_utils.c \
       parser/token_third_utils2.c \
       parser/token_third_utils3.c \
       parser/token_third_utils4.c \
       parser/token_third_utils5.c \
       parser/token_second_utils.c \
       parser/creat_list.c \
       parser/creat_list_utils1.c \
       parser/creat_list_utils2.c \
       parser/last_verif_parent.c \
       parser/creat_ast.c \
       exec/exec_general.c \
       exec/exec_ast.c \
       exec/get_path.c \
       exec/exec_cmd.c \
       exec/exec_cmd_utils.c \
       exec/exec_cmd_utils2.c \
       exec/expand.c \
       exec/expand_utils.c \
       signals/signals.c 

# Dossier des objets
OBJDIR = obj

# Objets correspondants dans obj/
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Compilateur & flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Librairies
LIBFT = libft/libft.a
READLINE = -lreadline

# Compilation de base
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

# Règle générique pour compiler .c → .o dans obj/
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)   # crée le dossier si besoin
	$(CC) $(CFLAGS) -c $< -o $@

# Règles de nettoyage
clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re