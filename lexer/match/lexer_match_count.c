/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_match_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:44:18 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:21:21 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_match_count(
	t_regex *regex,
	char *pat,
	int size_left,
	int *size_match)
{
	(void)regex;
	if (!size_left || *pat != '{')
		return (NO);
	while (size_left && pat[*size_match] && pat[*size_match] != '}')
	{
		if (pat[*size_match] == '-')
			return (NO);
		size_left--;
		(*size_match)++;
	}
	if (pat[*size_match] != '}')
		return (NO);
	(*size_match)++;
	return (OK);
}
