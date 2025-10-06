/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsmail <nsmail@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:34:36 by nsmail            #+#    #+#             */
/*   Updated: 2025/10/06 18:45:34 by nsmail           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

/*
** Restaure les signaux par défaut pour les processus enfants
** Utilisé avant execve() pour que les commandes réagissent normalement
** aux signaux (Ctrl+C tue la commande, Ctrl+\ aussi)
*/
void	set_signal_child(void)
{
	signal(SIGINT, SIG_DFL);   // Ctrl+C → comportement par défaut (tue le processus)
	signal(SIGQUIT, SIG_DFL);  // Ctrl+\ → comportement par défaut (tue + core dump)
}

/*
** Fonction appelée périodiquement par readline
** Permet de checker les signaux pendant que readline attend une entrée
** Retourne toujours SUCCESS pour que readline continue
*/
int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

/*
** Gestionnaire principal des signaux pour le shell parent
** Appelé quand un signal est reçu pendant que le shell attend une commande
*/
void	signal_handler(int sig)
{
	if (sig == SIGINT)  // Ctrl+C reçu
	{
		rl_done = 1;                    // Dit à readline de s'arrêter
		g_signal_status = sig + 128;    // Sauvegarde le statut (130 = 2 + 128)
	}
}

/*
** Configure les signaux pour le shell en mode "prompt"
** Appelé au début du programme et après chaque commande
*/
void	ft_signal(void)
{
	rl_event_hook = sig_event;          // Active le checking périodique des signaux
	signal(SIGINT, signal_handler);     // Ctrl+C → notre gestionnaire custom
	signal(SIGQUIT, SIG_IGN);           // Ctrl+\ → ignoré (ne fait rien)
	signal(SIGTSTP, SIG_IGN);           // Ctrl+Z → ignoré (pas de suspend)
}
