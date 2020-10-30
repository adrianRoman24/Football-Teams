#ifndef FOOTBALL_CLUB_H_D
#define FOOTBALL_CLUB_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// List node which contains information about one football player.
typedef struct Player {
	char *name;					// player's name
	char *position;				// player's game position
	int score;					// player's score
	int injured;				// indicator for injury (1 true, 0 false)
	struct Player *next;		// next list node
	struct Player *prev;		// previous list node
} Player;

// Structure which contains information about one football club.
typedef struct FootballClub {
	char *name;					// club's name
	Player *players;			// list with players in good shape
	Player *injured_players;	// list with injured players
	struct FootballClub *next;	// next list node
} FootballClub;

//allocate memory for a player 
Player *allocate_player(char *name, char *position, int score,
						int injured){
	//allocate memory and check if memory was allocated corectly
	Player *player = (Player *)malloc(sizeof(Player));
	if(player == NULL)
		exit(-1);
	player->score = score;
	player->injured = injured;	
	player->name = (char *)calloc(strlen(name) + 1, sizeof(char));
	if(player->name == NULL)
		exit(-1);
	strcpy(player->name, name);
	player->position = (char *)calloc(strlen(position) + 1, sizeof(char));
	if(player->position == NULL)
		exit(-1);
	strcpy(player->position, position);
	player->next = NULL;
	player->prev = NULL;
	return player;
}
/*gets the minimum score from a player list*/
int min_score(Player *player)
{
	int score = 100;
	Player *auxplayer = player;
	while(auxplayer != NULL)
	{
		if(auxplayer->score < score)
			score = auxplayer->score;
		auxplayer = auxplayer->next;
	}
	return score;
}
void sort_player_list_by_score(Player **club_players, Player *player){
	/*"player" is the player that will be added to the club_players,
	which is the beggining of the list of players*/
	Player *auxplayer = *club_players;
	if(auxplayer == NULL)
	{
		*club_players = player;
		return;
	}
	/*case new player's score > old player*/
	if(auxplayer->score < player->score)
	{
		auxplayer->prev = player;
		player->next = auxplayer;
		*club_players = player;
		return;
	}
	else
		/*case new player's score == old player and new player's name < old player's name*/
		if(strcmp(auxplayer->name, player->name) > 0 && auxplayer->score <= player->score)
		{
			auxplayer->prev = player;
			player->next = auxplayer;
			*club_players = player;
			return;
		}
	/*case new player's score < old player*/
	while(auxplayer->next != NULL)
		if(auxplayer->next->score > player->score)
			auxplayer = auxplayer->next;
		else
			break;
	/*case new player's score == old player and new player's name > old player's name*/
	while(auxplayer->next != NULL)
		if(auxplayer->next->score >= player->score && 
			strcmp(auxplayer->next->name, player->name) < 0)
			auxplayer = auxplayer->next;
		else
			break;
	//insert the new player
	if(auxplayer->next != NULL)
		auxplayer->next->prev = player;
	player->next = auxplayer->next;
	auxplayer->next = player;
	player->prev = auxplayer;
}
void sort_player_list(Player **club_players, Player *player){
	/*player is the player that will be added to the club_players,
	which is the beggining of the list of players*/
	Player *auxplayer = *club_players;
	if(auxplayer == NULL)
	{
		*club_players = player;
		return;
	}
	/*case new player's position < old player's position*/
	if(auxplayer->position[0] > player->position[0])
	{
		auxplayer->prev = player;
		player->next = auxplayer;
		*club_players = player;
		return;
	}
	if(auxplayer->position[0] == player->position[0])
	{
		/*case new player's position == old player's position
		and new player's score > old player's score*/
		if(auxplayer->score < player->score)
		{
			auxplayer->prev = player;
			player->next = auxplayer;
			*club_players = player;
			return;
		}
		else
			/*new player and old player have the same position, the same score, but 
			new player's name < old player's name*/
			if(strcmp(auxplayer->name, player->name) > 0 && auxplayer->score <= player->score)
			{
				auxplayer->prev = player;
				player->next = auxplayer;
				*club_players = player;
				return;
			}
	}
	/*old player's position < new player's position*/
	while(auxplayer->next != NULL)
		if(auxplayer->next->position[0] < player->position[0])
			auxplayer = auxplayer->next;
		else
			break;
	/*same position, but different score*/
	while(auxplayer->next != NULL)
		if(auxplayer->next->score > player->score &&
		 auxplayer->next->position[0] == player->position[0])
			auxplayer = auxplayer->next;
		else
			break;
	/*same position, same score, different names*/
	while(auxplayer->next != NULL)
		if(auxplayer->next->score >= player->score &&
		 auxplayer->next->position[0] == player->position[0] &&
		 strcmp(auxplayer->next->name, player->name) < 0)
			auxplayer = auxplayer->next;
		else
			break;
	//insert the new player
	if(auxplayer->next != NULL)
		auxplayer->next->prev = player;
	player->next = auxplayer->next;
	auxplayer->next = player;
	player->prev = auxplayer;
}
FootballClub *initialize_clubs(int clubs_no, char **names) {
	if(clubs_no <= 0)
		return NULL;
	if(names == NULL)
		return NULL;
	//allocate club
	FootballClub *club = (FootballClub *)malloc(sizeof(FootballClub));
	if(club == NULL)
		exit(-1);
	FootballClub *aux = club;
	int club_number = 0;
	while(aux != NULL)
	{
		//allocate name and give it the value*/
		aux->name = (char *)malloc(sizeof(char) * (strlen(names[club_number]) + 1));
		if(aux->name == NULL)
			exit(-1);
		strcpy(aux->name, names[club_number]);
		aux->players = NULL;
		aux->injured_players = NULL;
		clubs_no --;
		club_number ++;
		if(clubs_no > 0)
		{
			aux->next = (FootballClub *)malloc(sizeof(FootballClub));
			if(aux->next == NULL)
				exit(-1);
		}
		else
			aux->next = NULL;
		aux = aux->next;
	}
	return club;
}

FootballClub *add_club(FootballClub *clubs, char *name) {
	if(clubs == NULL)
	{
		//allocate club, club name and assign values
		clubs = (FootballClub *)malloc(sizeof(FootballClub));
		if(clubs == NULL)
			exit(-1);
		clubs->name = (char *)calloc((strlen(name) + 1), sizeof(char));
		if(clubs->name == NULL)
			exit(-1);
		clubs->players = NULL;
		clubs->injured_players = NULL;
		clubs->next = NULL;
		strcpy(clubs->name, name);
		return clubs;
	}
	//case clubs is  empty 
	FootballClub *aux = (FootballClub *)malloc(sizeof(FootballClub));
	if(aux == NULL)
		exit(-1);
	aux->name = (char *)calloc((strlen(name) + 1), sizeof(char));
	if(aux->name == NULL)
		exit(-1);
	strcpy(aux->name, name);
	aux->players = NULL;
	aux->injured_players = NULL;
	aux->next = NULL;
	FootballClub *aux2 = clubs;
	while(aux2->next != NULL)
		aux2 = aux2->next;
	aux2->next = aux;
	return clubs;
}

void add_player(FootballClub *clubs, char *club_name, 
				char *player_name, char *position, int score) {
	//check if new player can be added
	FootballClub *aux = clubs;
	if(aux == NULL)
		return;
	while(strcmp(aux->name, club_name) != 0)
	{
		aux = aux->next;
		if(aux == NULL)
			return;
	}
	//allocate player, player name, player position and assign values
	Player *player = allocate_player(player_name, position, score, 0);
	//add player to the club's player list
	sort_player_list(&(aux->players), player);
}

void transfer_player(FootballClub *clubs, char *player_name, 
					char *old_club, char *new_club) {
	//check if player can be transfered
	FootballClub *clubAux = clubs;
	if(clubAux == NULL)
		return;
	//search old club
	while(strcmp(clubAux->name, old_club) != 0)
	{
		clubAux = clubAux->next;
		if(clubAux == NULL)
			return;
	}
	//search player
	Player *player = clubAux->players;
	if(player != NULL)
		while(strcmp(player->name, player_name) != 0)
		{
			player = player->next;
			if(player == NULL)
				break;
		}
	if(player == NULL)
	{
		//case player is injured or it does not exist
		player = clubAux->injured_players;
		if(player != NULL)
			while(strcmp(player->name, player_name) != 0)
			{
				player = player->next;
				if(player == NULL)
					return;
			}
			else 
				return;
	}
	//search new club
	FootballClub *clubAux2 = clubs;
	while(strcmp(clubAux2->name, new_club) != 0)
	{	
		clubAux2 = clubAux2->next;
		if(clubAux2 == NULL)
			return;
	}
	//transfer player by checking if he is injured or not
	if(player->prev == NULL && player->next == NULL)
	{
		if(player->injured == 0)
			clubAux->players = NULL;
		else
			clubAux->injured_players = NULL;
	}
	if(player->prev != NULL)
		player->prev->next = player->next;
	else
		if(player->injured == 0)
			clubAux->players = player->next;
		else
			clubAux->injured_players = player->next;
	if(player->next != NULL)
		player->next->prev = player->prev;
	player->prev = NULL;
	player->next = NULL;
	//add uninjured player to new club
	if(player->injured == 0)
		sort_player_list(&(clubAux2->players), player);
	else
	{
		//add injured player to new club
		if(clubAux2->injured_players == NULL)
			clubAux2->injured_players = player;
		else
		{
			//case list of injured players is not empty
			Player *player2 = clubAux2->injured_players;
			if(strcmp(player2->name, player->name) > 0)
			{
				player2->prev = player;
				player->next = player2;
				clubAux2->injured_players = player;
			}
			else
			{
				while(strcmp(player2->name, player->name) < 0 && player2->next != NULL)
				{
					player2 = player2->next;
				}
				//add to new club
				if(player2->next != NULL)
					player2->next->prev = player;
				player->next = player2->next;
				player2->next = player;
				player->prev = player2;
			}
		}
	}
}

void remove_player(FootballClub *clubs, char *club_name, char *player_name) {
	//check if club and player exist
	FootballClub *aux = clubs;
	if(aux == NULL)
		return;
	//search club
	while(strcmp(aux->name, club_name) != 0)
	{
		aux = aux->next;
		if(aux == NULL)
			return;
	}
	//search player
	Player *auxplayer = aux->players;
	if(auxplayer == NULL)
	{
		//search player in injured list
		auxplayer = aux->injured_players;
		if(auxplayer == NULL)
			return;
		while(strcmp(auxplayer->name, player_name) != 0)
		{
			auxplayer = auxplayer->next;
			if(auxplayer == NULL)
				return;
		}
		//if found delete player
		if(auxplayer->prev != NULL)
			auxplayer->prev->next = auxplayer->next;
		else
			aux->injured_players = auxplayer->next;
		if(auxplayer->next != NULL)
			auxplayer->next->prev = auxplayer->prev;
		if(auxplayer->prev == NULL && auxplayer->next == NULL)
			aux->injured_players = NULL;
		free(auxplayer->name);
		free(auxplayer->position);
		free(auxplayer);
		return;
	}
	//sarch in noninjured players list
	while(strcmp(auxplayer->name, player_name) != 0)
	{
		auxplayer = auxplayer->next;
		if(auxplayer == NULL)
			return;
	}
	//if found delete player
	if(auxplayer->prev != NULL)
		auxplayer->prev->next = auxplayer->next;
	else
		aux->players = auxplayer->next;
	if(auxplayer->next != NULL)
		auxplayer->next->prev = auxplayer->prev;
	if(auxplayer->prev == NULL && auxplayer->next == NULL)
		aux->players = NULL;
	free(auxplayer->name);
	free(auxplayer->position);
	free(auxplayer);
}

void update_score(FootballClub *clubs, char *club_name, 
					char *player_name, int score) {
	//check if club and player exist
	FootballClub *aux = clubs;
	if(aux == NULL)
		return;
	//search club
	while(strcmp(aux->name, club_name) != 0)
	{
		aux = aux->next;
		if(aux == NULL)
			break;
	}
	//search player
	Player *player = aux->players;
	if(player != NULL)
		while(strcmp(player->name, player_name) != 0)
		{
			player = player->next;
			if(player == NULL)
				break;
		}
	if(player == NULL)
	{
		//search player in injured players list
		player = aux->injured_players;
		if(player != NULL)
			while(strcmp(player->name, player_name) != 0)
			{
				player = player->next;
				if(player == NULL)
					return;
			}
		else
			return;
	}
	//check score limits and assign score to player
	if(score < -100)
		player->score = -100;
	else
		player->score = score;
	if(score > 100)
		player->score = 100;
	else
		player->score = score;
	if(player->injured == 1)
		return;
	//remove player from player list
	if(player->prev == NULL && player->next == NULL)
		aux->players = NULL;
	if(player->prev != NULL)
		player->prev->next = player->next;
	else
		aux->players = player->next;
	if(player->next != NULL)
		player->next->prev = player->prev;
	player->prev = NULL;
	player->next = NULL;
	//reinsert player to playerlist to sort the list
	sort_player_list(&(aux->players), player);
}

void update_game_position(FootballClub *clubs, char *club_name, 
							char *player_name, char *position, int score) {
	//check if club and player exist
	FootballClub *aux = clubs;
	if(aux == NULL)
		return;
	//search club
	while(strcmp(aux->name, club_name) != 0)
	{
		aux = aux->next;
		if(aux == NULL)
			return;
	}
	//search player
	Player *player = aux->players;
	while(strcmp(player->name, player_name) != 0)
	{
		player = player->next;
		if(player == NULL)
			break;
	}
	if(player == NULL)
	{
		//search player in injured players list
		player = aux->injured_players;
		while(strcmp(player->name, player_name) != 0)
		{
			player = player->next;
			if(player == NULL)
				return;
		}
	}
	//check score limits and assign score
	if(score < -100)
		player->score = -100;
	else
		player->score = score;
	if(score > 100)
		player->score = 100;
	else
		player->score = score;
	//assign position
	free(player->position);
	player->position = (char *)calloc(strlen(position) + 1, sizeof(char));
	strcpy(player->position, position);
	if(player->injured == 1)
		return;
	//if player is not injured rearrange players list
	if(player->prev != NULL)
		player->prev->next = player->next;
	else
		aux->players = player->next;
	if(player->next != NULL)
		player->next->prev = player->prev;
	if(player->prev == NULL && player->next == NULL)
		aux->players = NULL;
	player->prev = NULL;
	player->next = NULL;
	sort_player_list(&(aux->players), player);
}

void add_injury(FootballClub *clubs, char *club_name,
				char *player_name, int days_no) {
	//check if player and club exist
	FootballClub *aux = clubs;
	if(aux == NULL)
		return;
	//search club
	while(strcmp(aux->name, club_name) != 0)
	{
		aux = aux->next;
		if(aux == NULL)
			return;
	}
	//search player
	Player *player = aux->players;
	if(player != NULL)
		while(strcmp(player->name, player_name) != 0)
		{
			player = player->next;
			if(player == NULL)
				return;
		}
	else
		return;
	//remove player from non injured players list (if found)
	if(player->next == NULL && player->prev == NULL)
		aux->players = NULL;
	if(player->prev != NULL)
		player->prev->next = player->next;
	else
		aux->players = player->next;
	if(player->next != NULL)
		player->next->prev = player->prev;
	player->next = NULL;
	player->prev = NULL;
	player->score = player->score - 0.1 * days_no;
	player->injured = 1;
	//update score
	if(player->score < -100)
		player->score = -100;
	Player *player2 = aux->injured_players;
	//add to injured players list
	if(player2 == NULL)
	{
		aux->injured_players = player;
		return;
	}
	if(strcmp(player2->name, player->name) > 0)
	{
		player2->prev = player;
		player->next = player2;
		aux->injured_players = player;
		return;
	}
	while(player2->next != NULL)
		if(strcmp(player2->name, player->name) < 0)
			player2 = player2->next;
		else
			break;
	if(player2->next != NULL)
		player2->next->prev = player;
	player->next = player2->next;
	player2->next = player;
	player->prev = player2;
	player->injured = 1;
}

void recover_from_injury(FootballClub *clubs, char *club_name, 
							char *player_name) {
	//check if club and player exist
	FootballClub *aux = clubs;
	if(aux == NULL)
		return;
	//search club
	while(strcmp(aux->name, club_name) != 0)
	{
		aux = aux->next;
		if(aux == NULL)
			return;
	}
	//search player in injured players list
	Player *player = aux->injured_players;
	if(player != NULL)
		while(strcmp(player->name, player_name) != 0)
		{
			player = player->next;
			if(player == NULL)
				return;
		}
	else
		return;
	//if player is found:remove player from injured players list
	if(player->prev == NULL && player->next == NULL)
		aux->injured_players = NULL;
	if(player->prev != NULL)
		player->prev->next = player->next;
	else
		aux->injured_players = player->next;
	if(player->next != NULL)
		player->next->prev = player->prev;
	player->injured = 0;
	player->next = NULL;
	player->prev = NULL;
	//add to non injured players list and sort list
	sort_player_list(&(aux->players), player);
}

// Frees memory for a list of Player.
void destroy_player_list(Player *player) {
	Player *aux = player, *aux2 = player;
	while(aux != NULL)
	{
		free(aux->name);
		free(aux->position);
		aux = aux->next;
		free(aux2);
		aux2 = aux;
	}
}

// Frees memory for a list of FootballClub.
void destroy_club_list(FootballClub *clubs) {
	FootballClub *aux = clubs, *aux2 = clubs;
	while(aux != NULL)
	{
		free(aux->name);
		destroy_player_list(aux->players);
		destroy_player_list(aux->injured_players);
		aux = aux->next;
		free(aux2);
		aux2 = aux;
	}
}

// Displays a list of players.
void show_list(FILE *f, Player *players, int free_memory) {
	fprintf(f, "P: ");
	Player *player = players;
	while (player) {
		fprintf(f, "(%s, %s, %d, %c) ", 
			player->name,
			player->position,
			player->score,
			player->injured ? 'Y' : '_');
		player = player->next;
	}
	if (free_memory) {
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}

// Displays a list of players in reverse.
void show_list_reverse(FILE *f, Player *players, int free_memory) {
	fprintf(f, "P: ");
	Player *player = players;
	if (player) {
		while (player->next) {
			player = player->next;
		}
		while (player) {
			fprintf(f, "(%s, %s, %d, %c) ", 
				player->name,
				player->position,
				player->score,
				player->injured ? 'Y' : '_');
			player = player->prev;
		}
	}
	if (free_memory) {
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}


// Displays information about a football club.
void show_clubs_info(FILE *f, FootballClub *clubs) {
	fprintf(f, "FCs:\n");
	while (clubs) {
		fprintf(f, "%s\n", clubs->name);
		fprintf(f, "\t");
		show_list(f, clubs->players, 0);
		fprintf(f, "\t");
		show_list(f, clubs->injured_players, 0);
		clubs = clubs->next;
	}
}

#endif // FOOTBALL_CLUB_H_INCLUDED