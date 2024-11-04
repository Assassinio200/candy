#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int R = 11,C = 11,bomb_tip = 4;
///////////////////////////INIT


int randomB() {
    return rand() % (bomb_tip + 1); //gen fructe
}

///////////////////////////AFIS
void printGrid(const vector<vector<int>>& grid) {
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout << "---------------" << endl;
}

///////////////////////////INIT-lista
void Vizual_Joc(vector<vector<int>>& grid) {
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            grid[i][j] = randomB();
        }
    }
}

//////////////////////////Conditii
int checkers(vector<vector<int>>& grid) {
    int punct = 0;


// de L de 3 -90%
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C - 3; ++j) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i+1][j] && grid[i][j] == grid[i+2][j] &&  grid[i][j] == grid[i][j +1]&&  grid[i][j] == grid[i][j+2]) {
                punct += 20;
                grid[i][j] = grid[i][j + 1] = grid[i][j + 2]=grid[i][j +1] =grid[i][j+2]= 0; //inlocuire cu nimic
            }
        }
    }




// de L de 3 -180%
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C - 3; ++j) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i+1][j] && grid[i][j] == grid[i+2][j] &&  grid[i][j] == grid[i][j +1]&&  grid[i][j] == grid[i][j+2]) {
                punct += 20;
                grid[i][j] = grid[i][j + 1] = grid[i][j + 2]=grid[i][j +1] =grid[i][j+2]= 0; //inlocuire cu nimic
            }
        }
    }




// de L de 3 180%
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C - 4; ++j) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i+1][j] && grid[i][j] == grid[i+2][j] &&  grid[i][j] == grid[i+2][j +1]&&  grid[i][j] == grid[i+2][j+2]) {
                punct += 20;
               grid[i][j] = grid[i][j + 1] = grid[i][j + 2]=grid[i+2][j +1] =grid[i+2][j+2]= 0; //inlocuire nimic
            }
        }
    }







     //orizontal de 5
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C - 4; ++j) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2] &&  grid[i][j] == grid[i][j + 3]&&  grid[i][j] == grid[i][j + 4]) {
                punct += 50;
                grid[i][j] = grid[i][j + 1] = grid[i][j + 2]=grid[i][j+3] =grid[i][j + 4]= 0; //inlocuire cu nimic
            }
        }
    }



   //orizontal de 4
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C - 3; ++j) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2] &&  grid[i][j] == grid[i][j + 3]) {
                punct += 10;
                grid[i][j] = grid[i][j + 1] = grid[i][j + 2]=grid[i][j+3] = 0; //inlocuire cu nimic
            }
        }
    }


    //orizontal de 3
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C - 2; ++j) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i][j + 1] && grid[i][j] == grid[i][j + 2]) {
                punct += 5;
                grid[i][j] = grid[i][j + 1] = grid[i][j + 2] = 0; //inlocuire cu nimic
            }
        }
    }

    //vertical de 5
    for (int i = 0; i < R - 4; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j] && grid[i][j]==grid[i + 3][j]&& grid[i][j]==grid[i + 4][j]) {
                punct += 10;
                grid[i][j] = grid[i + 1][j] = grid[i + 2][j] =grid[i + 3][j]=grid[i+3][j]= 0; // inlocuire cu nimic
            }
        }
    }

    //vertical de 4
    for (int i = 0; i < R - 3; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j] && grid[i][j]==grid[i + 3][j]) {
                punct += 10;
                grid[i][j] = grid[i + 1][j] = grid[i + 2][j] =grid[i + 3][j]= 0; // inlocuire cu nimic
            }
        }
    }
    //vertical de 3
    for (int i = 0; i < R - 2; ++i) {
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] != 0 && grid[i][j] == grid[i + 1][j] && grid[i][j] == grid[i + 2][j]) {
                punct += 5;
                grid[i][j] = grid[i + 1][j] = grid[i + 2][j] = 0; // inlocuire cu nimic
            }
        }
    }

    return punct;
}

////////////////////////////ADauga Full
void AdaugaBoombo(vector<vector<int>>& grid) {
    for (int j = 0; j < C; ++j) {
        int liber = R - 1; //
        for (int i = R - 1; i >= 0; --i) {
            if (grid[i][j] != 0) {
                grid[liber][j] = grid[i][j];
                if (liber != i) {
                    grid[i][j] = 0;
                }
                --liber;
            }
        }
    }
}

//simulare n jocuri
void playGame(int rounds) {
    vector<vector<int>> grid(R, vector<int>(C));
    srand(static_cast<unsigned int>(time(0))); // nr random

    int totalpunct = 0;

    for (int round = 0; round < rounds; ++round) {
        Vizual_Joc(grid);
        cout << "Tabel initial " << round + 1 << ":" << endl;
        printGrid(grid);

        int roundpunct = 0;
        bool matchesFound;

        //se joaca pana cand nu se mai poate
        do {
            matchesFound = false;
            int punct = checkers(grid);
            if (punct > 0) {
                roundpunct += punct;
                matchesFound = true;
                AdaugaBoombo(grid); //noi fructe
                cout << "Tabel nou:" << endl;
                printGrid(grid);
            }
        } while (matchesFound);

        totalpunct += roundpunct;
        cout << "puncte pr runda " << round + 1 << ": " << roundpunct << endl;
        cout << "-----------------------------" << endl;
    }

    cout << "Total puncte dupa " << rounds << "  runde: " << totalpunct << endl;
}

int main() {
    int gamesToPlay;
    cout << "Cate jocuri: ";
    cin >> gamesToPlay;

    playGame(gamesToPlay);

    return 0;
}
