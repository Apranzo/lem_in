/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cshinoha <cshinoha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:39:28 by cshinoha          #+#    #+#             */
/*   Updated: 2020/11/29 19:28:09 by cshinoha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <limits.h>
# include "../../core/includes/coreft.h"
# include "../../string/includes/string_builder.h"

# define PRINTF_BUFF_SIZE	16192
# define LENGTH_H	0x01
# define LENGTH_HH	0x02
# define LENGTH_L	0x04
# define LENGTH_LL	0x08
# define LENGTH_LLL	0x10
# define LENGTH_J	0x20
# define LENGTH_Z	0x40
# define LENGTH_T	0x80

typedef size_t		(*t_fflush)(t_pntr buffer);

typedef struct		s_data
{
	char			*str;
	int				length;
	char			*prefix;
	unsigned		negative : 1;
}					t_data;

typedef struct		s_buffer
{
	t_pntr			out;
	int				index;
	int				fd;
	int				length;
	char			content[PRINTF_BUFF_SIZE];
	t_fflush		flush_buf;

}					t_buffer;

typedef struct		s_info
{
	va_list			ap;
	char			type;
	int				width;
	int				length;
	int				precision;
	unsigned		hash	: 1;
	unsigned		zero	: 1;
	unsigned		plus	: 1;
	unsigned		minus	: 1;
	unsigned		space	: 1;
	unsigned		point	: 1;
	t_buffer		buffer;
}					t_info;

int					ft_common(const char *format, t_info *info);
int					ft_sbprintf(t_str_bld *str, const char *format, ...);
int					ft_sprintf(char **str, const char *format, ...);
int					ft_vfprintf(int fd, const char *format, ...);
int					ft_printf(const char *format, ...);
void				parsing(const char **format, t_info *info);

void				initialize_flags(t_info *info);
void				initialize_specs(t_info *info);
void				initialize_buffer(int fd, t_buffer *buffer);
int					buffer_full(t_buffer *buffer);
void				print_buffer(t_buffer *buffer);
void				write_char(t_buffer *buffer, char c);
void				write_str(t_buffer *buffer, char *str, int length);

void				get_si(intmax_t *number, t_info *info);
void				get_ui(uintmax_t *number, t_info *info);
void				get_f(long double *number, t_info *info);
void				apply_specs(t_info *info, t_data *data);
typedef void		(*t_handler)(const char **format, t_info *info);
void				flag_hash(const char **format, t_info *info);
void				flag_zero(const char **format, t_info *info);
void				flag_plus(const char **format, t_info *info);
void				flag_minus(const char **format, t_info *info);
void				flag_space(const char **format, t_info *info);
void				digit(const char **format, t_info *info);
void				set_width(const char **format, t_info *info);
void				set_precision(const char **format, t_info *info);
void				length_h(const char **format, t_info *info);
void				length_j(const char **format, t_info *info);
void				length_l(const char **format, t_info *info);
void				length_t(const char **format, t_info *info);
void				length_z(const char **format, t_info *info);
void				type_b(const char **format, t_info *info);
void				type_c(const char **format, t_info *info);
void				type_d(const char **format, t_info *info);
void				type_f(const char **format, t_info *info);
void				type_o(const char **format, t_info *info);
void				type_p(const char **format, t_info *info);
void				type_s(const char **format, t_info *info);
void				type_u(const char **format, t_info *info);
void				type_x(const char **format, t_info *info);
void				unknown(const char **format, t_info *info);
void				percent(const char **format, t_info *info);
void				wildcard(const char **format, t_info *info);

static t_handler	g_jump_table[] = {
	flag_space, unknown, unknown, flag_hash, unknown, percent, unknown, unknown,
	unknown, unknown, wildcard, flag_plus, unknown, flag_minus, set_precision,
	unknown, flag_zero, digit, digit, digit, digit, digit, digit, digit, digit,
	digit, unknown, unknown, unknown, unknown, unknown, unknown, unknown,
	unknown, type_b, type_c, type_d, unknown, type_f, unknown, unknown,
	unknown, unknown, unknown, length_l, unknown, unknown, type_o, unknown,
	unknown, unknown, type_s, unknown, type_u, unknown, unknown, type_x,
	unknown, unknown, unknown, unknown, unknown, unknown, unknown, unknown,
	unknown, type_b, type_c, type_d, unknown, type_f, unknown, length_h,
	type_d, length_j, unknown, length_l, unknown, unknown, type_o, type_p,
	unknown, unknown, type_s, length_t, type_u, unknown, unknown, type_x,
	unknown, length_z, unknown, unknown, unknown, unknown
};

#endif
