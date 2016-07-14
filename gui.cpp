#include "gui.h"

void draw_pixel(SDL_Surface *dst, int x, int y, Uint32 color)
{
    SDL_Rect offset = {0, 0, 1, 1};

    offset.x = x;
    offset.y = y;

    SDL_FillRect(dst, &offset, SDL_MapRGB(dst->format,
                            (char)(color >> 16),
                            (char)(color >> 8),
                            (char)color));
}

void draw_vline(SDL_Surface *dst, int x, int y, int len, Uint32 color)
{
    SDL_Rect offset = {0, 0, 1, 1};

    offset.x = x;
    offset.y = y;
    offset.h = len;

    SDL_FillRect(dst, &offset, SDL_MapRGB(dst->format,
                            (char)(color >> 16),
                            (char)(color >> 8),
                            (char)color));
}

void draw_hline(SDL_Surface *dst, int x, int y, int len, Uint32 color)
{
    SDL_Rect offset = {0, 0, 1, 1};

    offset.x = x;
    offset.y = y;
    offset.w = len;

    SDL_FillRect(dst, &offset, SDL_MapRGB(dst->format,
                            (char)(color >> 16),
                            (char)(color >> 8),
                            (char)color));
}

void draw_rect(SDL_Surface *dst, int x, int y, int w, int h, Uint32 color)
{
    SDL_Rect offset = {0, 0, 1, 1};

    offset.x = x;
    offset.y = y;
    offset.w = w;
    offset.h = h;

    SDL_FillRect(dst, &offset, SDL_MapRGB(dst->format,
                            (char)(color >> 16),
                            (char)(color >> 8),
                            (char)color));
}


void draw_box(SDL_Surface *dst, int x, int y, int w, int h, int border, Uint32 border_color, Uint32 color)
{
    draw_rect(dst, x, y, w, h, border_color);
    draw_rect(dst, x + border, y + border, w - 2 * border, h - border * 2, color);
}




//24 13
SDL_Surface * init(void){

    int ret,i;
    SDL_Surface *screen = NULL;

    ret = SDL_Init(SDL_INIT_VIDEO);
   // ERRP(-1 == ret, goto ERR1, 2, "SDL_Init: %s\n", SDL_GetError());

    screen = SDL_SetVideoMode(280, 280, 32, SDL_SWSURFACE);
    //ERRP(NULL == screen, goto ERR2, 2, "SDL_SetVideoMode: %s\n", SDL_GetError());
   
//     SDLK_UP         = 273     SDLK_DOWN       = 274,
//     SDLK_RIGHT      = 275     SDLK_LEFT       = 276,

draw_vline(screen,ox-1,oy-1,len_y,0xE0EEEE);
draw_vline(screen,ox-1+len_x,oy-1,len_y,0xE0EEEE);
draw_hline(screen,ox-1,oy-1,len_x,0xE0EEEE);
draw_hline(screen,ox-1,oy-1+len_y,len_x,0xE0EEEE);
SDL_Flip(screen);
 
return screen;
}

/*void draw_d(pattern *pat, SDL_Surface * screen)
{ 
for(int i=0;i<24;i++)
{for(int j=0;j<13;j++)
{
 if(pat->get(i,j)==1)
 {
   
    draw_box(screen, ox+j*cub_len, oy+i*cub_len, cub_len,cub_len,1,0x0,0x9400D3);
  }
 
}
}
}
*/
void draw_d(SDL_Surface * screen ,int (*data)[13])
{ 

for(int i=0;i<24;i++)
{for(int j=0;j<13;j++)
{
 if(data[i][j]==1)
 {
   
    draw_box(screen, ox+j*cub_len, oy+i*cub_len, cub_len,cub_len,1,0x0,0x9400D3);
  }
 
}
}
}


void clear_d(SDL_Surface * screen ,int (*data)[13])
{
for(int i=0;i<24;i++)
{for(int j=0;j<13;j++)
{
 if(data[i][j]==1)
 {
   
    draw_box(screen, ox+j*cub_len, oy+i*cub_len, cub_len,cub_len,1,0x0,0x0);
  }
 
}
}
}



void draw( pattern * pat,SDL_Surface * screen,int cur_p,int is)
{


for(int i=0 ;i<4;i++)
draw_box(screen,ox+(pat->get_rundata(i,cur_p,is).get_x()*cub_len),oy+(pat->get_rundata(i,cur_p,is).get_y()*cub_len),cub_len,cub_len,1,0x0,0x9400D3);


}

void clear( pattern * pat,SDL_Surface * screen,int cur_p,int is)
{


for(int i=0 ;i<4;i++)
draw_box(screen,ox+(pat->get_rundata(i,cur_p,is).get_x()*cub_len),oy+(pat->get_rundata(i,cur_p,is).get_y()*cub_len),cub_len,cub_len,1,0x0,0x0);

printf("clear\n");

}





