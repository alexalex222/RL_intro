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
    this->hashVal = 0;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            int a = this->data[i][j];
            if (a == -1) a = 2;
            this->hashVal = this->hashVal*3 + a;
        }
    }
    return this->hashVal;
}

int GridStatus::getRow() {
    return this->rows;
}

int GridStatus::getCol() {
    return this->cols;
}

vector<vector<int>> GridStatus::getData() {
    return this->data;
}

int GridStatus::getWinner() {
    return this->winner;
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

    for(auto i = result.begin(); i != result.end(); i++) {
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
        this->end = true;
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
            if (this->data[i][j] == 1) token = "*";
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

void GridStatus::getAllStatesImpl(GridStatus current_state, int current_symbol,
                                  unordered_map<int, GridStatus> &all_states)
{
    for (int i = 0; i < current_state.getRow(); i++) {
        for (int j = 0; j < current_state.getCol(); j++) {
            if (current_state.getData()[i][j] == 0) {
                GridStatus next_state = current_state.nextStatus(i, j, current_symbol);
                int new_hash = next_state.getHash();
                if (all_states.find(new_hash) == all_states.end()) {
                    all_states.emplace(new_hash, next_state);
                    if (!next_state.isEnd()) {
                        GridStatus::getAllStatesImpl(next_state, -current_symbol, all_states);
                    }
                }
            }
        }
    }
}

unordered_map<int, GridStatus> GridStatus::getAllStates(GridStatus current_state) {
    int current_symbol = 1;
    unordered_map<int, GridStatus> all_states;
    all_states.emplace(current_state.getHash(), current_state);
    GridStatus::getAllStatesImpl(current_state, current_symbol, all_states);
    return all_states;
}