/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:14:07 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 11:12:44 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		valid_first_node(t_bin_tree *node)
{
	if ((node->re_token.type & TKN_OP_EXPR))
	{
		printf("Can't find operator expression at start.");
		return (KO);
	}
	return (OK);
}

int		valid_node(t_bin_tree *last, t_bin_tree *node)
{
	if (!last)
		return (valid_first_node(node));
	if ((last->re_token.type & TKN_OP_EXPR)
		&& (node->re_token.type & TKN_OP_EXPR))
	{
		printf("Can't find operator token after another one.");
		return (KO);
	}
	else if ((last->re_token.type & TKN_OP_OR)
		&& (node->re_token.type & TKN_OP_OR))
	{
		printf("Can't find operator OR after another one.");
		return (KO);
	}
	else if (last->re_token.type == TKN_OP_EXPR)
	{
		printf("Can't find expression before token operator.");
		return (KO);
	}
	return (OK);
}
