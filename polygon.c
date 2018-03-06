#include "primlib.h"
#include <stdlib.h>
#include <math.h>

#define DEFAULT_XCORD screenWidth() / 2 //X axis coordinate of the polygon's centre
#define DEFAULT_YCORD screenHeight() / 2 //Y axis coordinate of the polygon's centre
#define DEFAULT_VERTICE_LENGTH 150
#define VERTICES 6 //Number of vertices of the polygon
#define PI 3.14
#define ANGLE_STEP 0.15 //Number of radians
#define ZOOM_STEP 1.025 //Multiplicator of the vertice length
#define FPS_RATE 60


int main(int argc, char* argv[]) {
    if(initGraph()) {
        exit(3);
    }

    int i, next_xcord, next_ycord, prev_xcord = DEFAULT_XCORD, prev_ycord = DEFAULT_YCORD;;
    float rotation_angle = 0, vertice_length = DEFAULT_VERTICE_LENGTH;
    SDL_Event event;

    while(1) {
        filledRect(0, 0, screenWidth(), screenHeight(), BLACK); //Black background
        //Drawing the actual polygon
        for(i = 1; i <= VERTICES; i++) {
            next_xcord = vertice_length * cos((2 * PI * i + rotation_angle) / VERTICES) + DEFAULT_XCORD;
            next_ycord = vertice_length * sin((2 * PI * i + rotation_angle) / VERTICES) + DEFAULT_YCORD;
            line(prev_xcord, prev_ycord, next_xcord, next_ycord, WHITE); //Drawing the vertice
            prev_xcord = next_xcord;
            prev_ycord = next_ycord;
    }

        updateScreen(); //Refreshing the screen
        SDL_Delay(1000 / FPS_RATE); //Setting FPS cap
        SDL_PollEvent(&event); //Event detection

        //Handling keyinput without keyrepeat feature
        /*getkey();
        if (isKeyDown(SDLK_RIGHT))
            rotation_angle += ANGLE_STEP;
        else if (isKeyDown(SDLK_LEFT))
            rotation_angle -= ANGLE_STEP;
        else if (isKeyDown(SDLK_UP))
            vertice_length *= ZOOM_STEP ;
        else if (isKeyDown(SDLK_DOWN))
            vertice_length /= ZOOM_STEP;
        else if (isKeyDown(SDLK_ESCAPE))
            exit(0);*/

        //Handling keyinput with keyrepeat feature
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                       rotation_angle -= ANGLE_STEP;
                       break;
                    case SDLK_RIGHT:
                       rotation_angle += ANGLE_STEP;
                       break;
                    case SDLK_UP:
                       vertice_length *= ZOOM_STEP;
                       break;
                    case SDLK_DOWN:
                       vertice_length /= ZOOM_STEP;
                       break;
                    case SDLK_ESCAPE:
                       exit(1);
                    default:
                       break;
                }
        }
    }
    return 0;
}
