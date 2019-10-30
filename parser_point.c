#include "regex.h"
#include "internal_regex.h"

int		lexer_parser_point(t_token *token, char *pat, int size_match)
{
	token->type = token->type | TKN_EXPR_ANY;
	return (OK);
}