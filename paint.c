#include<stdio.h>
#include<SDL2/SDL.h>
#include<stdbool.h>
#include<math.h>


#define start_radius 20
#define FPS 60
#define width 900  // macro whenever you use width it will use value 900
#define height 900
#define color_rect_size 45 
#define start_color 0x00FF00
Uint32 color = start_color;
Uint32 color_pallete[] = {0xFFFFFF,0x00FF00,0xFF0000,0x0000FF,0xF000F0,0x0FFFF0};
const int color_palatte_size=15;
bool inside_color_palatte(int x, int y)
{
   if(x <= color_palatte_size*color_rect_size && y<=color_rect_size )
   {
    return true;
   }
   return false;
}
//This checks if the user selects any color palatte and then returns the chossen color otherwise reurns nothing stays to default color 
void check_color_palatte_chosen(int x,int y)
{
  int i;
  if(inside_color_palatte(x,y))
  {
    //mouse is inside x,y range of color palatte
    i= x/color_rect_size;
    color= color_pallete[i];
  }
}
void draw_palette(SDL_Surface *surface,Uint32 *color,int size)
{
    SDL_Rect color_rect ;
    for(int i =0;i<size;i++)
    {
        color_rect=(struct SDL_Rect){i*color_rect_size,0,color_rect_size,color_palatte_size};
        SDL_FillRect(surface,&color_rect,color[i]);
    }

}

void draw_circle(SDL_Surface *surface , int x_center , int y_center , int radius , Uint32 color)
{
   SDL_Rect pixel ={0,0,1,1};
   for (int x=x_center-radius;x < x_center+radius;x++ )
   {
    for(int y=y_center-radius;y<y_center+radius;y++)
    {
        //is this pixel part of the circle ?
        int distance_form_center =  sqrt(pow(x-x_center,2)+pow(y-y_center,2));
        if (distance_form_center<radius)
        {
            pixel.x=x;
            pixel.y=y;
            SDL_FillRect(surface,&pixel,color);
        }

    }
   }
}

int main()
{   

    
    int radius = start_radius; 
    
    int x,y;
    bool draw = false;
    bool done = false;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Painting",
                                          SDL_WINDOWPOS_CENTERED,    // x postiotn
                                          SDL_WINDOWPOS_CENTERED,    // y positon
                                          width, 
                                          height, 
                                          0 );             // flags     
    
                                          
    
    float delay = (1.0/FPS)*1000;   // for optimastion and better resource usage FPS = frames per second you want (example: 60) 1.0 / FPS = time for one frame in seconds * 1000 = converts seconds → milliseconds
    while (!done) {     // keeps the window open util done becomes false 
    SDL_Event event;    // SDL_Event store user action 
   
    SDL_Surface *surface = SDL_GetWindowSurface(window);
     draw_palette(surface,color_pallete,color_palatte_size);
    SDL_UpdateWindowSurface(window);

    while (SDL_PollEvent(&event)) {      // checks if any evet has occured 
        switch (event.type)
        {
        case SDL_QUIT:
            done = true;
            break;
        
        case SDL_MOUSEMOTION:
            x = event.motion.x;
            y = event.motion.y;
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            x = event.motion.x;
            y = event.motion.y;
            check_color_palatte_chosen(x,y);
            if(inside_color_palatte(x,y)== false)
            {
                 draw=true;
            }

            break;
        case SDL_MOUSEBUTTONUP:
            draw = false;
            break;
        case SDL_MOUSEWHEEL:
            radius += event.wheel.preciseY;
            if(radius < 5)
               radius=5;
            break;
            
        }
    }

    if (draw)
    {
        draw_circle(surface,x,y,radius,color);
              
        SDL_UpdateWindowSurface(window);

    }
      
    SDL_Delay(delay);   //pauses the program,prevents the loop from running too fast,keeps FPS stable
    // Do game logic, present a frame, etc.
    
}
  return 0;

}