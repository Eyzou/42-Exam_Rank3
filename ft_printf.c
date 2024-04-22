/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehamm <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:15:28 by ehamm             #+#    #+#             */
/*   Updated: 2024/04/22 17:15:30 by ehamm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int  ft_putstr(char *str)
{
	int i = 0;
	int len = 0;

	if(!str)
		str = "(null)";
	while(str[i])
	{
		len += write(1,&str[i],1);
		i++;
	}
	return(len);
}

int ft_putnbr(long long nb, int base)
{
	int len = 0;
	if(nb < 0)
	{
		nb = nb * - 1;
		len += write(1,"-",1);
	}
	if(nb >= base)
		len += ft_putnbr((nb / base), base);
	len += write(1,&"0123456789abcdef"[nb % base],1);
	return(len);
}



int ft_printf(const char *format, ...)
{
	int idx = 0;
	int len = 0;
	va_list arg;
	
	va_start(arg,format);
	while(format[idx])
	{
		if(format[idx] != '%')
			len += write(1,&format[idx],1);
		else if(format[idx] == '%' && format[idx + 1] != '\0')
		{
			idx++;
			if(format[idx] == 's')
				len += ft_putstr(va_arg(arg,char *));
			else if(format[idx] == 'd')
				len += ft_putnbr((long long)va_arg(arg,int),10);
			else if(format[idx] == 'x')
				len += ft_putnbr((long long)va_arg(arg,unsigned int),16);
		}
		idx++;	
	}
	va_end(arg);
	return(len);
}

/*int main (void)
{
	ft_printf("%s\n", "toto");
	ft_printf("Magic %s is %d\n", "number", 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
}
*/
