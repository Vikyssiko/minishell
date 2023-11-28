/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:22:38 by vkozlova          #+#    #+#             */
/*   Updated: 2023/06/14 18:40:12 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	size_t	s1_size;
	size_t	s2_size;
	int		index;

	index = 0;
	s1_size = ft_strlen_gnl(s1);
	s2_size = ft_strlen_gnl(s2);
	if (s2_size == 0)
		return (s1);
	result = malloc(s1_size + s2_size + 1);
	if (!result)
		return (NULL);
	while (s1 && s1[index])
	{
		result[index] = s1[index];
		index++;
	}
	if (s1)
		free(s1);
	while (*s2)
		result[index++] = *s2++;
	result[index] = '\0';
	return (result);
}

char	*read_till_new_line(int fd, char *str)
{
	int		read_bytes;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr_n(str) && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		str = ft_strjoin_gnl(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*clean(char *str)
{
	int		new_index;
	int		index;
	char	*new_str;

	if (ft_strlen_gnl(str) == 0)
		return (NULL);
	new_index = 0;
	index = 0;
	while (str[index] && str[index] != '\n')
		index++;
	if (str[index] == '\n')
		index++;
	if (ft_strlen(str) - index == 0)
	{
		free(str);
		return (NULL);
	}
	new_str = malloc(ft_strlen(str) - index + 1);
	if (!new_str)
		return (NULL);
	while (str[index])
		new_str[new_index++] = str[index++];
	new_str[new_index] = '\0';
	free(str);
	return (new_str);
}

char	*read_line(char *str)
{
	char	*result;
	int		index;

	index = 0;
	if (ft_strlen(str) == 0)
		return (NULL);
	while (str[index] && str[index] != '\n')
		index++;
	if (str[index] == '\n')
		result = malloc(index + 2);
	else
		result = malloc(index + 1);
	if (!result)
		return (NULL);
	index = 0;
	while (str[index] && str[index] != '\n')
	{
		result[index] = str[index];
		index++;
	}
	if (str[index] == '\n')
		result[index++] = '\n';
	result[index] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*strings[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	strings[fd] = read_till_new_line(fd, strings[fd]);
	if (!strings[fd])
		return (NULL);
	line = read_line(strings[fd]);
	strings[fd] = clean(strings[fd]);
	return (line);
}

//#include <fcntl.h>
//
//int main()
//{
//	int fd = open("one_line_no_nl.txt", O_RDONLY);
//	char *str1 = get_next_line(fd);
//	printf("line1: %s", str1);
//	free(str1);
//	char *str2 = get_next_line(fd);
//	printf("line2: %s", str2);
//	free(str2);
//	char *str3 = get_next_line(fd);
//	printf("line3: %s", str3);
//	free(str3);
//	char *str4 = get_next_line(fd);
//	printf("line4: %s", str4);
//	free(str4);
//	char *str5 = get_next_line(fd);
//	printf("line5: %s", str5);
//	free(str5);
//}