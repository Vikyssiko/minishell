/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envirlists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkozlova <vkozlova@student.42wolfsburg.d>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:09:36 by vkozlova          #+#    #+#             */
/*   Updated: 2023/11/07 14:03:59 by vkozlova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_envadd_back(t_envir **lst, t_envir *new)
// {
//     t_envir	*tmp;

//     if (!*lst)
//         *lst = new;
//     else
//     {
//         tmp = ft_envlast(*lst);
// 		if (tmp)
// 		{
//     		tmp->next = new;
//         	new->prev = tmp;
// 		}
// 		else
// 			ft_envadd_front(lst, new);
//     }
// }

// void	ft_envadd_front(t_envir **lst, t_envir *new)
// {
//     new->next = *lst;
//     if (*lst != NULL)
//         (*lst)->prev = new;
//     *lst = new;
// }

// void	ft_envclear(t_envir **lst)
// {
// 	t_envir  *head;

// 	while (*lst)
// 	{
// 		head = (*lst)->next;
// 		free(*lst);
// 		(*lst) = head;
// 	}
// }

// void	ft_envdelone(t_envir *lst, void (*del)(void *))
// {
//     if (!lst || !del)
//         return ;
//     if (lst->var_name)
//         free(lst->var_name);
//     if (lst->var_value)
//         free(lst->var_value);
//     free(lst);
// }

// void	ft_enviter(t_envir *lst, void (*f)(void *))
// {
//     if (!f)
//         return ;
//     while (lst)
//     {
//         f(lst);
//         lst = lst->next;
//     }
// }

// t_envir	*ft_envlast(t_envir *lst)
// {
// 	t_envir	*node;
// 	node = lst;
//     while (node != NULL)
// 	{
// 		while (node->next != NULL)
// 			node = node->next;
// 	}
//     return (node);
// }

// t_envir	*ft_envnew(char *var_name, char *var_value)
// {
//     t_envir	*head;

//     head = malloc(sizeof(t_envir));
//     if (!head)
//         return (NULL);
//     head->var_name = var_name;
//     head->var_value = var_value;
//     head->count = 1;
//     head->next = NULL;
//     head->prev = NULL;
//     return (head);
// }

// int	ft_envsize(t_envir *lst)
// {
//     int	size;

//     size = 0;
//     while (lst)
//     {
//         size++;
//         lst = lst->next;
//     }
//     return (size);
// }