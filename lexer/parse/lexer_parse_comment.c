/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_comment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:47:55 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:28:36 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_parse_comment(
	t_regex *regex,
	t_bin_tree *node,
	char *pat,
	int size_match)
{
	(void)regex;
	node->re_token.data.expr.cst.value = malloc(size_match + 1);
	strncpy(node->re_token.data.expr.cst.value, pat, size_match);
	node->re_token.data.expr.cst.value[size_match] = 0;
	node->re_token.data.expr.cst.size = size_match;
	return (OK);
}
