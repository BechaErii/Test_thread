# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mewormse <mewormse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/26 18:59:22 by mewormse          #+#    #+#              #
#    Updated: 2024/10/28 10:41:05 by mewormse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

CC				= cc

CFLAGS 			= -Wall -Wextra -Werror -pthread -g

INCLUDE			= -I includes


##############################  COLORS  ###################################

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[3;92m
YELLOW = \033[0;93m
BLUE = \033[3;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m


##############################  SOURCES  #####################################

SRC_DIR			= sources

OBJ_DIR			= object

SRC_FILES	=	philo.c \
				lib_fonction.c \
				parsing.c \
				fill_struct.c \
				free.c \
				routine.c \
				utils.c \
				monitor.c
				
OBJ             = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

##############################  RULES  #######################################

all: $(NAME)

$(NAME): $(OBJ) 
	@$(CC) $(OBJ) $(CFLAGS) $(INCLUDE) -o $(NAME)
	@echo "${YELLOW}~~> Dinner is ready ! <~~ ${DEF_COLOR}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "${BLUE}Philosophers object files cleaned! ${DEF_COLOR}"

fclean: clean
	@rm -f $(NAME)
	@echo "${YELLOW}Philosophers files cleaned! ${DEF_COLOR}"

re: fclean all

.PHONY: all clean fclean re