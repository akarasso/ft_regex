#include "regex.h"
#include "internal_regex.h"

int		lexer_match_end(char *pat, int size_left, int *size)
{
	if (*pat == '$')
	{
		*size = 1;
		return (OK);
	}
	return (KO);
}

int		lexer_match_start(char *pat, int size_left, int *size)
{
	if (*pat == '^')
	{
		*size = 1;
		return (OK);
	}
	return (KO);
}

int		lexer_match_point(char *pat, int size_left, int *size)
{
	if (!size_left || *pat != '.')
		return (NO);
	if (*pat == '.')
	{
		*size = 1;
		return (OK);
	}
	return (NO);
}

int		lexer_match_subexpre(char *pat, int size_left, int *size)
{
	if (!size_left || *pat != '(')
		return (NO);
	while (size_left && pat[*size] && pat[*size] != ')')
	{
		size_left--;
		(*size)++;
	}
	if (pat[*size] != ')')
		return (ERROR_INCOMPLETE_RANGE);
	return (OK);
}

int		lexer_match_bracket(char *pat, int size_left, int *size)
{
	int stack;

	stack = 0;
	if (size_left < 3 || *pat != '[')
		return (NO);
	while (size_left - *size > 0 && pat[*size])
	{
		if (pat[*size] == '[')
			stack++;
		else if (pat[*size] == ']')
			stack--;
		if (stack == 0 && pat[*size] == ']')
			break;
		(*size)++;
	}
	if (pat[*size] != ']')
		return (ERROR_INCOMPLETE_RANGE);
	(*size)++;
	return (OK);
}

int		lexer_match_count(char *pat, int size_left, int *size)
{
	if (!size_left || (*pat != '{' && *pat != '*' && *pat != '?' && *pat != '+'))
		return (NO);
	if (*pat == '?' || *pat == '*' || *pat == '+')
	{
		*size = 1;
		return (OK);
	}
	while (size_left && pat[*size] && pat[*size] != '}')
	{
		if (pat[*size] == '-')
			return (NO);
		size_left--;
		(*size)++;
	}
	if (pat[*size] != '}')
		return (NO);
	(*size)++;
	return (OK);
}