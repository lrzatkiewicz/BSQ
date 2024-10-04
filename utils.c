#include "project.h"
#include <unistd.h>
#include <limits.h>

void	ft_putstr(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		++len;
	write(1, str, len);
}

void	ft_putnbr(int nb)
{
	char	digit;

	if (nb < 0)
	{
		if (nb == INT_MIN)
		{
			write(1, "-2147483648", 11);
			return ;
		}
		nb = -nb;
		write(1, "-", 1);
	}
	if (nb >= 10)
		ft_putnbr(nb / 10);
	digit = nb % 10 + '0';
	write(1, &digit, 1);
}

void	ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_putchar_space(char c)
{
	write(1, &c, 1);
	write(1, " ", 1);
}
