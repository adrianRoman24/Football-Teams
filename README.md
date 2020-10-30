# Football-Teams

Functions' description

Player * allocate_player (char * name, char * position, int score,
you are injured)
-allocate a player
-is used in most of the required functions

int min_score (Player * player)
- scroll through the player list and return the lowest score found on a player
-helps in get_best_team function

void sort_player_list_by_score (Player ** club_players, Player * player)
- enter the player player in the club_players list keeping the order
decreasing the score and the alphabetical one the name
-is used in TeamExtractor for most functions

void sort_player_list (Player ** club_players, Player * player)
-add the player to the club_players list considering all that
three criteria for arranging the list of players in the requirement
-is used in TeamExtractor

FootballClub * initialize_clubs (int clubs_no, char ** names)
-allocate space for clubs_no clubs
- go through aux clubs and allocate them
-allocate only the club, and the lists of players will be allocated later

FootballClub * add_club (FootballClub * clubs, char * name)
-if clubs are NULL this will become the new club
-otherwise go through the whole list of clubs and add the new club at the end

void add_player (FootballClub * clubs, char * club_name,
char * player_name, char * position, int score)
-in case of error (for example: clubs = NULL) it exits the function with return
-otherwise we allocate the player and call the sort_player_list function (& (aux-> players),
player) to add the new player and keep the list in order

void transfer_player (FootballClub * clubs, char * player_name,
char * old_club, char * new_club)

- look for the old club and in case there is, extract the player ("breaking" the ties
with the list of players from the old club
- look for the new club and, in case it exists, introduce the new player (keeping
list order) in the corresponding list (injured or normal)

void remove_player (FootballClub * clubs, char * club_name, char * player_name)
-look for the player in the club's player list and in case it exists, break
links to the club's list of players and frees its memory

void update_score (FootballClub * clubs, char * club_name,
char * player_name, int score)
-looks for the player and in case he finds him he changes the score and makes sure that
the list remains ordered accordingly by using the sort function

void update_game_position (FootballClub * clubs, char * club_name,
char * player_name, char * position, int score)
- look for the player and in case he finds it, change the score and the position and
ensure that the list remains properly ordered by using the function
 assortment

void add_injury (FootballClub * clubs, char * club_name,
char * player_name, int days_no)
- look for the player in case he finds him and he is in the list of uninjured players
change the injured indicator to 1 and move the player to the list of players
teeth keeping the lists in order

void recover_from_injury (FootballClub * clubs, char * club_name,
char * player_name)

-look for the player in the list of injured players of the club and in case that
finds it breaks the links with the list of injured players and adds it
in the list of injured players keeping the sorted list, using the function
mentioned above

Player * union_teams (FootballClub * clubs, char * club_A, char * club_B)
-if a club is NULL ignore it
-using the sort function puts in a list all the players it has
find from each club and so the new list of players will be sorted
suitable

Player * get_best_player (FootballClub * clubs, char * position)
-if there are clubs and players remember the first player found, and then
if it finds a player with a higher score, it replaces the one initially found
with it

Player * get_top_players (FootballClub * clubs, int N)
-extract the best N players from each club (if any) in a list
initial, and then, scrolling through this list add using the sort function
these players to the final list that will be returned

Player * get_players_by_score (FootballClub * clubs, int score)
- go through the lists of players from each club, and if the players have the score
> = with score are added to the final list using the sort function

Player * get_players_by_position (FootballClub * clubs, char * position)
- go through the lists of players from each club, and if the players have the position
positions are added to the final list using the sort function

void add_player_to_team (Player ** playerlist, int striker,
Player * auxplayer, char * position)
-is used in get_best_team
-if found, for example, a better defender than the weakest
"best" team defender this defender is added, and the existing one is
deleted

Player * get_best_team (FootballClub * clubs)
- Go through all the clubs and add players to the "team" until all the seats
for a position are occupied
