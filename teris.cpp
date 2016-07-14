#include <unistd.h>
#include <pthread.h>
#include"gui.h"
#include <stdlib.h>
#include<time.h>
#include <signal.h>
static int mydata[24][13];
//static bool mydata[24][13]={1,1,1};

int ob =0;
 void print(void)
{
for(int i=0;i<24;i++)
{for(int j=0;j<13;j++)
{
 printf( " %d " ,mydata[i][j]);

}
printf("\n");
}

}


void set_data(pattern * p,bool value,int cur_flag,int isorig)//此处导致段错误
{


for(int j=0;j<4;j++)
{

mydata[p->get_rundata(j,cur_flag,isorig).get_y()][p->get_rundata(j,cur_flag,isorig).get_x()]=value;

}
print();
}







int  down(pattern *p, int &flag,int &cur_pat,int& isorig,int& ob)
{
//pattern **pat=(pattern **)p;

int f=0,e=0;
for(int j=0; j<4;j++)
{
if(p->get_rundata(j,flag,0).get_y()+off>23)
 { f=1;
  break;}
}

if(f==1)
{

set_data(p, 1,flag,0);
cur_pat=rand()%5;
isorig=0;
flag=0;
ob=1;
return 0;
}



for(int i=0; i<4;i++)
{

if(mydata[p->get_rundata(i,flag,0).get_y()+off][p->get_rundata(i,flag,0).get_x()] ==1)
{
e=1;
break;
}

}

if(e==1)
{

set_data(p, 1,flag,0);
cur_pat=rand()%5;
isorig=0;
flag=0;
ob=1;
}
else
{
for(int i=0; i<4;i++)
{

p->get_rundata(i,flag,0).set(p->get_rundata(i,flag,0).get_x(),p->get_rundata(i,flag,0).get_y()+off);

}

}

return 0;
}


int  updata(int press_flag ,int flag,pattern * p)//左右移动时也调用该函数更新数据
{
      if(press_flag==SDLK_UP)
	{   

          for(int i=0; i<4;i++)
           {  
           
             if((mydata[p->get_initdata(i,flag).get_y()][p->get_initdata(i,flag).get_x()] ==1)||(p->get_initdata(i,flag).get_x()>13)||(p->get_initdata(i,flag).get_x()<0))
              {
                  
		   return -1;
                  
		  
	       }
	   }
         }
       else if(press_flag==SDLK_LEFT)
 	{
          for(int i =0;i<4;i++)
          {
         
          if(((p->get_initdata(i,flag).get_x()-off)<0)||(mydata[p->get_initdata(i,flag).get_y()][p->get_initdata(i,flag).get_x()-off]==1))
            return -2;
           
          }
          for(int i =0;i<4;i++)
          {
         
         
         p->get_initdata(i,flag).setx( p->get_initdata(i,flag).get_x()-off);
       
           
          }
	    
 	}
        else if(press_flag==SDLK_RIGHT)
        {
         for(int i =0;i<4;i++)
          {
         
          if(((p->get_initdata(i,flag).get_x()+off)>12)||(mydata[p->get_initdata(i,flag).get_y()][p->get_initdata(i,flag).get_x()+off]==1))
            return -3;
           
          }
          for(int i =0;i<4;i++)
          {
         
         
         p->get_initdata(i,flag).setx( p->get_initdata(i,flag).get_x()+off);
        
           
          }
	    

	}
   

   return 0;

}






void init_data(void)
{

for(int i=0;i<24;i++)
{for(int j=0;j<13;j++)
{

mydata[i][j]=0;

}
}

}


void caculate(void)
{
int count=0,x=0,num=0,lastflag=0,pos=0,t=0,h=0;
for(int i=23;i>=0;i--)
{

for(int j=0;j<13;j++)
{
if(mydata[i][j]==1)
{

count+=1;

}
}//for
printf("count=%d",count);
 if(count<13&&lastflag==1)
{
pos=i;//拷贝的位置 
break;
}

if(count>=13)
{
num++;//需要消除的行数

lastflag=1;
}

count=0;
}//for



printf("\n");
printf("num=%d pos=%d",num,pos);

h=pos+num;
if(num<=0)
{
return;
}
else{
for( ;h>=0;h--,pos--) 
for(int x=0;x<13;x++)
{

if(pos<=-1)
{
//printf("posend=%d" ,pos);
mydata[h][x]=0;
}
else{
mydata[h][x]=mydata[pos][x];
}
}//for

}//else


}


int state=0;
bool END=0;
SDL_Event event;
SDL_Surface * screen=NULL;
pthread_t thread_id1,thread_id2;


void * thread_start_1(void *p)
{ 

screen = init();
pattern **pat =(pattern **)p;
int cur_pat=rand()%5;
//int cur_pat=4;
int last_pat,firstflag=0;
int last_flags;
//int cur_flags = pat[cur_pat]->get_cur();//读的时候的状态可能与在执行时更改
int cur_flags=0;

while(!END)
{

 if(state!=0)
{
  
  switch(state)
   {
          
                case SDLK_UP :
                 pat[cur_pat]->rotate(cur_flags);
                 firstflag=0;
                 last_flags=cur_flags;
                 cur_flags=pat[cur_pat]->nextflags(cur_flags);
               if( updata(state,cur_flags,pat[cur_pat]) == -1)
                  {         
                     cur_flags=last_flags ;
                   }
               clear(pat[cur_pat],screen,last_flags,firstflag);
               //  draw(pat[cur_pat],screen,cur_flags,firstflag);
                // SDL_Flip(screen);
               //printf("cur_pat=%d,cur_flags=%d,firstflag=%d",cur_pat,cur_flags,firstflag);
                  state=0;
 		//SDL_Delay(5);
		    break;

                case SDLK_RIGHT :
		//printf("hello\n");
                  firstflag=0;
                
               clear(pat[cur_pat],screen,cur_flags,firstflag);
              updata(state,cur_flags,pat[cur_pat]);
               
               // draw(pat[cur_pat],screen,cur_flags,firstflag);
              //  SDL_Flip(screen);
                 
                  state=0;
                // SDL_Delay(5);
		    break;

   		case SDLK_LEFT:
		printf("hello\n");
		firstflag=0;
           clear(pat[cur_pat],screen,cur_flags,firstflag);
             updata(state,cur_flags,pat[cur_pat]);
              
              //   draw(pat[cur_pat],screen,cur_flags,firstflag);
              //   SDL_Flip(screen);
                 
                  state=0;
                //SDL_Delay(5);
 		    break;

       		case SDLK_DOWN:
  		 
  		   break;
               default:
                break;

      }//switch
         

  
  }else
{
//SDL_Delay(300);

}




///*

//需要初始化init数据

clear(pat[cur_pat],screen,cur_flags,firstflag);//此处导致数据混乱
down(pat[cur_pat],cur_flags,cur_pat,firstflag,ob);
clear_d(screen ,mydata);
caculate();
draw_d(screen ,mydata);
SDL_Flip(screen);
if(ob==1)
{
pat[cur_pat]->init( cur_flags);
ob=0;
}
//clear_d(screen ,mydata);
//draw_d(screen ,mydata);
draw(pat[cur_pat],screen,cur_flags,firstflag);
SDL_Flip(screen);

SDL_Delay(400);
//*/
}//while



}



int main()
{
srand(time(NULL));
shape_L L;
shape_Z Z;
shape_I I;
shape_T T;
shape_O O;
pattern * p[]={&L,&Z,&I,&O,&T};


pthread_t thid1;
pthread_create(&thid1,NULL,thread_start_1,(void*)p);
init_data();



while (1)
    {
        if (SDL_WaitEvent(&event))
        {
            if (event.type == SDL_QUIT) 
               {
                  END=1;
                  break;
                   }
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym){
		case SDLK_UP :

                   state=SDLK_UP;
		    break;

                case SDLK_RIGHT :
                   state=SDLK_RIGHT;
		    break;

   		case SDLK_LEFT:
		   state=SDLK_LEFT;
 		    break;

       		case SDLK_DOWN:
  		   state=SDLK_DOWN;
  		   break;
                   }
            }
        }
     SDL_Delay(100);
          
    }




SDL_FreeSurface(screen);
SDL_Quit();
return 0;
}






