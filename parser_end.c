#include "regex.h"
#include "internal_regex.h"

int		lexer_parser_end(t_token *token, char *pat, int size_match)
{
	token->type = token->type | TKN_OP_END;
	return (OK);
}