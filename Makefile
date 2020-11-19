# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/10 19:26:38 by sadawi            #+#    #+#              #
#    Updated: 2020/11/19 18:28:18 by sadawi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc.so
LINK = libft_malloc_$(HOSTTYPE).so

CFILES = malloc.c free.c realloc.c

SRCS = $(addprefix srcs/, $(CFILES))
OBJS = $(addprefix objs/, $(notdir $(SRCS:.c=.o)))

INCLUDES = -I includes/
FLAGS = -Wall -Wextra -Werror

all:
	@make --no-print-director $(NAME)

$(NAME): $(SRCS)
	@/bin/rm -f $(NAME) $(LINK)
	@rm -rf objs
	@echo Compiling $(NAME_ASM)...
	@gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
	@mkdir objs
	@mv $(notdir $(SRCS:.c=.o)) objs
	@gcc -shared $(INCLUDES) $(OBJS) -o $(NAME)
	@ln -s $(NAME) $(LINK)
	@echo $(NAME) compiled succesfully!

lib:
	@$(RUN_LIB)

clean:
	@/bin/rm -f $(OBJS)
	@rm -rf objs
	@make -C libft/ clean
	@echo Clean successful!

fclean: clean
	@make -C libft/ fclean
	@echo FClean successful!

re: fclean all