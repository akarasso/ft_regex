#include "regex.h"
#include "internal_regex.h"

int		lexer_match_comment(t_regex *regex, char *pat, int size_left, int *size_match)
{
	if ((regex->options & FLAG_IGNORE_WHITESPACE) && *pat == '#')
	{
		*size_match = size_left;
		return (OK);
	}
	return (KO);
}
