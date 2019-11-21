/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:48:44 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:28:52 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_parse_end(
	t_regex *regex,
	t_bin_tree *node,
	char *pat,
	int size_match)
{
	(void)regex;
	(void)pat;
	(void)size_match;
	node->re_token.type = node->re_token.type | TKN_OP_END;
	return (OK);
}
