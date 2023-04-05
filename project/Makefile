# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/05 17:59:55 by kichkiro          #+#    #+#              #
#    Updated: 2023/04/05 18:04:47 by kichkiro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Config ---------------------------------------------------------------------->

NAME		:= minishell
SRCS		:= main.c
SRC_DIR     := src
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)
BUILD_DIR   := .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS 		:= $(OBJS:.o=.d)
LIB         := ft
LIB_TARGET  := ./lib/libft/libft.a 
INCS        := ./include ./lib/libft/include
CC          := clang
CFLAGS      := -g -lreadline  #-Wall -Wextra -Werror
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIB_TARGET)))
LDLIBS      := $(addprefix -l,$(LIB))
RM          := rm -rf
MAKEFLAGS   := --no-print-directory
DIR_DUP     = mkdir -p $(@D)

.PHONY: all clean fclean re
.SILENT:

# Rules ----------------------------------------------------------------------->

all: header $(NAME)

$(NAME): $(OBJS) $(LIB_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	${info ${BOLD}Creating  -> ${BLUE}$(NAME)${NO_COLOR}}

$(LIB_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	${info ${BOLD}Compiling -> ${BLUE}$@${NO_COLOR}}

-include $(DEPS)

clean:
	for f in $(dir $(LIB_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(BUILD_DIR)
	${info }
	${info ${BOLD}${YELLOW}Cleaning in progress...${NO_COLOR}	🧹 🧹 🧹}

fclean: clean
	for f in $(dir $(LIB_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME) $(NAME_CLIENT)
	
re:
	$(MAKE) fclean
	$(MAKE) all

# Style ----------------------------------------------------------------------->

RED 		:= ${shell tput setaf 1}
YELLOW		:= ${shell tput setaf 3}
BLUE		:= ${shell tput setaf 4}
NO_COLOR	:= ${shell tput sgr0}
BOLD		:= ${shell tput bold}

header:
	${info ${NO_COLOR}}	
	${info ███    ███ ██ ███    ██ ██ ████████  █████  ██      ██   ██ }
	${info ████  ████ ██ ████   ██ ██    ██    ██   ██ ██      ██  ██  }
	${info ██ ████ ██ ██ ██ ██  ██ ██    ██    ███████ ██      █████   }
	${info ██  ██  ██ ██ ██  ██ ██ ██    ██    ██   ██ ██      ██  ██  }
	${info ██      ██ ██ ██   ████ ██    ██    ██   ██ ███████ ██   ██ }
	${info ${NO_COLOR}}
	
# ------------------------------------------------------------------------------
