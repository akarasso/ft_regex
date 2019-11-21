/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_define.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:19:56 by akarasso          #+#    #+#             */
/*   Updated: 2019/11/21 11:21:15 by akarasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_DEFINE_H
# define INTERNAL_DEFINE_H

# define OK 0
# define KO 1
# define NO 1
# define ERROR_INCOMPLETE_RANGE 2
# define ERROR_BAD_CHARACTERS_CLASSES 3
# define ERROR_RANGE_OUT_OF_ORDER 4

/*
**	Lexer
*/

# define TKN_OP					1 << 1
# define TKN_OP_EXPR			1 << 12
# define TKN_EXPR				1 << 2
# define TKN_OP_STAR			1 << 3
# define TKN_OP_START			1 << 11
# define TKN_OP_END				1 << 13
# define TKN_OP_OR				1 << 14
# define TKN_FLAG				1 << 15
# define TKN_OP_COUNT_RANGE		1 << 4
# define TKN_OP_QUERY			1 << 5
# define TKN_OP_PLUS			1 << 6
# define TKN_GROUP				1 << 7
# define TKN_EXPR_RNG			1 << 8
# define TKN_EXPR_CST			1 << 9
# define TKN_EXPR_ANY			1 << 10

/*
** Flag
*/

# define FLAG_CASE_INSENSITIVE	1 << 1
# define FLAG_GLOBAL			1 << 2
# define FLAG_MULTILINE			1 << 3
# define FLAG_IGNORE_WHITESPACE	1 << 5
# define FLAG_SINGLE_LINE		1 << 6
# define FLAG_EXTENDED			1 << 7
# define FLAG_ANCHOR			1 << 8
# define EXTRACT_SUBGROUP		1 << 9

#endif
