/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_match_flag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:45:03 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:21:27 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_match_flag(
	t_regex *regex,
	char *pat,
	int size_left,
	int *size_match)
{
	(void)regex;
	if (!size_left || *pat != '(' || *(pat + 1) != '?')
		return (NO);
	pat += 2;
	*size_match = 2;
	if (*pat == '!')
	{
		(*size_match)++;
		pat++;
	}
	while (size_left && *pat && *pat != ')')
	{
		pat++;
		size_left--;
		(*size_match)++;
	}
	if (*pat == ')')
	{
		pat++;
		size_left--;
		(*size_match)++;
	}
	return (OK);
}
