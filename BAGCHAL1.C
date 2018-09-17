#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<dos.h>

void drawLine(int,int,int,int);	 //draws a line
void drawCircle(int,int,int,int);    //draws a circle
void drawGoat(int,int);    //draws goat
void drawTiger(int,int);   //draws tiger
void drawBoard(char[],int,int);    //draws Game Board
void checkPlace(int,int*);         //converts user input(11,22,43,etc) to actual pos (0-24)
void getCoord(int,int*,int*); //gets coordinate for tiger and goat to draw
int pathCheck(int,int); //Checks whether there exists a path between two coordinates
int goatWin(char[]);     //checks winning condition
void game();             //function for running the game
void displayGoatWin();   //display if goat wins
char* goatPlayerMove(int*,char[],int);
char* tigerPlayerMove(int,char[],int*);
char* goatBotMove(int*,char[],int);
char* tigerBotMove(int,char[],int*);
int convertToUserPos(int);   //converts actual pos to user input

const int path[25][25]={  {0,1,2,0,0,1,1,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
			  {1,0,1,2,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
			  {2,1,0,1,2,0,1,1,1,0,2,0,2,0,2,0,0,0,0,0,0,0,0,0,0},
			  {0,2,1,0,1,0,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},
			  {0,0,2,1,0,0,0,0,1,1,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0},
			  {1,0,0,0,0,0,1,2,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0,0,0},
			  {1,1,1,0,0,1,0,1,2,0,1,1,1,0,0,0,2,0,2,0,0,0,0,0,0},
			  {0,0,1,0,0,2,1,0,1,2,0,0,1,0,0,0,0,2,0,0,0,0,0,0,0},
			  {0,0,1,1,1,0,2,1,0,1,0,0,1,1,1,0,2,0,2,0,0,0,0,0,0},
			  {0,0,0,0,1,0,0,2,1,0,0,0,0,0,1,0,0,0,0,2,0,0,0,0,0},
			  {2,0,2,0,0,1,1,0,0,0,0,1,2,0,0,1,1,0,0,0,2,0,2,0,0},
			  {0,2,0,0,0,0,1,0,0,0,1,0,1,2,0,0,1,0,0,0,0,2,0,0,0},
			  {2,0,2,0,2,0,1,1,1,0,2,1,0,1,2,0,1,1,1,0,2,0,2,0,2},
			  {0,0,0,2,0,0,0,0,1,0,0,2,1,0,1,0,0,0,1,0,0,0,0,2,0},
			  {0,0,2,0,2,0,0,0,1,1,0,0,2,1,0,0,0,0,1,1,0,0,2,0,2},
			  {0,0,0,0,0,2,0,0,0,0,1,0,0,0,0,0,1,2,0,0,1,0,0,0,0},
			  {0,0,0,0,0,0,2,0,2,0,1,1,1,0,0,1,0,1,2,0,1,1,1,0,0},
			  {0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,2,1,0,1,2,0,0,1,0,0},
			  {0,0,0,0,0,0,2,0,2,0,0,0,1,1,1,0,2,1,0,1,0,0,1,1,1},
			  {0,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,2,1,0,0,0,0,0,1},
			  {0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,1,1,0,0,0,0,1,2,0,0},
			  {0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,0,1,0,1,2,0},
			  {0,0,0,0,0,0,0,0,0,0,2,0,2,0,2,0,1,1,1,0,2,1,0,1,2},
			  {0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,1,0,0,2,1,0,1},
			  {0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,1,1,0,0,2,1,0}};


void main()
{
   int gdriver = DETECT, gmode, errorcode;

   //initialize variables here :
   char play;

   initgraph(&gdriver, &gmode, "C:\\turboc3\\bgi");

   setbkcolor(BROWN);
   setcolor(BLUE);
   settextstyle(4,0,9);
   outtextxy(getmaxx()/2-280,getmaxy()/2-125,"BAGHCHAL");
   settextstyle(1,0,1);
   outtextxy(getmaxx()/2-300,getmaxy()/2+20,"(Press any key to continue!!)");
   getch();
   cleardevice();
   settextstyle(4,0,6);
   outtextxy(100,50,"INSTRUCTIONS");
   settextstyle(0,0,1);
   setcolor(WHITE);
   printf("\n\n\n\n\n\n\n\n\n\n1) Two player game - GOAT and TIGER.\n2) GOAT plays first\n3) There are 20 GOATS and 4 TIGERS\n4) TIGER moves one step, but when the GOAT is in middle TIGER can jump over if and only if there is empty space beside GOAT. Jumped over GOAT is out of the game.\n5) GOAT cannot be moved unless all 20 GOATS are placed on the board. GOATS only move one step. They cannot jump over.\n6) Moves should be input in array form such as \n\t11\t12\t13\t14\t15\n\t21\t22\t23\t24\t25\n\t31\t32\t33\t34\t35\n\t41\t42\t43\t44\t45\n\t51\t52\t53\t54\t55\n7) The game is over if TIGER eats 5 GOATS or each TIGER is trapped by the GOATS.");
   getch();
   cleardevice();
   setcolor(BLUE);
   settextstyle(0,0,1);
   game();

   while(1)
   {
	clrscr();
	cleardevice();
	printf("\n\n\t\t\t==============================");
	printf("\n\n\t\t\tPLAY AGAIN [y/n] ? \t");
	scanf("%s",&play);
	if(play=='n' || play=='N')
	{
		break;
	}
	else if(play=='y' || play=='Y')
	{
		settextstyle(0,0,1);
		game();
	}
   }

   exit(1);

}

int convertToUserPos(int arr)
{
	int pos,fd,sd;

	if(arr>=0 && arr<=4)
	{
		fd=1;
		sd=arr+1;
	} else if(arr>=5 && arr<=9)
	{
		fd=2;
		sd=arr-4;
	} else if(arr>=10 && arr<=14)
	{
		fd=3;
		sd=arr-9;
	} else if(arr>=15 && arr<=19)
	{
		fd=4;
		sd=arr-14;
	} else if(arr>=20 && arr<=24)
	{
		fd=5;
		sd=arr-19;
	}

	pos = fd*10 + sd;

	return pos;
}

char* tigerPlayerMove(int goatNo,char placeHolder[25],int* goatEaten)
{
	int afd,asd,bfd,bsd,c,csd,cfd,loc1,loc2,y,z,tigerSelect,tigerShift;

	while(1)
	{
	outtextxy(480,50,"Select tiger:");
	scanf("%d",&loc1);
	checkPlace(loc1,&tigerSelect);
	if(placeHolder[tigerSelect]=='T')
	{
		{
			outtextxy(480,70,"Postion to shift:");
			scanf("%d",&loc2);
			checkPlace(loc2,&tigerShift);
			z=pathCheck(loc1,loc2);

			if(z==1)
			{
				if(placeHolder[tigerShift]=='X')
				{

				placeHolder[tigerSelect]='X';
				placeHolder[tigerShift]='T';
				clrscr();
				cleardevice();
				drawBoard(placeHolder,goatNo,*goatEaten);
				break;
				}
				else
				{
				outtextxy(480,90,"There's something!!");
				getch();
				clrscr();
				cleardevice();
				drawBoard(placeHolder,goatNo,*goatEaten);
				}
			}
			else if(z==2)
			{
				afd=(int)loc1/10;
				asd=(int)loc1%10;
				bfd=(int)loc2/10;
				bsd=(int)loc2%10;

				if(afd==bfd)
				{
					cfd=afd;
					if(asd>bsd)
					{
						csd=asd-1;
					}
					else
					{
						csd=asd+1;
					}
				}
				else if(asd==bsd)
				{
					csd=asd;
					if(afd>bfd)
					{
						cfd=afd-1;
					}
					else
					{
						cfd=afd+1;
					}
				}
				else
				{
					if(afd>bfd && asd>bsd)
					{
						cfd=afd-1;
						csd=asd-1;
					}
					else if(afd>bfd && asd<bsd)
					{
						cfd=afd-1;
						csd=asd+1;
					} else if(afd<bfd && asd<bsd)
					{
						cfd=afd+1;
						csd=asd+1;
					}
					else
					{
						cfd=afd+1;
						csd=asd-1;
					}
				}

				c = (cfd * 10) + csd;

				checkPlace(c,&y);

				if((placeHolder[y]=='G') && (placeHolder[tigerShift]=='X'))
				{
				placeHolder[y]='X';
				(*goatEaten)++;

				placeHolder[tigerSelect]='X';
				placeHolder[tigerShift]='T';
				clrscr();
				cleardevice();
				drawBoard(placeHolder,goatNo,*goatEaten);
				break;
				}
				else
				{
				outtextxy(480,90,"Invalid!!");
				getch();
				clrscr();
				cleardevice();
				drawBoard(placeHolder,goatNo,*goatEaten);

				}
			}
			else
			{
				outtextxy(480,90,"Invalid position!!");
				getch();
				clrscr();
				cleardevice();
				drawBoard(placeHolder,goatNo,*goatEaten);
			}

		}
	}
	else
	{
	outtextxy(480,70,"No tiger there!!");
	getch();
	clrscr();
	cleardevice();
	drawBoard(placeHolder,goatNo,*goatEaten);
	}
	}

	return placeHolder;
}

char* goatBotMove(int* goatNo,char placeHolder[25],int goatEaten)
{
	int r,i;

	if( (*goatNo) < 20 )
	{
	     while(1)
	     {
	     r=(int) rand() % 25;

	     if(placeHolder[r]=='X')
	     {
		placeHolder[r]='G';
		(*goatNo)++;
		delay(1000);
		clrscr();
		cleardevice();
		drawBoard(placeHolder,*goatNo,goatEaten);
		break;
	     }
	     }
	}

	else
	{
	 //goat Bot Move for goatno = 20
	 while(1)
	 {
	 r = (int) rand() % 25;
	 if(placeHolder[r]=='G')
	 {
	   for(i=0;i<25;i++)
	   {
		if(path[r][i]==1 && placeHolder[i]=='X')
		{
			placeHolder[r]='X';
			placeHolder[i]='G';
			delay(1000);
			clrscr();
			cleardevice();
			drawBoard(placeHolder,*goatNo,goatEaten);
			break;
		}
	   }
	   if(placeHolder[r]=='X')
	   break;
	 }
	 }
	}
	return placeHolder;
}
char* goatPlayerMove(int* goatNo, char placeHolder[25],int goatEaten)
{
int loc,x,z,loc1,loc2,goatSelect,goatShift;


if( (*goatNo) < 20 )
{
	while(1)
	{
	clrscr();
	cleardevice();
	drawBoard(placeHolder,*goatNo,goatEaten);
	outtextxy(480,50,"Location for GOAT:");
	scanf("%d",&loc);
	checkPlace(loc,&x);

	if(placeHolder[x]=='X')
	{   clrscr();
	    cleardevice();
	    placeHolder[x]='G';
	    (*goatNo)++;
	    drawBoard(placeHolder,*goatNo,goatEaten);
	    return placeHolder;
	}
	else
	{
		outtextxy(480,70,"There's something!!");
		getch();
	}
 }
}
//goat move for goatNO=20
else
	{
	while(1)
	{
	clrscr();
	cleardevice();
	drawBoard(placeHolder,*goatNo,goatEaten);
	outtextxy(480,50,"Select goat:");
	scanf("%d",&loc1);
	checkPlace(loc1,&goatSelect);
	if(placeHolder[goatSelect]=='G')
	{

			outtextxy(480,70,"Postion to shift:");
			scanf("%d",&loc2);
			checkPlace(loc2,&goatShift);
			z=pathCheck(loc1,loc2);

			if(z==1)
			{
				if(placeHolder[goatShift]=='X')
				{
					placeHolder[goatSelect]='X';
					placeHolder[goatShift]='G';
					clrscr();
					cleardevice();
					drawBoard(placeHolder,*goatNo,goatEaten);
					return placeHolder;
				}
				else
				{
				outtextxy(480,90,"There's something!!");
				getch();
				cleardevice();
				drawBoard(placeHolder,*goatNo,goatEaten);
				}
			}
			else
			{
				outtextxy(480,90,"Invalid position!!");
				getch();
				cleardevice();
				drawBoard(placeHolder,*goatNo,goatEaten);
			}



	}
	else
	{
	outtextxy(480,90,"No goat there!!");
	getch();
	clrscr();
	cleardevice();
	drawBoard(placeHolder,*goatNo,goatEaten);
	}
	}
	}



}

char* tigerBotMove(int goatNo,char placeHolder[25],int* goatEaten)
{
	int r,i,j,loc1,loc2,afd,asd,bfd,bsd,cfd,csd,c,y;

	for(i=0;i<25;i++)
	{
		if(placeHolder[i]=='T')
		{
			for(j=0;j<25;j++)
			{
				if(path[i][j]==2)
				{
					loc1=convertToUserPos(i);
					loc2=convertToUserPos(j);
					afd=(int)loc1/10;
				asd=(int)loc1%10;
				bfd=(int)loc2/10;
				bsd=(int)loc2%10;

				if(afd==bfd)
				{
					cfd=afd;
					if(asd>bsd)
					{
						csd=asd-1;
					}
					else
					{
						csd=asd+1;
					}
				}
				else if(asd==bsd)
				{
					csd=asd;
					if(afd>bfd)
					{
						cfd=afd-1;
					}
					else
					{
						cfd=afd+1;
					}
				}
				else
				{
					if(afd>bfd && asd>bsd)
					{
						cfd=afd-1;
						csd=asd-1;
					}
					else if(afd>bfd && asd<bsd)
					{
						cfd=afd-1;
						csd=asd+1;
					} else if(afd<bfd && asd<bsd)
					{
						cfd=afd+1;
						csd=asd+1;
					}
					else
					{
						cfd=afd+1;
						csd=asd-1;
					}
				}

				c = (cfd * 10) + csd;

				checkPlace(c,&y);

				if(placeHolder[y]=='G' && placeHolder[j]=='X')
				{
				placeHolder[y]='X';
				placeHolder[i]='X';
				placeHolder[j]='T';
				(*goatEaten)++;
				delay(1000);
				clrscr();
				cleardevice();
				drawBoard(placeHolder,goatNo,*goatEaten);
				return placeHolder;
				}
			} }
		}
	}

	//tiger bot move for no goat eaten
	while(1)
	{
	c=1;
	r = (int) rand() % 4 + 1;

	for(i=0;i<25;i++)
	{
	      if(placeHolder[i]=='T')
	      {
		if(c==r)
		{
			break;
		}
		else
		{
			c++;
		}

	      }

	}

	for(j=0;j<25;j++)
	{
		if(path[i][j]==1 && placeHolder[j]=='X')
		{
			placeHolder[i]='X';
			placeHolder[j]='T';
			delay(1000);
			clrscr();
			cleardevice();
			drawBoard(placeHolder,goatNo,*goatEaten);
			return placeHolder;
		}
	}


	}
}

void displayGoatWin()
{
	clrscr();
	cleardevice();
	setbkcolor(BROWN);
	setcolor(BLUE);
	settextstyle(4,0,7);
	outtextxy(getmaxx()/2-280,getmaxy()/2-125,"GOAT WINS!!");
}

void game()
{
   int choose,i,goatEaten=0,goatNo=0;
   char play;
   char* pos;
   char placeHolder[25]={'T','X','X','X','T','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','T','X','X','X','T'};

   while(1)
   {
   clrscr();
   cleardevice();
   printf("\n\t=========================================");
   printf("\n\n\tCHOOSE GAME MODE :\n\n\t1) Two Player\n\n\t2) Play as Tiger with Computer Bot\n\n\t3) Play as Goat with Computer Bot\n\n\t4) Exit");
   printf("\n\n\n\tENTER [1-4] : ");
   scanf("%d",&choose);

   switch(choose)
   {

   case 1: while(goatEaten<5)
   {
	// goat move
	pos=goatPlayerMove(&goatNo,placeHolder,goatEaten);

	for(i=0;i<25;i++)
	{
		placeHolder[i]=*(pos+i);
	}


	//check goat win
	if(goatWin(placeHolder))
	{
	displayGoatWin();
	getch();
	return;
	}

	//tiger Move

	pos=tigerPlayerMove(goatNo,placeHolder,&goatEaten);

	for(i=0;i<25;i++)
	{
		placeHolder[i]=*(pos+i);
	}
   }

   if(goatEaten==5)
   {    clrscr();
	cleardevice();
	setbkcolor(BROWN);
	setcolor(BLUE);
	settextstyle(4,0,7);
	outtextxy(getmaxx()/2-280,getmaxy()/2-125,"TIGER WINS!!");
	getch();
	return;
   }
   break;

   case 2:

	while(goatEaten<5)
	{
	pos=goatBotMove(&goatNo,placeHolder,goatEaten);

	for(i=0;i<25;i++)
	{
		placeHolder[i]=*(pos+i);
	}


	//check goat win
	if(goatWin(placeHolder))
	{
	displayGoatWin();
	getch();
	return;
	}

	//tiger Move

	pos=tigerPlayerMove(goatNo,placeHolder,&goatEaten);

	for(i=0;i<25;i++)
	{
		placeHolder[i]=*(pos+i);
	}
   }

   if(goatEaten==5)
   {    clrscr();
	cleardevice();
	setbkcolor(BROWN);
	setcolor(BLUE);
	settextstyle(4,0,7);
	outtextxy(getmaxx()/2-280,getmaxy()/2-125,"TIGER WINS!!");
	getch();
	return;
   }
		break;

   case 3:
		 while(goatEaten<5)
   {
	// goat move
	pos=goatPlayerMove(&goatNo,placeHolder,goatEaten);

	for(i=0;i<25;i++)
	{
		placeHolder[i]=*(pos+i);
	}


	//check goat win
	if(goatWin(placeHolder))
	{
	displayGoatWin();
	getch();
	return;
	}

	//tiger Move

	pos=tigerBotMove(goatNo,placeHolder,&goatEaten);

	for(i=0;i<25;i++)
	{
		placeHolder[i]=*(pos+i);
	}
   }

   if(goatEaten==5)
   {    clrscr();
	cleardevice();
	setbkcolor(BROWN);
	setcolor(BLUE);
	settextstyle(4,0,7);
	outtextxy(getmaxx()/2-280,getmaxy()/2-125,"TIGER WINS!!");
	getch();
	return;
   }

		break;

   case 4: exit(1);

   default : printf("\n\n\n\tENTER FROM 1-4!!!");
		getch();
		break;
   }

   }

}

int goatWin(char placeHolder[25])
{
	int i,j,count=0;
	for(i=0;i<=24;i++)
	{
		if(placeHolder[i]=='T')
		{
			for(j=0;j<=24;j++)
			{
				if((path[i][j]==1 && placeHolder[j]=='X') || (path[i][j]==2 && placeHolder[j]=='X'))
				{
					return 0;
				}

			}
			count++;
		}
	}

	return 1;

}
void getCoord(int a,int *i,int *j)   //takes a from 0 - 24, provides coordiantes
{
      int rem;
      rem=(int) (a+1)%5;

      switch(rem)
      {
	case 0: *i=450;
		break;
	case 1: *i=50;
		break;
	case 2: *i=150;
		break;
	case 3: *i=250;
		break;
	case 4: *i=350;
		break;
      }

      if(a<=4)
      {
	*j=50;

      } else if(a>4 && a<=9)
      {
	*j=150;

      } else if(a>9 && a<=14)
      {
	*j=250;

      } else if(a>14 && a<=19)
      {
	*j=350;

      } else if(a>19 && a<=24)
      {
	*j=450;

      }
}

void checkPlace(int a,int *x) //changes game postion(11,12,32,55,etc) to 0-24
{
      int fd,sd;
      sd=(int) a%10;
      fd=(int) a/10;

      if(fd==1)
	{
		*x=sd-1;

	} else if(fd==2)
	{
		*x=sd+4;

	} else if(fd==3)
	{
		*x=sd+9;
	}else if(fd==4)
	{
		*x=sd+14;
	}else if(fd==5)
	{
		*x=sd+19;
	}

}

int pathCheck(int axy,int bxy) //returns 0 for no path,1 for single step path and 2 for double step path
{
	int afd,asd,bfd,bsd,x,y;

	afd=(int)axy/10;
	bfd=(int)bxy/10;
	asd=(int)axy%10;
	bsd=(int)bxy%10;

	if(afd==1)
	{
		x=asd-1;

	} else if(afd==2)
	{
		x=asd+4;

	} else if(afd==3)
	{
		x=asd+9;
	}else if(afd==4)
	{
		x=asd+14;
	}else if(afd==5)
	{
		x=asd+19;
	}
	if(bfd==1)
	{
		y=bsd-1;

	} else if(bfd==2)
	{
		y=bsd+4;

	} else if(bfd==3)
	{
		y=bsd+9;
	}else if(bfd==4)
	{
		y=bsd+14;
	}else if(bfd==5)
	{
		y=bsd+19;
	}

	if(path[x][y]==1)
	{
	return 1;
	}
	else if(path[x][y]==2)
	{
	return 2;
	}
	else
	{
	return 0;
	}
}

void drawBoard(char placeHolder[25],int goatNo,int goatEaten)
{
	int i,j,xcoo,ycoo;

	outtextxy(50,20,"1");
	outtextxy(150,20,"2");
	outtextxy(250,20,"3");
	outtextxy(350,20,"4");
	outtextxy(450,20,"5");
	outtextxy(15,50,"1");
	outtextxy(15,150,"2");
	outtextxy(15,250,"3");
	outtextxy(15,350,"4");
	outtextxy(15,450,"5");
	printf("Goats Left=%d\tGoat Eaten=%d\t",(20-goatNo),goatEaten);
	for(i=0;i<450;i+=100)
	{
		drawLine(50,50+i,450,50+i);
		drawLine(50+i,50,50+i,450);
	}

	drawLine(50,50,450,450);
	drawLine(450,50,50,450);
	drawLine(50,250,250,50);
	drawLine(250,50,450,250);
	drawLine(50,250,250,450);
	drawLine(450,250,250,450);
	for(i=0;i<=24;i++)
	{
		if(placeHolder[i]=='T')
		{
			getCoord(i,&xcoo,&ycoo);
			drawTiger(xcoo,ycoo);
		}
		else if(placeHolder[i]=='G')
		{
			getCoord(i,&xcoo,&ycoo);
			drawGoat(xcoo,ycoo);
		}

	}
}

void drawGoat(int x,int y)
{
	int i;
	for(i=1;i<=8;i++)
	drawCircle(x,y,i,GREEN);
}

void drawTiger(int x,int y)
{       int i;
	for(i=1;i<=17;i++)
	drawCircle(x,y,i,RED);
}

void drawLine(int x1,int y1,int x2,int y2)
{
   float xinc,yinc;
   int dx,dy;
   int steps,j;
   dx=x2-x1;
   dy=y2-y1;
   if(abs(dx)>abs(dy))
   steps=abs(dx);
   else
   steps=abs(dy);
   xinc=dx/steps;
   yinc=dy/steps;
   for(j=0;j<=steps;j++)
   {
	x1=x1+xinc;
	y1=y1+yinc;
	putpixel((int)(x1+0.5),(int)(y1+0.5),55);
   }
}
void drawCircle(int x,int y,int r,int m)
{
	int pk,x1,y1;
	x1=0;
	y1=r;
	pk=1-y1;
	while(x1<=y1)
	{
		putpixel(x1+x,y1+y,m);
		putpixel(y1+x,x1+y,m);
		putpixel(y1+x,-x1+y,m);
		putpixel(x1+x,-y1+y,m);
		putpixel(-x1+x,-y1+y,m);
		putpixel(-y1+x,-x1+y,m);
		putpixel(-y1+x,x1+y,m);
		putpixel(-x1+x,y1+y,m);
		if(pk<0)
		{
			x1=x1+1;
			pk=pk+2*x1+1;

		}
		else
		{
			x1=x1+1;
			y1=y1-1;
			pk=pk+2*x1-2*y1+1;
		}
	}
}
