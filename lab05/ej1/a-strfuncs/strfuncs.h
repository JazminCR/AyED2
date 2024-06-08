#ifndef _STRFUNCS_H
#define _STRFUNCS_H
#include <stdbool.h>

// calcula la longitud de la cadena apuntada por str
size_t string_length(const char *str);

// filtra los caracteres iguales a c de la cadena apuntada por str
char *string_filter(const char *str, char c);

// determina si la cadena apuntada por str es simétrica
bool string_is_symmetric(const char *str);

#endif
