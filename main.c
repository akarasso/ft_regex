#include "regex.h"
#include "internal_regex.h"

t_match_parser parser_func[] = {
	{re_match_bracket,	re_parser_bracket, "Match bracket"},
	{re_match_subexpre,	0x0, "Match sub expr"}, // TBD
	{re_match_point,	re_parser_point, "Match point"},
	{re_match_count,	re_parser_count, "Match count"},
	{re_match_constant,	re_parser_const, "Match const"},
};

t_parser_func	re_internal_match_token(char *pat, int size, int *size_match)
{
	int i;

	i = 0;
	while (i < 5)
	{
		*size_match = 0;
		if (parser_func[i].match(pat, size, size_match) == OK)
		{
			printf("%s\n", parser_func[i].debug);
			return parser_func[i].parser;
		}
		i++;
	}
	return (0x0);
}

int		re_match_constant(char *pat, int size_left, int *size_match)
{
	int i;
	int no;

	no = 0;
	while (pat[*size_match])
	{
		i = 0;
		while (i < 4)
		{
			if (parser_func[i].match(&pat[*size_match], size_left - *size_match, &no) == OK)
				return (OK);
			i++;
		}
		(*size_match)++;	
	}
	return (OK);
}

int		re_compile_internal(t_regex *r, char *pat, int full_size)
{
	t_bin_tree		*leaf;
	int				size_match;
	int				cursor;
	t_parser_func	parser;

	cursor = 0;
	while (cursor < full_size)
	{
		printf("Try to parse {%s}\n", &pat[cursor]);
		parser = re_internal_match_token(&pat[cursor], full_size - cursor, &size_match);
		if (parser)
		{
			leaf = create_leaf();
			parser(&(leaf->re_token), &pat[cursor], size_match); // Check return error here in futur
			cursor += size_match;
			continue;
		}
		printf("KO on %s\n", &pat[cursor]);
		return (KO);
	}
	return (OK);
}

int	ft_regcomp(t_regex *r, char *pat)
{
	int ret;

	r->test = pat;
	r->tree = 0x0;
	ret = re_compile_internal(r, pat, strlen(pat));
	return (ret);
}

int main(int argc, char **argv)
{
	t_regex	regex;

	if (argc > 1)
	{
		printf("INPUT: %s\n", argv[1]);
		ft_regcomp(&regex, argv[1]);
	}
	return 0;
}