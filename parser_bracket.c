#include "regex.h"
#include "internal_regex.h"

t_bracket_parser brackets[] = {
	{":alnum:", "[A-Za-z0-9]"},
};

int		lexer_parser_bracket_chars_classes(t_bin_tree *leaf, char *pat, int *cursor)
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
				lexer_parser_bracket(leaf, brackets[index_char_classes].associated, strlen(brackets[index_char_classes].associated));
				return (OK);
			}
			index_char_classes++;
		}
		return (ERROR_BAD_CHARACTERS_CLASSES);
	}
	*cursor = save_cursor;
	return (KO);
}

int		lexer_parser_bracket_range(t_bin_tree *leaf, char *pat)
{
	int		start;
	int		end;

	start = *pat;
	end = *(pat + 2);
	if (start > end)
		return (KO);
	while (start <= end)
	{
		leaf->re_token.data.expr.rng.sbc[start] = 1;
		start++;
	}
	return (OK);
}

int		lexer_parser_bracket_parser(t_bin_tree *leaf, char *pat, int size_match)
{
	int		cursor;
	int		err;
	int		end_bracket;

	cursor = 0;
	while (cursor < size_match)
	{
		if (pat[cursor] == '\\')
		{
			cursor++;
			continue;
		}
		if (pat[cursor] == '[' && pat[cursor + 1] == ':')
		{
			err = lexer_parser_bracket_chars_classes(leaf, &pat[cursor + 1], &cursor);
			if (err == OK)
			{
				cursor++;
				continue;
			}
			else if (err != OK && err != KO)
				return (ERROR_BAD_CHARACTERS_CLASSES);
		}
		if (size_match - cursor > 2 && pat[cursor + 1] == '-')
		{
			if (lexer_parser_bracket_range(leaf, &pat[cursor]) == KO)
				return (ERROR_RANGE_OUT_OF_ORDER);
			cursor += 2;
		}
		else
			leaf->re_token.data.expr.rng.sbc[(int)pat[cursor]] = 1;
		cursor++;
	}
	return OK;
}

int		lexer_parser_bracket(t_bin_tree *leaf, char *pat, int size_match)
{
	int err;

	leaf->re_token.type = leaf->re_token.type | TKN_EXPR_RNG;
	if (pat[1] == '^')
	{
		leaf->re_token.data.expr.rng.reverse = 1;
		err = lexer_parser_bracket_parser(leaf, &pat[2], size_match - 3);
	}
	else
		err = lexer_parser_bracket_parser(leaf, &pat[1], size_match - 2);
	return err;
}
