#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

static WINDOW *p_screen;

int nib_poll_kbd(void)
{
  int key = getch();

  return key;
}

void nib_put_scr(int x, int y, int ch)
{
  mvprintw(y, x, "%c", ch);
  wrefresh(p_screen);
}

void nib_init(void)
{
	srand(time(0));           /* Init randomiser */
	p_screen = initscr();     /* Create the window */
	start_color();            /* We use color (well...) */
	curs_set(0);              /* Make cursor invisible */
	noecho();                 /* Don't output chars on screen when written */
	keypad(p_screen, TRUE);   /* Give p_screen keyboard focus */
	nodelay(p_screen, TRUE);  /* Make getch nonblocking */

	printw("SnakeASM Apocalypse");
}

void nib_end(void)
{
  endwin();
  exit(0);
}

int get_x()
{
	int x, y;
	getmaxyx(p_screen, y, x);

	return x;
}
int get_y()
{
	int x, y;
	getmaxyx(p_screen, y, x);

	return y;
}

int get_x_half()
{
	int x, y;
	getmaxyx(p_screen, y, x);

	return x/2;
}
int get_y_half()
{
	int x, y;
	getmaxyx(p_screen, y, x);

	return y/2;
}

void nib_clear_screen()
{
	wclear(p_screen);
	wborder(p_screen, '|', '|', '-', '-', '+', '+', '+', '+');

	wrefresh(p_screen);
}

void nib_update()
{
	refresh();
}

int nib_rand_x()
{
	return (rand()%(get_x()-2))+1;
}
int nib_rand_y()
{
	return (rand()%(get_y()-2))+1;
}

void nib_debug_print() 
{
	printf( "DEBUG\n" );
}