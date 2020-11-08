# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
##    By: cshinoha <cshinoha@student.42.fr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/16 01:04:56 by cshinoha          #+#    #+#              #
#    Updated: 2020/08/11 13:47:32 by cshinoha         ###   ########.fr        #
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
              lmn_alight.c				\
              lmn_ants.c				\
              lmn_bfs.c					\
              lmn_check_unuses.c		\
              lmn_del_dead_end.c		\
              lmn_del_input_forks.c		\
              lmn_del_output_forks.c	\
              lmn_parsing.c				\
              lmn_path.c				\
              lmn_prepare_paths.c		\
              lmn_print.c				\
              lmn_produce_output.c		\
              lmn_read.c				\
              lmn_rooms.c

SRC			= $(addprefix $(SRCDIR)/, $(SRCNAME))
OBJ			= $(addprefix $(OBJDIR)/, $(SRCNAME:.c=.o))
DPN			= $(addprefix $(OBJDIR)/, $(SRCNAME:.c=.d))
LFT			= $(addprefix $(LIBDIR)/, $(LIBNAME))
LFTOBJ		= $(LIBDIR)/objects/*.o


CLEAR       = "\033[K"
EOC			= "\033[0;0m"
GREEN		= "\033[0;32m"
CR			= "\r"$(CLEAR)

all: $(LFT) $(NAME)

-include $(DPN)

$(NAME): $(LFT) $(OBJ)
	$(GCC) $(WOPT) $(OOPT) $(IOPT) $(OBJ) -o $(NAME) -L $(LIBDIR) -lft
	@printf $(CR)$(GREEN)"✓ $(NAME) is created\n"$(EOC)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(OBJDIR)
	$(GCC) $(WOPT) $(OOPT) -MMD -MP -c $< -o $@

$(LFT):
	$(MAKE) $(LIBDIR)

clean:
	$(RM) $(OBJ) $(OBJDIR)
	$(MAKE) $(LIBDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) $(LIBDIR) fclean

re: fclean all

.PHONY: all clean fclean re norm
