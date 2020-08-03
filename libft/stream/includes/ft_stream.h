#ifndef LEM_IN_FT_STREAM_H
#define LEM_IN_FT_STREAM_H

#include "coreft.h"

typedef struct	s_stream
{
	int			fd;
	char		buf[BUFSIZE];
	ssize_t		size;
	size_t		cursor;
}				t_stream;

#endif //LEM_IN_FT_STREAM_H
