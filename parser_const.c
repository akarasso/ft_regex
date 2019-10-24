#include "regex.h"
#include "internal_regex.h"

int		re_parser_const(t_token *token, char *pat, int size_match)
{
	token->type = TKN_EXPR;
	
	return (OK);
}