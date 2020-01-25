/*
1.数据设计
2.模块化设计
3.实现功能

/////////////////////////////////////////////////////////////////////
//								贪吃蛇 
//                          编写 20190818   bug:蛇撞左右墙不死
*/				//			改写 20191002   20190818bug未修复 原因未知
/*                          修复 20191228   20190818bug修复                                       */


#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
////////////////////辅助宏定义
#define	MAPHEIGHT 20   //高度
#define MAPWIDTH 30	 //宽度
#define MAXSIZE 30	//最大长度
					


//数据设计
//								食物
struct Food
{  int x,y;	//坐标定位


}food;
//								蛇
struct Snake	// 每一节蛇的 坐标
{  int x[MAXSIZE];
   int y[MAXSIZE];
	int len;
	int speed;



		
}snake;

/////////////////////////////////////////
/////////全局变量
int key_last = 'w' ;	 //上次运动初始方向
int key_next='w';		  //新的运动方向
int changeflag  = 0;//运动方向改变标志

//模块化设计  --》功能划分--》》抽象到函数
									
										
//1.画地图
void drawmap();
//2. 食物
void creatfood();
//3.按键操作
void KeyDown();
//4.蛇的状态
int snakestatus();
//5.辅助函数 光标移动
void gotoxy(int x,int y);
	

int main ()
{
//	gotoxy(1,1);
	drawmap();
	
	while (1)
	{		creatfood();
			Sleep(snake.speed*2);
			KeyDown(); 
			if(!snakestatus())
				{
					break;
				}  
	}
	gotoxy(MAPWIDTH/2-4,MAPHEIGHT/2);
	printf("Game over!\t");
	
	system("pause");
		
return 0;
}  

	
void gotoxy(int x,int y)
{
 //调用win32的API 去设置控制台的光标位置
//1.找到控制台窗口
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
//2.光标的结构体
	COORD coord;
//3.设置坐标 光标
	coord.X=x;
	coord.Y=y;
//4.同步到控制台
	SetConsoleCursorPosition(handle,coord);


			

}
void drawmap()
{  	
//////////////////////////⚪	  ＋ 
	//int height=40,width=30;
   //1.圈地
	for(int i=0;i<=MAPHEIGHT;i++)
	{
		gotoxy(0,i);
		printf("■");
		gotoxy(MAPWIDTH,i);
		printf("■");
	}

	for(int j=2 ;j<=MAPWIDTH;j+=2)
	{
		gotoxy(j,0);
		printf("■");
		gotoxy(j,MAPHEIGHT);
		printf("■");
	
	}		
	//2.画蛇					
	//2.1蛇的属性
	snake.len=3;
	snake.speed=100;
	snake.x[0]=MAPWIDTH/2;		//蛇头置于屏幕中间
	snake.y[0]=MAPHEIGHT/2;
	//蛇头
	gotoxy(snake.x[0],snake.y[0]);
	printf("■");
	//蛇身体
	for(int k=1;k<snake.len;k++)
	{
		snake.x[k]=snake.x[k-1]+2;
		snake.y[k]=snake.y[k-1];
		gotoxy(snake.x[k],snake.y[k]);
		printf("■");
	}	

	
	//3.画食物
	//3.1 坐标 
		
		while(1)
		{ 
			int flag=1;
			srand((unsigned int)time(NULL));//随机函数种子
			food.x=rand()%((MAPWIDTH-4))+2;
			food.y=rand()%((MAPHEIGHT-2))+1;		
			//不能在蛇的身上
			for(int k=0 ;k<snake.len;k++)
				{
					if(snake.x[k]==food.x && snake.y[k]== food.y)  //食物在蛇的身上
						{
							flag=0;								   //标志置于0 ，即食物位置不对,需要重来
						}
				}
			/*if(food.x%2!=0)
						 {
					//	food.x+=1;				  	//食物位置正确		而且 食物在偶数位置
				//		break;
						}	  */
			if(flag&&(food.x!=2&&food.x!=MAPWIDTH-2||food.x!=1||food.x!=MAPHEIGHT-1)&&food.x%2!=0)	//位置正确	且食物不在墙里	
						{
						break;	
						}				
		}  
	//3.2 画画
		gotoxy(food.x,food.y);
		printf("●");	
		
}
void creatfood()
{	//食物被吃
	if(food.x==snake.x[0]&&food.y==snake.y[0])	  //说明食物被吃掉
	{
		//随机种子
		 srand((unsigned int)time(NULL));
		//产生的食物不能在蛇的身上
		//食物坐标应该是偶数  否则会只能吃一半
		while(1)
		{
			int flag = 1;
				 //准备产生新的食物
			food.x=rand()%(MAPWIDTH-4)+2;
			food.y=rand()%(MAPHEIGHT-2)+1;		
		//不能在蛇的身上
			for(int k=0 ;k<snake.len;k++)
				{
					if(snake.x[k]==food.x && snake.y[k]== food.y)  //食物在蛇的身上
						{
							flag=0;								   //标志置于0 ，即食物位置不对
						}
				}
			
			if(flag&&food.x%2!=0)		//食物位置正确		而且 食物在偶数位置			  ????		food.x%2!=0	成功???
				{
					break;	
				}
		}
	
	gotoxy(food.x,food.y);
	printf("●"); 	 //⊙⊙⊙⊙▇
	snake.len++;
	changeflag=1;//不执行擦除尾巴操作		即长度增加
	}
    
		
}	  
//3.按键操作
void  KeyDown()
{
  //如果按下
	if(_kbhit())
	{
		fflush(stdin);
		key_next = _getch();	

	}
///////擦除之前的蛇  的尾巴
	if(!changeflag)//如果方向不变 擦除之前的蛇  的尾巴
	{
		gotoxy(snake.x[snake.len-1],snake.y[snake.len-1]);
		printf("  ");
	}
	 //其他蛇身
	for(int i =snake.len-1 ;i>0;i--)
	{
		snake.x[i]=snake.x[i-1];
		snake.y[i]=snake.y[i-1];
	}
	 

	//如果有 按下

	//移动方向有变化

	switch (key_next)
	{
		case 'w':
		case 'W':
	
			snake.y[0]--;
	
			key_last=key_next;
			break;
		case 'a':
		case 'A':
			
			snake.x[0]-=2;
			key_last=key_next;
			break;
		case 's':
		case 'S':
		
			snake.y[0]++;
			key_last=key_next;
			break;
		case 'D':
		case 'd':
		
			snake.x[0]+=2; //一个符号横向占两个字符	
			key_last=key_next;
			break;
		
		}
	
	gotoxy(snake.x[0],snake.y[0]);//new snake head position
	printf("■");				//draw new snake head
	changeflag=0;	   //方向改变标志reset
	gotoxy(MAPHEIGHT+2,0); //移动光标到头
	//否则移动方向无变化
	//则方向不变 keynext =keylast 
	
	
}	
//4.蛇的状态
int snakestatus()
{	  
			   //4.2蛇不能撞到墙壁
			if(snake.x[0]==1||snake.x[0]==MAPWIDTH-1||snake.y[0]==0||snake.y[0]==MAPHEIGHT)	//将	 snake.x[0]==0
			{						//只有当snake.x[0]为奇数时才判断为真							// snake.x[0]==MAPWIDTH	
				return 0;			//但snake.x[0]不可能为奇数									//	修改 snake.x[0]==1
			 }																			  // snake.x[0]==MAPWIDTH-1
		 //4.1蛇不能撞到自己	的身体													//bug修复完成
			for(int k=2;k<snake.len;k++)
			{
				if(snake.x[0]==snake.x[k]&&snake.y[0]==snake.y[k])
					return 0;	//失败			
		
			}						
		//	if(snake.x[0]==snake.x[1]&&snake.y[0]==snake.y[1])return 1;

			
			//蛇不能倒退 否则无效
   return 1;			
}