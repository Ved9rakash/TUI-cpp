#include <iostream>
#include <ncurses.h>

//Width and height of window
constexpr int WIDTH = 30;
constexpr int HEIGHT = 10;

int startx = 0;
int starty = 0;

char *choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Exit",
};

int n_choices = sizeof(choices) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight);

int main()
{
    WINDOW* menu_win;
    int highlight{1};
    int selectedChoice{0};
    int enteredCharacter{};

    initscr();

    //clear();

    noecho();
    cbreak();

    int startx{(80 - WIDTH)/2};
    int starty{(24 - HEIGHT)/2};

    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys");
    refresh();
    print_menu(menu_win, highlight);
    while (1)
    {
        enteredCharacter = wgetch(menu_win);
        switch (enteredCharacter)
        {
            case KEY_UP:
                if (highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;

            case KEY_DOWN:
                if (highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            
            case 10:
                selectedChoice = highlight;
                break;
            
            default:
                mvprintw(24, 0, "Character pressed is %3d hopefully it can be printed as %c",
                        enteredCharacter, enteredCharacter);
                refresh();
                break;
        }
        print_menu(menu_win, highlight);

        if (selectedChoice != 0)
            break;
    }
    mvprintw(23, 0, "You choose %d with choice string.", selectedChoice);
    clrtoeol();
    refresh();
    endwin();
    return 0;
}

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;	

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}