//
//  main.cpp
//  BattleShip
//
//  Created by Abigail Darmofal on 8/8/19.
//  Copyright © 2019 Abigail Darmofal. All rights reserved.
//

#include <iostream>
#include <string>
#include "Player.cpp"

using namespace std;

int main(int argc, const char * argv[]) {

    
    cout << "Let's Play BattleShip!!\n" << "Please enter your name: \n";
    
    string P1Name;
    cin >> P1Name;
    
    Player P1 = Player(P1Name);
    Player AI = Player("Opponent");
    
    
    P1.assignShips();
    AI.assignShips();
    cout << "Your ships have been placed for you, here is what your board looks like\n";
    P1.showBoard(P1.personalBoard.board);

    
    
    bool gameOverPlayer = false;
    bool gameOverAI = false;
    
    cout << "It's your tuen to go first!\n";
    while(gameOverAI == false && gameOverPlayer == false)
    {
        gameOverPlayer = P1.playRound(AI.personalBoard.board, AI.Ships);
        if (gameOverPlayer) break;
        gameOverAI = AI.takeTurnAI(P1.personalBoard.board, P1.Ships);
        if(gameOverAI) break;
        
    }
    
    if(gameOverPlayer)
    {
        cout << "Winnerrrrr";
    }
    else if(gameOverAI)
    {
        cout << "Loserrrr";
    }
    return 0;
}
