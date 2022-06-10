/* ************************************************************************** */
/*		*/
/*	:::	  ::::::::   */
/*   get_next_line.c		:+:	  :+:	:+:   */
/*		+:+ +:+	 +:+	 */
/*   By: iouardi <iouardi@student.42.fr>		+#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2021/11/25 18:16:08 by iouardi	   #+#	#+#		 */
/*   Updated: 2021/11/28 00:05:29 by iouardi	  ###   ########.fr	   */
/*		*/
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_readline(char *str, char *buffer, int fd)
{
	char	*temp;
	int		buffer_len;

	temp = NULL;
	buffer_len = 1;
	if (!str)
		str = ft_strdup_gl("");
	while (buffer_len > 0 && !ft_strchr_gl(str, '\n'))
	{
		buffer_len = read(fd, buffer, BUFFER_SIZE);
		buffer[buffer_len] = '\0';
		temp = ft_strjoin_gl(str, buffer);
		free(str);
		str = temp;
	}
	return (str);
}

char	*ft_strdup_gl(const char *s1)
{
	char	*s2;

	s2 = malloc((ft_strlen_gl(s1) + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	ft_memcpy_gl(s2, s1, sizeof(char) * (ft_strlen_gl(s1) + 1));
	return (s2);
}

char	*get_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	line = malloc((++i + 1) * sizeof(char));
	ft_memcpy_gl(line, str, i);
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*str;
	char		*line;
	size_t		buffer_len;
	char		*temp;

	line = NULL;
	temp = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer, 0) == -1)
		return (NULL);
	buffer_len = 1;
	str = ft_readline(str, buffer, fd);
	line = get_line(str);
	if (ft_strchr_gl(str, '\n'))
		temp = ft_strdup_gl(ft_strchr_gl(str, '\n'));
	free(str);
	str = temp;
	if (!ft_strlen_gl(line))
		return (free(str), free(line), NULL);
	return (line);
}
