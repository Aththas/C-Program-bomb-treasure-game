#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAXIMUM_PATH 70
#define MIN_PATH 10
#define MIN_LIVES 1
#define MAX_LIVES 10


struct PlayerInfo {
	int num_lives;
	char character_symbol;
	int num_treasure;
	int positions[MAXIMUM_PATH];
};
struct GameInfo {
	int max_num_move;
	int path_length;
	int bombs[MAXIMUM_PATH];
	int treasure[MAXIMUM_PATH];

};

int main()
{
	struct PlayerInfo player;
	struct GameInfo game;
	int i, j;
	printf("================================\n");
	printf("         Treasure Hunt!         \n");
	printf("================================\n\n");
	printf("PLAYER Configuration\n");
	printf("--------------------\n");
	printf("Enter a single character to represent the player: ");
	scanf("%c",&player.character_symbol);
	do {
		printf("Set the number of lives: ");
		scanf("%d", &player.num_lives);
		if (player.num_lives < MIN_LIVES || player.num_lives > MAX_LIVES) {
			printf("     Must be between 1 and 10!\n");
		}
	} while (player.num_lives < MIN_LIVES || player.num_lives > MAX_LIVES);
	printf("Player configuration set-up is complete\n\n");
	printf("GAME Configuration\n------------------\n");
	do {
		printf("Set the path length (a multiple of 5 between 10-70): ");
		scanf("%d", &game.path_length);
		if (game.path_length < MIN_PATH || game.path_length > MAXIMUM_PATH || game.path_length % 5 != 0) {
			printf("     Must be a multiple of 5 and between 10-70!!!\n");
		}
	} while (game.path_length < MIN_PATH || game.path_length > MAXIMUM_PATH || game.path_length % 5 != 0);
	do {
		printf("Set the limit for number of moves allowed: ");
		scanf("%d", &game.max_num_move);
		if (game.max_num_move < player.num_lives || game.max_num_move > (game.path_length*75/100)) {
			printf("    Value must be between %d and %d\n",player.num_lives, (game.path_length*75/100));
		}
	} while (game.max_num_move < player.num_lives || game.max_num_move > (game.path_length*75/100));
	printf("\nBOMB Placement\n--------------\nEnter the bomb positions in sets of 5 where a value\nof 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n(Example: 1 0 0 1 1) NOTE: there are %d to set!\n",game.path_length);
	for (i = 0; i < game.path_length; i += 5) {
		printf("   Positions [%2d-%2d]: ", i + 1, i + 5);
		for (j = i; j < i + 5; j++) {
			scanf("%d", &game.bombs[j]);
		}
	}
	printf("BOMB placement set\n\n");
	printf("TREASURE Placement\n------------------\nEnter the treasure placements in sets of 5 where a value\nof 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n(Example: 1 0 0 1 1) NOTE: there are %d to set!\n",game.path_length);
	for (i = 0; i < game.path_length; i += 5) {
		printf("   Positions [%2d-%2d]: ", i + 1, i + 5);
		for (j = i; j < i + 5; j++) {
			scanf("%d", &game.treasure[j]);
		}
	}
	printf("TREASURE placement set\n\n");
	printf("GAME configuration set-up is complete...\n\n");
	printf("------------------------------------\nTREASURE HUNT Configuration Settings\n------------------------------------\n");
	printf("Player:\n");
	printf("   Symbol     : %c\n", player.character_symbol);
	printf("   Lives      : %d\n", player.num_lives);
	printf("   Treasure   : [ready for gameplay]\n");
	printf("   History    : [ready for gameplay]\n");
	printf("\nGame:\n");
	printf("   Path Length: %d\n", game.path_length);
	printf("   Bombs      : ");
	for (i = 0; i < game.path_length; i++) {
		printf("%d", game.bombs[i]);
	}
	printf("\n   Treasure   : ");
	for (i = 0; i < game.path_length; i++) {
		printf("%d", game.treasure[i]);
	}
	printf("\n\n====================================\n~ Get ready to play TREASURE HUNT! ~\n====================================\n\n  ");

	for (i = 0; i < game.path_length; i++) {
        printf("-");
	}
	printf("\n  ");
	for (i = 0; i < game.path_length; i++) {
        if((i + 1) % 10 == 0)
            printf("%d", (i + 1) / 10);
        else
            printf("|");
	}
	printf("\n  ");
	for (i = 0; i < game.path_length; i++) {
        printf("%d",(i + 1) % 10);
	}
	printf("\n");

    int treasure_count = 0,k=game.max_num_move,p;
	for(p=0; p<=game.max_num_move;p++)
	{

        int move[70],m=0;
        char symbol[70];
        printf("+---------------------------------------------------+\n");
        printf(" Lives: %2d | Treasures: %2d | Moves Remaining: %2d\n",player.num_lives,treasure_count,k);
        printf("+---------------------------------------------------+\n");

        if(player.num_lives == 0 || k == 0){
            printf("\n##################\n#   Game over!   #\n##################\n\nYou should play again and try to beat your score!!");
            break;
        }
        do {
		printf("Next Move [1-%2d] :",game.path_length);
		scanf("%d", &move[p]);
		if (move[p] < 1 || move[p] > game.path_length) {
			printf("  Out of Range!!!\n");
		}
        } while (move[p] < 1 || move[p] > game.path_length);
        int n;
        for(n = 0; n<p;n++){
            if(move[p] == move[n]){
            printf("\n===============> Dope! You've been here before!\n\n  "); m = move[p];symbol[p] = symbol[n]; p--; k++;
            goto a;
            }
        }

        if(game.bombs[move[p]-1] == 0 && game.treasure[move[p]-1] == 0){
            printf("\n===============> [.] ...Nothing found here... [.]\n\n  "); symbol[p] = '.';
        }
        else if(game.bombs[move[p]-1] == 1 && game.treasure[move[p]-1] == 1){
            printf("\n===============> [&] !!! BOOOOOM !!! [&]\n===============> [&] $$$ Life Insurance Payout!!! [&]\n\n  "); symbol[p] = '&';
            player.num_lives--; treasure_count++;
        }
        else if(game.bombs[move[p]-1] == 1 && game.treasure[move[p]-1] == 0){
            printf("\n===============> [!] !!! BOOOOOM !!! [!]\n\n  ");  symbol[p] = '!';
            player.num_lives--;
        }
        else{
            printf("\n===============> [$] $$$ Found Treasure! $$$ [$]\n\n  ");   symbol[p] = '$';
            treasure_count++;
        }

        if(player.num_lives == 0){
            printf("\b\bNo more LIVES remaining!\n\n  ");
        }
        else if(k == 0){
            printf("\b\bNo more MOVES remaining\n\n  !");
        }

        a:
        for (i = 0; i < game.path_length; i++) {
                char d = ' ';
            if(m == 0)
            {
                if((i+1) == move[p])
                d = player.character_symbol;
            }
            else
            {
                if((i+1) == m)
                d = player.character_symbol;
            }

                printf("%c",d);
        }

            printf("\n  ");
        for (i = 1; i <= game.path_length; i++)
        {
                char c = '-';
                if(i == move[p])
                {
                    c=symbol[p];
                }
                for(n=0; n<p;n++)
                {
                    if(move[n] != move[p] && i == move[n])
                    {
                        c=symbol[n];
                    }
                }
                printf("%c",c);
        }
        printf("\n  ");
        for (i = 0; i < game.path_length; i++) {
            if((i + 1) % 10 == 0)
                printf("%d", (i + 1) / 10);
            else
                printf("|");
        }
        printf("\n  ");
        for (i = 0; i < game.path_length; i++) {
            printf("%d",(i + 1) % 10);
        }
        printf("\n");
        k--;
	}

	return 0;
}


