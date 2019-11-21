/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puch_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:14:07 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 10:56:45 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

void	push_node_op_expr(t_regex *r, t_bin_tree *node)
{
	if (r->last->parent)
	{
		r->last->parent->right = node;
	}
	else
	{
		r->tree = node;
	}
	node->parent = r->last->parent;
	node->left = r->last;
	r->last->parent = node;
	r->last = node;
}

void	push_node_op_or(t_regex *r, t_bin_tree *node)
{
	node->left = r->tree;
	node->parent = 0x0;
	r->tree->parent = node->left;
	r->tree = node;
	r->last = node;
}

int		push_node(t_regex *r, t_bin_tree *node)
{
	if (valid_node(r->last, node) != OK)
		return (KO);
	if (!r->last)
	{
		r->tree = node;
		r->last = node;
		node->parent = 0x0;
	}
	else
	{
		if ((node->re_token.type & TKN_OP_EXPR))
			push_node_op_expr(r, node);
		else if ((node->re_token.type & TKN_OP_OR))
			push_node_op_or(r, node);
		else
		{
			r->last->right = node;
			node->parent = r->last;
			r->last = node;
		}
	}
	return (OK);
}
