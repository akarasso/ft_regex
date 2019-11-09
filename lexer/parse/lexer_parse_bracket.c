#include "regex.h"
#include "internal_regex.h"

int		lexer_parse_bracket_chars_classes(t_regex *regex, t_bin_tree *node, char *pat, int *cursor)
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
		while (index_char_classes < char_classes_count)
		{
			if (!strncmp(char_classes[index_char_classes].match, &pat[save_cursor], *cursor))
			{
				(*cursor)++;
				lexer_parse_bracket(regex, node, char_classes[index_char_classes].associated, ft_strlen(char_classes[index_char_classes].associated));
				return (OK);
			}
			index_char_classes++;
		}
		return (ERROR_BAD_CHARACTERS_CLASSES);
	}
	*cursor = save_cursor;
	return (KO);
}

int		lexer_parse_bracket_range(t_bin_tree *node, char *pat)
{
	int		start;
	int		end;

	start = *pat;
	end = *(pat + 2);
	if (start > end)
		return (KO);
	while (start <= end)
	{
		if ((node->re_token.options & FLAG_CASE_INSENSITIVE) && start >= 'A' && start <= 'Z')
			node->re_token.data.expr.rng.sbc[start + 'a' - 'A'] = 1;
		else
			node->re_token.data.expr.rng.sbc[start] = 1;
		start++;
	}
	return (OK);
}

int		lexer_parse_bracket_parser(t_regex *regex, t_bin_tree *node, char *pat, int size_match)
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
			err = lexer_parse_bracket_chars_classes(regex, node, &pat[cursor + 1], &cursor);
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
			if (lexer_parse_bracket_range(node, &pat[cursor]) == KO)
				return (ERROR_RANGE_OUT_OF_ORDER);
			cursor += 2;
		}
		else
		{
			if ((node->re_token.options & FLAG_CASE_INSENSITIVE) && pat[cursor] >= 'A' && pat[cursor] <= 'Z')
				node->re_token.data.expr.rng.sbc[(int)pat[cursor] + 'a' - 'A'] = 1;
			else
				node->re_token.data.expr.rng.sbc[(int)pat[cursor]] = 1;
		}
		cursor++;
	}
	return OK;
}

int		lexer_parse_bracket(t_regex *regex, t_bin_tree *node, char *pat, int size_match)
{
	int err;

	if (pat[1] == '^')
	{
		node->re_token.data.expr.rng.reverse = 1;
		err = lexer_parse_bracket_parser(regex, node, &pat[2], size_match - 3);
	}
	else
		err = lexer_parse_bracket_parser(regex, node, &pat[1], size_match - 2);
	return err;
}
