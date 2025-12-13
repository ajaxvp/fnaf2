#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_video.h"
#include "SDL3/SDL_image.h"

#include "log.h"

#define SCREEN_WIDTH_RATIO 4
#define SCREEN_HEIGHT_RATIO 3

SDL_Window* gWindow = NULL;

SDL_Surface* gScreenSurface = NULL;

SDL_Surface* gHelloWorld = NULL;

bool init(size_t window_multiplier)
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) == false)
    {
        errorf("failed to initialize SDL: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", SCREEN_WIDTH_RATIO * window_multiplier, SCREEN_HEIGHT_RATIO * window_multiplier, 0);
        if (!gWindow)
        {
            errorf("could not create program window: %s\n", SDL_GetError());
            success = false;
        }
        else
            gScreenSurface = SDL_GetWindowSurface(gWindow);
    }

    return success;
}

bool load_media(void)
{
    bool success = true;

    char* imagePath = "resources/img/1.png";
    gHelloWorld = IMG_Load(imagePath);
    if (!gHelloWorld)
    {
        errorf("Unable to load image %s! SDL Error: %s\n", imagePath, SDL_GetError());
        success = false;
    }

    return success;
}

void close(void)
{
    //Clean up surface
    SDL_DestroySurface(gHelloWorld);
    gHelloWorld = NULL;
    
    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gScreenSurface = NULL;

    SDL_Quit();
}


int main(int argc, char** argv)
{
    //Final exit code
    int code = EXIT_SUCCESS;

    //Initialize
    if (init(256) == false )
    {
        SDL_Log( "Unable to initialize program!\n" );
        code = EXIT_FAILURE;
    }
    else
    {
        //Load media
        if (!load_media())
        {
            SDL_Log( "Unable to load media!\n" );
            code = EXIT_FAILURE;
        }
        else
        {
            //The quit flag
            bool quit = false;

            //The event data
            SDL_Event e;
            SDL_zero(e);
            
            //The main loop
            while (!quit)
            {
                //Get event data
                while (SDL_PollEvent(&e))
                {
                    //If event is quit type
                    if (e.type == SDL_EVENT_QUIT)
                    {
                        //End the main loop
                        quit = true;
                    }
                }

                //Fill the surface white
                SDL_FillSurfaceRect(gScreenSurface, NULL, SDL_MapSurfaceRGB( gScreenSurface, 0xFF, 0xFF, 0xFF));
            
                //Render image on screen
                SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

                //Update the surface
                SDL_UpdateWindowSurface(gWindow);
            } 
        }
    }

    //Clean up
    close();

    return code;
}
