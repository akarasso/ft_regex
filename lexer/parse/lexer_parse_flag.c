#include "regex.h"
#include "internal_regex.h"

static int	lexer_find_flag(char c)
{
	int i;

	i = 0;
	while (i < flag_count - 2)
	{
		if (flags[i].flag == c)
			return i;
		i++;
	}
	return (-1);
}

/*
** (?iXx...)
** (?!iXx...)
*/

int			lexer_parse_flag(t_regex *regex, t_bin_tree *node, char *pat, int size_match)
{
	int i;
	int i_flag;

	if (pat[size_match - 1] != ')')
		return KO;
	node->re_token.data.flag.reverse = (pat[2] == '!') ? 1 : 0;
	i = (pat[2] == '!') ? 3 : 2;
	while (i < size_match - 1)
	{
		i_flag = lexer_find_flag(pat[i]);
		if (i_flag < 0)
		{
			printf("Error unknow modifier\n");
			return (KO);
		}
		node->re_token.data.flag.options |= flags[i_flag].value;
		i++;
	}
	if (node->re_token.data.flag.reverse)
		regex->options &= ~node->re_token.data.flag.options;
	else
		regex->options |= node->re_token.data.flag.options;
	return (OK);
}