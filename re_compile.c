#include "regex.h"
#include "internal_regex.h"

t_lexer_match_parser	*re_internal_match_token(t_regex *regex, char *pat, int size, int *size_match)
{
	int i;

	i = 0;
	while (i < rule_count)
	{
		*size_match = 0;
		if (parser_func[i].match(regex, pat, size, size_match) == OK)
		{
			printf("Match token :: %s\n", parser_func[i].debug);
			return &parser_func[i];
		}
		i++;
	}
	return (0x0);
}

int		re_compile_internal(t_regex *regex, char *pat, int full_size)
{
	t_lexer_match_parser	*match;
	t_bin_tree				*node;
	int						size_match;
	int						cursor;

	cursor = 0;
	while (cursor < full_size)
	{
		match = re_internal_match_token(regex, &pat[cursor], full_size - cursor, &size_match);
		if (!match)
		{
			printf("No match '%s'\n", &pat[cursor]);
			return (KO);
		}
		node = create_node(match);
		node->re_token.options = regex->options;
		if (push_node(regex, node) != OK)
		{
			printf("%s\n", &pat[cursor]);
			return (KO);
		}
		if (match->parser(regex, node, &pat[cursor], size_match) != OK)
			return (KO);
		if (node->re_token.type & TKN_GROUP)
			regex->n_subgroup_max++;
		cursor += size_match;
	}
	return (OK);
}