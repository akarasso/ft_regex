#include "regex.h"
#include "internal_regex.h"

t_bracket_parser brackets[] = {
	{":alnum:", "[A-Za-z0-9]"},
};

int		re_parser_bracket_chars_classes(t_token *token, char *pat, int *cursor)
{
	int	save_cursor;
	int	index_char_classes;
	int len_match;

	save_cursor = *cursor;
	index_char_classes = 0;
	while (pat[*cursor] && pat[*cursor] != ']')
		(*cursor)++;
	if (*cursor > 1 && pat[*cursor] == ']' && pat[*cursor - 1] == ':')
	{
		while (index_char_classes < 1)
		{
			if (!strncmp(brackets[index_char_classes].match, &pat[save_cursor], *cursor))
			{
				(*cursor)++;
				re_parser_bracket(token, brackets[index_char_classes].associated, strlen(brackets[index_char_classes].associated));
				return (OK);
			}
			index_char_classes++;
		}
		return (ERROR_BAD_CHARACTERS_CLASSES);
	}
	*cursor = save_cursor;
	return (KO);
}

int		re_parser_bracket_range(t_token *token, char *pat)
{
	int		start;
	int		end;

	start = *pat;
	end = *(pat + 2);
	if (start > end)
		return (KO);
	while (start <= end)
	{
		token->data.expr.data.rng.sbc[start] = 1;
		start++;
	}
	return (OK);
}

int		re_parser_bracket_parser(t_token *token, char *pat, int size_match)
{
	int		cursor;
	int		err;
	int		end_bracket;

	cursor = 0;
	while (cursor < size_match)
	{
		if (pat[cursor] == '[' && pat[cursor + 1] == ':')
		{
			err = re_parser_bracket_chars_classes(token, &pat[cursor + 1], &cursor);
			if (err == OK)
			{
				printf("CHAR CLASSES\n");
				cursor++;
				continue;
			}
			else if (err != OK && err != KO)
				return (ERROR_BAD_CHARACTERS_CLASSES);
		}
		if (size_match - cursor > 2 && pat[cursor + 1] == '-')
		{
			printf("RANGE\n");
			if (re_parser_bracket_range(token, &pat[cursor]) == KO)
				return (ERROR_RANGE_OUT_OF_ORDER);
			cursor += 2;
		}
		else
		{
			printf("SBC %c\n", pat[cursor]);
			token->data.expr.data.rng.sbc[(int)pat[cursor]] = 1;
		}
		cursor++;
	}
	return OK;
}

int		re_parser_bracket(t_token *token, char *pat, int size_match)
{
	int err;

	token->type = TKN_EXPR;
	printf("Range token {%.*s}\n", size_match - 2, &pat[1]);
	err = re_parser_bracket_parser(token, &pat[1], size_match - 2);
	if (err != OK)
	{
		printf("Error num: %d\n", err);
	}
}
