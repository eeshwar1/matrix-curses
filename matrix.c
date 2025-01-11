#include<ncurses.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>

void update_state(char** state);
void rotate_right(char **arr, int n, int k);

int main(int argc, char* argv[]) {


	char *my_name = "Matrix";
	int ch;
	srand(time(NULL));

	initscr();
	cbreak();
	mvprintw(1, (COLS - strlen(my_name))/2, my_name);
	refresh();
	curs_set(0);
	timeout(500);
	keypad(stdscr, TRUE);

//	start_color();
//	init_pair(1, COLOR_WHITE, COLOR_CYAN);

	WINDOW* matrix = subwin(stdscr, 20, COLS - 2, 2, 2);
	wbkgd(matrix, COLOR_PAIR(1));
	wrefresh(matrix);
	keypad(matrix, TRUE);

	char **state;

	state = (char**)calloc(20,sizeof(char*));
	for(int i=0; i< COLS; i++)
	{
		state[i] = (char*)calloc(COLS - 2, sizeof(char));
	}


	for(int i=0; i < 20; i++) {
		for(int j=0; j < COLS - 2; j++) 
		{
			state[i][j]=' ';
		}
	}


	for(int j=0; j < COLS - 2; j++)
	{
		state[0][j] = (rand() % 2) == 1 ? '*': ' ';
		state[2][j] = (rand() % 2) == 1 ? '*': ' ';
	}

	while(getch() != KEY_F(1)) 
	{

		update_state(state);
		wclear(matrix);
		for (int i=0; i < 20; i++)
		{
			for(int j=0; j < COLS - 2; j++)
			{
				mvwprintw(matrix, i + 1, j + 1,"%c",state[i][j]);
			}
		}
			
		wrefresh(matrix);
	//	usleep(2000000);
	//	sleep(1000);
	//	timeout(1000);
		

	
	}
//	ch = getch();

	endwin();

	return 0;

}

void update_state(char **state)
{

	rotate_right(state, 20, 1);

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
