/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_match_comment.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:47:43 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:26:37 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_match_comment(
	t_regex *regex,
	char *pat,
	int size_left,
	int *size_match)
{
	(void)pat;
	(void)size_left;
	if ((regex->options & FLAG_IGNORE_WHITESPACE) && *pat == '#')
	{
		*size_match = size_left;
		return (OK);
	}
	return (KO);
}
