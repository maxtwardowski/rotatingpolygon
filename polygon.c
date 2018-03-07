#include "primlib.h"
#include <stdlib.h>
#include <math.h>

#define DEFAULT_XCORD screenWidth() / 2 //X axis coordinate of the polygon's centre
#define DEFAULT_YCORD screenHeight() / 2 //Y axis coordinate of the polygon's centre
#define DEFAULT_VERTICE_LENGTH 120 //Initial vertice length
#define VERTICES 7 //Number of vertices of the polygon
#define ANGLE_STEP 10 * M_PI / 180 //Number of radians added per one tick
#define ZOOM_STEP 1.015 //Multiplicator of the vertice length
#define FPS_RATE 60 //FPS cap
#define THRESHOLD 50 //Maximum number of iterations before zoom in/out change

void cleanScreen();

void polygonDraw(double vertice_length, double rotation_angle);

int main(int argc, char* argv[]) {
    if(initGraph()) {
        exit(3);
    }
    int loop_counter, zoomin = 1;
    double rotation_angle = 0, vertice_length = DEFAULT_VERTICE_LENGTH;

    while(1) {
        cleanScreen();
        polygonDraw(vertice_length, rotation_angle);

        loop_counter++;
        if (loop_counter >= THRESHOLD) {
            loop_counter = 0;
            if (zoomin)
                zoomin = 0;
            else
                zoomin = 1;
            }

            //Spinning and zooming
            rotation_angle += ANGLE_STEP;
            if (zoomin) {
                    vertice_length *= ZOOM_STEP;
            }
            else {
                    vertice_length /= ZOOM_STEP;
            }
            updateScreen(); //Refreshing the screen
            SDL_Delay(1000 / FPS_RATE); //Setting FPS cap
    }
    return 0;
}

void cleanScreen() {
    //This function clears the screen making it black
	filledRect(0, 0, screenWidth(), screenHeight(), BLACK);
}

void polygonDraw(double vertice_length, double rotation_angle) {
    //This function draws a polygon
    double next_xcord, next_ycord, prev_xcord, prev_ycord;
    int i;
    for(i = 0; i <= VERTICES; i++) {
            next_xcord = vertice_length * cos((2 * M_PI * i + rotation_angle) / VERTICES) + DEFAULT_XCORD;
            next_ycord = vertice_length * sin((2 * M_PI * i + rotation_angle) / VERTICES) + DEFAULT_YCORD;
            if (i != 0)
                line(prev_xcord, prev_ycord, next_xcord, next_ycord, RED);
            prev_xcord = next_xcord;
            prev_ycord = next_ycord;
    }
}
