/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_bracket.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:47:10 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:32:59 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_try_chars_classes(t_regex *re, t_bin_tree *nd, char *s, int *crs)
{
	int		err;

	err = lexer_parse_bracket_chars_classes(re, nd, &s[(*crs) + 1], crs);
	if (err == OK)
	{
		(*crs)++;
		return (OK);
	}
	else if (err != OK && err != KO)
		return (-1);
	return (KO);
}

void	lexer_parse_bracket_char(t_bin_tree *node, int c)
{
	if ((node->re_token.options & FLAG_CASE_INSENSITIVE)
		&& c >= 'A' && c <= 'Z')
	{
		node->re_token.data.expr.rng.sbc[c + 'a' - 'A'] = 1;
	}
	else
	{
		node->re_token.data.expr.rng.sbc[c] = 1;
	}
}

int		lexer_parse_bracket_parser(
	t_regex *re,
	t_bin_tree *nd,
	char *pat,
	int size_match)
{
	int		crs;

	crs = 0;
	while (crs < size_match)
	{
		if (pat[crs] != '\\')
		{
			if (pat[crs] == '[' && pat[crs + 1] == ':')
			{
				if (lexer_try_chars_classes(re, nd, &pat[crs], &crs) == OK)
					continue ;
			}
			if (size_match - crs > 2 && pat[crs + 1] == '-')
			{
				if (lexer_parse_bracket_range(nd, &pat[crs], &crs) == KO)
					return (ERROR_RANGE_OUT_OF_ORDER);
			}
			continue ;
		}
		else
			crs++;
		lexer_parse_bracket_char(nd, (int)pat[crs]);
		crs++;
	}
	return (OK);
}

int		lexer_parse_bracket(
	t_regex *regex,
	t_bin_tree *node,
	char *pat,
	int size_match)
{
	int err;

	if (pat[1] == '^')
	{
		node->re_token.data.expr.rng.reverse = 1;
		err = lexer_parse_bracket_parser(regex, node, &pat[2], size_match - 3);
	}
	else
		err = lexer_parse_bracket_parser(regex, node, &pat[1], size_match - 2);
	return (err);
}
