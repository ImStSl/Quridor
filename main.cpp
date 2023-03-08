#include <iostream>

using namespace std;

class game
{

private:
    char board[9][9];

    bool HWalls[8][8], VWalls[8][8];

    char player;
    char winner;

    int limitedMovesG=20, limitedMovesR=20, limitedMovesW=20, limitedMovesB=20;
    int WallsLeftG=5, WallsLeftR=5, WallsLeftW=5, WallsLeftB=5;
    int locG, locR, locW, locB;

    char directionG, directionB, directionW, directionR;

public:

    string mode="unlimited";

    game()
    {
        for(int i=0; i<9; i++)
            for(int j=0; j<9; j++)
                board[i][j]='O';

        for(int i=0; i<8; i++)
            for(int j=0; j<8; j++)
                HWalls[i][j]=VWalls[i][j]=false;

        board[0][4]='G';
        board[4][0]='B';
        board[8][4]='R';
        board[4][8]='W';
        player='G';
        winner='N';
        locB=51;
        locG=15;
        locR=95;
        locW=59;
    }

    void setPlayerDirection(char d)
    {
        if(player=='G')
            directionG=d;
        if(player=='B')
            directionB=d;
        if(player=='W')
            directionW=d;
        if(player=='R')
            directionR=d;
    }

    char getPlayerDirection()
    {
        if(player=='G')
            return directionG;
        if(player=='B')
            return directionB;
        if(player=='W')
            return directionW;
        if(player=='R')
            return directionR;
    }

    bool isemptycell(int location)
    {
        if(board[(location/10 -1)][location%10 -1]!='O')
            return false;
        return true;
    }

    int getPlayerLocation()
    {
        if(player=='G')
            return locG;
        if(player=='B')
            return locB;
        if(player=='W')
            return locW;
        if(player=='R')
            return locR;
    }

    void setPlayerLocation(int newL)
    {
        if(player=='G')
            locG=newL;
        if(player=='B')
            locB=newL;
        if(player=='W')
            locW=newL;
        if(player=='R')
            locR=newL;
    }

    bool isWall()
    {
        int row = getPlayerLocation()/10 -1;
        int col = getPlayerLocation()%10 -1;

        if(getPlayerDirection()=='R')
        {
            if(VWalls[row][col])
                return true;
            return false;
        }
        if(getPlayerDirection()=='L')
        {
            if(VWalls[row][col-1])
                return true;
            return false;
        }
        if(getPlayerDirection()=='U')
        {
            if(HWalls[row-1][col])
                return true;
            return false;
        }
        if(getPlayerDirection()=='D')
        {
            if(HWalls[row][col])
                return true;
            return false;
        }
    }

    int getPlayerMoves()
    {
        if(player=='G')
            return limitedMovesG;
        if(player=='B')
            return limitedMovesB;
        if(player=='W')
            return limitedMovesW;
        if(player=='R')
            return limitedMovesR;
    }
    bool validMove(int newlocation)
    {
        if(mode=="Limited")
        {
            if(getPlayerMoves()<1)
            {
                changePlayer();
                return false;
            }
        }
        if(isemptycell(newlocation) )
        {
            if(isWall()==false)
                return true;
            return false;
        }
        else
        {
            int realLoc=getPlayerLocation();
            setPlayerLocation(newlocation);
            if(isemptycell(findNewLocation()))
            {
                setPlayerLocation(realLoc);
                if(isWall()==false)
                    return true;
                return false;
            }
            setPlayerLocation(realLoc);
            return false;
        }
    }

    void moveTo(int newLocation)
    {
        int row=getPlayerLocation()/10-1;
        int col=getPlayerLocation()%10-1;

        if(isemptycell(newLocation))
        {
            int rowN=newLocation/10-1;
            int colN=newLocation%10-1;
            board[row][col]='O';
            board[rowN][colN]=player;
            setPlayerLocation(newLocation);
        }
        else
        {
            board[row][col]='O';
            setPlayerLocation(newLocation);
            newLocation=findNewLocation();
            int rowN=newLocation/10-1;
            int colN=newLocation%10-1;
            board[rowN][colN]=player;
            setPlayerLocation(newLocation);
        }
        if(mode=="Limited")
        {
            if(player=='G')
                limitedMovesG--;
            else if(player=='B')
                limitedMovesB--;
            else if(player=='W')
                limitedMovesW--;
            else
                limitedMovesR--;
        }
        changePlayer();
    }

    int findNewLocation()
    {
        int newLRow, newLCol;
        int loc=getPlayerLocation();
        int locRow=loc/10, locCol=loc%10;
        int d=getPlayerDirection();
        int newL;

        if(d=='U')
        {
            newLRow=locRow-1;
            newLCol=locCol;
            if(newLRow<1)
                return -1;
            newL=newLRow*10 + newLCol;

        }
        if(d=='D')
        {
            newLRow=locRow+1;
            newLCol=locCol;
            if( newLRow>9)
                return -1;
            newL=newLRow*10 + newLCol;

        }
        if(d=='L')
        {
            newLRow=locRow;
            newLCol=locCol+1;
            if(newLCol>9)
                return -1;
            newL=newLRow*10 + newLCol;

        }
        if(d=='R')
        {
            newLRow=locRow;
            newLCol=locCol-1;
            if(newLCol<1)
                return -1;
            newL=newLRow*10 + newLCol;

        }
        return newL;
    }

    void display()
    {
        int counter=1;
        cout<<"   ";
        for(int i=1; i<=8; i++)
            cout<<i<<" ";
        cout<<"\n";
        cout<<" +";
        for(int i=1; i<=9; i++)
            cout<<"-+";
        cout<<"\n";
        for(int i=0; i<9; i++)
        {
            cout<<" |";
            for(int c=0; c<9; c++)
            {
                cout<<board[i][c];
                if(c!=8 && i!=8)
                {
                    if(VWalls[i][c])
                        cout<<"|";
                    else
                        cout<<" ";
                }
                else if(i==8 && c!=8)
                    cout<<" ";
            }
            cout<<"|\n";
            if(i!=8)
            {
                cout<<counter<<"|";
                counter++;
                for(int c=0; c<8; c++)
                {
                    if(HWalls[i][c])
                        cout<<"-";
                    else
                        cout<<" ";
                    cout<<"+";
                }
                cout<<" |\n";
            }
        }
        cout<<" +";
        for(int i=1; i<=9; i++)
            cout<<"-+";
        cout<<"\n";
    }

    bool isGameOver()
    {
        if(locG/10 == 9)
        {
            winner='G';
            return true;
        }
        else if(locB%10 == 9)
        {
            winner='B';
            return true;
        }
        else if(locR/10 == 1)
        {
            winner='R';
            return true;
        }
        else if(locW%10 == 1)
        {
            winner='W';
            return true;
        }
        else if(!limitedMovesB && !limitedMovesG && !limitedMovesR && !limitedMovesW)
            return true;
        else
            return false;
    }

    void getWinner()
    {
        if(winner=='N')
            cout<<"TIE";
        else
            cout<<winner;
    }

    bool validWall()
    {
        if(player=='G')
        {
            if(WallsLeftG==0)
                return false;
            return true;
        }
        if(player=='R')
        {
            if(WallsLeftR==0)
                return false;
            return true;
        }
        if(player=='B')
        {
            if(WallsLeftB==0)
                return false;
            return true;
        }
        if(player=='W')
        {
            if(WallsLeftW==0)
                return false;
            return true;
        }
    }

    bool setWall(int loc, char state)
    {
        int row=loc/10-1;
        int col=loc%10-1;
        if(state=='H')
        {
            if(HWalls[row][col])
                return false;
            else
            {
                HWalls[row][col]=true;
                return true;
            }
        }
        else
        {
            if(VWalls[row][col])
                return false;
            else
            {
                VWalls[row][col]=true;
                return true;
            }
        }
    }

    void changePlayer()
    {
        if(player=='G')
            player='R';
        else if(player=='W')
            player='B';
        else if(player=='R')
            player='W';
        else
            player='G';
    }

    void startMenu()
    {
        int decision;
        cout<<"1->Start Game\n2->Exit\n";
        cin>>decision;
        if(decision==2)
            exit(1);
    }

    void getPlayer()
    {
        cout<<player<<endl;
    }
};
int main()
{
    int choice;
    game newGame;
    newGame.startMenu();
    cout<<"enter the mode: 1->Limited moves\t2->Unlimited Moves : ";
    int m;
    cin>>m;
    if(m==1)
        newGame.mode="Limited";
    system("cls");
    while(newGame.isGameOver()==false)
    {
        newGame.display();
        cout<<"\n\n";
        cout<<"player: ";
        newGame.getPlayer();
        cout<<"1->Add Wall\n2->Move\n3->Exit To Menu :";
        cin>>choice;
        if(choice==3)
            newGame.startMenu();
        else if(choice==1)
        {
            if(newGame.validWall()==false)
            {
                cout<<"you cant add a wall\n";
                continue;
            }
            else
            {
                cout<<"Enter your wall place and Type of wall placement (start-x start-y H/ V): ";
                int wallocr, wallocc, walloc;
                cin>>wallocr;
                cin>>wallocc;
                walloc=wallocr*10 + wallocc;
                char state;
                cin>>state;
                newGame.setWall(walloc, state);
                newGame.changePlayer();

            }
        }
        else
        {
            cout<<"enter your direction:\n U->up D->Down R->Right L->Left\n";
            char d;
            cin>>d;
            newGame.setPlayerDirection(d);
            if(newGame.validMove(newGame.findNewLocation())==false)
            {
                cout<<"unvalid move\n";
                continue;
            }
            else
            {
                newGame.moveTo(newGame.findNewLocation());
            }
        }
    }
    newGame.getWinner();
    return 0;
}
