/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:23:28 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:44:49 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

t_char_class g_char_classes[] = {
	{":alnum:", "[A-Za-z0-9]"},
};

int g_char_classes_count = sizeof(g_char_classes) / sizeof(g_char_classes[0]);

t_lexer_flag g_flags[] = {
	{ 'm', FLAG_MULTILINE },
	{ 'i', FLAG_CASE_INSENSITIVE },
	{ 'x', FLAG_IGNORE_WHITESPACE },
	{ 's', FLAG_SINGLE_LINE },
	{ 'X', FLAG_EXTENDED },
	{ 'A', FLAG_ANCHOR },
	{ 'g', FLAG_GLOBAL },
};

int g_flag_count = sizeof(g_flags) / sizeof(g_flags[0]);

t_lexer_match_parser g_parser_func[] = {
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

int g_rule_count = sizeof(g_parser_func) / sizeof(g_parser_func[0]);
