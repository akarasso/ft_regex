/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_match_expr_rng.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:20:28 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:00:34 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		re_match_expr_rng(
	t_regex_match *match,
	t_bin_tree *node,
	char *origin,
	int *cursor)
{
	(void)match;
	if ((node->re_token.data.expr.rng.sbc[(unsigned int)*origin] == 1
			&& node->re_token.data.expr.rng.reverse == 0)
		|| (node->re_token.data.expr.rng.sbc[(unsigned int)*origin] == 0
			&& node->re_token.data.expr.rng.reverse == 1))
	{
		(*cursor)++;
		return (OK);
	}
	return (KO);
}
