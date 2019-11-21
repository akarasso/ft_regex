/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:14:07 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 10:55:20 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

t_bin_tree	*create_node(t_lexer_match_parser *match)
{
	t_bin_tree	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (0x0);
	memset(node, 0, sizeof(*node));
	node->re_token.type = match->token_type;
	node->exec = match->exec;
	return (node);
}
