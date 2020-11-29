# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/16 01:04:56 by cshinoha          #+#    #+#              #
#    Updated: 2020/11/19 15:20:00 by cshinoha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= lem-in
LIBNAME		= libft.a

GCC			= /usr/bin/clang
WOPT		= -Wall -Wextra -Werror
OOPT		= -g
IOPT		= -I $(INCDIR)

AR			= /usr/bin/ar -rc
MAKE		= /usr/bin/make -C
RANLIB		= /usr/bin/ranlib
MKDIR		= /bin/mkdir -p
RM			= /bin/rm -rf
ZSH			= /bin/zsh

LIBDIR		= libft
SRCDIR		= src
OBJDIR		= objects
INCDIR		= includes
DPNDIR		= depends

SRCNAME		= lem_in.c					\
              lmn_ants.c				\
              lmn_bfs.c					\
              lmn_parsing.c				\
              lmn_path.c				\
              lmn_prepare_paths.c		\
              lmn_print.c				\
              lmn_produce_output.c		\
              lmn_read.c				\
              lmn_rooms.c				\
              et_tu_brute.c				\
              lmn_options.c				\
              lmn_shortest.c

SRC			= $(addprefix $(SRCDIR)/, $(SRCNAME))
OBJ			= $(addprefix $(OBJDIR)/, $(SRCNAME:.c=.o))
DPN			= $(addprefix $(OBJDIR)/, $(SRCNAME:.c=.d))
LFT			= $(addprefix $(LIBDIR)/, $(LIBNAME))
LFTOBJ		= $(LIBDIR)/objects/*.o


CLEAR       = "\033[K"
EOC			= "\033[0;0m"
GREEN		= "\033[32m"
TURQUOISE   = "\033[36m"
CR			= "\r"$(CLEAR)

all: $(LFT) $(NAME)

-include $(DPN)

$(NAME): $(LFT) $(OBJ)
	@$(GCC) $(WOPT) $(OOPT) $(IOPT) $(OBJ) -o $(NAME) -L $(LIBDIR) -lft
	@echo "\n"
	@echo "\033[32m [OK] \033[0m\033[32mExecution file:\033[36m" $(NAME)
	@echo $(EOC)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(OBJDIR)
	@$(GCC) $(WOPT) $(OOPT) -MMD -MP -c $< -o $@
	@echo "\033[32m [OK] \033[0m\033[32mCompiling:\033[36m " $@

$(LFT):
	@$(MAKE) $(LIBDIR)

clean:
	@$(RM) $(OBJ) $(OBJDIR)
	@$(MAKE) $(LIBDIR) clean
	@echo "\033[31m [OK] \033[0m\033[31mDeleting catalog and binaries:\033[33m " $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) $(LIBDIR) fclean
	@echo "\033[31m [OK] \033[0m\033[31mDeleting execution file:\033[33m " $(NAME)
	@echo $(EOC)

re: fclean all

.PHONY: all clean fclean re norm
