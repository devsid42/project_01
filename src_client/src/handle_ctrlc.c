/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrlc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avasseur <avasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 22:52:49 by avasseur          #+#    #+#             */
/*   Updated: 2017/06/02 18:20:10 by avasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_client.h"

void	handle_ctrl_c(int sig)
{
	ft_printf(1, "\n[%d] Please quit with /QUIT\n", sig);
	ft_printf(1, "[PRESS A KEY FOR CONTINUE]\n");
}
