

#include<iostream>
#include<conio.h>
#include <stdlib.h>
#include<time.h>
#include<windows.h>

#define width 50
#define height 22

#define user_bullet 30
#define cpu_bullet 31
#define wall 219
#define user 'U'
#define cpu 'C'

#define max_bullets  18;//height-4;
using namespace std;

char grid[height][width]= {' '};
bool gameflag=true;
int chealth=10;
int uhealth=10;
int upos=width/2;
int cpos=width/2;
int timecount=0;
int userBulletCount=20;
int reloadingTime=0;

int ubcount=0,cbcount=0;
char input;

///Define Struct to store bullet positions
struct bullet
{
    int x=-1;
    int y=-1;
};

bullet  ubullets[18];
bullet cbullets[18];

void initArena()
{

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            grid[i][j]=' ';
        }
    }


    for(int i=0; i<width; i++)
    {
        grid[0][i] = grid[height-1][i] = wall;
    }
    for(int i=1; i<height-1; i++)
    {
        grid[i][0] = grid[i][width-1] = wall;
    }
    grid[1][cpos] = cpu;
    grid[height-2][upos] = user;
}

void printScore()
{
    cout<< "Computer: " <<chealth<<"\tUser: "<<uhealth<<"\tBullets: ";

    if(userBulletCount==0)
        cout<<"Reloading"<<endl;
    else
        cout<<userBulletCount<<endl;
}

void printArena()
{
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            cout<<grid[i][j];
        }
        cout<<endl;
    }
}

void printScreen()
{
    system("cls");
    printScore();
    printArena();
}

void delay(int iLim,int jLim)
{
    int i,j;
    for(i=0; i<iLim; i++)
    {
        for(j=0; j<jLim; j++)
        {
            //DO NOTHING;
        }
    }
}

void printGameOver()
{
    grid[height/2][width/2-2]='G';
    printScreen();
    delay(5000,5000);

    grid[height/2][width/2-1]='A';
    printScreen();
    delay(5000,5000);

    grid[height/2][width/2]='M';
    printScreen();
    delay(5000,5000);

    grid[height/2][width/2+1]='E';
    printScreen();
    delay(5000,5000);

    grid[height/2+1][width/2-2]='O';
    printScreen();
    delay(5000,5000);

    grid[height/2+1][width/2-1]='V';
    printScreen();
    delay(5000,5000);

    grid[height/2+1][width/2]='E';
    printScreen();
    delay(5000,5000);

    grid[height/2+1][width/2+1]='R';
    printScreen();
    delay(5000,5000);

    grid[height/2+2][width/2-4]='Y';
    printScreen();
    delay(5000,5000);

    grid[height/2+2][width/2-3]='O';
    printScreen();
    delay(5000,5000);

    grid[height/2+2][width/2-2]='U';
    printScreen();
    delay(5000,5000);


    if(chealth==0)
    {
        grid[height/2+2][width/2]='W';
        printScreen();
        delay(5000,5000);

        grid[height/2+2][width/2+1]='O';
        printScreen();
        delay(5000,5000);

        grid[height/2+2][width/2+2]='N';
        printScreen();
        delay(5000,5000);

        grid[height/2+2][width/2+3]='!';
        printScreen();
        delay(5000,5000);

    }
    else
    {
        grid[height/2+2][width/2]='L';
        printScreen();
        delay(5000,5000);

        grid[height/2+2][width/2+1]='O';
        printScreen();
        delay(5000,5000);

        grid[height/2+2][width/2+2]='S';
        printScreen();
        delay(5000,5000);

        grid[height/2+2][width/2+3]='T';
        printScreen();
        delay(5000,5000);
    }

}
void moveCpuBot(){

    ///Smart CPU controls
    if(timecount%3==0)
    {
        if(cpos>upos)            ///moves left
        {
            grid[1][cpos]=' ';
            cpos=cpos-1;
            grid[1][cpos]=cpu;
        }
        else if(cpos<upos)       ///moves right
        {
            grid[1][cpos]=' ';
            cpos=cpos+1;
            grid[1][cpos]=cpu;
        }
        if( abs(cpos-upos)<3 )
        {
            grid[2][cpos]=cpu_bullet;
            if(cbcount>=18)
            {
                cbcount=0;
            }
            cbullets[cbcount].x=cpos;
            cbullets[cbcount].y=2;
            cbcount++;
        }
    }
}

void moveCpuBullets(){

    ///Move CPU bullets

        for(int k=0;k<18;k++)
        {
            if(cbullets[k].y<height-2 && grid[cbullets[k].y+1][cbullets[k].x]==' ')
            {
                grid[cbullets[k].y][cbullets[k].x]=' ';                ///moves the bullets forward
                grid[cbullets[k].y+1][cbullets[k].x]=cpu_bullet;
                cbullets[k].y++;
            }
            if(grid[cbullets[k].y+1][cbullets[k].x]==user_bullet)
            {
                grid[cbullets[k].y][cbullets[k].x]=' ';                      ///user bullets collision with CPU bullets
                grid[cbullets[k].y+1][cbullets[k].x]=' ';
                cbullets[k].x=-1;
                cbullets[k].y=-1;
            }
            if(grid[cbullets[k].y+1][cbullets[k].x]==user) ///bullet hits user
            {
                uhealth--;
                grid[cbullets[k].y][cbullets[k].x]=' ';
                cbullets[k].x=-1;
                cbullets[k].y=-1;

                if(uhealth==0)  ///user dies
                    gameflag=false;
            }
            if( cbullets[k].y==height-2)
                {
                    grid[cbullets[k].y][cbullets[k].x]=' ';                 ///bullets collision with wall
                    cbullets[k].x=-1;
                    cbullets[k].y=-1;
                }
            }
}

void moveUserBullets(){

    ///Move User bullets

        for(int k=0; k<18; k++)
        {
            if(ubullets[k].y>1 && grid[ubullets[k].y-1][ubullets[k].x]==' ' )
            {
                grid[ubullets[k].y][ubullets[k].x]=' ';
                grid[ubullets[k].y-1][ubullets[k].x]=user_bullet;
                ubullets[k].y--;             ///moves the user bullets forward
            }
            if( grid[ubullets[k].y-1][ubullets[k].x]==cpu_bullet)
            {
                grid[ubullets[k].y][ubullets[k].x]=' ';                      ///user bullets collision with CPU bullets
                grid[ubullets[k].y-1][ubullets[k].x]=' ';
                ubullets[k].y=ubullets[k].x=-1;
            }
            if(grid[ubullets[k].y-1][ubullets[k].x]==cpu) ///bullet hits CPU
            {
                chealth--;
                grid[ubullets[k].y][ubullets[k].x]=' ';
                ubullets[k].y=ubullets[k].x=-1;

                if(chealth==0)  ///CPU dies
                    gameflag=false;
            }
            if(ubullets[k].y==1) ///user bullets collision with wall
            {
                grid[ubullets[k].y][ubullets[k].x]=' ';
                ubullets[k].y=ubullets[k].x=-1;
            }
        }

}

int main()
{
    initArena();
    while(gameflag)
    {

        ///responsive input
        if(kbhit())
        {
            input = getch();
            if(input==27)
            {
                gameflag==false;
            }
            else if(input=='a')
            {
                if(upos>1)
                {
                    grid[height-2][upos]=' ';
                    upos=upos-1;
                    grid[height-2][upos]=user;
                }
            }
            else if(input =='d')
            {
                if(upos<width-3)
                {
                    grid[height-2][upos]=' ';
                    upos=upos+1;
                    grid[height-2][upos]=user;
                }

            }
            if(input=='w')
            {
                if(userBulletCount>0)
                {
                    if(ubcount>=18)
                    {
                         ubcount=0;

                    }
                        grid[height-3][upos]=user_bullet;
                        ubullets[ubcount].x=upos;
                        ubullets[ubcount].y=height-3;
                        ubcount++;
                        userBulletCount--;
                }
            }
        }


        ///check bullet count
        if(userBulletCount==0)
        {
            reloadingTime++;
            if(reloadingTime%30==0)
                userBulletCount=30;
        }

        moveCpuBot();

        moveCpuBullets();

        moveUserBullets();

        delay(1000,100);
        printScreen();
        timecount++;
    }
    printGameOver();
    getch();
    return 0;
}


