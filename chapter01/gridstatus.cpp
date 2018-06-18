//
// Created by Kuilin Chen on 2018-06-16.
//

#include "gridstatus.h"

GridStatus::GridStatus(int board_rows, int board_cols) {
    this->rows = board_rows;
    this->cols = board_cols;
    this->end = false;
    this->winner = 0;
    this->hashVal = 0;
    this->data = std::vector<std::vector<int>>(this->rows, std::vector<int>(cols, 0));
}

GridStatus::GridStatus(GridStatus *p) {
    this->rows = p->rows;
    this->cols = p->cols;
    this->end = p->end;
    this->winner = p->winner;
    this->hashVal = p->hashVal;
    this->data = p->data;
}

int GridStatus::getHash() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            int a = this->data[i][j];
            if (a == -1) a = 2;
            this->hashVal = this->hashVal*3 + a;
        }
    }
    return this->hashVal;
}

bool GridStatus::isEnd() {
    std::vector<int> result;
    int s = 0;
    // check row
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) s += this->data[i][j];
        result.push_back(s);
        s = 0;
    }
    // check column
    for(int i = 0; i < this->rows; i++) {
        for(int j = 0; j < this->cols; j++) s += this->data[j][i];
        result.push_back(s);
        s= 0;
    }
    // check diagonal
    for(int i = 0; i < this->rows; i++) s += this->data[i][i];
    result.push_back(s);
    s = 0;
    // check anti-diagonal
    for(int i = 0; i < this->rows; i++) s += this->data[i][cols - 1 -i];
    result.push_back(s);

    for(std::vector<int>::iterator i = result.begin(); i != result.end(); i++) {
        if(*i == 3) {
            this->winner = 1;
            this->end = true;
            return this->end;
        }

        if(*i == -3) {
            this->winner = -1;
            this->end = true;
            return this->end;
        }
    }
    // check for tie
    s = 0;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            s += std::abs(this->data[i][j]);
        }
    }
    if (s == this->rows*this->cols) {
        this->winner = 0;
        this->end = 0;
        return this->end;
    }
    // game still going on
    this->end = false;
    return this->end;

}

void GridStatus::show() {
    std::string out = "";
    std::string token = "";
    for (int i = 0; i < this->rows; i++) {
        std::cout<<"-------------"<<std::endl;
        out = "| ";
        for (int j = 0; j < this->cols; j++) {
            if (this->data[i][i] == 1) token = "*";
            else if (this->data[i][j] == 0) token = "0";
            else if (this->data[i][j] == -1) token = "x";

            out += token + " | ";
        }
        std::cout<< out <<std::endl;
    }
    std::cout<<"-------------"<<std::endl;
}

GridStatus GridStatus::nextStatus(int row, int col, int symbol) {
    GridStatus n = GridStatus(this);
    n.data[row][col] = symbol;
    return n;
}