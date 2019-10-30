#include "regex.h"
#include "internal_regex.h"

int		lexer_parser_subexpre(t_token *token, char *pat, int size_match)
{
	token->type = TKN_TREE; // Do recreate full tree from regex shouldn't be here
}

void	lexer_parser_count_range(t_token *token, char *pat, int size_match)
{
	int		index;
	char	selecteur;

	selecteur = 0;
	index = 0;
	token->data.op.min = 0;
	token->data.op.max = -1;
	while (index < size_match)
	{
		if (pat[index] >= '0' && pat[index] <= '9')
		{
			if (!selecteur)
				token->data.op.min = token->data.op.min * 10 + (pat[index] - '0');
			else
			{
				// printf("Min %d Max %d\n", token->data.op.min, token->data.op.max);
				if (token->data.op.max < 0)
					token->data.op.max = 0;
				token->data.op.max = token->data.op.max * 10 + (pat[index] - '0');
			}
		}
		else if (pat[index] == ',')
			selecteur++;
		index++;
	}
}

int		lexer_parser_count(t_token *token, char *pat, int size_match)
{
	if (*pat == '*')
		token->type = token->type | TKN_OP_STAR;
	else if (*pat == '?')
		token->type = token->type | TKN_OP_QUERY;
	else if (*pat == '+')
		token->type = token->type | TKN_OP_PLUS;
	else
	{
		// printf("Range count\n");
		token->type = token->type | TKN_OP_RANGE;
		lexer_parser_count_range(token, pat + 1, size_match);
		// printf("Min %d Max %d\n", token->data.op.min, token->data.op.max);
	}
}