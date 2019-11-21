/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_match_bracket.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:43:54 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:27:20 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_match_bracket(
	t_regex *regex,
	char *pat,
	int size_left,
	int *size_match)
{
	int stack;

	(void)regex;
	stack = 0;
	if (size_left < 3 || *pat != '[')
		return (NO);
	while (size_left - *size_match > 0 && pat[*size_match])
	{
		if (pat[*size_match] == '[')
			stack++;
		else if (pat[*size_match] == ']')
			stack--;
		if (stack == 0 && pat[*size_match] == ']')
			break ;
		(*size_match)++;
	}
	if (pat[*size_match] != ']')
		return (ERROR_INCOMPLETE_RANGE);
	(*size_match)++;
	return (OK);
}
