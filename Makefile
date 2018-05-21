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
	@echo -e "\e[32;1mLinking.. \e[0m"
	@clang $(LDFLAGS) -o $@ $^
	@echo -e "\e[32;1mCreated:\e[0m "$(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo -e "\e[34;1mCompiling: \e[0m"$<
	@clang $(CPPFLAGS) -MMD -c $< -o $@

libft/libft.a:
	@make -sC libft

clean:
	@echo -e "\e[31;1mCleaning..\e[0m"
	@rm -f $(OBJ)
	@make -sC libft clean

fclean:
	@echo -e "\e[31;1mFull Cleaning..\e[0m"
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)
	@make -sC libft fclean

re:	fclean all

deps:
	@./deps.sh

.PHONY: clean fclean all re docs
