# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/10 19:26:38 by sadawi            #+#    #+#              #
#    Updated: 2020/12/01 11:37:30 by sadawi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so
LINK = libft_malloc_$(HOSTTYPE).so

CFILES = malloc.c free.c realloc.c show_alloc_mem.c globals.c error.c

SRCS = $(addprefix srcs/, $(CFILES))
OBJS = $(addprefix objs/, $(notdir $(SRCS:.c=.o)))

INCLUDES = -I includes/
FLAGS = -Wall -Wextra -Werror
LINUX_FLAGS = -fPIC

all:
	@make --no-print-director $(NAME)

$(NAME): $(SRCS)
	@/bin/rm -f $(NAME) $(LINK)
	@rm -rf objs
	@echo Compiling $(NAME)...
	@gcc $(FLAGS) $(INCLUDES) -c $(SRCS) $(LINUX_FLAGS)
	@mkdir objs
	@mv $(notdir $(SRCS:.c=.o)) objs
	@gcc -shared $(FLAGS) $(INCLUDES) $(OBJS) -o $(NAME)
	@ln -s $(NAME) $(LINK)
	@echo $(NAME) compiled succesfully!

lib:
	@$(RUN_LIB)

clean:
	@/bin/rm -f $(OBJS)
	@rm -rf objs
	@echo Clean successful!

fclean: clean
	@rm -rf $(NAME) $(LINK)
	@echo FClean successful!

re: fclean all
