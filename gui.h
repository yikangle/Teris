#include<SDL/SDL.h>
#include"teris.h"
#define ox 73
#define oy 18
#define len_x 131
#define len_y 242
#define max_x 12
#define max_y 22
#define cub_len 10


void draw_pixel(SDL_Surface *dst, int x, int y, Uint32 color);


void draw_vline(SDL_Surface *dst, int x, int y, int len, Uint32 color);

void draw_hline(SDL_Surface *dst, int x, int y, int len, Uint32 color);


void draw_rect(SDL_Surface *dst, int x, int y, int w, int h, Uint32 color);



void draw_box(SDL_Surface *dst, int x, int y, int w, int h, int border, Uint32 border_color, Uint32 color);




//24 13
SDL_Surface * init(void);


void draw( pattern * pat,SDL_Surface * screen,int cur_p,int is);

void draw_d( SDL_Surface * screen,int (*data)[13] );

void clear( pattern * pat,SDL_Surface * screen,int last_p,int is);

void clear_d(SDL_Surface * screen ,int (*data)[13]);

