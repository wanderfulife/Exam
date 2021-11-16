#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct	{
	va_list	arg;
	int	count;
}			t_hold;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
}

void	ft_str(t_hold *args)
{
	char *str;
	int	i;

	str = va_arg(args->arg, char *);
	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

void	ft_itoa(int nb, int len)
{
	int	n;
	int	i = 0;
	char	*str;

	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return ;
	if (nb < 0)
	{
		str[0] = '-';
		n = -nb;
	}
	else
		n = nb;
	if (nb == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (n)
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	while (str[i])
		ft_putchar(str[i++]);
}

static char	*ft_strsize(unsigned long num, int *i)
{
	char	*str;

	while (num >= 16)
	{
		num = num / 16;
		*i += 1;
	}
	str = (char *)malloc((*i + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str[*i] = '\0';
	return (str);
}

void	ft_putnbr(t_hold *args)
{
	int	len = 1;
	int	nb_to_convert;
	int	temp;
	
	nb_to_convert = va_arg(args->arg, int);
	temp = nb_to_convert;
	if (temp < 0)
	{
		temp = -temp;
		len++;
	}
	while (temp > 9)
	{
		temp /= 10;
		len++;
	}
	ft_itoa(nb_to_convert, len);
	args->count += len;	
}

void	ft_puthex(t_hold *args)
{
	unsigned int	n;
	int				i = 1;
	char			*str;

	n = va_arg(args->arg, unsigned int);
	str = ft_strsize(n, &i);
	i--;
	while (i >= 0)
	{
		if (n % 16 < 10)
			str[i] = '0' + (n % 16);
		else
			str[i] = 'a' - 10 + (n % 16);
		n /= 16;
		i--;
		args->count += 1;
	}
	ft_putstr(str);
	free(str);
}

void	convert_type(char c, t_hold *args)
{
	if (c == 's')
		ft_str(args);
	else if (c == 'd')
		ft_putnbr(args);
	else if (c == 'x')
		ft_puthex(args);
	else if (c == '%')
	{
		ft_putchar('%');
		args->count++;
	}
}


static t_hold	*init_args(void)
{
	t_hold	*args;

	args = (t_hold *)malloc(sizeof(t_hold));
	if (!args)
		return (0);
	args->count = 0;
	return (args);
}

int	ft_printf(char	*str, ...)
{
	t_hold	*args;
	int	count;
	int	i;

	i = 0;
	count = 0;
	args = init_args();
	va_start(args->arg, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar(str[i]);
			count++;
		}
		else if (str[i] == '%')
			convert_type(str[++i], args);
		i++;	
	}
	count += args->count;
	va_end(args->arg);
	free(args);
	return (count);
}

int	main(void)
{	
	char	*name = "Sara";
	int	year = 2022;
	ft_printf("Hey there %s, it's almost %x", name, year);
}
