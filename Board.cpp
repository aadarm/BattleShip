//
//  Board.cpp
//  BattleShip
//
//  Created by Abigail Darmofal on 8/8/19.
//  Copyright © 2019 Abigail Darmofal. All rights reserved.
//


#include "Coordinates.cpp"
#include <vector>
using namespace std;

class Board
{
    public:
    
    vector<Coordinates> board;
    
    Board()
    {
        for(int row = 0; row < 10; row++)
        {
            for(int col = 0; col < 10; col++)
            {
                board.push_back(Coordinates(row, col));
            }
        }
    }
    
};
