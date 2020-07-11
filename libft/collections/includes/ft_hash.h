#ifndef HASH_STRING_H
#define HASH_STRING_H

#include <stddef.h>
#include <coreft.h>

size_t	ft_hash(pointer pointer);
size_t	string_nocase_hash(void *string);
size_t	int_hash(pointer pointer);
size_t	pointer_hash(pointer pointer);

#endif

