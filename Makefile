# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: logan  <logan@42.us.org>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
#    Updated: 2018/05/08 18:59:19 by twalton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
LIST = main \

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addsuffix .c, $(addprefix src/, $(LIST)))
OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST)))
DEP = $(OBJ:%.o=%.d)

CPPFLAGS = -Wall -Wextra -Werror \
-I libft/includes \
-g -O3 -march=native \
#-fsanitize=undefined -fsanitize=address

LDFLAGS = -L libft -lft \
#-fsanitize=undefined -fsanitize=address

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@echo "\033[32;1mLinking.. \033[0m"
	@clang $(LDFLAGS) -o $@ $^
	@echo "\033[32;1mCreated:\033[0m "$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "\033[34;1mCompiling: \033[0m"$<
	@clang $(CPPFLAGS) -MMD -c $< -o $@

libft/libft.a:
	@make -C libft

clean:
	@echo "\033[31;1mCleaning..\033[0m"
	@rm -f $(OBJ)
	@make -C libft clean

fclean:
	@echo "\033[31;1mFull Cleaning..\033[0m"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@make -C libft fclean

re:	fclean all

deps:
	@./deps.sh

.PHONY: clean fclean all re docs
