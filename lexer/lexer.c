#include "regex.h"
#include "internal_regex.h"

t_char_class char_classes[] = {
	{":alnum:", "[A-Za-z0-9]"},
};

size_t char_classes_count = sizeof(char_classes) / sizeof(char_classes[0]);

t_lexer_flag flags[] = {
	{ 'm', FLAG_MULTILINE },
	{ 'i', FLAG_CASE_INSENSITIVE },
	{ 'x', FLAG_IGNORE_WHITESPACE },
	{ 's', FLAG_SINGLE_LINE },
	{ 'X', FLAG_EXTENDED },
	{ 'A', FLAG_ANCHOR },
	{ 'g', FLAG_GLOBAL },
};

size_t flag_count = sizeof(flags) / sizeof(flags[0]);

t_lexer_match_parser parser_func[] = {
	{
		lexer_match_comment,
		lexer_parse_comment,
		re_match_flag,
		TKN_EXPR,
		"comment"
	},
	{
		lexer_match_flag,
		lexer_parse_flag,
		re_match_flag,
		TKN_OP | TKN_FLAG,
		"flag"
	},
	{
		lexer_match_bracket,
		lexer_parse_bracket,
		re_match_expr_rng,
		TKN_EXPR | TKN_EXPR_RNG,
		"bracket"
	},
	{
		lexer_match_or,
		lexer_parse_or,
		re_match_op_or,
		TKN_OP_OR,
		"or"
	},
	{
		lexer_match_group,
		lexer_parse_group,
		re_match_expr_group,
		TKN_EXPR | TKN_GROUP,
		"group"
	},
	{
		lexer_match_any,
		lexer_parse_any,
		re_match_expr_any,
		TKN_EXPR | TKN_EXPR_ANY,
		"point"
	},
	{
		lexer_match_star,
		lexer_parse_star,
		re_match_op_star,
		TKN_OP_EXPR | TKN_OP_STAR,
		"star"
	},
	{
		lexer_match_plus,
		lexer_parse_plus,
		re_match_op_plus,
		TKN_OP_EXPR | TKN_OP_PLUS,
		"plus"
	},
	{
		lexer_match_query,
		lexer_parse_query,
		re_match_op_query,
		TKN_OP_EXPR | TKN_OP_QUERY,
		"query"
	},
	{
		lexer_match_count,
		lexer_parse_count,
		re_match_op_count,
		TKN_OP_EXPR | TKN_OP_COUNT_RANGE,
		"count"
	},
	{
		lexer_match_start,
		lexer_parse_start,
		re_match_op_start,
		TKN_OP | TKN_OP_START,
		"SOL"
	},
	{
		lexer_match_end,
		lexer_parse_end,
		re_match_op_end,
		TKN_OP | TKN_OP_END,
		"EOL"
	},
	{
		lexer_match_constant,
		lexer_parse_const,
		re_match_expr_cst,
		TKN_EXPR | TKN_EXPR_CST,
		"const"
	},
};

size_t rule_count = sizeof(parser_func) / sizeof(parser_func[0]);