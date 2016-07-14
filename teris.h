
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
#define xf (6)
#define yf  (0)
#define off (1)
#include<stdlib.h>



class Cub{

int x1,y1;
public:
 Cub(int x,int y)
{
x1=x;
y1=y;

}
int get_x()
{
return x1;

}
int get_y()
{
return y1;

}
Cub & setx(int x)
{
  x1=x;
return *this;

}


Cub& set(int x, int y)
{
x1=x;
y1=y;
return *this;

}
Cub &set_y(int y)
{

y1=y;
return *this;
}

 Cub() {}

};



class pattern{

//bool data[24][13];
public:
//virtual int out_board(int flag){}
 int updata(int press_flag ,int flags){}
virtual Cub & get_rundata(int ,int,int ){}
virtual void   adjust_initdata(void){}//调整初始化数据
virtual int  get_cur(void){}
virtual int  nextflags(int cur_flags){}
virtual void rotate(int last_pattern){}
virtual Cub & get_initdata(int,int){}
virtual void init(int cur_flags){}



};







class shape_L :public pattern{
int cur,lastpattern,j;

Cub last_data[4];//
Cub init_array[4][4];
Cub sta[4][4];//不能修改
enum  {LL=0,LD,LR,LU};
public:
shape_L():cur(0)
{
 
 for(int i=0;i<4;i++)//先初始化第一个数据,接着调用rotate初始化剩下的
{
  
   if(i<3)
   init_array[LL][i].set(xf,yf+i);
   else
   init_array[LL][i].set(xf-off,yf+i-off);
   

}

rotate(LL);
rotate(LD);
rotate(LR);


adjust_initdata();


}

void init(int cur_flags)
{
for(int i=0;i<4;i++)
  init_array[cur_flags][i]=sta[cur_flags][i];

}

int nextflags(int cur_flags)
{
  
   return (cur_flags+1)%4;


}

int get_cur(void)
{
  
  return cur;
}


void  adjust_initdata(void)//调整初始化数据
{
 
 for(int i=0;i<4;i++)
   {
   
     init_array[LD][i].set_y(init_array[LD][i].get_y()-off);
     
     init_array[LU][i].set_y(init_array[LU][i].get_y()-off);
      
   }
  
  memcpy((void*)sta , (const void *)init_array,sizeof(init_array));
}





Cub &get_initdata(int i,int cur_flag)
{

   return init_array[cur_flag][i];

}

Cub &get_rundata(int i,int cur_flag,int isfirst)
{

 if(isfirst==1)
 return sta[cur_flag][i];
 else
 return init_array[cur_flag][i];
}


void rotate(int last_pattern)
{

  switch (last_pattern){

 case LL:
  init_array[LD][0].set(init_array[LL][3].get_x(),    init_array[LL][3].get_y()-off);
  init_array[LD][1].set(init_array[LL][0].get_x(),    init_array[LL][0].get_y()+off);
  init_array[LD][2].set(init_array[LL][1].get_x()+off,init_array[LL][1].get_y());
  init_array[LD][3].set(init_array[LL][2].get_x()+off,init_array[LL][2].get_y());
   break;
 case LD: 
  init_array[LR][0].set(init_array[LD][1].get_x(),    init_array[LD][1].get_y()-off);
  init_array[LR][1].set(init_array[LD][0].get_x(),    init_array[LD][0].get_y()-off);
  init_array[LR][2].set(init_array[LD][2].get_x()-2*off,init_array[LD][2].get_y());
  init_array[LR][3].set(init_array[LD][3].get_x()-2*off,init_array[LD][3].get_y());
   break;
 case LR:
  init_array[LU][0].set(init_array[LR][1].get_x(),      init_array[LR][1].get_y()+off);
  init_array[LU][1].set(init_array[LR][2].get_x(),      init_array[LR][2].get_y()+off);
  init_array[LU][2].set(init_array[LR][0].get_x(),      init_array[LR][0].get_y()+2*off);
  init_array[LU][3].set(init_array[LR][3].get_x()+2*off,init_array[LR][3].get_y());
   break;
 case LU:
  init_array[LL][0].set(init_array[LU][2].get_x(),      init_array[LU][2].get_y()-2*off);
  init_array[LL][1].set(init_array[LU][0].get_x()+off,  init_array[LU][0].get_y());
  init_array[LL][2].set(init_array[LU][3].get_x()-off,  init_array[LU][3].get_y());
  init_array[LL][3].set(init_array[LU][1].get_x(),      init_array[LU][1].get_y());
   break;
  default:break;

         }

    }

 //cout<<"last"<<endl;

};


class shape_T :public pattern
{
int cur,num;
Cub run_data[4];
Cub init_array[4][4];
Cub sta[4][4];
int flags;
enum  {TU=0,TL,TD,TR};
public:
shape_T():cur(0)
{

  
  init_array[TU][0].set(xf,yf+off);
  init_array[TU][1].set(xf-off,yf+2*off);
  init_array[TU][2].set(xf,yf+2*off);
  init_array[TU][3].set(xf+off,yf+2*off);

rotate(TU);
rotate(TL);
rotate(TD);

adjust_initdata();
}

int nextflags(int cur_flags)
{
  
   return (cur_flags+1)%4;


}


void init(int cur_flags)
{
for(int i=0;i<4;i++)
  init_array[cur_flags][i]=sta[cur_flags][i];

}

int get_cur(void)
{
  
  return cur;
}

void  adjust_initdata(void)//调整初始化数据
{
 
 for(int i=0;i<4;i++)
   {
   
     
     init_array[TU][i].set_y(init_array[TU][i].get_y()-off);
     init_array[TD][i].set_y(init_array[TD][i].get_y()-off);
     
      
   }

  memcpy((void*)sta , (const void *)init_array,sizeof(init_array));
}


Cub &get_initdata(int i,int cur_flag)
{

   return init_array[cur_flag][i];

}


Cub &get_rundata(int i,int cur_pat,int isfirst)
{

 if(isfirst==1)
 return sta[cur_pat][i];
 else
 return init_array[cur_pat][i];
}



void rotate(int last_pattern)
{
   switch (last_pattern){

 case TU:
  init_array[TL][0].set(init_array[TU][1].get_x(),          init_array[TU][1].get_y()-off);
  init_array[TL][1].set(init_array[TU][0].get_x(),          init_array[TU][0].get_y()-off);
  init_array[TL][2].set(init_array[TU][2].get_x(),          init_array[TU][2].get_y()-off);
  init_array[TL][3].set(init_array[TU][3].get_x()-off,      init_array[TU][3].get_y());
  break;
 case TL:
  init_array[TD][0].set(init_array[TL][3].get_x(),      init_array[TL][3].get_y());
  init_array[TD][1].set(init_array[TL][0].get_x(),      init_array[TL][0].get_y());
  init_array[TD][2].set(init_array[TL][1].get_x(),      init_array[TL][1].get_y()+off);
  init_array[TD][3].set(init_array[TL][2].get_x()+off,  init_array[TL][2].get_y()); 
  break;
 case TD:
  init_array[TR][0].set(init_array[TD][3].get_x(),      init_array[TD][3].get_y());
  init_array[TR][1].set(init_array[TD][2].get_x(),      init_array[TD][2].get_y()-off);
  init_array[TR][2].set(init_array[TD][1].get_x()+off,  init_array[TD][1].get_y());
  init_array[TR][3].set(init_array[TD][0].get_x(),      init_array[TD][0].get_y()); 
  break;

 case TR:
  init_array[TU][0].set(init_array[TR][2].get_x()+off,      init_array[TR][2].get_y());
  init_array[TU][1].set(init_array[TR][1].get_x(),          init_array[TR][1].get_y()+2*off);
  init_array[TU][2].set(init_array[TR][0].get_x(),          init_array[TR][0].get_y()+off);
  init_array[TU][3].set(init_array[TR][3].get_x()+2*off,    init_array[TR][3].get_y()); 

  break;
  default :
  break;

   }

  }


};


class shape_Z :public pattern
{
int cur,num;
Cub run_data[4];
Cub init_array[2][4];
Cub sta[2][4];
int flags;
enum  {ZV=0,ZH};
public:
shape_Z():cur(0)
{

  
  init_array[ZV][0].set(xf,yf);
  init_array[ZV][1].set(xf,yf+off);
  init_array[ZV][2].set(xf-off,yf+off);
 init_array[ZV][3].set(xf-off,yf+2*off);

rotate(ZV);

adjust_initdata();

}

int nextflags(int cur_flags)
{
  
   return (cur_flags+1)%2;


}

void init(int cur_flags)
{
for(int i=0;i<4;i++)
  init_array[cur_flags][i]=sta[cur_flags][i];

}

Cub &get_initdata(int i,int cur_flag)
{

   return init_array[cur_flag][i];

}


int get_cur(void)
{
  
  return cur;
}


void  adjust_initdata(void)//调整初始化数据
{
 
 for(int i=0;i<4;i++)
   {
   
     init_array[ZH][i].set_y(init_array[ZH][i].get_y()-off);
   }
memcpy((void*)sta , (const void *)init_array,sizeof(init_array));

}


Cub &get_rundata(int i,int cur_pat,int isfirst)
{

 if(isfirst==1)
 return sta[cur_pat][i];
 else
 return init_array[cur_pat][i];
}


void rotate(int last_pattern)
{
   switch (last_pattern){
  
  case ZV:
  
  init_array[ZH][0].set(init_array[ZV][2].get_x(),          init_array[ZV][2].get_y());
  init_array[ZH][1].set(init_array[ZV][0].get_x(),          init_array[ZV][0].get_y()+off);
  init_array[ZH][2].set(init_array[ZV][1].get_x(),          init_array[ZV][1].get_y()+off);
  init_array[ZH][3].set(init_array[ZV][3].get_x()+2*off,    init_array[ZV][3].get_y()); 
  break;
  case ZH:
  
  init_array[ZV][0].set(init_array[ZH][1].get_x(),          init_array[ZH][1].get_y()-off);
  init_array[ZV][1].set(init_array[ZH][2].get_x(),          init_array[ZH][2].get_y()-off);
  init_array[ZV][2].set(init_array[ZH][0].get_x(),          init_array[ZH][0].get_y());
  init_array[ZV][3].set(init_array[ZH][3].get_x()-2*off,    init_array[ZH][3].get_y()); 

  break;
  default:
  break;
   }

  }


};





class shape_I :public pattern
{
int cur,num;
Cub run_data[4];
Cub init_array[2][4];
Cub sta[2][4];
int flags;
enum  {IV=0,IH};
public:
shape_I():cur(0)
{

  for(int i=0;i<4;i++)
  {
	  run_data[i]=init_array[IV][i].set(xf,yf+i);
      
  
  }     
   
  
     rotate(IV);
adjust_initdata();

}

int nextflags(int cur_flags)
{
  
   return (cur_flags+1)%2;


}

void init(int cur_flags)
{
for(int i=0;i<4;i++)
  init_array[cur_flags][i]=sta[cur_flags][i];

}

int get_cur(void)
{
  
  return cur;
}

void  adjust_initdata(void)//调整初始化数据
{
 
 for(int i=0;i<4;i++)
   {
   
     init_array[IH][i].set_y(init_array[IH][i].get_y()-3*off);
      
   }

  memcpy((void*)sta , (const void *)init_array,sizeof(init_array));

}

Cub &get_initdata(int i,int cur_flag)
{

   return init_array[cur_flag][i];

}


Cub &get_rundata(int i,int cur_pat,int isfirst)
{

 if(isfirst==1)
 return sta[cur_pat][i];
 else
 return init_array[cur_pat][i];
}


void rotate(int last_pattern)
{
   switch (last_pattern){
  
 case IV:
  init_array[IH][0].set(init_array[IV][3].get_x()-off,      init_array[IV][3].get_y());
  init_array[IH][1].set(init_array[IV][3].get_x(),          init_array[IV][3].get_y());
  init_array[IH][2].set(init_array[IV][3].get_x()+off,      init_array[IV][3].get_y());
  init_array[IH][3].set(init_array[IV][3].get_x()+2*off,    init_array[IV][3].get_y());
  break;
  
 case IH:
  init_array[IV][0].set(init_array[IH][1].get_x(),      init_array[IH][1].get_y()-3*off);
  init_array[IV][1].set(init_array[IH][1].get_x(),      init_array[IH][1].get_y()-2*off);
  init_array[IV][2].set(init_array[IH][1].get_x(),      init_array[IH][1].get_y()-off);
  init_array[IV][3].set(init_array[IH][1].get_x(),      init_array[IH][1].get_y());
  break;

 default:
  break;





     }


   }

};


  
class shape_O :public pattern
{
int cur,num;
Cub run_data[4];
Cub init_array[4];
Cub sta[4];
int flags;
enum  {O=0};
public:
shape_O():cur(0)
{

  
   init_array[0].set(xf-off,yf);
   init_array[1].set(xf,yf);
   init_array[2].set(xf-off,yf+off);
   init_array[3].set(xf,yf+off);

adjust_initdata();

}

void init(int cur_flags)
{
for(int i=0;i<4;i++)
  init_array[i]=sta[i];

}

int nextflags(int cur_flags)
{
  
   return (cur_flags+1)%1;


}

int get_cur(void)
{
  
  return cur;
}

void  adjust_initdata(void)//调整初始化数据
{
 
memcpy((void*)sta , (const void *)init_array,sizeof(init_array));

}

Cub &get_initdata(int i,int cur_flag)
{

   return init_array[i];

}


Cub &get_rundata(int i,int cur_pat,int isfirst)
{

 if(isfirst==1)
 return sta[i];
 else
 return init_array[i];
}




void rotate(int last_pattern)
{
    

return;  

 
}

 };













