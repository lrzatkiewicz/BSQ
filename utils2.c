#include "project.h"
#include <unistd.h>
#include <limits.h>

void	print_error(const char *message)
{
	int	length;

	length = 0;
	while (message[length] != '\0')
		++length;
	write(1, message, length);
	write(1, "\n", 1);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		++len;
	return (len);
}

void	ft_put_new_line(void)
{
	write(1, "\n", 1);
}

int	min(int a, int b, int c)
{
	int	m;

	m = a;
	if (m > b)
		m = b;
	if (m > c)
		m = c;
	return (m);
}
