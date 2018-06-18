#pragma once

#include<vector>
#include<numeric>
#include<cmath>
#include<iostream>
#include<string>



class GridStatus
{
private:
    int rows;
    int cols;
    bool end;
    int winner;
    int hashVal;
    std::vector<std::vector<int>> data;



public:
    GridStatus(int board_rows, int board_cols);     //constructor
    GridStatus(GridStatus* p);                      //constructor

    int getHash();
    bool isEnd();   // check whether the game reaches the end
    void show();    // print the board
    GridStatus nextStatus(int row, int col, int symbol);    // the status after a move

};
