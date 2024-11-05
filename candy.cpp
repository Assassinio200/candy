#include <iostream>
#include <vector>
#include <cstdlib> //pt random
#include <algorithm>

using namespace std;

const int R = 11, C = 11, bomb_tip = 4;

///////////////////////////INIT


int randomB() {
    return rand() % (bomb_tip + 1); // bombo random
}

///////////////////////////AFIS

// Print the grid
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

// Initialize the grid with random fruits
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

    ///orizontal 3,4,5
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C - 2; ++j) {
            if (grid[i][j] != 0) {

                int len = 1;
                while (j + len < C && grid[i][j] == grid[i][j + len]) {
                    ++len;
                }
                if (len >= 3) {
                                                    ///SCOR
                    if (len == 3) {
                        punct += 5;
                    } else if (len == 4) {
                        punct += 10;
                    } else if (len == 5) {
                        punct += 50;
                    }
                    for (int k = 0; k < len; ++k) {
                        grid[i][j + k] = 0;  // curatare gasire
                    }
                }
            }
        }
    }

    /// Vertical 3,4,5
    for (int j = 0; j < C; ++j) {
        for (int i = 0; i < R - 2; ++i) {
            if (grid[i][j] != 0) {

                int len = 1;
                while (i + len < R && grid[i][j] == grid[i + len][j]) {
                    ++len;
                }
                if (len >= 3) {
                                                ///SCOR
                    if (len == 3) {
                        punct += 5;
                    } else if (len == 4) {
                        punct += 10;
                    } else if (len == 5) {
                        punct += 50;
                    }
                    for (int k = 0; k < len; ++k) {
                        grid[i + k][j] = 0;  // curatare gasire
                    }
                }
            }
        }
    }

    /// L T rotatii
    auto VerForma = [&grid, &punct](int i, int j, vector<pair<int, int>> shape, int PctFormaa) {
        bool valid = true;
        for (const auto& [di, dj] : shape) {
            if (i + di < 0 || i + di >= R || j + dj < 0 || j + dj >= C || grid[i + di][j + dj] == 0) {
                valid = false;
                break;
            }
        }
        if (valid) {
            punct += PctFormaa; ///pct pe forme
            for (const auto& [di, dj] : shape) {
                grid[i + di][j + dj] = 0; // curaatre gasire
            }
        }
    };

    /// L
    for (int i = 0; i < R - 2; ++i) {
        for (int j = 0; j < C - 2; ++j) {
VerForma(i, j, {{0, 0}, {1, 0}, {2, 0}, {2, 1}}, 20);  //  L
   VerForma(i, j, {{0, 0}, {0, 1}, {0, 2}, {1, 0}}, 20);  // 90 L
 VerForma(i, j, {{0, 0}, {1, 0}, {2, 0}, {0, 1}}, 20);  // 180 L
            VerForma(i, j, {{0, 0}, {0, 1}, {0, 2}, {-1, 2}}, 20); // 270  L
        }
    }

    /// T
    for (int i = 0; i < R - 2; ++i) {
        for (int j = 0; j < C - 2; ++j) {
VerForma(i, j, {{0, 0}, {1, 0}, {2, 0}, {1, 1}}, 30);  //  T
  VerForma(i, j, {{0, 0}, {0, 1}, {0, 2}, {1, 1}}, 30);  // 90 T
  VerForma(i, j, {{0, 0}, {1, 0}, {2, 0}, {1, -1}}, 30); // 180 T
            VerForma(i, j, {{0, 0}, {0, 1}, {0, 2}, {-1, 1}}, 30); // 270 T
        }

    }

    return punct;
}

////////////////////////////ADauga bombo Full

void AdaugaBoombo(vector<vector<int>>& grid) {
    for (int j = 0; j < C; ++j) {
        int liber = R - 1;
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

///////////////////////////Miscari

// Swap de bombo
void SchimbaBombo(vector<vector<int>>& grid, int i1, int j1, int i2, int j2) {
    int temp = grid[i1][j1];
    grid[i1][j1] = grid[i2][j2];
    grid[i2][j2] = temp;
}

// miscari bombo
int tryAllMoves(vector<vector<int>>& grid) {
    int maxScore = 0;


    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (j + 1 < C) {  // Swap dreapta
                SchimbaBombo(grid, i, j, i, j + 1);
                int score = checkers(grid);
                maxScore = max(maxScore, score);
                SchimbaBombo(grid, i, j, i, j + 1);  // reintoarcere
            }
            if (i + 1 < R) {  // Swap jos
                SchimbaBombo(grid, i, j, i + 1, j);
                int score = checkers(grid);
                maxScore = max(maxScore, score);
                SchimbaBombo(grid, i, j, i + 1, j);  // reintoarcerer
            }
        }
    }

    return maxScore;
}

////////////////////////////Main

int main() {
    int DeJucat;
    cout << "Cate jocuri: ";
    cin >> DeJucat;

    vector<vector<int>> grid(R, vector<int>(C));

    int totalPoints = 0;

    for (int runda = 0; runda < DeJucat; ++runda) {
        if (totalPoints >= 10000) {
            cout << "Stop ,scor maxim!" << endl;
            break;
        }

        Vizual_Joc(grid);
        cout << "Tabel initial " << runda + 1 << ":" << endl;
        printGrid(grid);

        int rundaPct = 0;
        bool Gasiree;

        do {
            Gasiree = false;
            int punct = checkers(grid);
            if (punct > 0) {
                rundaPct += punct;
                Gasiree = true;
                cout << "Tabel nou:" << endl;
                printGrid(grid);
                AdaugaBoombo(grid);
            }
        } while (Gasiree);

        totalPoints += rundaPct;
        cout << "Total puncte per runda " << runda + 1 << ": " << rundaPct << endl;
        cout << "-----------------------------" << endl;
    }

    if (totalPoints < 10000) {
        cout << "Total puncte : " << totalPoints << endl;
    }

    return 0;
}
