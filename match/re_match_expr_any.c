/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_match_expr_any.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:20:28 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:59:56 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		re_match_expr_any(
	t_regex_match *match,
	t_bin_tree *node,
	char *origin,
	int *cursor)
{
	(void)match;
	if (origin[*cursor] == '\n' && !(node->re_token.options & FLAG_SINGLE_LINE))
		return (KO);
	if (origin[*cursor])
		(*cursor)++;
	return (OK);
}
