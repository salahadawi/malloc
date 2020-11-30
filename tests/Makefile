# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/10 19:26:38 by sadawi            #+#    #+#              #
#    Updated: 2020/11/30 12:20:31 by sadawi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCLUDES = -I ../includes/

PROGRAMS = test0 test1 test2 test3 test3+ test4 test5 main main_multithread

FLAGS = -pthread

all: $(PROGRAMS)

$(PROGRAMS): %: %.c
	$(CC) $(FLAGS) -o $@ $< ../srcs/* $(INCLUDES)

clean:
	@rm -rf $(PROGRAMS)
	@echo Clean successful!

fclean: clean
	@rm -rf $(PROGRAMS)
	@echo FClean successful!

re: fclean all
