#define UNICODE   // turn off this when using the terminal not sopporting UNICODE
//constant definitions
enum COLORS{BLACK=30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
#define bg(c) (c+10)   //macro definition
//function declarations
void clearScreen(void);
void setColors(short fg,short bg);//it is not necessary to write down "fg,bg"
void resetColors(void);
void barChart(int []);
