#include "leaderboard.h"

void write_to_leaderboard(int score, char *user_name)
{
    Data data = {.score = score, .name = ""};
    if (user_name != NULL && *user_name != 0 && *user_name != '\0')
    {
        strcpy(data.name, user_name);
        FILE *leadboard_text = fopen("../Scenes/Leaderboard/leaderboard.txt", "ab");
        assert(leadboard_text);
        fwrite(&data, sizeof(Data), 1, leadboard_text);
        fclose(leadboard_text);
    }
}

Data *read_from_leaderboard(int *row_count)
{

    FILE *leadboard_text = fopen("../Scenes/Leaderboard/leaderboard.txt", "rb");
    assert(leadboard_text);

    *row_count = floor(fsize(leadboard_text) / sizeof(Data));
    Data *data = (Data *)malloc(*row_count * sizeof(Data));

    for (int i = 0; i < *row_count; i++)
    {
        fread(&data[i], sizeof(Data), 1, leadboard_text); // Write the player data to the file
    }

    fclose(leadboard_text);
    return data;
}

int fsize(FILE *fp)
{
    int prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, prev, SEEK_SET); // go back to where we were
    return sz;
}

Data *best_score_sorted(int *row_count)
{
    *row_count = 0;

    Data *all_data = read_from_leaderboard(row_count);

    bubbleSort(all_data, *row_count);

    return all_data;
}

// perform the bubble sort
void bubbleSort(Data *data, int size)
{
    // loop to access each array element
    for (int step = 0; step < (size - 1); ++step)
    {
        // loop to compare array elements
        for (int i = 0; i < (size - step - 1); ++i)
        {

            if (data[i].score < data[i + 1].score)
            {

                Data temp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = temp;
            }
        }
    }
}