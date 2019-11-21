/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parse_bracket_range.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:47:10 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:30:23 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_parse_bracket_range(t_bin_tree *node, char *pat, int *cursor)
{
	int		start;
	int		end;

	start = *pat;
	end = *(pat + 2);
	if (start > end)
		return (KO);
	while (start <= end)
	{
		if ((node->re_token.options & FLAG_CASE_INSENSITIVE)
			&& start >= 'A' && start <= 'Z')
			node->re_token.data.expr.rng.sbc[start + 'a' - 'A'] = 1;
		else
			node->re_token.data.expr.rng.sbc[start] = 1;
		start++;
	}
	(*cursor) += 2;
	return (OK);
}
