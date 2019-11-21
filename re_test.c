/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:14:07 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 11:16:53 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "regex.h"
#include "internal_regex.h"

int		re_test(t_regex *r, char *str)
{
	int				cursor;
	int				old;

	cursor = 0;
	while (str[cursor])
	{
		old = cursor;
		if (r->tree->exec(0x0, r->tree, str, &cursor) == OK && old != cursor)
			return (OK);
		cursor++;
	}
	return (KO);
}
