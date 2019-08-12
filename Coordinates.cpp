//
//  Coordinates.cpp
//  BattleShip
//
//  Created by Abigail Darmofal on 8/8/19.
//  Copyright © 2019 Abigail Darmofal. All rights reserved.
//

#include <stdio.h>


class Coordinates
{
    public:
    
    int Row;
    int Col;
    
    enum coordinateType
    {
        X, M, o, A, B, C, D, S
    };
    
    coordinateType CoordinateType;
    
    Coordinates(int row, int col)
    {
        Row = row;
        Col = col;
        CoordinateType = o;
    }
};
