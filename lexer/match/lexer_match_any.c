#include "regex.h"
#include "internal_regex.h"

int		lexer_match_any(t_regex *regex, char *pat, int size_left, int *size_match)
{
	if (!size_left || *pat != '.')
		return (NO);
	if (*pat == '.')
	{
		*size_match = 1;
		return (OK);
	}
	return (NO);
}
