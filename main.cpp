#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>

using namespace std;


struct pos {
    int row;
    int col;
};

class Sudoku {
    int gameBoard [9][9] = {
            {0,1,0,6,0,0,0,0,3},
            {0,0,0,0,5,9,7,0,0},
            {0,0,0,2,0,0,0,0,0},
            {0,8,2,0,0,0,0,9,1},
            {0,0,6,0,0,0,0,0,0},
            {3,4,0,0,0,0,8,7,0},
            {0,0,0,0,0,1,0,0,0},
            {0,0,3,0,2,0,0,0,0},
            {9,0,0,0,0,6,0,5,0}
        };
        vector<pos> emptySpaces;
        int amountCalled = 0;
        HANDLE h;
        CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

public:

    //Constructor
    Sudoku() {
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(h, &bufferInfo);
    }

    bool solvePuzzle(){


        Sleep(1);
        printBoard();
        pos position;
        amountCalled++;
        if (!findEmptySpace(position))
            return true;

        for(int i = 1; i <= 9; i++)
        {
           if ( doesNumFit(i, position) ){
                gameBoard[position.row][position.col] = i;

                //printEmptySpaces(newEmpty);
                if(solvePuzzle())
                    return true;

                //failure
                gameBoard[position.row][position.col] = 0;
           }
           //printBoard();
        }
        return false;
    }


    bool doesNumFit(int num, const pos &position){
        for(int i = 0; i < 9; i++){
            //check horizontal
            if(gameBoard[i][position.col] == num)
                return false;
            else if(gameBoard[position.row][i] == num)
                return false;
        }

        int miniX = position.row - ((position.row)%3);
        int miniY = position.col - ((position.col)%3);

        for(int i = 0; i < 3; ++i)
            for(int j = 0; j < 3; ++j)
                if(gameBoard[miniX + i][miniY + j] == num)
                    return false;

        return true;
    }

    void findEmptySpaces(){
        for(int i = 0; i < 9; ++i)
        {
            for(int j = 0; j < 9; ++j)
            {
                if(gameBoard[i][j] == 0)
                {
                    pos position;
                    position.row = i;
                    position.col = j;
                    emptySpaces.push_back(position);
                }
            }
        }
    }

    bool findEmptySpace(pos &position){
        for(auto it = emptySpaces.begin(); it != emptySpaces.end(); ++it)
        {
            if(gameBoard[(*it).row][(*it).col] == 0){
                position = *it;
                return true;
            }
        }
        return false;
    }

    void printBoard()
    {
        SetConsoleCursorPosition(h, bufferInfo.dwCursorPosition);
        for(int i = 1; i <= 9; ++i)
        {
            for(int j = 1; j <= 9; ++j)
            {
                cout << gameBoard[i-1][j-1] << " ";
                if(j%3 == 0) cout << "| ";
            }
            cout << "\n";
            if(i%3 == 0) cout << "------+-------+---------" << endl;
        }
        cout << amountCalled << " solve calls made." << endl;
    }

};

int main()
{
    Sudoku puzzle;
    puzzle.findEmptySpaces();
    if (puzzle.solvePuzzle() == true)
        puzzle.printBoard();
    else
        cout << "No Solution" << endl;
    return 0;
}
