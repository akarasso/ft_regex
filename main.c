#include "regex.h"
#include "internal_regex.h"

t_lexer_match_parser parser_func[] = {
	{
		lexer_match_bracket,
		lexer_parser_bracket,
		re_match_expr_rng,
		TKN_EXPR,
		"bracket"
	},
	{
		lexer_match_or,
		lexer_parser_or,
		re_match_op_or,
		TKN_OP_OR,
		"or"
	},
	{
		lexer_match_group,
		lexer_parser_group,
		re_match_expr_group,
		TKN_EXPR,
		"group"
	},
	{
		lexer_match_any,
		lexer_parser_any,
		re_match_expr_any,
		TKN_EXPR,
		"point"
	},
	{
		lexer_match_star,
		lexer_parser_star,
		re_match_op_star,
		TKN_OP_EXPR,
		"star"
	},
	{
		lexer_match_plus,
		lexer_parser_plus,
		re_match_op_plus,
		TKN_OP_EXPR,
		"plus"
	},
	{
		lexer_match_query,
		lexer_parser_query,
		re_match_op_query,
		TKN_OP_EXPR,
		"query"
	},
	{
		lexer_match_count,
		lexer_parser_count,
		re_match_op_count,
		TKN_OP_EXPR,
		"count"
	},
	{
		lexer_match_start,
		lexer_parser_start,
		re_match_op_start,
		TKN_OP,
		"SOL"
	},
	{
		lexer_match_end,
		lexer_parser_end,
		re_match_op_end,
		TKN_OP,
		"EOL"
	},
	{
		lexer_match_constant,
		lexer_parser_const,
		re_match_expr_cst,
		TKN_EXPR,
		"const"
	},
};

t_lexer_match_parser	*re_internal_match_token(char *pat, int size, int *size_match)
{
	int i;

	i = 0;
	while (i < sizeof(parser_func) / sizeof(t_lexer_match_parser))
	{
		*size_match = 0;
		if (parser_func[i].match(pat, size, size_match) == OK)
		{
			printf("Match token :: %s\n", parser_func[i].debug);
			return &parser_func[i];
		}
		i++;
	}
	return (0x0);
}

int		lexer_match_constant(char *pat, int size_left, int *size_match)
{
	int i;
	int no;

	no = 0;
	while (pat[*size_match] && size_left - *size_match > 0)
	{
		i = 0;
		while (i < sizeof(parser_func) / sizeof(t_lexer_match_parser) - 1)
		{
			if (parser_func[i].match(&pat[*size_match], size_left - *size_match, &no) == OK)
			{
				if ((parser_func[i].token_type & TKN_OP_EXPR) && *size_match > 1)
					(*size_match)--;
				return (OK);
			}
			i++;
		}
		(*size_match)++;	
	}
	return (OK);
}

int		re_compile_internal(t_regex *r, char *pat, int full_size)
{
	t_lexer_match_parser	*match;
	t_bin_tree				*leaf;
	int						size_match;
	int						cursor;

	cursor = 0;
	while (cursor < full_size)
	{
		match = re_internal_match_token(&pat[cursor], full_size - cursor, &size_match);
		if (!match)
		{
			printf("No match '%s'\n", &pat[cursor]);
			return (KO);
		}
		leaf = create_leaf(match);
		if (push_leaf(r, leaf) != OK)
		{
			printf("%s\n", &pat[cursor]);
			return (KO);
		}
		if (match->parser(leaf, &pat[cursor], size_match) != OK)
			return (KO);
		if (leaf->re_token.type & TKN_GROUP)
			r->n_subgroup_max++;
		cursor += size_match;
	}
	return (OK);
}

int	ft_regcomp(t_regex *r, char *pat)
{
	int ret;

	r->test = pat;
	r->tree = 0x0;
	r->last = 0x0;
	r->option = 0;
	r->n_subgroup_max = 0;
	ret = re_compile_internal(r, pat, strlen(pat));
	return (ret);
}

int main(int argc, char **argv)
{
	t_regex			regex;
	t_regex_match	*match;
	int				n_match;

	if (argc > 1)
	{
		printf("INPUT: %s\n", argv[1]);
		if (ft_regcomp(&regex, argv[1]) == OK)
		{
			printf("PARSE OK\n");
			if (argc > 2)
			{
				if (re_exec(&regex, &match, &n_match, argv[2]) == OK)
				{
					int o = 0;
					while (o < match->n_subgroup)
					{
						printf("Group %d: %s\n", o, match->subgroup[o]);
						o++;
					}
					printf("MATCH\n");
				}
				else
					printf("NO MATCH\n");
				// if (re_test(&regex, argv[2]) == OK)
				// 	printf("MATCH\n");
				// else
				// 	printf("NO MATCH\n");
			}
		}
		else
			printf("PARSE KO\n");
	}
	return 0;
}