int				is_correct_value(char a)
{
	if (a >= '0' && a <= '9' || a >= 'a' && a <= 'f' || a >= 'A' && a <= 'F')
		return (1);
	return (0);
}

int				atoi_hex(char *str)
{
	int			value;
	int			i;

	value = 0;
	while (str[i])
	{
		if (is_correct_value(str[i])
			value = (value << 4) + convert_value(str[i]);
		else
			return (value);
		i++;
	}
}
