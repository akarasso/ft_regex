#include "regex.h"
#include "internal_regex.h"

static int	find_flag(char c)
{
	int i;

	i = 0;
	while (i < flag_count)
	{
		if (flags[i].flag == c)
			return flags[i].value;
		i++;
	}
	return 0x0;
}

static void	parse_flag(t_regex *r, char *s)
{
	while (*s)
	{
		r->options |= find_flag(*s);
		s++;
	}
}

int		find_start_flag(char *s, int len)
{
	while (len)
	{
		if (s[len] == '/')
			return (len);
		len--;
	}
	return (-1);
}

int	re_regcomp(t_regex *r, char *pat)
{
	int		ret;
	int		len;
	int		start_flag;

	len = ft_strlen(pat);
	r->test = pat;
	r->tree = 0x0;
	r->last = 0x0;
	r->options = 0x0;
	r->n_subgroup_max = 0;
	if (*pat == '/')
	{
		start_flag = find_start_flag(pat, len);
		parse_flag(r, &pat[start_flag + 1]);
		ret = re_compile_internal(r, &pat[1], &pat[start_flag] - &pat[1]);
	}
	else
		ret = re_compile_internal(r, pat, len);
	return (ret);
}