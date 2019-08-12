//
//  Player.cpp
//  BattleShip
//
//  Created by Abigail Darmofal on 8/8/19.
//  Copyright © 2019 Abigail Darmofal. All rights reserved.
//

#include <vector>
#include <string>
#include <iostream>

#include "Board.cpp"
#include "Ship.cpp"

using namespace std;

class Player
{
    public:
    string Name;

    vector<Ship> Ships;
    
    Board personalBoard;
    Board firingBoard;
    
    Player(string name)
    {
        Name = name;
        
        
        Ships.push_back(Ship("AirCraft Carrier",5));
        Ships.push_back(Ship("BattleShip", 4));
        Ships.push_back(Ship("Destroyer", 3));
        Ships.push_back(Ship("Cruiser", 3));
        Ships.push_back(Ship("Submarine", 3));
    }
    
    void showBoard(vector<Coordinates> board, bool enterEnabled=true)
    {
        char cols[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
        int rows[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        cout << "   |  " << rows[0] << "  |  "<< rows[1] << "  |  "<< rows[2]<< "  |  "<< rows[3] <<"  |  " << rows[4] << "  |  " << rows[5]<< "  |  " << rows[6] << "  |  " << rows[7] << "  |  " << rows[8]<< "  |  "<< rows[9] << "  |\n";
        
        for(int i = 0; i < 10; i++)
        {
            cout << "___|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n";
            cout << "   |     |     |     |     |     |     |     |     |     |     |\n";
            writeLineInColor(i, cols[i], board);
            
        }
        
        cout << "___|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|\n";
        
        if(enterEnabled)
        {
            
            cout << "Press 'enter' to continue\n";
            getchar();
            
            
        }
        
    }
    
    void writeLineInColor(int i, char col, vector<Coordinates> board)
    {
        cout << " " << col << " |";
        
        for(int j = 0; j < 10; j++)
        {
            cout << "  ";
            Coordinates::coordinateType type = board[i*10+j].CoordinateType;
            
            if(type == Coordinates::A)
            {
                cout << "A";
            }
            else if(type == Coordinates::B)
            {
                cout << "B";
            }
            else if(type == Coordinates::M)
            {
                cout << "M";
            }
            else if(type == Coordinates::o)
            {
                cout << "o";
            }
            else if(type == Coordinates::C)
            {
                cout << "C";
            }
            else if(type == Coordinates::S)
            {
                cout << "S";
            }
            else if(type == Coordinates::D)
            {
                cout << "D";
            }
            else if(type == Coordinates::X)
            {
                cout << "X";
            }
            cout << "  |";
        }
        cout << "\n";
    }
    
    
    bool playRound(vector<Coordinates> board, vector<Ship> ships)
    {
        cout << "Your Firing Board:\n";
        showBoard(firingBoard.board, false);
        
        cout << "Type in you coordinate to fire: ";
        string key = "";
        int row, col, index = 0;
        char key0 = 'a';
        
        bool validDigits = false;
        while(validDigits == false)
        {
            validDigits = true;
            cin >> key;
            if(key.length() != 2)
            {
                cout << "You must enter exactly 2 character\n";
                validDigits = false;
            }
            else
            {
                key0 = toupper(key[0]);
                row = convertRows(key0);
                col = convertCols(key[1]);
                index = 10*row+col;
            }
            if(key0 < 'A' || key0 > 'J' || key[1] < '0' || key[1] > '9')
            {
                cout << "Invalid Coordinates, Please try again\n";
                validDigits = false;
            }
            else if(firingBoard.board[index].CoordinateType != Coordinates::o)
            {
                cout << "You already fired here, please select other coordinates\n";
                validDigits = false;
            }
        }
        
        string shipName = "";
        
        if(board[index].CoordinateType != Coordinates::o)
        {
            int shipIndex = -1;
            
            switch(board[index].CoordinateType)
            {
                case Coordinates::D:
                    shipName = "Destroyer";
                    shipIndex = 0;
                    break;
                case Coordinates::S:
                    shipName = "Submarine";
                    shipIndex = 1;
                    break;
                case Coordinates::C:
                    shipName = "Cruiser";
                    shipIndex = 2;
                    break;
                case Coordinates::B:
                    shipName = "Battleship";
                    shipIndex = 3;
                    break;
                case Coordinates::A:
                    shipName = "AirCraft Carrier";
                    shipIndex = 4;
                    break;
                default:
                    break;
            }
            
            firingBoard.board[index].CoordinateType = Coordinates::X;
            cout << "Congrats!\n" << shipName << " Hit!\n";
            
            if(shipIndex != -1)
            {
                if(shipSunk(firingBoard.board, ships[shipIndex].Location))
                {
                    cout << shipName << " Sunk!\n";
                    for(int i = 0; i < ships[shipIndex].Location.size(); i++)
                    {
                        firingBoard.board[ships[shipIndex].Location[i]].CoordinateType = board[index].CoordinateType;
                    }
                    ships[shipIndex].isSunk = true;
                    for(int i = 0; i < Ships.size(); i++)
                    {
                        if(ships[i].isSunk == false)
                        {
                            showBoard(firingBoard.board);
                            return false;
                        }
                    }
                    
                    showBoard(firingBoard.board);
                    return true;
                }
            }
            showBoard(firingBoard.board);
        }
        else
        {
            cout << "You've missed :(\n";
            firingBoard.board[index].CoordinateType = Coordinates::M;
            showBoard(firingBoard.board);
        }
        cout << "Your opponent is aiming to fire\n ...\n...\n...\n";
        return false;
    }
    
    
    bool takeTurnAI(vector<Coordinates> board, vector<Ship> ships)
    {
        
        int suggested = AIStrategy(firingBoard.board);
        int startCol = -1, startRow=-1, index = -1;
        
        if(suggested != -1)
        {
            index = suggested;
            if(index < 10)
            {
                startRow = 0;
                startCol = index;
            }
            else
            {
                startRow = index/10;
                startCol = index %10;
            }
        }
        else
        {
            bool validIndex = false;
            
            vector<pair<int, int>> opts;
            
            while(!validIndex)
            {
                startCol = index%10;
                startRow = index/10;
                index = startRow*10 + startCol;
                if(firingBoard.board[index].CoordinateType == Coordinates::o)
                {
                    int score = checkForRoom(firingBoard, index);
                    if(score > 0)
                    {
                        validIndex = true;
                        pair<int, int> temp(index, score);
                        opts.push_back(temp);
                        
                        
                    }
                }
                
                
                if(opts.size() != 3)
                {
                    validIndex = false;
                }
                
            }
            
            int maxScore = 0;
            for(int i = 0; i < opts.size(); i++)
            {
                if(opts[i].second > maxScore)
                {
                    maxScore = opts[i].second;
                    index = opts[i].first;
                }
            }
        }
        
            cout << "Your oppnonent fired at coordinates: " << toLetters(startRow) << startCol << "\n";
            string shipName = "";
            
            if(board[index].CoordinateType != Coordinates::o)
            {
                int shipIndex = -1;
                
                switch(board[index].CoordinateType)
                {
                    case Coordinates::D:
                        shipName = "Destroyer";
                        shipIndex = 0;
                    case Coordinates::S:
                        shipName = "Submarine";
                        shipIndex = 1;
                    case Coordinates::C:
                        shipName = "Cruiser";
                        shipIndex = 2;
                    case Coordinates::B:
                        shipName = "Battleship";
                        shipIndex = 3;
                    case Coordinates::A:
                        shipName = "AirCraft Carrier";
                        shipIndex = 4;
                    default:
                        break;
                }
                
                cout << "Your " << shipName << " has been hit!\n";
                firingBoard.board[index].CoordinateType = Coordinates::X;
                board[index].CoordinateType = Coordinates::X;
                
                if(shipIndex != -1)
                {
                    if(shipSunk(firingBoard.board, Ships[shipIndex].Location))
                    {
                        cout << "Your " << shipName << " has been sunk!\n";
                        
                        for(int i = 0; i < ships[shipIndex].Location.size(); i++)
                        {
                            firingBoard.board[ships[shipIndex].Location[i]].CoordinateType = board[index].CoordinateType;
                        }
                        ships[shipIndex].isSunk = true;
                        for(int k = 0; k < ships.size(); k++)
                        {
                            if(ships[k].isSunk == false)
                            {
                                cout << "Now its your turn to fire\n";
                                showBoard(board);
                                return false;
                            }
                        }
                        return true;
                    }
                }
                
                showBoard(board);
                cout << "Now it's your turn to fire\n";
                
            }
            else
            {
                board[index].CoordinateType = Coordinates::M;
                cout << "Your opponent Missed! Get ready for your turn to fire!";
                showBoard(board);
                firingBoard.board[index].CoordinateType = Coordinates::M;
            }
        
        return false;
    }
    
    
    int AIStrategy(vector<Coordinates> firingBoard)
    {
        bool up=false, right=false;
        int index = -1;
        for(int i = 0; i < 100; i++)
        {
            if(firingBoard[i].CoordinateType == Coordinates::X)
            {
                index = i;
                if(firingBoard[index + 1].CoordinateType == Coordinates::X)
                {
                    right = true;
                }
                else if(firingBoard[index + 10].CoordinateType == Coordinates::X)
                {
                    up = true;
                }
                break;
            }
        }
        
        if(index != -1)
        {
            if(right)
            {
                for(int i = 0; i < 5; i++)
                {
                    if(firingBoard[index + i].CoordinateType == Coordinates::o)
                    {
                        if(index%10 == 0)
                        {
                            return index -1;
                        }
                        return index + i;
                            
                    }
                    if(firingBoard[index + i].CoordinateType == Coordinates::M)
                    {
                        return index-1;
                    }
                }
            }
            if(up)
            {
                for(int i = 1; i < 6; i++)
                {
                    if(firingBoard[index + 10*i].CoordinateType == Coordinates::o)
                    {

                        return index + 10*i;
                        
                    }
                    if(firingBoard[index + 10*i].CoordinateType == Coordinates::M)
                    {
                        return index-10;
                    }
                }
            }
            
            if(index < 99 && firingBoard[index+1].CoordinateType == Coordinates::o && index%10 != 9)
            {
                return index +1;
            }
            else if(index < 90 && firingBoard[index+10].CoordinateType == Coordinates::o)
            {
                return index + 10;
            }
            else if(index > 0 && firingBoard[index-1].CoordinateType == Coordinates::o && index%10 != 0)
            {
                return index -1;
            }
            else if(index > 9 && firingBoard[index-10].CoordinateType == Coordinates::o)
            {
                return index - 10;
            }

        }
        return -1;
    }
    
    
    bool shipSunk(vector<Coordinates> board, vector<int> Location)
    {
        for(int i = 0; i < Location.size(); i++)
        {
            if(board[Location[i]].CoordinateType == Coordinates::o)
            {
                return false;
            }
        }
        return true;
    }
    
    int checkForRoom(Board board, int index)
    {
        bool checker = true;
        int score = 0;
        
        for(int i = 0; i < 3; i++)
        {
            checker = true;
            for(int j = 3; j > 0; j--)
            {
                if(index %10 == 9 && (index + i - j)%10 == 0)
                {
                    checker = false;
                }
                else if(index %10 == 0 && (index + i - j)%10 == 9)
                {
                    checker = false;
                }
                if(index+i-j > 0 && board.board[index+i-j].CoordinateType != Coordinates::o)
                {
                    checker = false;
                }
            }
            if(checker)
            {
                score++;
            }
        }
        
        for(int i = 0; i < 3; i++)
        {
            checker = true;
            for(int j = 3; j>0; j--)
            {
                if(index+i*10-j*10 > 99 || index + i*10-j*10<0 || board.board[index+i*10-j*10].CoordinateType != Coordinates::o)
                {
                    checker = false;
                }
            }
            if(checker)
            {
                score++;
            }
        }
        
        return score;
    }
    
    bool assignShips()
    {
        
        for(int i = 0; i < Ships.size(); i++)
        {
            char type = Ships[i].Name[0];
            
            int startCol, startRow;
            
            startCol = rand() % 9;
            startRow = rand() % 9;
            
            int initialIndex = startRow *10 + startCol;
            
            int direction = rand() % 3;
            
            int otherIndex = -1;
            int tracker = 0;
            
            while(otherIndex == -1)
            {
                direction = rand()%3;
                initialIndex = startRow*10+startCol;
                otherIndex = chooseDirection(direction, startRow, startCol, Ships[i].Size, personalBoard.board);
                
                if(tracker >3)
                {
                    tracker = -1;
                    startCol = rand() % 9;
                    startRow = rand() % 9;
                    
                    initialIndex = startRow*10 + startCol;
                    direction = rand() % 3;
                    otherIndex = -1;
                }
                tracker++;
            }
            tracker = 0;
            
            for(int j = 0; j < Ships[i].Size; j++)
            {
                if(otherIndex - initialIndex < 5)
                {
                    if(otherIndex < initialIndex)
                    {
                        int temp = otherIndex;
                        otherIndex = initialIndex;
                        initialIndex = temp;
                    }
                    
                    Ships[i].Location.push_back(initialIndex + j);
                    
                    if(type == 'D')
                    {
                        personalBoard.board[initialIndex + j].CoordinateType = Coordinates::D;
                    }
                    else if(type == 'S')
                    {
                        personalBoard.board[initialIndex + j].CoordinateType = Coordinates::S;
                    }
                    else if(type == 'A')
                    {
                        personalBoard.board[initialIndex + j].CoordinateType = Coordinates::A;
                    }
                    else if(type == 'C')
                    {
                        personalBoard.board[initialIndex + j].CoordinateType = Coordinates::C;
                    }
                    else if(type == 'B')
                    {
                        personalBoard.board[initialIndex + j].CoordinateType = Coordinates::B;
                    }
                }
                else
                {
                    Ships[i].Location.push_back(initialIndex + j*10);
                    
                    if(type == 'D')
                    {
                        personalBoard.board[initialIndex + j*10].CoordinateType = Coordinates::D;
                    }
                    else if(type == 'S')
                    {
                        personalBoard.board[initialIndex + j*10].CoordinateType = Coordinates::S;
                    }
                    else if(type == 'A')
                    {
                        personalBoard.board[initialIndex + j*10].CoordinateType = Coordinates::A;
                    }
                    else if(type == 'C')
                    {
                        personalBoard.board[initialIndex + j*10].CoordinateType = Coordinates::C;
                    }
                    else if(type == 'B')
                    {
                        personalBoard.board[initialIndex + j*10].CoordinateType = Coordinates::B;
                    }
                }
            }
        }
        return true;
    }
    
    
    
    int chooseDirection(int given, int startRow, int startCol, int size, vector<Coordinates> board)
    {
        int initialIndex = startRow*10 + startCol;
        int secondIndex;
        
        switch(given)
        {
            default:
                return -1;
            case 0:
                secondIndex = initialIndex + size - 1;
                if(secondIndex > 99 || secondIndex < 0) return -1;
                if(canPlaceShip(initialIndex, secondIndex, size, board))
                {
                    return secondIndex;
                    
                }
                else return -1;
            case 1:
                secondIndex = initialIndex + (size - 1)*10;
                if(secondIndex > 99 || secondIndex < 0) return -1;
                if(canPlaceShip(initialIndex, secondIndex, size, board))
                {
                    return secondIndex;
                    
                }
                else return -1;
            case 2:
                secondIndex = initialIndex - (size - 1);
                if(secondIndex > 99 || secondIndex < 0) return -1;
                if(canPlaceShip(initialIndex, secondIndex, size, board))
                {
                    return secondIndex;
                    
                }
                else return -1;
            case 3:
                secondIndex = initialIndex - (size - 1)*10;
                int temp = secondIndex;
                secondIndex = initialIndex;
                initialIndex = temp;
                
                if(secondIndex > 99 || secondIndex < 0) return -1;
                if(canPlaceShip(initialIndex, secondIndex, size, board))
                {
                    return initialIndex;
                    
                }
                else return -1;
        }

    }

    
    bool canPlaceShip(int initialIndex, int secondIndex, int size, vector<Coordinates> board)
    {
        bool nine = false;
        bool zero = false;
        
        for(int i = 0; i < size; i++)
        {
            if(secondIndex - initialIndex < 5)
            {
                if(board[initialIndex + i].CoordinateType != Coordinates::o)
                {
                    return false;
                }
                string index = to_string(initialIndex+i);
                if(index == "9" || (index.length() == 2 && index[1] == '9'))
                {
                    nine = true;
                }
                if(index == "10" || (index.length() == 2 && index[1] == '0'))
                {
                    zero = true;
                }
                if(nine && zero)
                {
                    return false;
                }
            }
            else
            {
                if(board[initialIndex + i * 10].CoordinateType != Coordinates::o)
                {
                    return false;
                }
            }
        }
        return true;
    }
    
    
    void clearBoard()
    {
        for(int i = 0; i < 100; i++)
        {
            personalBoard.board[i].CoordinateType = Coordinates::o;
        }
    }
    
    
    
    string toLetters(int row)
    {
        switch(row)
        {
            case 0:
                return "A";
            case 1:
                return "B";
            case 2:
                return "C";
            case 3:
                return "D";
            case 4:
                return "E";
            case 5:
                return "F";
            case 6:
                return "G";
            case 7:
                return "H";
            case 8:
                return "I";
            case 9:
                return "J";
            default:
                return "";
        }
    }
    
    
    int convertRows(char row)
    {
        switch(row)
        {
            case 'A':
                return 0;
            case 'B':
                return 1;
            case 'C':
                return 2;
            case 'D':
                return 3;
            case 'E':
                return 4;
            case 'F':
                return 5;
            case 'G':
                return 6;
            case 'H':
                return 7;
            case 'I':
                return 8;
            case 'J':
                return 9;
            default:
                return -1;
        }
    }
    
    
    int convertCols(char col)
    {
        switch(col)
        {
            case '0':
                return 0;
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
            case '5':
                return 5;
            case '6':
                return 6;
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            default:
                return -1;
        }

    }
};
