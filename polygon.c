#include "primlib.h"
#include <stdlib.h>
#include <math.h>

#define START_X1 300
#define START_Y1 200
#define START_EDGE_LENGTH 150
#define EDGES 6
#define PI 3.14
#define ANGLE_STEP 0.15
#define ZOOM 1.025


int main(int argc, char* argv[]) {

    float rotation_angle, sidelength;
    rotation_angle = 0;

    sidelength = START_EDGE_LENGTH;

    if(initGraph()) {
        exit(3);
    }

    while(1) {

        filledRect(0, 0, screenWidth() - 1, screenHeight() - 1, BLACK);
        int i, x_next, y_next, x_prev, y_prev;

        x_prev = START_X1;
        y_prev = START_Y1;

        for(i = 0; i <= EDGES; i++) {

            x_next = sidelength * cos((2 * PI * i + rotation_angle) / EDGES) + START_X1;
            y_next = sidelength * sin((2 * PI * i + rotation_angle) / EDGES) + START_Y1;
            if(i != 0)
                line(x_prev, y_prev, x_next, y_next, WHITE);
            x_prev = x_next;
            y_prev = y_next;
        }

        updateScreen();
        SDL_Delay(1000 / FPS);
        getkey();
        if (isKeyDown(SDLK_RIGHT))
            rotation_angle += ANGLE_STEP;
        else if (isKeyDown(SDLK_LEFT))
            rotation_angle -= ANGLE_STEP;
        else if (isKeyDown(SDLK_UP))
            sidelength *= ZOOM ;
        else if (isKeyDown(SDLK_DOWN))
            sidelength /= ZOOM;
        else if (isKeyDown(SDLK_ESCAPE))
            exit(0);
    }
    return 0;
}
