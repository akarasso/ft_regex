#ifndef STRUCT_INTERNAL
# define STRUCT_INTERNAL

# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_regex				t_regex;
typedef struct s_lexer_match_parser	t_lexer_match_parser;
typedef struct s_lexer_flag			t_lexer_flag;
typedef struct s_token				t_token;
typedef struct s_bin_tree			t_bin_tree;
typedef struct s_regex_match		t_regex_match;
typedef struct s_char_class			t_char_class;
typedef int							(*t_lexer_match_func)(t_regex*, char*, int, int *);
typedef int							(*t_lexer_parse_func)(t_regex *regex, t_bin_tree*, char*, int);
typedef int							(*t_match_func)(t_regex_match *match, t_bin_tree *, char *, int *);


struct s_lexer_flag
{
	char	flag;
	int		value;
};

struct s_lexer_match_parser
{
	t_lexer_match_func	match;
	t_lexer_parse_func	parser;
	t_match_func		exec;
	int					token_type;
	char				*debug;
};

struct s_char_class
{
	char	*match;
	char	*associated;
};

/*
** struct s_token
**
**	min => minimum char to be match to valid expression
**	max => maximum char to be match to valid expression
**	type => type of token {expr, operator,}
**	sbc => Single byte char table: ascii code
**	cst => Handle constant expression
**	utf8_table => To handle in the futur utf8 char
*/

struct	s_token_op
{
	int	min;
	int	max;
};

struct	s_token_flag
{
	int	reverse;
	int	options;
};

struct	s_token_expr_range
{
	char	reverse;
	char	sbc[128];
	char	*utf8_table;
	size_t	utf8_size_table;
};

struct	s_token_expr_const
{
	char	*value;
	int		size;
};

union	u_token_expr
{
	struct	s_token_expr_const cst;
	struct	s_token_expr_range rng;
};

union	u_token
{
	struct s_token_op	op;
	struct s_token_flag	flag;
	union u_token_expr	expr;
};

struct	s_token
{
	int				type;
	int				options;
	union u_token	data;
};

/*
**	struct binary regex
*/

struct	s_bin_tree
{
	t_bin_tree		*parent;
	t_bin_tree		*left;
	t_bin_tree		*right;
	t_bin_tree		*first;
	t_match_func	exec;
	t_token			re_token;
};

struct	s_regex
{
	char		*test;
	t_bin_tree	*tree;
	t_bin_tree	*last;
	int			n_subgroup_max;
	int			options;
};

struct	s_regex_match
{
	t_regex_match	*next;
	char			*match;
	char			**subgroup;
	int				n_subgroup;
};

#endif