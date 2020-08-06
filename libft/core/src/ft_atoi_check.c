#include "coreft.h"
int					ft_atoi_check(int value, const char *str)
{
	char			*value_str;
	int				res;

	res = 0;
	value_str = ft_itoa_static(value);
	if (strcmp(value_str, str + (str[0] == '+')) == 0)
		res = 1;
	return (res);
}
