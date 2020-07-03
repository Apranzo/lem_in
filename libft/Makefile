# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/28 23:59:53 by cmeowth           #+#    #+#              #
#    Updated: 2020/06/16 00:58:26 by cshinoha         ###   ########.ru        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

GCC			= /usr/bin/clang
WOPT		= -Wall -Wextra -Werror
OOPT		= -O2
IOPT		= -I $(INCDIR)

AR			= /usr/bin/ar -rc
RM			= /bin/rm -rf
RANLIB		= /usr/bin/ranlib
NORMINETTE	= /usr/bin/norminette
MKDIR		= /bin/mkdir -p

INCDIR		= ./include
SRCDIR		= ./src
OBJDIR		= ./objects

SRCNAME		= printf/ft_printf.c				\
			  printf/parsing.c					\
			  printf/tools/buffer.c			\
			  printf/tools/initialization.c	\
			  printf/tools/get_si.c			\
			  printf/tools/get_ui.c			\
			  printf/tools/get_f.c				\
			  printf/specs/wildcard.c			\
			  printf/specs/set_specs.c			\
			  printf/specs/set_flags.c			\
			  printf/specs/set_length.c		\
			  printf/specs/apply_specs.c		\
			  printf/types/type_b.c			\
			  printf/types/type_c.c			\
			  printf/types/type_d.c			\
			  printf/types/type_f.c			\
			  printf/types/type_o.c			\
			  printf/types/type_p.c			\
			  printf/types/type_s.c			\
			  printf/types/type_u.c			\
			  printf/types/type_x.c			\
			  printf/types/unknown.c			\
			  printf/types/percent.c			\
			  ft_memset.c				\
			  ft_bzero.c				\
			  ft_memcpy.c				\
			  ft_memccpy.c				\
			  ft_memmove.c				\
			  ft_memchr.c				\
			  ft_memcmp.c				\
			  ft_strlen.c				\
			  ft_strdup.c				\
			  ft_strcpy.c				\
			  ft_strncpy.c				\
			  ft_strcat.c				\
			  ft_strncat.c				\
			  ft_strlcat.c				\
			  ft_strchr.c				\
			  ft_strrchr.c				\
			  ft_strstr.c				\
			  ft_strnstr.c				\
			  ft_strcmp.c				\
			  ft_strncmp.c				\
			  ft_atoi.c					\
			  ft_isalpha.c				\
			  ft_isdigit.c				\
			  ft_isalnum.c				\
			  ft_isascii.c				\
			  ft_isprint.c				\
			  ft_toupper.c				\
			  ft_tolower.c				\
			  ft_memalloc.c				\
			  ft_memdel.c				\
			  ft_strnew.c				\
			  ft_strdel.c				\
			  ft_strclr.c				\
			  ft_striter.c				\
			  ft_striteri.c				\
			  ft_strmap.c				\
			  ft_strmapi.c				\
			  ft_strequ.c				\
			  ft_strnequ.c				\
			  ft_strsub.c				\
			  ft_strjoin.c				\
			  ft_strtrim.c				\
			  ft_strsplit.c				\
			  ft_itoa.c					\
			  ft_putchar.c				\
			  ft_putstr.c				\
			  ft_putstrss.c				\
			  ft_putendl.c				\
			  ft_putnbr.c				\
			  ft_putchar_fd.c			\
			  ft_putstr_fd.c			\
			  ft_putendl_fd.c			\
			  ft_putnbr_fd.c			\
			  ft_lstnew.c				\
			  ft_lstdelone.c			\
			  ft_lstdel.c				\
			  ft_lstadd.c				\
			  ft_lstiter.c				\
			  ft_lstmap.c				\
			  ft_isupper.c				\
			  ft_islower.c				\
			  ft_isspace.c				\
			  ft_isseparator.c			\
			  ft_cntwords.c				\
			  ft_nblen.c				\
			  ft_swap.c					\
			  ft_strnew2d.c				\
			  ft_sitoa_base.c			\
			  ft_silen.c				\
			  ft_uitoa_base.c			\
			  ft_uilen.c				\
			  ft_litoa.c				\
			  ft_itoa_static.c			\
			  ft_litoa_static.c			\
			  ft_sitoa_base_static.c	\
			  ft_uitoa_base_static.c	\
			  ft_ftoa_static.c			\
			  ft_freematr.c				\
			  ft_gnl.c					\
			  ft_intlen.c				\
			  ft_iswhite.c				\
			  ft_lstfree.c				\
			  ft_strfrjoin.c			\
			  ft_strindexof.c			\
			  ft_lstpush.c				\
			  ft_error.c				\
			  ft_min.c					\
			  ft_max.c					\
			  ft_abs.c					\
			  ft_free.c

SRC			= $(addprefix $(SRCDIR)/, $(SRCNAME))
OBJ			= $(addprefix $(OBJDIR)/, $(SRCNAME:.c=.o))

CLEAR       = "\033[K"
EOC			= "\033[0;0m"
GREEN		= "\033[0;32m"
CR			= "\r"$(CLEAR)

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
	$(RANLIB) $(NAME)
	-@printf $(CR)$(GREEN)"✓ $(NAME) is created\n"$(EOC)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	-@$(MKDIR) $(OBJDIR)/printf/types
	-@$(MKDIR) $(OBJDIR)/printf/tools
	-@$(MKDIR) $(OBJDIR)/printf/specs
	$(GCC) $(WOPT) $(OOPT) $(IOPT) -c $< -o $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

norm:
	$(NORMINETTE) $(INCDIR) $(SRC)

.PHONY: all clean fclean re norm
