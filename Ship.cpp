//
//  Ship.cpp
//  BattleShip
//
//  Created by Abigail Darmofal on 8/8/19.
//  Copyright © 2019 Abigail Darmofal. All rights reserved.
//

#include <stdio.h>
#include <string>
#include <vector>

class Ship
{
    public:
    
    std::string Name;
    int Size;
    bool isSunk;
    std::vector<int> Location;
    
    Ship(std::string name, int size)
    {
        Name = name;
        Size = size;
        
        isSunk = false;
        
        
    }
    
    
    
    
    
};
