/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elo <elo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:30:05 by elo               #+#    #+#             */
/*   Updated: 2024/06/04 21:03:20 by elo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_strchr(char* str, int s)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == s)
            return(str + i);
        i++;
    }
    return(NULL);
}

int ft_strlen(char*str)
{
    int i = 0;
    while(str[i])
        i++;
    return(i);
}

void ft_strcpy(char* dst, char* src)
{
    while(*src)
        *dst++ = *src++;
    *dst = '\0';
}

char *ft_strdup(char *str)
{
    int len = ft_strlen(str);
    char *res = (char *)malloc(sizeof(char)*len);
    if(res == NULL)
        return(NULL);
    ft_strcpy(res,str);
    return(res);
}

char *ft_strjoin(char *s1, char *s2)
{
    int s1_len = ft_strlen(s1);
    int s2_len = ft_strlen(s2);
    char *join = malloc(s1_len + s2_len + 1);
    if(!s1 || !s2)
        return(NULL);
    if(!join)
        return(NULL);
    ft_strcpy(join,s1);
    ft_strcpy((join + s1_len),s2);
    free(s1);
    return(join);
}

char *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE + 1];
    char *line;
    char *newline;
    int count_read;
    int to_copy;

    line = ft_strdup(buf);
    while(!(newline = ft_strchr(line, '\n')) && (count_read = read(fd,buf,BUFFER_SIZE))) // si trouve un \n ou read renvoie 0
    {
        buf[count_read]='\0'; // met un 0 car pas de /n dans buf et ajoute le buf a la line
        line = ft_strjoin(line,buf);
    }
    if(ft_strlen(line) == 0)
        return(free(line),NULL);
    if(newline != NULL)
    {
        to_copy = newline - line + 1; //trouve la fin de la ligne léndroit du \n
        ft_strcpy(buf,newline +1);// copie ce qui suit le \n  dans le  buff
    }
    else 
    {
        to_copy = ft_strlen(line);
        buf[0] = '\0';
    }
    line[to_copy] = '\0';
    return(line);
}

/*int main(void)
{
    int i = 0;
    int fd = open("test.txt", O_RDONLY);
    char *line;
    while(i < 50)
    {
        line = get_next_line(fd);
        printf("%s",line);
        i++;
    }
}*/