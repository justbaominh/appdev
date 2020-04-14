//usually in a header file we have 2 parts:
//1. Function declarations
//2. Constant definitions

#define ESC 0x1B
enum FG {BLACK=30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
#define bg(c) (c+10) //this is called macro definition

#define UNICODE
#define BAR "\u2590"
#define BOX "\u2588"

#define DEBUG
//the following is the information of cursor position, this information
//will be decoded by an escape sequence ESC[6n, and query reply should be
//a string consisting row and column number of the cursor.
typedef struct {
	int row;
	int col;
}Position;

void setfgcolor(int);
void resetcolor(void);
void clearscreen(void);
void gotoXY(int, int);
void drawbar(int, int);
void setbgcolor(int);
void setcolors(int, int);
Position getscreensize(void);
