#ifdef __APPLE__
#include <GLUT/glut.h> // if we are on a Mac
#else
#include <GL/glut.h> // on linux
#endif

#include <math.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <png.h>
#include <stdlib.h>
#include <vector>
#include <fstream>

// User- Defined header files
#include "png_load.h"
#include "load_and_bind_texture.h"

#include "textures.h"
#include "maze.h"
#include "base.h"
#include "pacman.h"
#include "ghost.h"
#include "interface.h"

int gameTick = 0;
int deathTick = 0;
int frightenTick = 0;
int timestamp;
int score = 0;
int pills = 244;
int lives = 3;
int eatenCount = 0;
bool frighten;
float eatenX;
float eatenY;
int eatStamp;
Pacman pacman;
bool paused = false;
bool dead = false;

int fruitCounter = 0;
int tempFruitCounter = 0;
int eatFruitStamp = 0;
int eatenFruitX;
int eatenFruitY;
int fruitSpawned = 0;

using namespace std;

// Decleration of each of the ghosts.at their respective starting X and Y coordinates and their colour.
Ghost ghosts[4] = {
        Ghost(13.5f, 19.0f, RED),
        Ghost(11.5f, 16.0f, BLUE),
        Ghost(13.5f, 16.0f, PINK),
        Ghost(15.5f, 16.0f, YELLOW),
};

typedef enum {BEGIN, PLAY, DIE, OVER} gameState; // Enum defining each of the states the game can be in

gameState stateGame = BEGIN; // Initially the game in begin mode


void detectPill()
// Detects whether the pill is Bigg pill(O), then ghosts go to Frigthen mode or if pill is Fruit 
{
    if(pacman.getTile(pacman.get_X(), pacman.get_Y()) == O) 
    {
        frighten = true; // Set the flag to know that frigthen mode is on
        frightenTick = 0; // Set the counter to 0
        for(int i = 0; i < 4; i++) 
        {
            if(ghosts[i].get_moveType() == CHASE || ghosts[i].get_moveType() == SCATTER) 
            { 
                ghosts[i].set_eaten(false);
                ghosts[i].set_moveType(FRIGHTEN);
                if(ghosts[i].get_currentDir() == LEFT)  
                    ghosts[i].set_currentDir(RIGHT);
                else if(ghosts[i].get_currentDir() == UP) 
                    ghosts[i].set_currentDir(DOWN);
                else if(ghosts[i].get_currentDir() == RIGHT) 
                    ghosts[i].set_currentDir(LEFT);
                else 
                    ghosts[i].set_currentDir(UP);
            }
        }
    } 
    else if(pacman.getTile(pacman.get_X(), pacman.get_Y()) == F) 
    {
        eatenFruitX = pacman.get_X();
        eatenFruitY = pacman.get_Y();
    }
}

void detectGhost()
// Check if Pacman has encountered a Ghost (i.e. both are on the same tile)
{
    // Check pacmans position against all of the ghosts
    for(int i = 0; i < 4; i++) 
    { 
        if(pacman.get_X() == ghosts[i].get_X() && pacman.get_Y() == ghosts[i].get_Y()) 
        // If he is on the same tile as any ghost
        { 
            if(ghosts[i].get_moveType() != FRIGHTEN && ghosts[i].get_moveType() != DEATH) // Check if they are in a mode which can eat Pacman
            {
                // Execute the DIE gameType as the ghost has caught pacman 
                stateGame = DIE; 
                timestamp = gameTick;
            } 
            else {
                if(!ghosts[i].check_eaten()) 
                // Check the ghost hasnt already been eaten
                { 
                    eatenCount++;
                    eatStamp = gameTick;
                    switch(eatenCount)
                    // Check what eaten number the ghost is in order to increment the score correctly
                    { 
                        case 1: score += 200;
                            break;
                        case 2: score += 400;
                            break;
                        case 3: score += 800;
                            break;
                        case 4: score += 1600;
                            break;
                    }
                    // Store the position of the eating in order to draw the eating score tex in the correct place
                    eatenX = ghosts[i].get_X(); 
                    eatenY = ghosts[i].get_Y();
                    ghosts[i].set_eaten(true); // Set the flag for that specifc ghost to have been eaten so it cannot be eaten again in this frighten cycle
                }
                ghosts[i].set_moveType(DEATH); // Set the ghosts mode to DEATh as it has been eaten
            }
        }
    }
    if(stateGame == DIE && !dead)  
    // Check to see if pacman was indeed caught by the ghost and if so take away a life
    { 
        lives--;
        dead = true;
    }
}

void setMode()
// Sets the ghosts movement technique depending on what the gameTick is
{
    if(gameTick >= 4450) 
    {
        for (int i = 0; i < 4; i++) 
        {
            if (ghosts[i].get_moveType() != PEN && ghosts[i].get_moveType() != LEAVE && !frighten && ghosts[i].get_moveType() != DEATH) 
            // As long as the ghosts are only in SCATTER or CHASE and frighten mode is not on
                ghosts[i].set_moveType(CHASE); // Set the correct move type for all ghosts
        }
    } 
    else if(gameTick >= 4200) 
    {
        for(int i = 0; i < 4; i++) 
        {
            if(ghosts[i].get_moveType() != PEN && ghosts[i].get_moveType() != LEAVE && !frighten && ghosts[i].get_moveType() != DEATH)
                ghosts[i].set_moveType(SCATTER);
        }
    } 
    else if(gameTick >= 3200) 
    {
        for(int i = 0; i < 4; i++) 
        {
            if(ghosts[i].get_moveType() != PEN && ghosts[i].get_moveType() != LEAVE && !frighten && ghosts[i].get_moveType() != DEATH)
                ghosts[i].set_moveType(CHASE);
        }
    } 
    else if(gameTick >= 2950) 
    {
        for(int i = 0; i < 4; i++) 
        {
            if(ghosts[i].get_moveType() != PEN && ghosts[i].get_moveType() != LEAVE && !frighten && ghosts[i].get_moveType() != DEATH)
                ghosts[i].set_moveType(SCATTER);
        }
    } 
    else if(gameTick >= 1950) 
    {
        for(int i = 0; i < 4; i++) 
        {
            if(ghosts[i].get_moveType() != PEN && ghosts[i].get_moveType() != LEAVE && !frighten && ghosts[i].get_moveType() != DEATH)
                ghosts[i].set_moveType(CHASE);
        }
    } 
    else if (gameTick >= 1600) 
    {
        for(int i = 0; i < 4; i++) 
        {
            if(ghosts[i].get_moveType() != PEN && ghosts[i].get_moveType() != LEAVE && !frighten && ghosts[i].get_moveType() != DEATH)
                ghosts[i].set_moveType(SCATTER);
        }
    } 
    else if(gameTick >= 600) 
    {
        for(int i = 0; i < 4; i++) 
        {
            if(ghosts[i].get_moveType() != PEN && ghosts[i].get_moveType() != LEAVE && !frighten && ghosts[i].get_moveType() != DEATH)
                ghosts[i].set_moveType(CHASE);
        }
    }
}

void idle()
// All options are altered when game is in idle state
{
    if(!paused) 
    { // If the game is not paused
        switch (stateGame) 
        // Check what state the game is in
        { 
            case BEGIN:
                if (gameTick >= 250) 
                // After a certain amount of time switch the game into PLAY mode 
                    stateGame = PLAY;
                break;
            case PLAY:
                setMode(); // Set the movement mode for Ghosts
                detectPill(); // Check if pacman has eaten a super pill
                pacman.checkTile(); // Check if pacman has eaten a regular pill to increase score if he is in a portal
                detectGhost(); // Check if pacman has hit a ghost
                pacman.move(); // Move pacman in the maze
                detectGhost();
                // Move the ghosts in the maze
                for (int i = 0; i < 4; i++) 
                { 
                    ghosts[i].move(ghosts[0]);
                }
                detectGhost();
                // If frighten mode is on and not expired, increment the counter
                if (frightenTick <= 450 && frighten)  
                    frightenTick++;
                
                else if (frighten) 
                // If frighten mode is on but needs to expire, run correct expirary code
                { 
                    frighten = false;
                    eatenCount = 0;
                    frightenTick = 0;
                    for (int i = 0; i < 4; i++) 
                    {
                        if (ghosts[i].get_moveType() == FRIGHTEN) 
                            ghosts[i].set_eaten(false);
                    }
                    setMode(); // Set the ghosts back into the correct mode after frighten mode has finished
                }
                if (pills <= 0) 
                // If all the pills have been eaten reset the level so pacman can continue
                { 
                    fruitReset();
                    resetMaze();
                    pacman.reset();
                    pills = 244;
                    fruitSpawned = 0;
                    fruitCounter = 0;
                    tempFruitCounter = 0;
                    for (int i = 0; i < 4; i++) {
                        ghosts[i].reset();
                    }
                    gameTick = 0;
                    stateGame = BEGIN;
                }
                break;
            case DIE:
                if (gameTick - timestamp >= 150) 
                // Play pacmans death animation
                    deathTick++;
                break;

        }
        gameTick++;

        glutPostRedisplay(); // Force a redraw at the end
    }
}


void special(int key, int, int)
// to handle special keys such as directions and assign them 
{
    switch (key)
    {
        case GLUT_KEY_LEFT: pacman.setDirStore(LEFT); // If left key press set pacmans next direction to left
            break;
        case GLUT_KEY_UP: pacman.setDirStore(UP); // If up key press set pacmans next direction to up
            break;
        case GLUT_KEY_RIGHT: pacman.setDirStore(RIGHT); // If right key press set pacmans next direction to right
            break;
        case GLUT_KEY_DOWN: pacman.setDirStore(DOWN); // If down key press set pacmans next direction to down
            break;
    }
}

void init()
// Method run at the very beginning to initiale certain aspects of the game
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 300, 0, 300);
    loadAndBindTextures();
}


void display()
// Function to display objects on the screen (using draw)
{
    glClear (GL_COLOR_BUFFER_BIT);
    switch(stateGame)
    // Check what state the game is in
    { 
        case BEGIN:
            drawMaze();
            pacman.draw();
            for(int i = 0; i < 4; i++)
                ghosts[i].draw();
            drawInterface();
            drawReady();
            break;
            
        case PLAY:
            drawMaze();
            pacman.draw();
            if(pills <= 174 && fruitSpawned == 0) 
                locationFruit();
            if(pills <= 74 && fruitSpawned == 1) 
                locationFruit();
            if(fruitCounter > tempFruitCounter) 
                eatFruitStamp = gameTick;
            if(gameTick - eatFruitStamp <= 200)
                eatFruitScore(eatenFruitX, eatenFruitY);
            for(int i = 0; i < 4; i++)
            {
                ghosts[i].draw();
                if(frighten && gameTick - eatStamp <= 200) 
                    ghosts[i].drawEatScore(eatenX, eatenY);
            }
            drawInterface();
            tempFruitCounter = fruitCounter;
            break;
            
        case DIE:
            fruitReset();
            drawMaze();
            if(gameTick - timestamp < 150) 
            // Freeze pacman momentarily after he is hit by a ghost
            { 
                pacman.draw();
                for(int i = 0; i < 4; i++)
                    ghosts[i].draw();
            }
            if(gameTick - timestamp >= 150  && deathTick < 110) 
            // After that time has passed play pacmans death animation
                pacman.death();
            if(gameTick - timestamp >= 310) 
            // After the death animation, reset pacman
            { 
                pacman.reset();
                for(int i = 0; i < 4; i++)
                    ghosts[i].reset(); // Reset the ghosts also
                gameTick = 0;
                eatFruitStamp = -9999999;
                deathTick = 0;
                if(lives > 0)
                    // If pacman has lives left begin the game again
                    stateGame = BEGIN;
                else 
                { 
                    // Otherwise show the gameover screen
                    setHighScore(score); // If the game is finished check if the high score needs to be updated
                    stateGame = OVER;
                }
            }
            drawInterface();

            break;
        case OVER:
            drawMaze();
            drawInterface();
            drawGameOver();
    }

    glutSwapBuffers(); // Force a redraw at the end
}

void resetGame()
// Function to reset the game if the player wants to play the game again 
{
    gameTick = 0;
    deathTick = 0;
    score = 0;
    lives = 4;
    pills = 244;
    fruitCounter = 0;
    fruitSpawned = 0;
    tempFruitCounter = 0;
    stateGame = BEGIN;
}

void keyboard(unsigned char key, int, int)
// Function to assign keyboard buttons other than special ones
{
    switch (key)
    {
        case 'q': exit(1); // quit!
        case 'p':// Key to pause the game
            if(paused) 
                paused = false;
            else 
                paused = true;
            break;
        case 'r':
            if(stateGame == OVER) 
            {
                resetGame();
                pacman.reset();
                fruitReset();
                resetMaze();
                for(int i = 0; i < 4; i++) 
                    ghosts[i].reset(); // Reset the ghosts also
            }
            break;
    }

    glutPostRedisplay(); // force a redraw
}

int main(int argc, char* argv[])
{

    glutInit(&argc, argv); // we can pass certain X windows attributes to GLUT

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);

    glutInitWindowSize(750,725);
    glutCreateWindow("Pacman"); // a named window of default size and position
    glutDisplayFunc(display);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);


    init();
    glutMainLoop(); // go into the main loop and wait for window events...

    return 0; // safe to return 0 to shell unless error

}
