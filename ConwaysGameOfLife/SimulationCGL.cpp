enum SIMULATION_STATUS {RUNNING = 1, EDITING, PAUSED};
enum DEAD_STATUS {ACTIVE = 1, PASSIVE};

#define SCREEN_LENGTH 150
#define SCREEN_BREADTH 40

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define ALIVE true
#define DEAD false 

#define GOTO_CURSOR gotoxy(left_margin + cursor_col, top_margin + cursor_row)
#define CURRENT_CELL matrix[cursor_row][cursor_col]
#define GOTO_CELL gotoxy(left_margin + col, top_margin + row)
#define CELL matrix[row][col]
#define CACHE cache[row][col]
#define FREE (!isEditing && !isPaused)

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>

// universe params
bool **matrix;
int **cache;

// operational params
bool isPaused, isEditing, blink_on;
bool extended_neigh;
int frame_delay, min_frame_delay, blink_delay;
int num_rows, num_cols;
int cursor_row, cursor_col;
float operation_time;
int current_fps, fast_fps;

// display params
int max_rows, max_cols, min_rows, min_cols;
int para_delay, line_delay, char_delay;
int preset_no;
int left_margin, top_margin, line_x, line_y;
char living, passive_dead, active_dead;

// stats
int num_frames, sum_total;
int num_deaths, num_births, num_living;

// cacher
#include "cacher.cpp"

// presets
#include "presets.cpp"

// helper functions
void delay(int milliseconds);
void gotoxy(short x, short y);
void smoothLine(const char *line, bool tab = true);
void blink();
void safeReturn();

using namespace std;

void initialize()
{
    max_rows = 30;
    min_rows = 3;
    max_cols = 90;
    min_cols = 3;

    para_delay = 0;
    line_delay = 0;
    char_delay = 0;
    blink_delay = 100;
    min_frame_delay = 100;

    isPaused = false;
    isEditing = true;
    blink_on = false;

    line_x = 55;
    line_y = 2;

    living = 'X';
    passive_dead = 'o';
    active_dead = ' ';  

    num_frames = 0; 
    sum_total = 0;  

    extended_neigh = false;
}

void changeDead(int state)
{
    for(int row = 0; row < num_rows; row++)
    {
        for(int col = 0; col < num_cols; col++)
        {
            if(CELL == DEAD)
            {
                GOTO_CELL;
                if(state == ACTIVE) cout << active_dead;
                else cout << passive_dead;
            }
        }
    }
}

void killAll()
{
    for(int row = 0; row < num_rows; row++)
    {
        for(int col = 0; col < num_cols; col++)
        {
            CELL = DEAD;
            GOTO_CELL;
            cout << passive_dead;
        }
    }
}

void update()
{
    clock_t start = clock();
    num_frames++;

    cacheMiddle();
    cacheEdge();
    cacheCorner();

    num_births = 0;
    num_deaths = 0;
    for(int row = 0; row < num_rows; row++)
    {
        for(int col = 0; col < num_cols; col++)
        {
            if(CELL == ALIVE)
            {
                if(CACHE < 2 || CACHE > 3)
                {
                    GOTO_CELL;
                    cout << active_dead;
                    CELL = DEAD;
                    num_deaths++;
                }
            }
            else
            {
                if(CACHE == 3)
                {
                    GOTO_CELL;
                    cout << living;
                    CELL = ALIVE;
                    num_births++;
                }
            }
        }
    }

    num_living = 0;
    for(int row = 0; row < num_rows; row++)
    {
        for(int col = 0; col < num_cols; col++)
        {
            if(CELL == ALIVE) num_living++;
        }
    }
    sum_total = sum_total + num_living;

    if(num_living == 0 && !isEditing)
    {
        isEditing = true;
        changeDead(PASSIVE);
        Beep(1500, 100);
    }
    
    gotoxy(0,30);
    cout << " There were " << num_births << " births and " << num_deaths << " deaths    " << endl;
    cout << " Net change: " << num_births - num_deaths << " and current population: " << num_living << "    " << endl;
    printf(" Average population is %.2f over %d generations ", float(sum_total) / num_frames, num_frames);

    operation_time = clock() - start;
    gotoxy(line_x+1, 38);
    printf(" Computation time %f ms          ", operation_time);
}

void returnDefault()
{
    GOTO_CURSOR;

    if(CURRENT_CELL == ALIVE) cout << living;
    else cout << passive_dead;
    blink_on = true;
}

void setStatus(int status)
{
    gotoxy(1,3);
    switch(status)
    {
        case PAUSED:
            cout << "Currently: Paused   ";
            break;
        case EDITING:
            cout << "Currently: Editing  ";
            break;
        case RUNNING:
            cout << "Currently: Running  ";
            break;
        default:
            cout << "Status unknown      ";
    }
}

void simulate()
{
    int key, value;
    do
    {
        if(FREE)
        {
            update();
            delay(frame_delay);
        }
        if(isEditing)
        {
            blink();
            delay(blink_delay);
        }

    } while( !kbhit());

    key = getch();
    {
        if(key == 0XE0)
        {
            value = getch();
            {
                if(isEditing)
                {
                    if(value == UP)
                    {
                        returnDefault();
                        cursor_row--;

                        if(cursor_row < 0) cursor_row = num_rows - 1;
                    }
                    else if(value == DOWN)
                    {
                        returnDefault();
                        cursor_row++;

                        if(cursor_row == num_rows) cursor_row = 0;
                    }
                    else if(value == LEFT)
                    {
                        returnDefault();
                        cursor_col--;

                        if(cursor_col < 0) cursor_col = num_cols - 1;
                    }
                    else if(value == RIGHT)
                    {
                        returnDefault();
                        cursor_col++;

                        if(cursor_col == num_cols) cursor_col = 0;
                    }
                }
                if(isPaused && !isEditing)
                {
                    if(value == RIGHT)
                    {
                        update();
                    }
                }
            }
        }
        else if((key == 't' || key == 'T') && isEditing)
        {
            GOTO_CURSOR;

            if(CURRENT_CELL == ALIVE)
            {
                CURRENT_CELL = DEAD;
                cout << passive_dead;
            }
            else
            {
                CURRENT_CELL = ALIVE;
                cout << living;
            }
        }
        else if((key == 'r' || key == 'R') && (isEditing || isPaused))
        {
            returnDefault();
            isEditing = false;
            isPaused = false;
            setStatus(RUNNING);
            changeDead(ACTIVE);
        }
        else if((key == 'e' || key == 'E') && !isEditing)
        {
            isEditing = true;
            isPaused = false;
            setStatus(EDITING);
            changeDead(PASSIVE);
        }
        else if((key == 'p' || key == 'P') && !isPaused)
        {
            returnDefault();
            isPaused = true;
            isEditing = false;
            setStatus(PAUSED);
            changeDead(ACTIVE);
        }
        else if(key == 'k' || key == 'K')
        {
            isEditing = true;
            isPaused = false;
            setStatus(EDITING);
            killAll();
            sum_total = 0;
            num_frames = 0;
        }
        else if(key == 'm' || key == 'M')
        {
            delete(matrix);
            delete(cache);
            safeReturn();
        }
        else if(key == 's' || key == 'S')
        {
            int row_count = 1;

            system("cls");
            gotoxy(0,0);
            printf("Use the following code to regenerate the current state:\n");
            for(int row = 0; row < num_rows; row++)
            {
                for(int col = 0; col < num_cols; col++)
                {
                    if(CELL == ALIVE) 
                    {
                        printf("makeAlive(%d,%d);",row,col);
                        row_count++;

                        if(row_count == 7)
                        {
                            cout << endl;
                            row_count = 1;
                        }
                    }
                }
            }
            isPaused = true;
        }
    }

    simulate();
}

int displayMenu()
{
    gotoxy(1,1);
    cout << "---> Conway's Game of Life <---" << endl << endl;
    cout << " Conway's Game of Life is a cellular automaton scheme devised by British mathematician John Horton Conway in 1970" << endl;
    cout << " It is a full information, zero player game in which the future state is dependent on the initial state" << endl;
    cout << " The game is set in a 2D universe entirely consisting of a M x N matrix of square cells which can be in two states - alive or dead" << endl << endl;

    delay(para_delay);
    smoothLine("Only the initial state of each cell must be provided, after which the game operates on its own, following a strict set of instructions:", false);
    cout << endl;
    delay(line_delay);
    smoothLine("1. A living cell with one or fewer alive neighbours will die due to loneliness");
    delay(line_delay);
    smoothLine("2. A living cell with four or more alive neighbours will die due to overcrowding");
    delay(line_delay);
    smoothLine("3. A living cell with two or three alive neighbours will continue to live due to mutual sustenance");
    delay(line_delay);
    smoothLine("4. A dead cell with exactly three neighbours will become alive due to reproduction");
    delay(line_delay);
    cout << endl << " *horizontal, vertical as well as diagonally neighbouring cells are considered as neighbours" << endl << endl;

    delay(para_delay);
    cout << " ---> Options <---" << endl << endl;
    cout << " 1. Set initial state and start simulation" << endl;
    cout << " 2. Use presets" << endl;
    cout << " 3. Exit" << endl << endl;

    int choice;
    cout << " Your choice: ";
    cin >> choice;
    cout << endl;

    return choice;  
}

int getSize()
{
    cout << " ---> Configuring operational parameters <---" << endl << endl;
    cout << " A. Universe size:" << endl;
    cout << " \t1. Small square - 10 x 10" << endl;
    cout << " \t2. Medium square - 20 x 20" << endl;
    cout << " \t3. Large square - 30 x 30" << endl;
    cout << " \t4. Standard rectangle - 60 x 30" << endl;
    cout << " \t5. Largest rectangle - 90 x 30" << endl;
    cout << " \t6. Custom size" << endl << endl;

    int choice, neigh_choice;
    cout << " Enter your choice: ";
    cin >> choice;
    
    while(choice < 1 || choice > 6)
    {
        cout << " Please enter a valid choice: ";
        cin >> choice;
    }

    cout << endl;
    cout << " Do you want edge and corner blocks to have a neighbour in the opposite edge/corner of the board?" << endl << endl;
    cout << " 0: No" << endl;
    cout << " 1: Yes" << endl << endl;
    cout << " Your choice: ";
    cin >> neigh_choice;

    if(neigh_choice == 1) extended_neigh = true;
    else if(neigh_choice == 0) extended_neigh = false;
    else
    {
        cout << "Unresolved choice received. Extended neighbourhood set to TRUE" << endl;
        extended_neigh = true;
    }
    
    return choice;
}

void getCustomSize(int *num_rows, int *num_cols)
{
    int temp_rows, temp_cols;
    cout << " Enter number of rows (minimum 5, maximum 30): ";
    cin >> temp_rows;

    while(temp_rows < min_rows || temp_rows > max_rows)
    {
        cout << " Please enter a number within bounds: ";
        cin >> temp_rows;
    }
    *num_rows = temp_rows;

    cout << " Enter number of columns (minimum 5, maximum 90): ";
    cin >> temp_cols;

    while(temp_cols < min_cols || temp_cols > max_cols)
    {
        cout << " Please enter a number within bounds: ";
        cin >> temp_cols;
    }
    *num_cols = temp_cols;
}

int getDelay()
{
    int temp_delay;
    cout << endl << " The delay between two frames is dependent on your PC as well as the following choice" << endl;
    cout << " Enter delay between two frames (minimum 100 milliseconds): ";
    cin >> temp_delay;

    while(temp_delay < min_frame_delay)
    {
        cout << " You cannot distinguish between the frames. Please enter a value greater than or equal to " << min_frame_delay << ": ";
        cin >> temp_delay;
    }
    return temp_delay;
}

void makeUniverse()
{
    matrix = new bool* [num_rows];
    cache = new int* [num_rows];
    for(int i = 0; i < num_rows; i++)
    {
        matrix[i] = new bool [num_cols];
        cache[i] = new int [num_cols];
    }
    
    for(int i = 0; i < num_rows; i++)
    {
        for(int j = 0; j < num_cols; j++)
        {
            matrix[i][j] = DEAD;
            cache[i][j] = 0;
        }
    }

    left_margin = (SCREEN_LENGTH - line_x - num_cols - 1) / 2;
    left_margin = left_margin + line_x;
    top_margin = (SCREEN_BREADTH - line_y - num_rows - 1) / 2;
    top_margin = top_margin + line_y;

    cursor_row = num_rows / 2;
    cursor_col = num_cols / 2;
} 

void drawLayout()
{
    gotoxy(65,1);
    cout << "Conway's Game of Life";
    for(int i = 3; i < SCREEN_BREADTH - 1; i++)
    {
        gotoxy(line_x, i);
        cout << "|";
    }
    for(int i = 1; i < SCREEN_LENGTH - 1; i++)
    {
        gotoxy(i, line_y);
        cout << "-";
    }

    setStatus(EDITING);
    cout << endl << endl;
    cout << " INSTRUCTIONS:" << endl;
    cout << " A living cell is denoted by " << living << endl;
    cout << " A dead cell is denoted by " << endl;
    cout << " '" << passive_dead << "' when paused or editing" << endl;
    cout << " '" << active_dead << "' while running" << endl;
    cout << " Extended neighbourhood: ";
    if(extended_neigh) cout << "TRUE" << endl << endl;
    else cout << "FALSE" << endl << endl;
    
    cout << " CONTROL KEYS:" << endl;
    cout << " E: Edit" << endl;
    cout << " K: Kill all" << endl;
    cout << " M: Return to Menu" << endl;
    cout << " P: Pause" << endl;
    cout << " R: Resume simulation" << endl;
    cout << " S: Generate code for saving current state" << endl;
    cout << " T: (During edit) Toggle state of cell" << endl << endl;

    cout << " NAVIGATION:" << endl;
    cout << " When Paused," << endl;
    cout << " Use the -> key to go to the next frame" << endl;
    cout << " When Editing," << endl;
    cout << " Use the cursor keys to navigate" << endl;
    cout << " Press T to toggle the state of a cell" << endl << endl;

    cout << " STATS:" << endl;
    cout << " There are " << num_rows * num_cols << " cells. Dimension is " << num_rows << "x" << num_cols << endl;

    for(int i = 0; i < num_rows; i++)
    {
        for(int j = 0; j < num_cols; j++)
        {
            gotoxy(left_margin + j, top_margin + i);
            if(matrix[i][j] == ALIVE) cout << living;
            else
            {
                if(isEditing) cout << passive_dead;
                else cout << active_dead;
            }
        }
    }

    gotoxy(1,38);
    printf("Developed by: ChanRT");
}

int main()
{
    initialize();
    int menu_choice, matrix_choice;
    menu_choice = displayMenu();

    if(menu_choice == 1)
    {
        matrix_choice = getSize();
        switch(matrix_choice)
        {
            case 1:
                num_rows = num_cols = 10;
                break;
            case 2:
                num_rows = num_cols = 20;
                break;
            case 3:
                num_rows = num_cols = 30;
                break;
            case 4:
                num_rows = 30;
                num_cols = 60;
                break;
            case 5:
                num_rows = 30;
                num_cols = 90;
                break;
            case 6:
                getCustomSize(&num_rows, &num_cols);
                break;
        }
        frame_delay = getDelay();
        preset_no = 0;
    }
    else if(menu_choice == 2)
    {
        preset_no = presetMenu();
        prepareForPreset(preset_no);
        frame_delay = getDelay();
    }
    else exit(1);

    makeUniverse();
    system("cls");

    if(preset_no > 0)
    {
        isPaused = false;
        isEditing = false;
        makePreset(preset_no);
    }
    drawLayout();
    if(preset_no > 0)
    {
        setStatus(RUNNING);
        delay(1000);
    }
    simulate();

    return 0;
}

void delay(int milliseconds)
{
    clock_t start = clock();

    while (clock() < start + milliseconds)
        ;
}

void gotoxy(short x, short y)
{
    COORD p = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void blink()
{
    GOTO_CURSOR;

    if(blink_on)
    {
        printf(" ");
        blink_on = false;
    }
    else if(matrix[cursor_row][cursor_col] == ALIVE)
    {
        cout << living;
        blink_on = true;
    }
    else
    {
        cout << passive_dead;
        blink_on = true;
    }
}

void smoothLine(const char *line, bool tab)
{
    cout << " ";
    if(tab) cout << "\t";
    for(int i = 0; line[i] != '\0'; i++)
    {
        cout << line[i];
        delay(char_delay);
    }
    cout << endl;
}

void safeReturn()
{
    system("cls");
    main();
}