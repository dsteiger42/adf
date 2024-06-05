/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsteiger <dsteiger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:33:14 by dsteiger          #+#    #+#             */
/*   Updated: 2024/06/05 18:46:16 by dsteiger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	variable_types(char type, va_list *ap)
{
	int	i;

	i = 0;
	if (type == 'c')
		i += print_char(va_arg(*ap, int));
	else if (type == 's')
		i += print_str(va_arg(*ap, char *));
	else if (type == 'p')
		i += print_ptr(va_arg(*ap, unsigned long int));
	else if (type == 'd' || type == 'i')
		i += print_int(va_arg(*ap, int));
	else if (type == 'u')
		i += print_uint(va_arg(*ap, int));
	else if (type == 'x')
		i += print_hexa((long)va_arg(*ap, unsigned int));
	else if (type == 'X')
		i += print_upperhexa((long)va_arg(*ap, unsigned int));
	else if (type == '%')
		i += print_char('%');
	return (i);
}

static int	check_var_type(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	if (!format)
		return (-1);
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			if (check_var_type(FLAGS, (*(format + 1))))
			{
				format++;
				len += variable_types(*format, &ap);
			}
		}
		else
			len += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (len);
}
// 43 - se encontrar a flag, para de procurar
// 63 - se encontrar uma letra que pertenca as FLAGS e
// esteja na posicao seguinte( + 1)
// 66 - executa a funcao
// 70 - caso a letra nao seja uma FLAG, escreve so sem
// 71 - executar funcao nenhuma

// int	main(void)
// {
// 	int	test;
// 	int test1;

// 	test = ft_printf("%s\n", "araujo");
// 	printf("%d\n", test);
// 	test1 = printf("%s\n", "araujo");
// 	printf("%d\n", test1);
// }
