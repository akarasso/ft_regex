#include "regex.h"
#include "internal_regex.h"

int		lexer_match_end(char *pat, int size_left, int *size_match)
{
	if (*pat == '$')
	{
		*size_match = 1;
		return (OK);
	}
	return (KO);
}

int		lexer_match_or(char *pat, int size_left, int *size_match)
{
	if (size_left && *pat == '|')
	{
		*size_match = 1;
		return (OK);
	}
	return (KO);
}

int		lexer_match_start(char *pat, int size_left, int *size_match)
{
	if (*pat == '^')
	{
		*size_match = 1;
		return (OK);
	}
	return (KO);
}

int		lexer_match_any(char *pat, int size_left, int *size_match)
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

int		lexer_match_group(char *pat, int size_left, int *size_match)
{
	int		stack;

	if (!size_left || *pat != '(')
		return (NO);
	stack = 0;
	while (size_left && pat[*size_match])
	{
		if (pat[*size_match] == '(')
		{
			stack++;
		}
		else if (pat[*size_match] == ')')
		{
			stack--;
			if (stack == 0)
				break;
		}
		size_left--;
		(*size_match)++;
	}
	if (pat[*size_match] != ')')
		return (ERROR_INCOMPLETE_RANGE);
	(*size_match)++;
	return (OK);
}

int		lexer_match_bracket(char *pat, int size_left, int *size_match)
{
	int stack;

	stack = 0;
	if (size_left < 3 || *pat != '[')
		return (NO);
	while (size_left - *size_match > 0 && pat[*size_match])
	{
		if (pat[*size_match] == '[')
			stack++;
		else if (pat[*size_match] == ']')
			stack--;
		if (stack == 0 && pat[*size_match] == ']')
			break;
		(*size_match)++;
	}
	if (pat[*size_match] != ']')
		return (ERROR_INCOMPLETE_RANGE);
	(*size_match)++;
	return (OK);
}

int		lexer_match_star(char *pat, int size_left, int *size_match)
{
	if (!size_left || *pat != '*')
		return (NO);
	*size_match = 1;
	return (OK);
}

int		lexer_match_query(char *pat, int size_left, int *size_match)
{
	if (!size_left || *pat != '?')
		return (NO);
	*size_match = 1;
	return (OK);
}

int		lexer_match_plus(char *pat, int size_left, int *size_match)
{
	if (!size_left || *pat != '+')
		return (NO);
	*size_match = 1;
	return (OK);
}

int		lexer_match_count(char *pat, int size_left, int *size_match)
{
	if (!size_left || *pat != '{')
		return (NO);
	while (size_left && pat[*size_match] && pat[*size_match] != '}')
	{
		if (pat[*size_match] == '-')
			return (NO);
		size_left--;
		(*size_match)++;
	}
	if (pat[*size_match] != '}')
		return (NO);
	(*size_match)++;
	return (OK);
}