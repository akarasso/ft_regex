#include "regex.h"
#include "internal_regex.h"

int		lexer_match_flag(t_regex *regex, char *pat, int size_left, int *size_match)
{
	int			i;

	if (!size_left || *pat != '(' || *(pat + 1) != '?')
		return (NO);
	pat += 2;
	*size_match = 2;
	if (*pat == '!')
	{
		(*size_match)++;
		pat++;
	}
	while (size_left && *pat && *pat != ')')
	{
		pat++;
		size_left--;
		(*size_match)++;
	}
	if (*pat == ')')
	{
		pat++;
		size_left--;
		(*size_match)++;
	}
	return (OK);
}