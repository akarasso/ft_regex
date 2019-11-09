#include "regex.h"
#include "internal_regex.h"

int		lexer_parse_group(t_regex *regex, t_bin_tree *node, char *pat, int size_match)
{
	t_regex sub;
	int ret;

	sub.test = pat;
	sub.tree = 0x0;
	sub.last = 0x0;
	sub.options = regex->options;
	ret = re_compile_internal(&sub, pat + 1, size_match - 2);
	if (ret == OK)
		node->left = sub.tree;
	return (ret);
}
