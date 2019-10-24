#ifndef INTERNAL_REGEX
# define INTERNAL_REGEX

int		re_compile_internal(t_regex *r, char *pat, int s);

/*
** Match
*/
int		re_match_subexpre(char *pat, int size_left, int *size_match);
int		re_match_bracket(char *pat, int size_left, int *size_match);
int		re_match_count(char *pat, int size_left, int *size_match);
int		re_match_point(char *pat, int size_left, int *size_match);
int		re_match_constant(char *pat, int size_left, int *size_match);

/*
** Parse
*/

int		re_parser_count(t_token *token, char *pat, int size_match);
int		re_parser_bracket_chars_classes(t_token *token, char *pat, int *cursor);
int		re_parser_bracket_parser(t_token *token, char *pat, int size_match);
int		re_parser_bracket(t_token *token, char *pat, int size_match);
int		re_parser_point(t_token *token, char *pat, int size_match);
int		re_parser_const(t_token *token, char *pat, int size_match);

/*
** Tree
*/

t_bin_tree	*create_leaf();

#endif

