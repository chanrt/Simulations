#include <iostream>
using namespace std;

int presetMenu()
{
    int choice;

    cout << " A. Bodies in motion:" << endl;
    cout << " \t1. Glider" << endl;
    cout << " \t2. Spaceship" << endl << endl;

    cout << " B. Replicators:" << endl;
    cout << " \t3. Gosper's glider gun" << endl;
    cout << " \t4. Simkin glider gun" << endl << endl;

    cout << " C. Oscillators" << endl;
    cout << " \t5. Pulsar" << endl;
    cout << " \t6. Pentadecathlon" << endl << endl;

    cout << " D. Long time evolvers" << endl;
    cout << " \t7. R-pentomino" << endl;
    cout << " \t8. Acorn" << endl;

    cout << " Visit https://playgameoflife.com/lexicon for more" << endl << endl;
    cout << " Your choice: ";
    cin >> choice;

    while(choice < 1 || choice > 8)
    {
        cout << "Please enter a valid choice: ";
        cin >> choice;
    }

    return choice;
}

void prepareForPreset(int preset_num)
{
    if(preset_num == 1 || preset_num == 2)
    {
        num_rows = max_rows;
        num_cols = max_cols;
        extended_neigh = true;
    }
    else if(preset_num == 3 || preset_num == 4)
    {
        num_rows = max_rows;
        num_cols = 50;
        extended_neigh = false;
    }
    else if(preset_num == 5)
    {
        num_rows = 30;
        num_cols = 30;
        extended_neigh = false;
    }
    else if(preset_num == 6)
    {
        num_rows = 20;
        num_cols = 20;
        extended_neigh = false;
    }
    else if(preset_num == 7 || preset_num == 8)
    {
        num_rows = max_rows;
        num_cols = max_cols;
        extended_neigh = false;
    }
}

void makeAlive(int index1, int index2)
{
    matrix[index1][index2] = 1;
}

void makePreset(int preset_num)
{
    if(preset_num == 1)
    {
        makeAlive(1,2);makeAlive(2,3);makeAlive(3,3);makeAlive(3,2);makeAlive(3,1);
    }
    else if(preset_num == 2)
    {
        makeAlive(4,7);makeAlive(4,8);makeAlive(5,6);makeAlive(5,7);makeAlive(5,8);makeAlive(5,9);
        makeAlive(6,6);makeAlive(6,7);makeAlive(6,9);makeAlive(6,10);makeAlive(7,8);makeAlive(7,9);
    }
    else if(preset_num == 3)
    {
        makeAlive(1,25);makeAlive(2,23);makeAlive(2,25);makeAlive(3,13);makeAlive(3,14);makeAlive(3,21);
        makeAlive(3,22);makeAlive(3,35);makeAlive(3,36);makeAlive(4,12);makeAlive(4,16);makeAlive(4,21);
        makeAlive(4,22);makeAlive(4,35);makeAlive(4,36);makeAlive(5,1);makeAlive(5,2);makeAlive(5,11);
        makeAlive(5,17);makeAlive(5,21);makeAlive(5,22);makeAlive(6,1);makeAlive(6,2);makeAlive(6,11);
        makeAlive(6,15);makeAlive(6,17);makeAlive(6,18);makeAlive(6,23);makeAlive(6,25);makeAlive(7,11);
        makeAlive(7,17);makeAlive(7,25);makeAlive(8,12);makeAlive(8,16);makeAlive(9,13);makeAlive(9,14);
    }
    else if(preset_num == 4)
    {
        makeAlive(1,24);makeAlive(2,22);makeAlive(2,24);makeAlive(3,13);makeAlive(3,21);makeAlive(3,23);
        makeAlive(3,35);makeAlive(3,36);makeAlive(4,12);makeAlive(4,13);makeAlive(4,20);makeAlive(4,23);
        makeAlive(4,35);makeAlive(4,36);makeAlive(5,1);makeAlive(5,2);makeAlive(5,11);makeAlive(5,12);
        makeAlive(5,17);makeAlive(5,18);makeAlive(5,21);makeAlive(5,23);makeAlive(6,1);makeAlive(6,2);
        makeAlive(6,10);makeAlive(6,11);makeAlive(6,12);makeAlive(6,17);makeAlive(6,18);makeAlive(6,22);
        makeAlive(6,24);makeAlive(7,11);makeAlive(7,12);makeAlive(7,17);makeAlive(7,18);makeAlive(7,24);
        makeAlive(8,12);makeAlive(8,13);makeAlive(9,13);
    }
    else if(preset_num == 5)
    {
        makeAlive(8,11);makeAlive(8,12);makeAlive(8,13);makeAlive(8,17);makeAlive(8,18);makeAlive(8,19);
        makeAlive(10,9);makeAlive(10,14);makeAlive(10,16);makeAlive(10,21);makeAlive(11,9);makeAlive(11,14);
        makeAlive(11,16);makeAlive(11,21);makeAlive(12,9);makeAlive(12,14);makeAlive(12,16);makeAlive(12,21);
        makeAlive(13,11);makeAlive(13,12);makeAlive(13,13);makeAlive(13,17);makeAlive(13,18);makeAlive(13,19);
        makeAlive(15,11);makeAlive(15,12);makeAlive(15,13);makeAlive(15,17);makeAlive(15,18);makeAlive(15,19);
        makeAlive(16,9);makeAlive(16,14);makeAlive(16,16);makeAlive(16,21);makeAlive(17,9);makeAlive(17,14);
        makeAlive(17,16);makeAlive(17,21);makeAlive(18,9);makeAlive(18,14);makeAlive(18,16);makeAlive(18,21);
        makeAlive(20,11);makeAlive(20,12);makeAlive(20,13);makeAlive(20,17);makeAlive(20,18);makeAlive(20,19);
    }
    else if(preset_num == 6)
    {
        makeAlive(9,7);makeAlive(9,12);makeAlive(10,5);makeAlive(10,6);makeAlive(10,8);makeAlive(10,9);
        makeAlive(10,10);makeAlive(10,11);makeAlive(10,13);makeAlive(10,14);makeAlive(11,7);makeAlive(11,12);
    }
    else if(preset_num == 7)
    {
        makeAlive(14,45);makeAlive(14,46);makeAlive(15,44);makeAlive(15,45);makeAlive(16,45);
    }
    else if(preset_num == 8)
    {
        makeAlive(14,43);makeAlive(15,45);makeAlive(16,42);makeAlive(16,43);makeAlive(16,46);makeAlive(16,47);
        makeAlive(16,48);
    }
}