#include "regex.h"
#include "internal_regex.h"

t_lexer_match_parser parser_func[] = {
	{ lexer_match_bracket, lexer_parser_bracket, TKN_EXPR, "Match bracket" },
	{ lexer_match_subexpre, 0x0, TKN_EXPR, "Match sub expr" },
	{ lexer_match_point, lexer_parser_point, TKN_EXPR, "Match point" },
	{ lexer_match_count, lexer_parser_count, TKN_OP_EXPR, "Match count" },
	{ lexer_match_start, lexer_parser_start, TKN_OP, "Match SOL" },
	{ lexer_match_end, lexer_parser_end, TKN_OP, "Match EOL" },
	{ lexer_match_constant, lexer_parser_const, TKN_EXPR, "Match const" },
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
			printf("Match token:: %s\n", parser_func[i].debug);
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
	while (pat[*size_match])
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

int		valid_stack(t_bin_tree *stack[2], char *left)
{
	if (stack[0] && stack[1] && (stack[0]->re_token.type & (TKN_OP))
		&& (stack[1]->re_token.type & (TKN_OP)))
	{
		printf("Can't find operator token after another one. '%s'\n", left);
		return (KO);
	}
	else if (stack[0]->re_token.type == TKN_OP_EXPR)
	{
		printf("Can't find expression before token operator. '%s'\n", left);
		return (KO);
	}
	return (OK);
}

int		re_stack_inc(t_bin_tree **stack, int size, int token_type)
{
	t_bin_tree		*leaf;

	stack[size] = create_leaf(token_type);
	(size)++;
}

void	re_depop_stack(t_regex *r, t_bin_tree *stack[2], int *stack_crt_size)
{
	if (stack[1]->re_token.type & TKN_OP_EXPR)
	{
		push_leaf(r, stack[1]);
		push_leaf(r, stack[0]);
	}
	else
	{
		push_leaf(r, stack[0]);
		push_leaf(r, stack[1]);
	}
	*stack_crt_size = 0;
}

int		re_compile_internal(t_regex *r, char *pat, int full_size)
{
	t_bin_tree		*stack[2];
	int				stack_crt_size;
	int				size_match;
	int				cursor;
	t_lexer_match_parser	*match;

	cursor = 0;
	stack[0] = 0;
	stack[1] = 0;
	stack_crt_size = 0;
	while (cursor < full_size)
	{
		match = re_internal_match_token(&pat[cursor], full_size - cursor, &size_match);
		if (!match)
		{
			printf("No match '%s'\n", &pat[cursor]);
			return (KO);
		}
		re_stack_inc(stack, stack_crt_size, match->token_type);
		stack_crt_size++;
		if (valid_stack(stack, &pat[cursor]) != OK)
			return (KO);
		match->parser(&(stack[stack_crt_size - 1]->re_token), &pat[cursor], size_match);
		if (stack_crt_size == 2)
			re_depop_stack(r, stack, &stack_crt_size);
		cursor += size_match;
	}
	if (stack_crt_size == 1)
		push_leaf(r, stack[0]);
	return (OK);
}

int	ft_regcomp(t_regex *r, char *pat)
{
	int ret;

	r->test = pat;
	r->tree = 0x0;
	r->last = 0x0;
	ret = re_compile_internal(r, pat, strlen(pat));
	return (ret);
}

int main(int argc, char **argv)
{
	t_regex	regex;

	if (argc > 1)
	{
		printf("INPUT: %s\n", argv[1]);
		if (ft_regcomp(&regex, argv[1]) == OK)
		{
			printf("PARSE OK\n");
			if (argc > 2)
			{
				if (re_exec(&regex, argv[2]) == OK)
					printf("MATCH\n");
				else
					printf("NO MATCH\n");
			}
		}
		else
			printf("PARSE KO\n");
	}
	return 0;
}