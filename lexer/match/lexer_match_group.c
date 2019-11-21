/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_match_group.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:45:11 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:20:37 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_match_group(
	t_regex *regex,
	char *pat,
	int size_left,
	int *size_match)
{
	int		stack;

	(void)regex;
	if (!size_left || *pat != '(')
		return (NO);
	stack = 0;
	while (size_left && pat[*size_match])
	{
		if (pat[*size_match] == '(')
		{
			stack++;
		}
		else if (pat[*size_match] == ')')
		{
			stack--;
			if (stack == 0)
				break ;
		}
		size_left--;
		(*size_match)++;
	}
	if (pat[*size_match] != ')')
		return (ERROR_INCOMPLETE_RANGE);
	(*size_match)++;
	return (OK);
}
