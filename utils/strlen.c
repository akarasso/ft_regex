int		ft_strlen(char *s)
{
	char *e;

	e = s;
	while (*e)
		e++;
	return e - s;
}