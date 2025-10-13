# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchapot <lchapot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/21 12:55:13 by nsmail            #+#    #+#              #
#    Updated: 2025/10/13 16:32:47 by lchapot          ###   ########.fr        #
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
	signals/signals.c \
	builtins/atoi.c \
	builtins/cd.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/exit.c \
	builtins/export.c \
	builtins/free.c \
	builtins/builtins.c \
	builtins/pwd.c \
	builtins/unset.c \

# Dossier des objets
OBJDIR = .obj

# Objets correspondants dans obj/
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Compilateur & flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Librairies
LIBFT = libft/libft.a
READLINE = -lreadline

GREEN := \033[0;32m
CYAN := \033[0;36m
RESET := \033[0m
BIG_GREEN :=\033[1;32m
On_Green=\033[42m
UBlack=\033[4;30m
Yellow=\033[0;33m

# Compilation de base
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
#	@$(MAKE) -s --no-print-directory -C $(LIBFTDIR)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)
	@echo "       ⢀⣀⡤⠴⠶⠶⠒⠲⠦⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⠀⠀⢀⡠⠞⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠲⠤⣄⡀⠀⠀⠀⠀⠀"
	@echo "⠀⠀⣀⡴⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⡿⠀⠀⠀⠀⠀"
	@echo "⠀⢾⣅⡀⠀⠀⠀⠀⣀⠀⠀⠀⠀⠀⠀⢀⡦⠤⠄⠀⠀⢻⡀⠀⠀⠀⠀⠀"
	@echo "⠀⠈⢹⡏⠀⠀⠐⠋⠉⠁⠀⠻⢿⠟⠁⠀⠀⢤⠀⠀⠠⠤⢷⣤⣤⢤⡄⠀"
	@echo "⠀⠀⣼⡤⠤⠀⠀⠘⣆⡀⠀⣀⡼⠦⣄⣀⡤⠊⠀⠀⠀⠤⣼⠟⠀⠀⢹⡂"
	@echo "⠀⠊⣿⡠⠆⠀⠀⠀⠈⠉⠉⠙⠤⠤⠋⠀⠀⠀⠀⠀⠀⡰⠋⠀⠀⠀⡼⠁"
	@echo "⠀⢀⡾⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠜⠁⠀⠀⠀⣸⠁⠀"
	@echo "⠀⠀⠀⡼⠙⠢⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠃⠀⠀"
	@echo "⠀⢀⡞⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⠃⠀⠀⠀"
	@echo "⠀⡼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀"
	@echo "⣾⠁⠀⢀⣠⡴⠆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀"
	@echo "⠈⠛⠻⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  "
	@echo "🦭            🦭             🦭   "
	@echo "$(UBlack)$(On_Green)Executable created ✔$(RESET)"

# Règle générique pour compiler .c → .o dans obj/
$(OBJDIR)/%.o: %.c Makefile mini.h
	@mkdir -p $(dir $@)   # crée le dossier si besoin
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BIG_GREEN)[OK] $(CYAN)Compilation $<$(RESET)"

# Règles de nettoyage
clean:
#	@$(MAKE) --no-print-directory -C $(LIBFTDIR) clean
	@rm -rf $(OBJDIR)
	@echo "$(CYAN)Objects cleaned ✔$(RESET)"

fclean: clean
	@$(RM) $(NAME)
#	@$(MAKE) --no-print-directory -C $(LIBFTDIR) fclean
	@echo "$(CYAN)Full clean done ✔$(RESET)"

re: fclean all

.PHONY: all clean fclean re