# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryatan <ryatan@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/09 08:56:45 by ryatan            #+#    #+#              #
#    Updated: 2026/05/15 15:50:44 by ryatan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
COMPILER = cc
INCLUDES = -Iinclude
CFLAGS = -Wall -Wextra -Werror
EXT_LIBS = -lpthread

OBJ_DIR = obj
SRC_DIR = src

SRC = $(SRC_DIR)/errors.c \
	  $(SRC_DIR)/helpers.c \
	  $(SRC_DIR)/atoi.c \
	  $(SRC_DIR)/threads.c \
	  $(SRC_DIR)/scheduler.c \
	  $(SRC_DIR)/initializer.c \
	  $(SRC_DIR)/main.c \

# pattern substitution
# $(patsubst WHAT_TO_MATCH,WHAT_TO_REPLACE_IT_WITH,WHERE_TO_LOOK)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

$(NAME): $(OBJ)
	$(COMPILER) $(CFLAGS) $(EXT_LIBS)  $(OBJ) -o $(NAME)

$(OBJ_DIR): 
	mkdir -p $(OBJ_DIR)

#To build any object file inside obj/,
#compile the matching source file inside src/,
#and create the needed subfolder first.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
