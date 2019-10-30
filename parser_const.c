#include "regex.h"
#include "internal_regex.h"

int		lexer_parser_const(t_token *token, char *pat, int size_match)
{
	token->type = token->type | TKN_EXPR_CST;
	token->data.expr.cst.value = malloc(size_match + 1);
	strncpy(token->data.expr.cst.value, pat, size_match);
	token->data.expr.cst.value[size_match] = 0;
	token->data.expr.cst.size = size_match;
	return (OK);
}