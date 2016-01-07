#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <ctime>
#include <fstream>
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESCAPE 27
using namespace std;
void coutc(int, char*);
void borders();
void gameOver();
void food();
void gotoxy(int ,int);
COORD cOnv(int, int);
int exfood();///kant void
void step(char, bool &);
bool checkSnake(int, int);
void snakeLogo();
void menu(bool &);    ///
void about(bool &);
void GameSpeed(bool &);
void GameMode(bool &);
int exscoreval(long long);
void drawBords();
void position_of_snake();
int sFile = 0;
char pName[15];
char name[30];
const int width = 79, height = 20;
int xh, yh, xt, yt, gameMode,count1=1,x,count2=10;
int food_x, food_y, exfood_x, exfood_y, exfoodFlag, foodCount, score, prevdir,prevdev,i,X,Y;
double speed=5;
long long exscore=0;
vector<COORD> snake(3);
vector<COORD> bords(0);
pair<int,string> Names[10000];

int main()
{

    system("TITLE Snake -New Way Team");
    char rep;
    do
    {
        speed=5;
        prevdev=-1;
        system("CLS");
        prevdir = RIGHT;
        snake.resize(3);
        exfoodFlag = 0;
        foodCount=0;
        score=0;
        bool eXit = true;
        menu(eXit);

        if(!eXit)
        {
            return 0;
        }

        for (int x=0; x<80; x++)
        {
            gotoxy(x,20);
            coutc(15,".");
        }
        for(unsigned int i=0; i<snake.size(); i++)
        {
            gotoxy(snake[i].X, snake[i].Y);
            coutc(10, "*");
        }

        while(true)
        {


            if(kbhit())
            {
                char c = getch();
                if(c == prevdir)
                {
                    continue;
                }
                step(c, eXit);

            }
            else
            {
                _sleep(150-(speed*10));
                step(prevdir, eXit);

            }
            if(!eXit)
            {
                break;
            }
        }
        gotoxy(32, 12);
        cout << "Would You Like To Repeat Again ? (Y/N)";
        while((rep = getch()))
        {
            if(rep == 'Y' || rep == 'y')
            {
                break;
            }
            else if(rep == 'N' || rep == 'n')
            {
                break;
            }
        }
    }
    while(rep == 'Y' || rep == 'y');
    return 0;
}

COORD cOnv(int x, int y)
{
    COORD temp;
    temp.X = x;
    temp.Y = y;

    return temp;
}

void step(char c, bool &eXit)
{
    borders();
    xt = snake[snake.size() - 1].X;
    yt = snake[snake.size() - 1].Y;
    xh = snake[0].X;
    yh = snake[0].Y;

    if(foodCount % 9 == 0 && exfoodFlag == 0 && foodCount != 0 && exscore == 0)
    {

        x=exfood();
        count1=1;
        count2=10;
        if(x==5)
        {
            if(xh == exfood_x && yh == exfood_y) ///kant xt&yt
            {
                gameOver();
                eXit=false;
            }
            if(count2<=1)
            {

                gotoxy(31,height+2);
                cout<<" ";
            }

        }

        else if(x==3&&xh == exfood_x && yh == exfood_y)
        {
            speed-=2;
        }
        if(x==2)
        {
            speed+=2;
        }
        exscore = 2700000000000000000;
        exfoodFlag = 1;
    }
    if(exscore > 2)
    {
        exscore /= 2;///code el time ma7tot hna

        if(count1%6==0)
        {
            count1++;
            gotoxy(31,height+2);
            cout<<"  ";
            gotoxy(31,height+2);
            cout<<count2--;
        }
        else
        {
            count1++;
        }
    }
    if(count2<=0)
    {
        gotoxy(31,height+2);
        cout<<" ";
    }

    if(xh == exfood_x && yh == exfood_y)
    {
        gotoxy(31,height+2);
        cout<<" ";
        ///speed++;
        _sleep(150-(speed*10));
        if(x==1)
        {
            score += exscoreval(exscore);
            gotoxy(15, 21);
            cout << score;
        }
        exfoodFlag = 2;
        exscore = 0;
        exfood_x = 0;
        exfood_y = 0;
    }
    else if(exscore <= 2 && exfoodFlag == 1)
    {
        gotoxy(exfood_x, exfood_y);
        cout << " ";
        exfoodFlag = 2;
        exscore = 0;
        exfood_x = 0;
        exfood_y = 0;
        gotoxy(31,height+2);
        cout<<" ";
    }


    if(xh == food_x && yh == food_y)
    {
        if(speed<15)///
            speed+=0.5;
        if (speed/5==0)
        {
            _sleep(100-(speed*10));
        }
        food();
        cout <<"\7";
//        _sleep(150-(speed*10));
//		food();
        snake.insert(snake.begin(),cOnv(xh, yh));
        score += 100;
        foodCount++;
        gotoxy(15, height + 2);
        cout << score;

        if(exfoodFlag == 2)
        {
            exfoodFlag = 0;
        }

    }

    if((c == UP||c=='y')&&prevdir!=DOWN)
    {
        prevdir=UP;
        if(yh - 1 == 0)
        {
            gotoxy(xh, height - 1);
            coutc(10, "*");
            snake.insert(snake.begin(),cOnv(xh, height - 1));
            if(checkSnake(xh, height - 1))
            {
                gameOver();
                eXit = false;
            }

        }
        else
        {
            gotoxy(xh, yh - 1);
            coutc(10, "*");
            snake.insert(snake.begin(),cOnv(xh, yh - 1));
            if(checkSnake(xh, yh-1))
            {
                gameOver();
                eXit = false;
            }

        }
        gotoxy(xt, yt);
        cout << " ";
        snake.erase(snake.end()-1);

    }

    else if((c == DOWN||c=='n') && prevdir != UP)
    {
        prevdir = DOWN;

        if(yh + 1 == height)
        {
            gotoxy(xh, 1);
            coutc(10, "*");
            snake.insert(snake.begin(),cOnv(xh, 1));
            if(checkSnake(xh, 1))
            {
                gameOver();
                eXit = false;
            }

        }

        else
        {

            gotoxy(xh, yh + 1);
            coutc(10, "*");
            snake.insert(snake.begin(),cOnv(xh, yh + 1));
            if(checkSnake(xh, yh+1))
            {
                gameOver();
                eXit = false;
            }

        }

        ///--------
        gotoxy(xt, yt);
        cout << " ";
        snake.erase(snake.end()-1);
        ///---------
    }
    else if((c == LEFT ||c=='g') && prevdir != RIGHT)
    {
        prevdir = LEFT;

        if(xh - 1 == 0)
        {
            gotoxy(width -1, yh);
            coutc(10, "*");
            snake.insert(snake.begin(),cOnv(width - 1, yh));
            if(checkSnake(width - 1, yh))
            {
                gameOver();
                eXit = false;
            }
        }
        else
        {
            gotoxy(xh - 1, yh);
            coutc(10, "*");
            snake.insert(snake.begin(),cOnv(xh - 1, yh));
            if(checkSnake(xh-1, yh))
            {
                gameOver();
                eXit = false;
            }
        }

        gotoxy(xt, yt);
        cout << " ";
        snake.erase(snake.end()-1);
    }
    else if((c == RIGHT ||c=='j') && prevdir != LEFT)
    {
        prevdir = RIGHT;

        if(xh + 1 == width)
        {
            gotoxy(1, yh);
            coutc(10, "*");
            snake.insert(snake.begin(),cOnv(1, yh));
            if(checkSnake(1, yh))
            {
                gameOver();
                eXit = false;
            }
        }
        else
        {
            gotoxy(xh + 1, yh);
            coutc(10, "*");
            snake.insert(snake.begin(),cOnv(xh + 1, yh));
            if(checkSnake(xh+1, yh))
            {
                gameOver();
                eXit = false;
            }
        }

        gotoxy(xt, yt);
        cout << " ";
        snake.erase(snake.end()-1);
    }
    else if(c == ESCAPE)
    {
        gotoxy(width - 10, height + 2);
        system("PAUSE > NUL | echo Pause !!");
        gotoxy(width - 10, height + 2);
        cout << "\t\t";
    }



}

void gotoxy(int x, int y)
{
    COORD cursorPlace;
    cursorPlace.X = x;
    cursorPlace.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPlace);
}


void food()
{
    // 3ayzeen nehandle beta3et el te3ban (food)
    while(true)
    {

        srand (time(NULL));
        food_x = rand() % (width - 1) + 1;
        food_y = rand() % (height - 1) + 1;
        for(int i=0; i<snake.size(); i++)
        {
            if((snake[i].X == food_x && snake[i].Y == food_y) || (exfood_x == food_x && exfood_y == food_y))
            {
                food_x = rand() % (width - 1) + 1;
                food_y = rand() % (height - 1) + 1;
            }
        }
        if(bords.size() > 0)
        {
            for(int i=0; i<bords.size(); i++)
            {
                if((bords[i].X == food_x && bords[i].Y == food_y))
                {
                    food_x = rand() % (width - 1) + 1;
                    food_y = rand() % (height - 1) + 1;
                }
            }
        }
        gotoxy(food_x, food_y);
        coutc(12, "\3");
        break;
    }
}


int exfood() ///kant void
{
    // 3ayzeen nehandle beta3et el te3ban (food)
    char* arr[5] = {"\1", "\2", "\4", "\5", "x"};
    int x;
    while(true)
    {
        srand (time(NULL) + time(NULL));
        exfood_x = rand() % (width - 1) + 1;
        exfood_y = rand() % (height - 1) + 1;
        for(int i=0; i<snake.size(); i++)
        {
            if(snake[i].X == exfood_x && snake[i].Y == exfood_y)
            {
                exfood_x = rand() % (width - 1) + 1;
                exfood_y = rand() % (height - 1) + 1;
            }
        }
        if(bords.size() > 0)
        {
            for(int i=0; i<bords.size(); i++)
            {
                if((bords[i].X == exfood_x && bords[i].Y == exfood_y))
                {
                    exfood_x = rand() % (width - 1) + 1;
                    exfood_y = rand() % (height - 1) + 1;
                }
            }
        }
        X=exfood_x;
        Y=exfood_y;
        gotoxy(exfood_x, exfood_y);
        x = (exfood_x + exfood_y) % 5;
        if(arr[x]=="\1" ||arr[x]=="\2")
        {
            coutc(10, arr[x]);///
            return 1;
        }

        else if(arr[x]=="\4"||arr[x]=="\5") ///
        {
            coutc(9,arr[x]);
            return 3;
        }
        else if(arr[x]=="x") ///
        {
            coutc(12, arr[x]);
            return 5;
        }
        else if(arr[x]=="\5") ///
        {
            coutc(13,arr[x]);
            return 2;
        }



        break;
    }

}
void gameOver()
{

    system("CLS");
    cout << "     *********             *****         ******       ******   ***************\n";
    _sleep(200);
    cout << "   *           *          *     *        *     *     *     *   *             *\n";
    _sleep(250);
    cout << "   *     ***    *        *   *   *       *      *   *      *   *    **********\n";
    _sleep(250);
    cout << "   *   *     *  *       *   * *   *      *       * *       *   *    *\n";
    _sleep(250);

    cout << "   *   *     ****      *   *   *   *     *        *        *   *    **********\n";
    _sleep(200);
    cout << "   *   *              *   *******   *    *                 *   *             *\n";
    _sleep(100);
    cout << "   *   *             *               *   *    *       *    *   *             *\n";
    _sleep(100);

    cout << "   *   *   *******   *    *******    *   *    * *   * *    *   *    **********\n";
    _sleep(100);
    cout << "   *   *    *   *    *    *     *    *   *    *   *   *    *   *    *\n";
    _sleep(100);
    cout << "   *     **     *    *    *     *    *   *    *       *    *   *    **********\n";
    _sleep(100);
    cout << "   *           *     *    *     *    *   *    *       *    *   *             *\n";
    _sleep(100);
    cout << "     * ********      ******     ******   ******       ******   ***************\n";
    _sleep(100);
    cout << "\n";
    _sleep(100);
    cout << "       ****       *****         *****   ***************      ********* \n";
    _sleep(100);
    cout << "     *      *     *   *         *   *   *             *    *           *\n";
    _sleep(100);
    cout << "    *  ****  *    *   *         *   *   *    **********   *    *****    *\n";
    _sleep(100);
    cout << "   *  *    *  *   *   *         *   *   *    *            *   *     *   *\n";
    _sleep(100);
    cout << "   *  *    *  *   *   *         *   *   *    **********   *    *****   *\n";
    _sleep(100);
    cout << "   *  *    *  *   *   *         *   *   *             *   *           *\n";
    _sleep(100);
    cout << "   *  *    *  *   *    *       *    *   *             *   *   * *   *\n";
    _sleep(100);
    cout << "   *  *    *  *    *    *     *    *    *    **********   *   *   *   *\n";
    _sleep(100);
    cout << "   *  *    *  *     *    *****    *     *    *            *   *    *   *\n";
    _sleep(100);
    cout << "    *  ****  *       *           *      *    **********   *   *     *   *\n";
    _sleep(100);
    cout << "     *      *         *         *       *             *   *   *      *   *\n";
    _sleep(100);
    cout << "       ****             *******         ***************   *****       *****";

    PlaySound("game-over-sound-effects---fx-11676086-sound-fx_cutted.WAV", NULL, SND_FILENAME );

    gotoxy(0, 12);
    coutc(12, "\tYour score is : ");
    cout << score;
    _sleep(1000);
    fstream file ;
    file.open("PlayerName.txt",ios::in|ios::out);
    file.seekg(0,ios::end);
    file<<name<<"|"<<score;
    file.close();

}

void position_of_snake()
{
    prevdir=RIGHT;

    for(int i=0,x=snake.size()-1; i<snake.size(); i++,x--)
    {
        snake[i].X=x;
        snake[i].Y=height/2;
    }
}

void borders()
{

    int recentdev=score/100;
    if(recentdev!=prevdev)
    {
        position_of_snake();
        if(score/100==0)
        {

            gotoxy(70,21);
            coutc(9,"Level 1");

            ///S--------
            for (int i=0; i<height; i++)
            {
                gotoxy(0,i);
                coutc(14,"S");
                gotoxy(width,i);
                cout<<"S";
            }
            for (int i=1; i<width; i++)
            {
                gotoxy(i,0);
                cout<<"S"<<endl;
            }
            bords.clear();
            i=0;
            bords.resize(100);
            gotoxy(1,21);
            coutc(9,"Your score is: ");
            gotoxy(15,21);
            cout<<score;
///el5t elly fo2
            for(int x=30; x<50; x++)
            {
                gotoxy(x,3);
                coutc(15,"#");
                bords[i++]=cOnv(x,3);
            }
///el 5at elly fe elgnb
            for(int y=4; y<10; y++)
            {
                gotoxy(29,y);
                coutc(15,"#");
                if(y==6||y==7)
                {
                    gotoxy(29,y);
                    coutc(15," ");
                }
                else
                    bords[i++]=cOnv(29,y);
            }
///el 5at elly fe el nos
            for(int x=30; x<50; x++)
            {
                gotoxy(x,10);
                coutc(15,"#");
                bords[i++]=cOnv(x,10);
            }
///el 5at elly 3la el yemen
            for(int y=11; y<17; y++)
            {
                gotoxy(50,y);
                coutc(15,"#");
                if(y==13||y==14)
                {
                    gotoxy(50,y);
                    coutc(15," ");
                }
                else
                    bords[i++]=cOnv(50,y);
            }
///el 5at elly t7t
            for(int x=50; x>29; x--)
            {
                gotoxy(x,17);
                coutc(15,"#");
                bords[i++]=cOnv(x,17);
            }

        }

        else if(score/100==1)
        {


            ///N

            system("cls");
            for (int i=0; i<height; i++)
            {
                gotoxy(0,i);
                coutc(14,"N");
                gotoxy(width,i);
                cout<<"N";
            }
            for (int i=1; i<width; i++)
            {
                gotoxy(i,0);
                cout<<"N"<<endl;

            }

            for (int x=0; x<80; x++)
            {
                gotoxy(x,20);
                coutc(15,".");
            }
            gotoxy(70,21);
            coutc(9,"Level 2");
            bords.clear();
            i=0;
            bords.resize(100);
            gotoxy(1,21);
            coutc(9,"Your score is:");
            gotoxy(15,21);
            cout<<score;
///el5at el straight elly fo2
            for(int x=30; x<=34; x++)
            {
                gotoxy(x,3);
                coutc(15,"#");
                bords[i++]=cOnv(x,30);
            }
            ///el 3amod
            for(int y=4; y<18; y++)
            {
                gotoxy(29,y);
                coutc(15,"#");
                if(y==8||y==9||y==10)
                {
                    gotoxy(29,y);
                    cout<<" ";
                }
                else
                {
                    bords[i++]=cOnv(29,y);
                }
            }
///el 5at el ma3oog
            for(int x=35,y=4; y<17; y++,x++)
            {
                gotoxy(x,y);
                coutc(15,"#");
                if(y==8||y==9||y==10&&x==40||x==41||x==42)
                {
                    gotoxy(x,y);
                    cout<<" ";
                }
                else
                    bords[i++]=cOnv(x,y);
            }
///el5at el straight elly t7t
            for(int x=48; x<=52; x++)
            {
                gotoxy(x,17);
                coutc(15,"#");
                bords[i++]=cOnv(x,17);

            }
///el 3amod el yemen
            for(int y=16; y>=3; y--)
            {
                gotoxy(53,y);
                coutc(15,"#");
                if(y==8||y==9||y==10)
                {
                    gotoxy(53,y);
                    cout<<" ";
                }
                else
                    bords[i++]=cOnv(53,y);
            }

        }
        else if(score/100==2)
        {


            ///A
            i=0;
            system("cls");
            for (int i=0; i<height; i++)
            {
                gotoxy(0,i);
                coutc(14,"A");
                gotoxy(width,i);
                cout<<"A";
            }
            for (int i=1; i<width; i++)
            {
                gotoxy(i,0);
                cout<<"A"<<endl;

            }

            for (int x=0; x<80; x++)
            {
                gotoxy(x,20);
                coutc(15,".");
            }
            gotoxy(70,21);
            coutc(9,"Level 3");
            bords.clear();
            bords.resize(100);
            gotoxy(1,21);
            coutc(9,"Your score is:");
            gotoxy(15,21);
            cout<<score;
            ///deh el dot ely fe el nos
            gotoxy(40,2);
            coutc(15,"#");
            ///dah sater el yemen
            for(int x=39,y=2; y<=20; x--,y++)
            {
                if(y==14||y==13||y==11||y==10)
                {
                    gotoxy(x,y);
                    cout<<" ";
                }
                else
                {
                    gotoxy(x,y);
                    coutc(15,"#");
                    bords[i++]=cOnv(x,y);

                }
            }
///dah el line ely 3la el shmal
            for(int x=41,y=2; y<=20; x++,y++)
            {
                if(y==14||y==13||y==11||y==10)
                {
                    gotoxy(x,y);
                    cout<<" ";
                }

                else
                {
                    gotoxy(x,y);
                    coutc(15,"#");
                    bords[i++]=cOnv(x,y);
                }
            }
///dah ely fe el nos
            for(int x=33; x<49; x++)
            {
                gotoxy(x,12);
                coutc(15,"#");
                bords[i++]=cOnv(x,12);
            }

        }
        else if(score/100==3)
        {

/// K

            i=0;
            system("cls");
            for (int i=0; i<height; i++)
            {
                gotoxy(0,i);
                coutc(14,"K");
                gotoxy(width,i);
                cout<<"K";
            }
            for (int i=1; i<width; i++)
            {
                gotoxy(i,0);
                cout<<"K"<<endl;

            }

            for (int x=0; x<80; x++)
            {
                gotoxy(x,20);
                coutc(15,".");
            }
            gotoxy(70,21);
            coutc(9,"Level 4");
            bords.clear();
            bords.resize(100);
            gotoxy(1,21);
            coutc(9,"Your score is: ");
            gotoxy(15,21);
            cout<<score;
            ///el 3amod
            for(int y=3; y<=18; y++)
            {
                gotoxy(29,y);
                coutc(15,"#");
                if(y==5||y==6||y==15||y==14)
                {
                    gotoxy(29,y);
                    coutc(15," ");
                }
                else
                    bords[i++]=cOnv(29,y);
            }
///el 5at el mayel elly fo2
            for(int x=31,y=9; y>=3; y--,x+=2)
            {
                gotoxy(x,y);
                coutc(15,"#");
                bords[i++]=cOnv(x,y);
            }

///el 5at el mayel elly t7t
            for(int x=30,y=10; y<=18; y++,x+=2)
            {
                gotoxy(x,y);
                coutc(15,"#");
                bords[i++]=cOnv(x,y);
            }


        }
        if(score/100==4)
        {


            ///E
            system("cls");
            for (int i=0; i<height; i++)
            {
                gotoxy(0,i);
                coutc(14,"E");
                gotoxy(width,i);
                cout<<"E";
            }
            for (int i=1; i<width; i++)
            {
                gotoxy(i,0);
                cout<<"E"<<endl;

            }

            for (int x=0; x<80; x++)
            {
                gotoxy(x,20);
                coutc(15,".");
            }
            gotoxy(70,21);
            coutc(9,"Level 5");
            bords.clear();
            i=0;
            bords.resize(100);
            gotoxy(1,21);
            coutc(9,"Your score is: ");
            gotoxy(15,21);
            cout<<score;
            for(int x=29; x<45; x++)
            {
                gotoxy(x,3);
                coutc(15,"#");
                bords[i++]=cOnv(x,3);
            }
///dah fe el nos
            for(int x=29; x<=45; x++)
            {
                gotoxy(x,11);
                coutc(15,"#");
                bords[i++]=cOnv(x,11);
            }
///dah el 3amod
            for(int y=3; y<20; y++)
            {
                gotoxy(29,y);
                coutc(15,"#");
                if(y==7||y==6||y==8||y==17||y==15||y==16)
                {
                    gotoxy(29,y);
                    cout<<" ";
                }
                else
                    bords[i++]=cOnv(29,y);

            }
///da elly t7t
            for(int x=29; x<=45; x++)
            {
                gotoxy(x,20);
                coutc(15,"#");
                bords[i++]=cOnv(x,20);
            }
        }
        else if(score/100==5)
        {
            system("cls");
            bords.clear();

            coutc(14," ##############################################################################\n");
            coutc(14,".                                                                             .\n");
            coutc(14,".                                                                             .\n");
            coutc(14,".*           *  * *     *       *       *         *  *****  *         *       .\n");
            coutc(14,". *         *  *   *    *       *       *         *    *    **        *       .\n");
            coutc(14,".  *       *  *     *   *       *       *         *    *    * *       *       .\n");
            coutc(14,".   *     *  *       *  *       *       *         *    *    *  *      *       .\n");
            coutc(14,".    *   *  *         * *       *       *         *    *    *   *     *       .\n");
            coutc(14,".     * *   *         * *       *       *    *    *    *    *    *    *       .\n");
            coutc(14,".      *    *         * *       *       *   * *   *    *    *     *   *       .\n");
            coutc(14,".      *     *       *  *       *       *  *   *  *    *    *      *  *       .\n");
            coutc(14,".      *      *     *   *       *       * *     * *    *    *       * *       .\n");
            coutc(14,".      *       *   *    *       *       **       **    *    *        **       .\n");
            coutc(14,".      *        * *      * * * *  *     *         *  *****  *         *       .\n");
            coutc(14,".                                                                             .\n");
            coutc(14,".                                                                             .\n");
            coutc(14," ##############################################################################\n");
            PlaySound("win-game-sound---big-rewards---gift-coin-level-up-mission-complete-power-up-sound-effects---fx-46565918-sound-fx_cutted.WAV", NULL, SND_FILENAME );
            return ;

        }

        food();
    }
    prevdev=score/100;

}

bool checkSnake(int x, int y)
{

    for(int i=1; i<snake.size(); i++)
    {
        if (snake[i].X==x && snake[i].Y==y)
        {


            return true;
        }
    }
    if(bords.size() > 0)
    {
        for(int i=0; i<bords.size()-1; i++)
        {
            if (bords[i].X==snake[0].X && bords[i].Y==snake[0].Y)
            {
                return true;
            }
        }
    }
    return false;
}

void coutc(int color, char* output)
{
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( handle, color);
    cout<< output;
    SetConsoleTextAttribute( handle, color);
}

void snakeLogo()
{
//    coutc(15, " ##############################################################################\n");
//    coutc(15,"                                                                              \n");
//    coutc(15,"         ****      *         *           *           *     *     *********    \n");
//    coutc(15,"       *      *    * *       *          * *          *    *      *            \n");
//    coutc(15,"       *      *    *  *      *         *   *         *   *       *            \n");
//    coutc(15,"        *          *   *     *        *     *        *  *        *            \n");
//    coutc(15,"          *        *    *    *       *********       *  *        ******       \n");
//    coutc(15,"            *      *     *   *      *         *      *   *       *            \n");
//    coutc(15,"      *      *     *      *  *     *           *     *    *      *            \n");
//    coutc(15,"      *      *     *       * *    *             *    *     *     *            \n");
//    coutc(15,"        ****       *         *   *               *   *      *    *********    \n");
//    coutc(15,"                                                                              \n");
//    coutc(15," ##############################################################################\n");


    coutc(14," ##############################################################################\n");
    coutc(10,"                                                                               \n");
    coutc(10,"                                                                               \n");
    coutc(10,"         ***               ***               ***                               \n");
    coutc(10,"       **   **           **   **           **   **              **             \n");
    coutc(10,"      ***   ***         ***   ***         ***   ***           *  o  *          \n");
    coutc(10,"     ***     ***       ***     ***       ***     ***      ***      | * -----   \n");
    coutc(10,"    ***       ***     ***       ***     ***       ***    ***  *  o  *          \n");
    coutc(10,"   ***         ***   ***         ***   ***         ***   ***    **             \n");
    coutc(10,"  ***             ***               ***               ***                      \n");
    coutc(10,"                                                                               \n");
    coutc(10,"                                                                               \n");
    coutc(14," ##############################################################################\n");





    PlaySound("Air-Up-Suck-Fast Tremolo-Snake-ish 2.WAV", NULL, SND_FILENAME );

    for(int i=0; i<13; i++)
    {
        gotoxy(0,i);
        coutc(14 ,"#");
        gotoxy(width,i);
        coutc(14,"#");
    }
}



void about(bool &eXit)
{

    char ch;
    coutc(3 , "###############################################################################\n");
    coutc(9 , "\n");
    coutc(9 , "   *       *      *******  *         *      *         *     **    *       *    \n");
    coutc(9 , "   **      *      *        *         *      *         *    *  *    *     *     \n");
    coutc(9 , "   * *     *      *        *         *      *         *   *    *    *   *      \n");
    coutc(9 , "   *  *    *      *        *    *    *      *         *  *      *    * *       \n");
    coutc(9 , "   *   *   * Team *****    *   * *   *      *   * *   *  ********     *        \n");
    coutc(9 , "   *    *  *      *        *  *   *  *      *  *   *  *  *      *     *        \n");
    coutc(9 , "   *     * *      *        * *     * *      * *     * *  *      *     *        \n");
    coutc(9 , "   *      **      *        **       **      **       **  *      *     *        \n");
    coutc(9 , "   *       *      *******  *         *      *         *  *      *     *        \n");
    coutc(10 ," Thanks to EL E7SAN team \n  \n");
    coutc(9,"   \t\t\t\tTeam : (alphabetically)\n");
    coutc(11, "  Mohamed Ahmed \t\t\t\t1 - Bassent Morad \n");
    coutc(11, "  Mohamed Osama\t\t\t\t        2 - Hager Gamal \n");
    coutc(11, "  Mohamed Said    \t\t\t\t3 - Mai Ahmed \n");
    coutc(11, "  Hossam El Dein      \t\t\t\t4 - Taghreed Gamal\n");
    coutc(11, "                \t\t\t\t5 - Youmna Mansour                  \n");
    coutc(3, "###############################################################################\n");
    coutc(19, "\n");
    coutc(3, "       A lot of Thanks for EL_E7san Team and Resource Organization \n");

    PlaySound("win-game-sound---big-rewards---gift-coin-level-up-mission-complete-power-up-sound-effects---fx-46565918-sound-fx_cutted.WAV", NULL, SND_FILENAME );


    for(int i=0; i<18; i++)
    {
        gotoxy(0,i);
        coutc(3,"#");
        gotoxy(width,i);
        coutc(3,"#");
    }

    gotoxy(37, 22);
    cout << "\4 Back";
    gotoxy(0, 0);
    while((ch = getch()))
    {
        if(ch == ENTER || ch == ESCAPE)
        {
            system("CLS");
            menu(eXit);
            break;
        }
    }
}

int exscoreval(long long time)
{

    if(time >= 1 && time <= 392)
    {
        return speed * 2;
    }
    else if(time >= 785 && time <= 201165)
    {
        return speed * 3;
    }
    else if(time >= 402331 && time <= 102996826)
    {
        return speed * 4;
    }
    else if(time >= 205993652 && time <= 5273437500000)
    {
        return speed * 5;
    }
    else if(time >= 10546875000000 && time <= 2700000000000000000)
    {
        return speed * 6;
    }
    else
    {
        return 0;
    }
}

void HighScore(bool &eXit)
{
    //system("CLS");
    coutc(12,"                      High Score board            ");
    cout<<"\n\n";

    fstream file;
    file.open("PlayerName.txt", ios::in);
    //file.read((char*)&pName,sizeof(pName));
    int cnt=0;
    char a[30];
    int b;
    file.seekg(0,ios::beg);
    while(file.good())
    {
        file.getline(a,30,'|');
        for(int j=0; a[j]!='\0'; j++)
            Names[cnt].second+=a[j];
        file >> b;
        Names[cnt].first=b;
        cnt++;
    }

    sort(Names,Names+cnt);
    reverse(Names,Names+cnt);
//    for(int i=0; i<cnt-1; i++)
//    {
//        if(Names[i].second==Names[i+1].second)
//        {
//          sc = max(Names[i].first,Names[i].second);
//            for(int j=i; j<cnt; j++)
//            {
//                if(Names[j].second==name)
//                {
//                    score = max(Names[j].first,score);
//                    i++;
//                }
//                else break;
//            }
//        }
//        cout<<Names[i].second<<"     ";
//        coutc(8,"");
//        cout<< score <<endl;
//    }

    for(int i=0 ; i<cnt ; i++)
    {
        coutc(9," ");
        cout<<Names[i].second;
        coutc(8," ");
        cout<< Names[i].first<<endl;
    }
    char ch;
    while((ch = getch()))
    {
        if(ch == ENTER || ch == ESCAPE)
        {
            system("CLS");

            menu(eXit);
            break;
        }
    }
    file.close();
}
void HowToPlay(bool &eXit)
{

    coutc(3,"\n- Use UP, DOWN, LEFT, RIGHT Arrows to move Snake \n \n");
    coutc(5,"- Eat the food that appear to increase your score \n \n");
    coutc(3,"- If the extra food appear through the game, you should take it before time out \n\n ");
    coutc(5,"- In borders level ,avoid collide in the borders in order not to lose \n\n ");
    coutc(3,"- Press ESC to Pause the game \n\n");
    coutc(5,"- Avoid eating the ");
    coutc(12,"red");
    coutc(5," Extra_food or you will lose.  \n\n");
    coutc(3,"- The ");
    coutc(10,"Green ");
    coutc(3," Extra_Food will increase your score. \n\n");
    coutc(5,"- The ");
    coutc(9, "Blue ");
    coutc(5," Extra_Food will increase in your speed. \n\n");

    coutc(3,"- The ");
    coutc(13, "Bmbma Ms5s5 ");
    coutc(3," Extra_Food will decrease in your speed. \n\n");

    gotoxy(30, 20);
    cout << "\4 Back";
    gotoxy(0, 0);
    char ch;
    while((ch = getch()))
    {
        if(ch == ENTER || ch == ESCAPE)
        {
            system("CLS");
            menu(eXit);
            break;
        }
    }

}

void menu(bool &eXit)
{
    snakeLogo();
    gotoxy(37, 14 );
    coutc(2, " Main Menu " );
    gotoxy(33, 15);
    coutc(12, "Play Game");
    gotoxy(33, 16);
    coutc(12, "About");
    gotoxy(33, 17);
    coutc(12, "How To Play");
    gotoxy(33,18);
    coutc(12,"HighScore"); ///================> momkn n7ot el feature dy
    gotoxy(33,19);
    coutc(12,"Exit");
    coutc(2," ");

    char ch;
    int menop=1;
    gotoxy(31, 14+menop);
    cout << "\4";
    gotoxy(0, 0);
    while((ch = getch()))
    {
        if(ch == DOWN)
        {
            gotoxy(31, 14+menop);
            cout << " ";
//PlaySound("button-click-sound-effects-for-computer-or-interface-or-shutter-sound-effects---fx-53133335-sound-fx_cutted.WAV", NULL, SND_FILENAME );
            cout <<"\7";
            if(menop == 5)  menop = 1;
            else  menop++;

            gotoxy(31, 14+menop);
            cout << "\4";
            gotoxy(0, 0);
        }
        else if(ch == UP)
        {
            gotoxy(31, 14+menop);
            cout << " ";
//PlaySound("button-click-sound-effects-for-computer-or-interface-or-shutter-sound-effects---fx-53133335-sound-fx_cutted.WAV", NULL, SND_FILENAME );
            cout<<"\7";
            if(menop == 1) menop = 5;
            else menop--;

            gotoxy(31, 14+menop);
            cout << "\4";
            gotoxy(0, 0);
        }
        else if(ch == ENTER)
        {

            if(menop == 1)
            {
                system("CLS");
                cout<<"Enter your Name: " ;
                cin.getline(name,30);
                system("CLS");//  GameMode(eXit);
                GameSpeed(eXit);
                break;
            }
            else if(menop == 2)
            {
                system("CLS");
                about(eXit);
                break;
            }
            else if(menop == 3)
            {
                system("CLS");
                HowToPlay(eXit);
                break;
            }
            else if(menop == 4)
            {
                char name[10];
                system("CLS");

                HighScore(eXit);
                break;
            }
            else if(menop == 5)
            {
                eXit = false;
                break;
            }

        }
        else if(ch == ESCAPE)
        {
            eXit = false;
            break;
        }

    }
}
void GameSpeed(bool &eXit)
{

    snakeLogo();
    gotoxy(37, 10);
    coutc(10, "Game Mode");
    gotoxy(33, 14);
    coutc (10, "Easy");
    gotoxy(33, 15);
    coutc(10, "Medium");
    gotoxy(33, 16);
    coutc (10,"Hard");

    char ch;
    speed=1;
    gotoxy(31, 13+speed);
    coutc(15, "\4");
    gotoxy(0, 0);
    while((ch = getch()))
    {
        if(ch == DOWN)
        {
            gotoxy(31, 13+speed);
            cout << " ";
            cout<<"\7";
            //PlaySound("button-click-sound-effects-for-computer-or-interface-or-shutter-sound-effects---fx-53133335-sound-fx_cutted.WAV", NULL, SND_FILENAME );
            if(speed == 3)
            {
                speed = 1;
            }
            else
            {
                speed++;
            }
            gotoxy(31, 13+speed);
            coutc(15, "\4");
            gotoxy(0, 0);
        }
        else if(ch == UP)
        {
            gotoxy(31, 13+speed);
            cout << " ";
            cout <<"\7";
            //PlaySound("button-click-sound-effects-for-computer-or-interface-or-shutter-sound-effects---fx-53133335-sound-fx_cutted.WAV", NULL, SND_FILENAME );
            if(speed == 1)
            {
                speed = 3;
            }
            else
            {
                speed--;
            }
            gotoxy(31, 13+speed);
            coutc(15, "\4");
            gotoxy(0, 0);
        }
        else if(ch == ENTER)
        {
            if (speed==1) speed=5;
            else if(speed==2) speed=8;
            else if (speed==3) speed=12;
            system("CLS");
            break;
        }
        else if(ch == ESCAPE)
        {
            system("CLS");
            menu(eXit);
            break;
        }
    }

}
