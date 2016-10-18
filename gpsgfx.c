#include <panel.h>
#include <stdlib.h>
#include <ctype.h>
#include <curses.h>
#include <string.h>

#define NLINES 10
#define NCOLS 40

void init_wins(WINDOW **wins, int n);
void win_showmap(WINDOW *win, char *label, int label_color);
void win_showsat(WINDOW *win, char *label, int label_color);
void print_label(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void print_sats(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
char * intprtkey(int ch);

int main()
{	WINDOW *my_wins[3];
	PANEL  *my_panels[3];
	int ch;

	/* Initialize curses */
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/* Initialize all the colors */
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

	init_wins(my_wins, 3);
	
	/* Attach a panel to each window */ 	/* Order is bottom up */
	my_panels[0] = new_panel(my_wins[0]); 	/* Push 0, order: stdscr-0 */
	my_panels[1] = new_panel(my_wins[1]); 	/* Push 1, order: stdscr-0-1 */
	my_panels[2] = new_panel(my_wins[2]); 	/* Push 2, order: stdscr-0-1-2 */

	/* Set up the user pointers to the next panel */
	set_panel_userptr(my_panels[0], my_panels[1]);
	set_panel_userptr(my_panels[1], my_panels[2]);
	set_panel_userptr(my_panels[2], my_panels[0]);

	/* Update the stacking order. 2nd panel will be on top */
	update_panels();

	/* Show it on the screen */
	attron(COLOR_PAIR(4));
	attroff(COLOR_PAIR(4));
	doupdate();
	
	mvaddstr(20, 0, "    1: Satellite Details        Q: Quit");
	mvaddstr(21, 0, "You pressed: ");
	
	while((ch = getch()) != 'q')
	{	
		mvprintw(20, 0, "    1: Satellite Details        Q: Quit");
		mvprintw(21, 0, "You pressed: %s", intprtkey(ch));
		refresh();
		update_panels();
		doupdate();
	}
	endwin();
	return 0;
}

/* Put all the windows */
void init_wins(WINDOW **wins, int n)
{	
	char label[80];

	wins[0] = newwin(20/*height*/, 55/*width*/, /*y*/0, /*x*/0);
	sprintf(label, "Map");
	win_showmap(wins[0], label, 1);
	
	wins[1] = newwin(20, 25, /*y*/0, /*x*/55);
	sprintf(label, "Filllllllller");
	win_showsat(wins[1], label, 2);
	
	wins[2] = newwin(10, 80, /*y*/20, /*x*/0);
}

/* Show the window with a border and a label: map */
void win_showmap(WINDOW *win, char *label, int label_color)
{	int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE); 
	mvwhline(win, 2, 1, ACS_HLINE, width - 2); 
	mvwaddch(win, 2, width - 1, ACS_RTEE); 
	
	/* Prints title of panel */
	print_label(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

/* Show the window with a border and a label: satellites */
void win_showsat(WINDOW *win, char *label, int label_color)
{	int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE); 
	mvwhline(win, 2, 1, ACS_HLINE, width - 2); 
	mvwaddch(win, 2, width - 1, ACS_RTEE); 
	
	/* Prints title of panel */
	print_label(win, 1, 0, width, label, COLOR_PAIR(label_color));
	
	/* Prints text inside */
	print_sats(win, 3, 0, width, label, COLOR_WHITE);
}

void print_label(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

void print_sats(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int x, y;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	x = 1;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

/*  Struct to hold keycode/keyname information  */

struct keydesc {
    int  code;
    char name[20];
};


/*  Returns a string describing a character passed to it  */

char * intprtkey(int ch) {

    /*  Define a selection of keys we will handle  */

    static struct keydesc keys[] = { { KEY_UP,        "Up arrow"        },
				     { KEY_DOWN,      "Down arrow"      },
				     { KEY_LEFT,      "Left arrow"      },
				     { KEY_RIGHT,     "Right arrow"     },
				     { KEY_HOME,      "Home"            },
				     { KEY_END,       "End"             },
				     { KEY_BACKSPACE, "Backspace"       },
				     { KEY_IC,        "Insert"          },
				     { KEY_DC,        "Delete"          },
				     { KEY_NPAGE,     "Page down"       },
				     { KEY_PPAGE,     "Page up"         },
				     { KEY_F(1),      "Function key 1"  },
				     { KEY_F(2),      "Function key 2"  },
				     { KEY_F(3),      "Function key 3"  },
				     { KEY_F(4),      "Function key 4"  },
				     { KEY_F(5),      "Function key 5"  },
				     { KEY_F(6),      "Function key 6"  },
				     { KEY_F(7),      "Function key 7"  },
				     { KEY_F(8),      "Function key 8"  },
				     { KEY_F(9),      "Function key 9"  },
				     { KEY_F(10),     "Function key 10" },
				     { KEY_F(11),     "Function key 11" },
				     { KEY_F(12),     "Function key 12" },
				     { -1,            "<unsupported>"   }
    };
    static char keych[2] = {0};
    
    if ( isprint(ch) && !(ch & KEY_CODE_YES)) {

	/*  If a printable character  */

	keych[0] = ch;
	return keych;
    }
    else {

	/*  Non-printable, so loop through our array of structs  */

	int n = 0;
	
	do {
	    if ( keys[n].code == ch )
		return keys[n].name;
	    n++;
	} while ( keys[n].code != -1 );

	return keys[n].name;
    }    
    
    return NULL;        /*  We shouldn't get here  */
}

