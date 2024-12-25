#include "leaderboard.h"

void write_to_leaderboard(Player *player, char *user_name)
{
    FILE *leadboard_text = fopen("../Scenes/Leaderboard/leaderboard.txt", "a");
    assert(leadboard_text);
    fprintf(leadboard_text, "%s,%d;", user_name, player->score);
    fclose(leadboard_text);
}

void read_from_leaderboard()
{
    FILE *leadboard_text = fopen("../Scenes/Leaderboard/leaderboard.txt", "r");
    assert(leadboard_text);
    char input_text[2000];
    fread(input_text, sizeof(char), 2000, leadboard_text);

    char *string = strtok(input_text, ";");
    printf("%s\n", string);
    while ((string = strtok(NULL, ";")) != NULL)
    {
        printf("%s\n", string);
    }

    fclose(leadboard_text);
}
