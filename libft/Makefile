# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmarsell <dmarsell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/28 23:59:53 by cmeowth           #+#    #+#              #
#    Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

GCC			= /usr/bin/clang
WOPT		= -Wall -Wextra -Werror
OOPT		= -O2
IOPT		= -I ./core/includes		\
              -I ./collections/includes	\
              -I ./printf/includes		\
              -I ./string/includes

AR			= /usr/bin/ar -rc
RM			= /bin/rm -rf
RANLIB		= /usr/bin/ranlib
MKDIR		= /bin/mkdir -p

SRCDIR		= .
OBJDIR		= ./objects

SRCNAME		= printf/src/ft_printf.c				\
              printf/src/ft_printf_extend.c			\
			  printf/src/parsing.c					\
			  printf/src/tools/buffer.c				\
			  printf/src/tools/initialization.c		\
			  printf/src/tools/get_si.c				\
			  printf/src/tools/get_ui.c				\
			  printf/src/tools/get_f.c				\
			  printf/src/specs/wildcard.c			\
			  printf/src/specs/set_specs.c			\
			  printf/src/specs/set_flags.c			\
			  printf/src/specs/set_length.c			\
			  printf/src/specs/apply_specs.c		\
			  printf/src/types/type_b.c				\
			  printf/src/types/type_c.c				\
			  printf/src/types/type_d.c				\
			  printf/src/types/type_f.c				\
			  printf/src/types/type_o.c				\
			  printf/src/types/type_p.c				\
			  printf/src/types/type_s.c				\
			  printf/src/types/type_u.c				\
			  printf/src/types/type_x.c				\
			  printf/src/types/unknown.c			\
			  printf/src/types/percent.c			\
			  core/src/ft_memset.c				\
			  core/src/ft_bzero.c				\
			  core/src/ft_memcpy.c				\
			  core/src/ft_memccpy.c				\
			  core/src/ft_memmove.c				\
			  core/src/ft_memchr.c				\
			  core/src/ft_memcmp.c				\
			  core/src/ft_strlen.c				\
			  core/src/ft_strdup.c				\
			  core/src/ft_strstartwith.c		\
			  core/src/ft_strcpy.c				\
			  core/src/ft_strncpy.c				\
			  core/src/ft_strcat.c				\
			  core/src/ft_strncat.c				\
			  core/src/ft_strlcat.c				\
			  core/src/ft_strchr.c				\
			  core/src/ft_strrchr.c				\
			  core/src/ft_strstr.c				\
			  core/src/ft_strnstr.c				\
			  core/src/ft_strcmp.c				\
			  core/src/ft_strncmp.c				\
			  core/src/ft_atoi.c				\
			  core/src/ft_atoi_check.c			\
			  core/src/ft_isalpha.c				\
			  core/src/ft_isdigit.c				\
			  core/src/ft_isalnum.c				\
			  core/src/ft_isascii.c				\
			  core/src/ft_isprint.c				\
			  core/src/ft_toupper.c				\
			  core/src/ft_tolower.c				\
			  core/src/ft_memalloc.c			\
			  core/src/ft_memdel.c				\
			  core/src/ft_strnew.c				\
			  core/src/ft_strdel.c				\
			  core/src/ft_strclr.c				\
			  core/src/ft_striter.c				\
			  core/src/ft_striteri.c			\
			  core/src/ft_strmap.c				\
			  core/src/ft_strmapi.c				\
			  core/src/ft_strequ.c				\
			  core/src/ft_strnequ.c				\
			  core/src/ft_strsub.c				\
			  core/src/ft_strjoin.c				\
			  core/src/ft_strtrim.c				\
			  core/src/ft_strsplit.c			\
			  core/src/ft_itoa.c				\
			  core/src/ft_putchar.c				\
			  core/src/ft_putstr.c				\
			  core/src/ft_putstrss.c			\
			  core/src/ft_putendl.c				\
			  core/src/ft_putnbr.c				\
			  core/src/ft_putchar_fd.c			\
			  core/src/ft_putstr_fd.c			\
			  core/src/ft_putendl_fd.c			\
			  core/src/ft_putnbr_fd.c			\
			  core/src/ft_lstnew.c				\
			  core/src/ft_lstdelone.c			\
			  core/src/ft_lstdel.c				\
			  core/src/ft_lstadd.c				\
			  core/src/ft_lstiter.c				\
			  core/src/ft_lstmap.c				\
			  core/src/ft_isupper.c				\
			  core/src/ft_islower.c				\
			  core/src/ft_isspace.c				\
			  core/src/ft_isseparator.c			\
			  core/src/ft_cntwords.c			\
			  core/src/ft_nblen.c				\
			  core/src/ft_swap.c				\
			  core/src/ft_strnew2d.c			\
			  core/src/ft_sitoa_base.c			\
			  core/src/ft_silen.c				\
			  core/src/ft_uitoa_base.c			\
			  core/src/ft_uilen.c				\
			  core/src/ft_litoa.c				\
			  core/src/ft_itoa_static.c			\
			  core/src/ft_litoa_static.c		\
			  core/src/ft_sitoa_base_static.c	\
			  core/src/ft_uitoa_base_static.c	\
			  core/src/ft_ftoa_static.c			\
			  core/src/ft_freematr.c			\
			  core/src/ft_gnl.c					\
			  core/src/ft_intlen.c				\
			  core/src/ft_iswhite.c				\
			  core/src/ft_lstfree.c				\
			  core/src/ft_strfrjoin.c			\
			  core/src/ft_strindexof.c			\
			  core/src/ft_node_prepend.c		\
			  core/src/ft_node_append.c			\
			  core/src/ft_node_del.c			\
			  core/src/ft_error.c				\
			  core/src/ft_min.c					\
			  core/src/ft_max.c					\
			  core/src/ft_abs.c					\
			  core/src/ft_free.c				\
			  collections/src/ft_hash.c			\
			  collections/src/queue.c			\
			  collections/src/list.c			\
              collections/src/list_get.c		\
              collections/src/list_conv.c		\
              collections/src/list_insert.c		\
              collections/src/list_remove.c     \
			  collections/src/list_sort.c       \
              collections/src/ft_hash.c						\
              collections/src/hash_map.c					\
              collections/src/hm_init_free_clear.c			\
              collections/src/hm_lookup_remove_insert.c		\
              collections/src/iterator.c					\
              collections/src/queue.c						\
              collections/src/queue_push_pop.c				\
              collections/src/queue_peek.c					\
              string/src/string_builder.c					\
              string/src/string_builder_operats.c

SRC			= $(addprefix $(SRCDIR)/, $(SRCNAME))
OBJ			= $(addprefix $(OBJDIR)/, $(SRCNAME:.c=.o))

CLEAR       = "\033[K"
EOC			= "\033[0;0m"
GREEN		= "\033[0;32m"
CR			= "\r"$(CLEAR)

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@$(RANLIB) $(NAME)
	@echo "\n"
	@echo "\033[32m [OK] \033[0m\033[32mCompiling library: \033[36m " $(NAME)
	@echo "\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(MKDIR) $(OBJDIR)/printf/src/types
	@$(MKDIR) $(OBJDIR)/printf/src/tools
	@$(MKDIR) $(OBJDIR)/printf/src/specs
	@$(MKDIR) $(OBJDIR)/core/src
	@$(MKDIR) $(OBJDIR)/collections/src
	@$(MKDIR) $(OBJDIR)/string/src
	@$(GCC) $(WOPT) $(OOPT) $(IOPT) -g -c $< -o $@
	@echo "\033[32m [OK] \033[0m\033[32mCompiling:\033[36m " $@

clean:
	@$(RM) $(OBJDIR)
	@echo "\033[31m [OK] \033[0m\033[31mDeleting catalog and binaries:\033[33m " $(OBJDIR)

fclean: clean
	@$(RM) $(NAME)
	@echo "\033[31m [OK] \033[0m\033[31mDeleting execution file:\033[33m " $(NAME)

re: fclean all

norm:
	$(NORMINETTE) $(INCDIR) $(SRC)

.PHONY: all clean fclean re norm
