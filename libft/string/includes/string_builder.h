#ifndef LEM_IN_STRING_BUILDER_H
#define LEM_IN_STRING_BUILDER_H

# include <coreft.h>
# include <collections.h>

#ifndef SB_H
#define SB_H

#define SB_FAILURE				-1
#define SB_MAX_FRAG_LENGTH		4096

typedef struct s_string
{
	char					*str;
	int						length;
}							t_str;

typedef struct 				s_sting_builder
{
	t_qu 					*_qu;
	size_t					len;
} 							t_str_bld;

t_str_bld		*sb_create();
int				sb_empty(t_str_bld *sb);
int				sb_append(t_str_bld *sb, char *str);
//int				sb_appendf(t_str_bld *sb, const char *format, ...);
char			*sb_concat(t_str_bld *sb);
void 			sb_reset(t_str_bld *sb);
void			sb_free(t_str_bld *sb);

#endif

#endif //LEM_IN_STRING_BUILDER_H
