# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: logan  <logan@42.us.org>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/13 10:03:24 by logan             #+#    #+#              #
#    Updated: 2018/05/25 19:32:35 by lkaser           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
LIST = main \
sort

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addsuffix .c, $(addprefix src/, $(LIST)))
OBJ = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(LIST)))
DEP = $(OBJ:%.o=%.d)

CPPFLAGS = -Wall -Wextra -Werror \
-I libft/includes \
-g -O3 -march=native \
-fsanitize=address -fsanitize=undefined \

LDFLAGS = -L libft -lft \
-fsanitize=address -fsanitize=undefined \

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@printf "\e[32;1mLinking.. \e[0m\n"
	@clang $(LDFLAGS) -o $@ $^
	@printf "\e[32;1mCreated:\e[0m %s\n" $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "\e[34;1mCompiling: \e[0m%s\n" $<
	@clang $(CPPFLAGS) -MMD -c $< -o $@

libft/libft.a:
	@make -sC libft

clean:
	@printf "\e[31;1mCleaning..\e[0m\n"
	@rm -f $(OBJ) $(DEP)
	@make -sC libft clean

fclean:
	@printf "\e[31;1mFull Cleaning..\e[0m\n"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@make -sC libft fclean

re:	fclean all

deps:
	@./deps.sh

.PHONY: clean fclean all re docs
