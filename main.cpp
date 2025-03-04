#include<iostream>
#include<vector>
#include "raylib.h"
#include "perc.cpp"
#include "point.cpp"


void drawWindow(int height, int width, vector<point> &pt);
void drawPt(vector<point> &pt);

void init();

using namespace std;

perceptron perc; //initializing the perceptron only once

const int screenWidth = 600;
const int screenHeight = 600;
int numPoints = 2000;

int main()
{   
    init();

    vector<point> pt;
    for (int i = 0; i < numPoints; i++)
    {   
        point newpt(screenHeight,screenWidth);
        pt.push_back(newpt);
    }   
    
    drawWindow(screenHeight,screenWidth, pt);

    CloseWindow(); 
    
    return 0;
}

/*
    Draws the window and acts as the main loop for triggering the core functions
*/
void drawWindow(int height, int width, vector<point> &pt){
    
    ClearBackground(BLACK);
    int i = 0;
    while (!WindowShouldClose()) 
    {   
        BeginDrawing();
            
            DrawLine(0,0,screenHeight,screenWidth,LIGHTGRAY);
            drawPt(pt);
            cout<<++i<<endl; //keeping track of the frames
            
        EndDrawing();
    }


}


/*
    First Draws the points in the coordinates then passes the point coordinates as inputs
    and the points labels as the target values to the train function. 
*/
void drawPt(vector<point> &pt){

    for (int i = 0; i < pt.size(); i++)
    {   
        if(pt[i].label==1){
            DrawCircle(pt[i].x,pt[i].y,6,GRAY);
            DrawCircle(pt[i].x,pt[i].y,4,RAYWHITE);
        } else {
            DrawCircle(pt[i].x,pt[i].y,6,DARKGRAY);
        }

        vector<float> inputs = {pt[i].x,pt[i].y};
        int target = pt[i].label;

        perc.train(inputs,target);

        int eduGuess = perc.think(inputs); 

        if(eduGuess == target){
            DrawCircle(pt[i].x, pt[i].y,4,GREEN);
        } else {
            DrawCircle(pt[i].x, pt[i].y,4,RED);
        }

    }

    
}

/*
    Necessary Raylib initializations
*/
void init(){

    InitWindow(screenWidth, screenHeight, "Perceptron classification");
    SetTargetFPS(1);

}