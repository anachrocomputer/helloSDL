/* helloSDL --- simple hello world program for SDL          2016-04-16 */

#include <SDL2/SDL.h> 
#include <stdio.h> 

/* Window size */
#define SCREEN_WIDTH   (640) 
#define SCREEN_HEIGHT  (480)

int main(int argc, char *argv[])
{
   SDL_Joystick *joystick = NULL;   /* The SDL joystick */
   SDL_Window *window = NULL;       /* The SDL window */

   /* The surface contained by the window */
   SDL_Surface *screenSurface = NULL;

   Uint32 white, blue, black, grey; /* Precomputed colours */
   Uint32 red, yellow, green;       /* Precomputed colours */
   int nb;
   int jb[16];
   SDL_Rect jbut[16];
   int na;
   int ja[16];
   SDL_Rect jaxis[16], jposn[16];
   int nh;
   SDL_Rect box, pixel;
   SDL_Event e;
   int running = 1;
   int x, y, z;
   int i, x0, y0, z0;
   int hlx, hly, hlz;

   hlx = 0;
   hly = 0;
   hlz = 0;
      
   /* Initialise Simple DirectMedia Layer */
   if (SDL_Init(SDL_INIT_EVERYTHING)) {
      printf("SDL failed to initialise: SDL_Error: %s\n", SDL_GetError());
      exit(EXIT_FAILURE);
   }                    

   for (i = 0; i < 16; i++) {
      ja[i] = 0;
      jaxis[i].x = 10 + (16 * i);
      jaxis[i].y = 30;
      jaxis[i].w = 10;
      jaxis[i].h = 128 + 10;
      
      jposn[i].x = jaxis[i].x;
      jposn[i].y = jaxis[i].y;
      jposn[i].w = jaxis[i].w;
      jposn[i].h = 10;
   }
   
   for (i = 0; i < 16; i++) {
      jb[i] = 0;
      jbut[i].x = 10 + (16 * i);
      jbut[i].y = 10;
      jbut[i].w = 10;
      jbut[i].h = 10;
   }
   
   /* Do we have any joysticks connected? */
   if (SDL_NumJoysticks() < 1) {
      printf("Warning: No joysticks connected\n");
      na = nb = nh = 0;
   }
   else { 
      /* If we have one, open joystick */
      joystick = SDL_JoystickOpen(0);
      if (joystick == NULL) { 
         printf("Warning: Unable to open game controller: SDL Error: %s\n", SDL_GetError());
         na = nb = nh = 0;
      }
      else {
         printf("Name: %s\n", SDL_JoystickNameForIndex(0));
         printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joystick));
         printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joystick));
         printf("Number of Hats: %d\n", SDL_JoystickNumHats(joystick));
         
         na = SDL_JoystickNumAxes(joystick);
         nb = SDL_JoystickNumButtons(joystick);
         nh = SDL_JoystickNumHats(joystick);
      }
   }

   /* Create SDL window */
   window = SDL_CreateWindow("helloSDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

   if (window == NULL) { 
      printf("Window could not be created: SDL_Error: %s\n", SDL_GetError());
      SDL_Quit();
      exit(EXIT_FAILURE);
   }               

   /* Get window surface */
   screenSurface = SDL_GetWindowSurface(window); 

   /* Generate some colours */
   white = SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff);
   blue  = SDL_MapRGB(screenSurface->format, 0x40, 0x40, 0xff);
   black = SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00);
   grey  = SDL_MapRGB(screenSurface->format, 0x80, 0x80, 0x80);
   red   = SDL_MapRGB(screenSurface->format, 0xff, 0x40, 0x40);
   yellow= SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0x40);
   green = SDL_MapRGB(screenSurface->format, 0x40, 0xff, 0x40);
   
   x = (SCREEN_WIDTH / 2) - (100 / 2); 
   y = (SCREEN_HEIGHT / 2) - (100 / 2); 
      
   do {
      while (SDL_PollEvent(&e) != 0) {
         printf("EVENT: %d ", e.type);

         if (e.type == SDL_QUIT) {
            printf("QUIT\n");
            running = 0;
         }
         else if (e.type == SDL_WINDOWEVENT) {
            printf("WINDOW EVENT %d\n", e.window.event);
         }
         else if (e.type == SDL_MOUSEMOTION) {
            printf("MOUSE %d TO %d,%d\n", e.motion.which, e.motion.x, e.motion.y);
         }
         else if (e.type == SDL_MOUSEBUTTONDOWN) {
            printf("MOUSE %d BUTTON %d DOWN\n", e.button.which, e.button.button);
         }
         else if (e.type == SDL_MOUSEBUTTONUP) {
            printf("MOUSE %d BUTTON %d UP\n", e.button.which, e.button.button);
         }
         else if (e.type == SDL_JOYAXISMOTION) {
            printf("JOYSTICK %d MOVED AXIS %d TO %d\n", e.jaxis.which, e.jaxis.axis, e.jaxis.value);
            if (e.jaxis.which == 0) {
               ja[e.jaxis.axis] = e.jaxis.value;
               
               switch (e.jaxis.axis) {
               case 0:
                  if (e.jaxis.value < -8000) {
                     x -= 2;
                     if (hlx > 0)
                        hlx--;
                  }
                  else if (e.jaxis.value > 8000) {
                     x += 2;
                     if (hlx < 7)
                        hlx++;
                  }
                  break;
               case 1:
                  if (e.jaxis.value < -8000) {
                     y -= 2;
                     if (hly < 7)
                        hly++;
                  }
                  else if (e.jaxis.value > 8000) {
                     y += 2;
                     if (hly > 0)
                        hly--;
                  }
                  break;
               case 2:
                  break;
               case 3:
                  break;
               }
            }
         }
         else if (e.type == SDL_JOYHATMOTION) {
            printf("JOYSTICK %d HAT %d TO %d\n", e.jhat.which, e.jhat.hat, e.jhat.value);
         }
         else if (e.type == SDL_JOYBUTTONDOWN) {
            printf("JOYSTICK %d BUTTON %d DOWN\n", e.jbutton.which, e.jbutton.button);
            jb[e.jbutton.button] = 1;
            switch (e.jbutton.button) {
            case 0:
               if (hlx < 7)
                  hlx++;
               
               if (hly < 7)
                  hly++;

               break;
            case 1:
               if (hlx < 7)
                  hlx++;
               
               if (hly > 0)
                  hly--;
                  
               break;
            case 2:
               if (hlx > 0)
                  hlx--;
                  
               if (hly > 0)
                  hly--;
                  
               break;
            case 3:
               if (hlx > 0)
                  hlx--;

               if (hly < 7)
                  hly++;
                  
               break;
            case 4:
               break;
            case 8:
               running = 0;
               break;
            }
         }
         else if (e.type == SDL_JOYBUTTONUP) {
            printf("JOYSTICK %d BUTTON %d UP\n", e.jbutton.which, e.jbutton.button);
            jb[e.jbutton.button] = 0;
         }
         else if (e.type == SDL_KEYDOWN) {
            printf("KEYBOARD %d DOWN\n", e.key.keysym.sym);
            
            switch (e.key.keysym.sym) {
            case SDLK_UP:
               if (hly < 7)
                  hly++;

               y -= 2;
               break;
            case SDLK_DOWN:
               if (hly > 0)
                  hly--;

               y += 2;
               break;
            case SDLK_LEFT:
               if (hlx > 0)
                  hlx--;
                  
               x -= 2;
               break;
            case SDLK_RIGHT:
               if (hlx < 7)
                  hlx++;
                  
               x += 2;
               break;
            case SDLK_q:
               running = 0;
               break;
            }
         }
         else if (e.type == SDL_KEYUP) {
            printf("KEYBOARD %d UP\n", e.key.keysym.sym);
         }
         else {
            printf("UNHANDLED\n");
         }
      }
      
      /* Fill the surface white */
      SDL_FillRect(screenSurface, NULL, white);

#if 0
      /* Draw a blue box */
      box.x = x;
      box.y = y;
      box.w = 100;
      box.h = 100;
      
      SDL_FillRect(screenSurface, &box, blue);
#endif
      
      /* Display joystick buttons */
      for (i = 0; i < 16; i++) {
         if (i < nb) {
            if (jb[i])
               SDL_FillRect(screenSurface, &jbut[i], blue);
            else
               SDL_FillRect(screenSurface, &jbut[i], black);
         }
         else
            SDL_FillRect(screenSurface, &jbut[i], grey);
      }
      
      if (na >= 2) {
      }
      
      for (i = 0; i < 16; i++) {
         if (i < na) {
            SDL_FillRect(screenSurface, &jaxis[i], black);
            jposn[i].y = jaxis[i].y + (ja[i] / 512) + 64;
            SDL_FillRect(screenSurface, &jposn[i], blue);
         }
         else
            SDL_FillRect(screenSurface, &jaxis[i], grey);
      }
      
      /* Draw an isometric grid */
      for (y0 = 0; y0 <= 320; y0 += 40) {
         for (x0 = 0; x0 <= 320; x0 += 2) {

            pixel.x = ((SCREEN_WIDTH / 2) + x0) - (y0 / 1);
            pixel.y = ((SCREEN_HEIGHT - 1) - (x0 / 2)) - (y0 / 2);
            pixel.w = 2;
            pixel.h = 2;
         
            SDL_FillRect(screenSurface, &pixel, black);
         }
      }

      for (x0 = 0; x0 <= 320; x0 += 40) {
         for (y0 = 0; y0 <= 320; y0 += 2) {

            pixel.x = ((SCREEN_WIDTH / 2) + x0) - (y0 / 1);
            pixel.y = ((SCREEN_HEIGHT - 1) - (x0 / 2)) - (y0 / 2);
            pixel.w = 2;
            pixel.h = 2;
         
            SDL_FillRect(screenSurface, &pixel, black);
         }
      }

      /* Highlight one square on the isometric grid */
      z0 = 40;
      for (x0 = (hlx * 40) + 2; x0 < (hlx * 40) + 40; x0 += 2) {
         for (y0 = (hly * 40) + 2; y0 < (hly * 40) + 40; y0 += 2) {

            pixel.x = ((SCREEN_WIDTH / 2) + x0) - (y0 / 1);
            pixel.y = ((SCREEN_HEIGHT - 1) - (x0 / 2)) - (y0 / 2) - z0;
            pixel.w = 2;
            pixel.h = 2;
         
            SDL_FillRect(screenSurface, &pixel, red);
         }
      }

      x0 = (hlx * 40) + 2;
      for (z0 = (hlz * 40) + 0; z0 < (hlz * 40) + 38; z0 += 2) {
         for (y0 = (hly * 40) + 2; y0 < (hly * 40) + 40; y0 += 2) {

            pixel.x = ((SCREEN_WIDTH / 2) + x0) - (y0 / 1);
            pixel.y = ((SCREEN_HEIGHT - 1) - (x0 / 2)) - (y0 / 2) - z0;
            pixel.w = 2;
            pixel.h = 2;
         
            SDL_FillRect(screenSurface, &pixel, yellow);
         }
      }

      y0 = (hly * 40) + 2;
      for (z0 = (hlz * 40) + 0; z0 < (hlz * 40) + 38; z0 += 2) {
         for (x0 = (hlx * 40) + 2; x0 < (hlx * 40) + 40; x0 += 2) {

            pixel.x = ((SCREEN_WIDTH / 2) + x0) - (y0 / 1);
            pixel.y = ((SCREEN_HEIGHT - 1) - (x0 / 2)) - (y0 / 2) - z0;
            pixel.w = 2;
            pixel.h = 2;
         
            SDL_FillRect(screenSurface, &pixel, green);
         }
      }

      /* Update the surface */
      SDL_UpdateWindowSurface(window);

      SDL_Delay(40);
   } while (running);
   
   /* Destroy window */
   SDL_DestroyWindow(window);

   SDL_JoystickClose(joystick);
   
   /* Quit SDL subsystem */
   SDL_Quit();

   return (EXIT_SUCCESS);
}
