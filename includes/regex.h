#ifndef REGEX
# define REGEX

# include <string.h>

# include "internal_define.h"
# include "internal_typedef.h"

int		re_regcomp(t_regex *r, char *pat);
int		re_test(t_regex *regex, char *str);
int		re_exec(t_regex *regex, t_regex_match **match, int *n_match, char *str);

#endif