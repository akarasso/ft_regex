/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:14:07 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 17:08:20 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REGEX_H
# define REGEX_H

# include <string.h>

# include "internal_define.h"
# include "internal_typedef.h"
# include "internal_struct.h"

int		re_regcomp(t_regex *r, char *pat);
int		re_test(t_regex *regex, char *str);
int		re_exec(t_regex *regex, t_regex_match **match, int *n_match, char *str);

#endif
