/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_match_any.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:43:37 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:26:25 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_match_any(
	t_regex *regex,
	char *pat,
	int size_left,
	int *size_match)
{
	(void)regex;
	if (!size_left || *pat != '.')
		return (NO);
	if (*pat == '.')
	{
		*size_match = 1;
		return (OK);
	}
	return (NO);
}
