#include "regex.h"
#include "internal_regex.h"

int		lexer_parser_group(t_bin_tree *leaf, char *pat, int size_match)
{
	t_regex sub;
	int ret;

	leaf->re_token.type = leaf->re_token.type | TKN_GROUP;
	sub.test = pat;
	sub.tree = 0x0;
	sub.last = 0x0;
	printf("PARSE GROUP: %.*s\n", size_match - 2, pat + 1);
	ret = re_compile_internal(&sub, pat + 1, size_match - 2);
	if (ret == OK)
		leaf->left = sub.tree;
	return (ret);
}

void	lexer_parser_count_range(t_bin_tree *leaf, char *pat, int size_match)
{
	int		index;
	char	selecteur;

	selecteur = 0;
	index = 0;
	leaf->re_token.data.op.min = 0;
	leaf->re_token.data.op.max = -1;
	while (index < size_match)
	{
		if (pat[index] >= '0' && pat[index] <= '9')
		{
			if (!selecteur)
				leaf->re_token.data.op.min = leaf->re_token.data.op.min * 10 + (pat[index] - '0');
			else
			{
				if (leaf->re_token.data.op.max < 0)
					leaf->re_token.data.op.max = 0;
				leaf->re_token.data.op.max = leaf->re_token.data.op.max * 10 + (pat[index] - '0');
			}
		}
		else if (pat[index] == ',')
			selecteur++;
		index++;
	}
}

int		lexer_parser_count(t_bin_tree *leaf, char *pat, int size_match)
{
	leaf->re_token.type = leaf->re_token.type | TKN_OP_RANGE;
	lexer_parser_count_range(leaf, pat + 1, size_match);
	return (OK);
}

int		lexer_parser_star(t_bin_tree *leaf, char *pat, int size_match)
{
	leaf->re_token.type = leaf->re_token.type | TKN_OP_STAR;
	return (OK);
}

int		lexer_parser_query(t_bin_tree *leaf, char *pat, int size_match)
{
	leaf->re_token.type = leaf->re_token.type | TKN_OP_QUERY;
	return (OK);
}

int		lexer_parser_plus(t_bin_tree *leaf, char *pat, int size_match)
{
	leaf->re_token.type = leaf->re_token.type | TKN_OP_PLUS;
	return (OK);
}