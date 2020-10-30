
#ifndef TEAM_EXTRACTOR_H_D
#define TEAM_EXTRACTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FootballClub.h"



Player *union_teams(FootballClub *clubs, char *club_A, char *club_B) {
	//check if clubs exists
	FootballClub *aux = clubs;
	if(aux == NULL)
		return NULL;
	//search club_A
	while(strcmp(aux->name, club_A) != 0)
	{
		aux = aux->next;
		if(aux == NULL)
			break;
	}
	Player *playerlist = NULL;
	if(aux != NULL)
	{
		//add all non injured players from club_A to playerlist
		Player *auxplayer = aux->players, *player = NULL;
		while(auxplayer != NULL)
		{
			player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
			sort_player_list(&(playerlist), player);
			player = NULL;
			auxplayer = auxplayer->next;
		}
	}
	//search club_B
	aux = clubs;
	while(strcmp(aux->name, club_B) != 0)
	{
		aux = aux->next;
		if(aux == NULL)
			break;
	}
	if(aux != NULL)
	{
		//add all non injured players from club_B to playerlist
		Player *auxplayer = aux->players, *player = NULL;
		while(auxplayer != NULL)
		{
			player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
			sort_player_list(&(playerlist), player);
			player = NULL;
			auxplayer = auxplayer->next;
		}
	}
	return playerlist;
}

Player *get_best_player(FootballClub *clubs, char *position) {
	//check if clubs exist
	FootballClub *aux = clubs;
	if(aux == NULL)
		return NULL;
	Player *player = NULL;
	while(aux != NULL)
	{
		//search for player with "position" in every clubs's players list
		Player *auxplayer = aux->players;
		while(auxplayer != NULL)
		{
			if(strcmp(position, auxplayer->position) == 0)
			{
				//first player is found
				if(player == NULL)
				{
					player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
				}
				else
				{
					//check if the new player is "better" than the one already inserted
					if(strcmp(position, auxplayer->position) == 0 && auxplayer->score > player->score)
					{
						player->score = auxplayer->score;
						free(player->name);
						player->name = (char *)calloc(strlen(auxplayer->name) + 1, sizeof(char));
						if(player->name == NULL)
							exit(-1);
						strcpy(player->name, auxplayer->name);
					}
					else
						if(strcmp(position, auxplayer->position) == 0 && auxplayer->score == player->score)
							if(strcmp(player->name, auxplayer->name) > 0)
							{
								free(player->name);
								player->name = (char *)calloc(strlen(auxplayer->name) + 1, sizeof(char));
								if(player->name == NULL)
									exit(-1);
								strcpy(player->name, auxplayer->name);
							}
				}
			}
			auxplayer = auxplayer->next;
		}
		aux = aux->next;
	}
	return player;
}

Player *get_top_players(FootballClub *clubs, int N) {
	//check if clubs exist
	FootballClub *aux = clubs;
	if(aux == NULL)
		return NULL;
	if(N <= 0)
		return NULL;
	int initialN = N;
	Player *player = NULL, *playerlist = NULL, *auxplayerlist = NULL;
	while(aux != NULL)
	{
		//search for players
		Player *auxplayer = aux->players;
		while(auxplayer != NULL)
		{
			if(N > 0)
			{
				//case there are not N players already
				player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
				sort_player_list_by_score(&auxplayerlist, player);
				player = NULL;
				N --;
			}
			else
			{
				//check if this player is better than the weakest player from the list
				//case we introduce the newu player
				if(auxplayer->score > min_score(auxplayerlist))
				{
					//delete last player from playerlist
					Player *auxplayer2 = auxplayerlist;
					while(auxplayer2->next != NULL)
						auxplayer2 = auxplayer2->next;
					if(auxplayer2->prev != NULL)
						auxplayer2->prev->next = NULL;
					else
						auxplayerlist = auxplayer2->next;
					free(auxplayer2->name);
					free(auxplayer2->position);
					free(auxplayer2);
					auxplayer2 = NULL;
					//add new player
					player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
											auxplayer->injured);
					sort_player_list_by_score(&auxplayerlist, player);
					player = NULL;
				}
				//case we have to check if name of new player < name of old player
				if(auxplayer->score == min_score(auxplayerlist))
				{
					Player *auxplayer2 = auxplayerlist;
					while(auxplayer2->next != NULL)
						auxplayer2 = auxplayer2->next;
					if(strcmp(auxplayer2->name, auxplayer->name) > 0)
					{
						//delete old player
						if(auxplayer2->prev != NULL)
							auxplayer2->prev->next = NULL;
						else
							auxplayerlist = auxplayer2->next;
						free(auxplayer2->name);
						free(auxplayer2->position);
						free(auxplayer2);
						//introduce new player
						player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
												auxplayer->injured);
						sort_player_list_by_score(&auxplayerlist, player);
						player = NULL;
					}
				}
			}
			auxplayer = auxplayer->next;
		}
		//add the players found for the current club to our list
		Player *auxplayer2 = auxplayerlist;
		while(auxplayer2 != NULL)
		{
			player = auxplayer2;
			auxplayer2 = auxplayer2->next;
			player->prev = NULL;
			player->next = NULL;
			sort_player_list_by_score(&playerlist, player);
		}
		auxplayerlist = NULL;
		N = initialN;
		aux = aux->next;
	}
	return playerlist;
}

Player *get_players_by_score(FootballClub *clubs, int score) {
	//check if clubs exist
	FootballClub *aux = clubs;
	if(aux == NULL)
		return NULL;
	Player *playerlist = NULL, *player = NULL;
	while(aux != NULL)
	{
		//search for players
		Player *auxplayer = aux->players;
		while(auxplayer != NULL)
		{
			//case player is found
			if(auxplayer->score >= score)
			{
				player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
				sort_player_list_by_score(&(playerlist), player);
			}
			auxplayer = auxplayer->next;
		}
		//search in injured players list
		auxplayer = aux->injured_players;
		while(auxplayer != NULL)
		{
			if(auxplayer->score >= score)
			{
				//case player is found
				player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
				sort_player_list_by_score(&(playerlist), player);
			}
			auxplayer = auxplayer->next;
		}
		aux = aux->next;
	}
	return playerlist;
}

Player *get_players_by_position(FootballClub *clubs, char *position) {
	//check if clubs exist
	FootballClub *aux = clubs;
	if(aux == NULL)
		return NULL;
	Player *playerlist = NULL, *player = NULL;
	while(aux != NULL)
	{
		//search players
		Player *auxplayer = aux->players;
		while(auxplayer != NULL)
		{
			//player with position is found and added 
			if(strcmp(auxplayer->position, position) == 0)
			{
				player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
				sort_player_list_by_score(&(playerlist), player);
			}
			auxplayer = auxplayer->next;
		}
		//search injured players
		auxplayer = aux->injured_players;
		while(auxplayer != NULL)
		{
			if(strcmp(auxplayer->position, position) == 0)
			{
				//add player to our list
				player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
				sort_player_list_by_score(&(playerlist), player);
			}
			auxplayer = auxplayer->next;
		}
		aux = aux->next;
	}
	return playerlist;
}

void add_player_to_team(Player **playerlist, int striker, Player *auxplayer, char *position){
	Player *auxplayer2 = *playerlist;
	while(striker > 0)
	{
		//find weakest striker
		if(strcmp(auxplayer2->position, position) == 0)
		{
			striker --;
			if(striker == 0)
			break;
		}
		auxplayer2 = auxplayer2->next;
	}		
	if(auxplayer2->score < auxplayer->score || (auxplayer2->score == auxplayer->score 
		&& strcmp(auxplayer->name, auxplayer2->name) < 0))
	{
	//remove old striker
		if(auxplayer2->prev != NULL)
			auxplayer2->prev->next = auxplayer2->next;
		else
			*playerlist = auxplayer2->prev;
		if(auxplayer2->next != NULL)
			auxplayer2->next->prev = auxplayer2->prev;
		free(auxplayer2->name);
		free(auxplayer2->position);
		free(auxplayer2);
		//add new striker
		auxplayer2 = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
		auxplayer->injured);
		sort_player_list_by_score(&(*playerlist), auxplayer2);
	}
	striker = 3;
}
Player *get_best_team(FootballClub *clubs) {
	//check if clubs exist
	FootballClub *aux = clubs;
	if(aux == NULL)
		return NULL;
	//the list that will be returned
	Player *playerlist = NULL; 
	//counters for each type of player
	int goalkeeper = 0, striker = 0, midfielder = 0, defender = 0;
	//helps to go through both lists of players of a club in the same while(line 346)
	int injured_counter = 0;
	while(aux != NULL)
	{
		Player *player = NULL, *auxplayer = NULL;
		//search players
		//case not injured players list
		if(injured_counter == 0)
		{
			auxplayer = aux->players;
			injured_counter = 1;
		}
		//case injured players list
		else
		{
			auxplayer = aux->injured_players;
			injured_counter = 0;
		}

		while(auxplayer != NULL)
		{
			if(strcmp(auxplayer->position, "portar") == 0)
			{
				//case there are no goalkeepers
				if(goalkeeper == 0)
				{
					player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
					sort_player_list_by_score(&playerlist, player);
					goalkeeper ++;
				}
				else
					//check if new goalkeeper can replace the already added goalkeeper
					if(auxplayer->score >= min_score(playerlist))
						add_player_to_team(&playerlist, goalkeeper, auxplayer, "portar");
			}
			if(strcmp(auxplayer->position, "atacant") == 0)
			{
				//case the nr=umber of strikers is not complete
				if(striker < 3)
				{
					//add striker
					player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
					sort_player_list_by_score(&playerlist, player);
					striker ++;
				}
				else
					if(auxplayer->score >= min_score(playerlist))
						add_player_to_team(&playerlist, striker, auxplayer, "atacant");
			}
			if(strcmp(auxplayer->position, "mijlocas") == 0)
			{
				//the same as with striker
				if(midfielder < 3)
				{
					player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
					sort_player_list_by_score(&playerlist, player);
					midfielder ++;
				}
				else
					if(auxplayer->score >= min_score(playerlist))
						add_player_to_team(&playerlist, midfielder, auxplayer, "mijlocas");
			}
			if(strcmp(auxplayer->position, "fundas") == 0)
			{
				//the same as with striker
				if(defender < 4)
				{
					player = allocate_player(auxplayer->name, auxplayer->position, auxplayer->score, 
										auxplayer->injured);
					sort_player_list_by_score(&playerlist, player);
					defender ++;
				}
				else
					if(auxplayer->score >= min_score(playerlist))
						add_player_to_team(&playerlist, defender, auxplayer, "fundas");
			}
			auxplayer = auxplayer->next;
		}
		
		if(injured_counter == 0)
			aux = aux->next;
	}
	return playerlist;
}

#endif // TEAM_EXTRACTOR_H_INCLUDED