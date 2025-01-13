#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

#define KEY_q 81


typedef struct _streak {
        
        int pos;
        int length;
        bool isActive;

} streak;

void update_state(char** state, streak* streaks);
void rotate_right(char **arr, int n, int k);

#define MAX_STREAK_LENGTH 10
#define MAX_STREAKS 25

#define ROW_LENGTH COLS - 2

int main(int argc, char* argv[]) {


	char *my_name = "Matrix";
	int ch;
	srand(time(NULL));

	initscr();
	cbreak();
    noecho();
	mvprintw(1, (COLS - strlen(my_name))/2,"%s", my_name);
	refresh();
	curs_set(0);
	timeout(150);
	keypad(stdscr, TRUE);

        streak streaks[MAX_STREAKS];

        for(int s=0; s < MAX_STREAKS; s++)
        {
                streaks[s].isActive = rand()% 2 ? true: false;
                
                if (streaks[s].isActive == true) {

                        streaks[s].pos = rand() % ROW_LENGTH;
                } else {
                        streaks[s].pos = 0;
                }

                streaks[s].length = 0;
        }

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

	WINDOW* matrix = subwin(stdscr, 20, ROW_LENGTH, 2, 2);
	wbkgd(matrix, COLOR_PAIR(1));
	wrefresh(matrix);
	keypad(matrix, TRUE);

	char **state;

	state = (char**)calloc(20,sizeof(char*));
	for(int i=0; i< COLS; i++)
	{
		state[i] = (char*)calloc(ROW_LENGTH, sizeof(char));
	}


	for(int i=0; i < 20; i++) {
		for(int j=0; j < ROW_LENGTH; j++) 
		{
			state[i][j]=' ';
		}
	}

	while((ch = getch()) != 'q') 
	{

		update_state(state, streaks);
		wclear(matrix);
		for (int i=0; i < 20; i++)
		{
			for(int j=0; j < ROW_LENGTH; j++)
			{
				mvwprintw(matrix, i + 1, j + 1,"%c",state[i][j]);
			}
		}
			
		wrefresh(matrix);

	
	}

	endwin();

	return 0;

}

char* get_streaks_row(streak* streaks)
{

        char *row = (char*)calloc(ROW_LENGTH, sizeof(char));
        int r = 0;

        while(r < 5) {
                int rand_streak = rand()% MAX_STREAKS;

                if (streaks[rand_streak].isActive == false) 
                {
                        streaks[rand_streak].isActive = true;
                        streaks[rand_streak].pos = rand()%ROW_LENGTH;
                }
                r++;
        }


        for(int i=0; i< ROW_LENGTH; i++)
        {
                row[i]=' ';
        }

        for(int i=0; i < MAX_STREAKS; i++)
        {
                if(streaks[i].isActive == true)
                {
                        if (streaks[i].length < MAX_STREAK_LENGTH) 
                        {
                                char ch = (char) (rand()%127 + 32);
                                row[streaks[i].pos] = ch;
                                streaks[i].length++;
                        } else {

                                streaks[i].isActive = false;
                                streaks[i].length = 0;
                                streaks[i].pos = 0;
                        }
                }
        }

        return row;

}
void update_state(char **state, streak* streaks)
{

    char *row = get_streaks_row(streaks);

	rotate_right(state, 20, 1);
    state[0] = row;

}

void rotate_right(char **arr, int n, int k) {
    char **temp = (char **)malloc(k * sizeof(char *));

    // Store the last 'k' elements in a temporary array
    for (int i = 0; i < k; i++) {
        temp[i] = arr[n - k + i];
    }

    // Shift the remaining elements to the right
    for (int i = n - 1; i >= k; i--) {
        arr[i] = arr[i - k];
    }

    // Copy the elements from the temporary array back to the beginning
    for (int i = 0; i < k; i++) {
        arr[i] = temp[i];
    }

    free(temp);
}
