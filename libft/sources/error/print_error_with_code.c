/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_with_code.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:43:55 by abaryshe          #+#    #+#             */
/*   Updated: 2025/09/15 17:39:52 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prints to STDERR "object: msg".
 *
 * This function prints an error message to STDERR.
 * If msg is NULL,
 * uses perror to print the system error associated with 'object'.
 * If object is NULL, prints only msg.
 * Otherwise, prints "object: msg".
 * And returns an error code given.
 *
 * @param object The parameter to refer to from where the error comes.
 * Or to print assosiated perror.
 * @param msg The error message to be printed.
 * @param error_code The code to be returned after the print.
 * @return void
 */
int	print_error_with_code(char *object, char *msg, int error_code)
{
	char	*msg_with_colon;
	char	*full_msg;

	if (!object && !msg)
		return (0);
	if (object == NULL)
		write(STDERR_FD, msg, ft_strlen(msg));
	else if (msg == NULL)
		perror(object);
	else
	{
		msg_with_colon = ft_strjoin(object, ": ");
		if (!msg_with_colon)
			return (perror("ft_strjoin in print_error"), error_code);
		full_msg = ft_strjoin(msg_with_colon, msg);
		free(msg_with_colon);
		if (!full_msg)
			return (perror("ft_strjoin in print_error"), error_code);
		write(STDERR_FD, full_msg, ft_strlen(full_msg));
		free(full_msg);
	}
	return (error_code);
}
