/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_match_or.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:45:19 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 16:19:57 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		lexer_match_or(
	t_regex *regex,
	char *pat,
	int size_left,
	int *size_match)
{
	(void)regex;
	if (size_left && *pat == '|')
	{
		*size_match = 1;
		return (OK);
	}
	return (KO);
}
