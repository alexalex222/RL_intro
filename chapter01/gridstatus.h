#pragma once

#include <vector>
#include <numeric>
#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>

using std::vector;
using std::unordered_map;

class GridStatus
{
private:
    int rows;
    int cols;
    bool end;
    int winner;
    int hashVal;
    vector<vector<int>> data;



public:
    GridStatus(int board_rows=3, int board_cols=3);     //constructor
    GridStatus(GridStatus* p);                      //constructor

    int getHash();
    int getRow();
    int getCol();
    vector<vector<int>> getData();
    int getWinner();
    bool isEnd();   // check whether the game reaches the end
    void show();    // print the board
    GridStatus nextStatus(int row, int col, int symbol);    // the status after a move
    static void getAllStatesImpl(GridStatus current_state, int current_symbol,
                                 unordered_map<int, GridStatus>& all_states);
    static unordered_map<int, GridStatus> getAllStates(GridStatus current_state);
};
