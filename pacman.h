#ifndef COURSEWORK_PACMAN_H
#define COURSEWORK_PACMAN_H

#include "base.h"

int pacTick = 0;

extern int score;
extern int pills;
extern int deathTick;
extern bool dead;
extern int eatenCount;
extern int fruitCounter;

bool start = true;


class Pacman : public Character
{
    direction dirStore;
    float angle;
public:
    Pacman();
    direction get_dirStore();
    float get_angle();
    void draw();
    void reset();
    void checkTile();
    void death();
    void setDirStore(direction);
    void move();
    
  };


    Pacman :: Pacman()
    //Upon initialisation of pacman set X and Y directions. Also set the current direction and the stored direction to NONE
    {
        X = 13.5f;
        Y =  7.0f;
        currentDir = NONE;
        dirStore = NONE;
    }
    
    direction Pacman :: get_dirStore()
    {
        return dirStore;
    }
    
    float Pacman :: get_angle()
    {
        return angle;
    }

    void Pacman :: draw()
    // Draw pacman relative to his current X and Y positions
    {
        glPushMatrix();

        unsigned int pac_tex;
        int tickDiv;

        if(!dead) 
            tickDiv = pacTick % 30;

        if(currentDir == NONE) 
            tickDiv = 0;

        if(gameTick < 250) 
        // If the game is not in BEGIN mode
            pac_tex = pac_2_tex;
        else 
        {
            if (tickDiv % 30 < 10) 
                pac_tex = pac_0_tex;
            else if (tickDiv % 30 < 20) 
                pac_tex = pac_1_tex;
            else 
                pac_tex = pac_2_tex;
        }

        switch(currentDir)
        // Rotates pacman to face in his current travel direction
        { 
            case LEFT: angle = 0.0f;
                break;
            case UP: angle = 270.0f;
                break;
            case RIGHT: angle = 180.0f;
                break;
            case DOWN: angle = 90.0f;
                break;
            default: currentDir = NONE;
        }

        translateBottomLeft(); // Translate to bottom left of screen which is (0,0)
        translateToMazeCoords(X, Y);

        glTranslatef(-3.0f, -3.0f, 0.0f); // Translate to take into account pacmans size

        drawTex(pac_tex, 14, 14, angle);

        glPopMatrix();

        pacTick++;

    }

    void Pacman :: reset()
    // Reset all of pacmans variables to that when he is initiliased
    {
        X = 13.5f;
        Y =  7.0f;
        currentDir = NONE;
        dirStore = NONE;
        angle = 0.0f;
        start = true;
        dead = false;
        eatenCount = 0;
    }

    
    void Pacman :: death()
    // Applying death animation and translating pacman to correct area upon death due to ghost encounter
    {
        glPushMatrix();

        unsigned int pac_tex;

	// Depending on the deathTick, assign the corresponding death sprite
        if (deathTick < 10)                  
            pac_tex = dead_0_tex;
        else if (deathTick % 110 < 20) 
            pac_tex = dead_1_tex;
        else if (deathTick % 110 < 30) 
            pac_tex = dead_2_tex;
        else if (deathTick % 110 < 40) 
            pac_tex = dead_3_tex;
        else if (deathTick % 110 < 50) 
            pac_tex = dead_4_tex;
        else if (deathTick % 110 < 60) 
            pac_tex = dead_5_tex;
        else if (deathTick % 110 < 70) 
            pac_tex = dead_6_tex;
        else if (deathTick % 110 < 80) 
            pac_tex = dead_7_tex;
        else if (deathTick % 110 < 90) 
            pac_tex = dead_8_tex;
        else if (deathTick % 110 < 100) 
            pac_tex = dead_9_tex;
        else 
            pac_tex = dead_10_tex;
        

        translateBottomLeft();  // Translate to bottom left of screen which is (0,0)
        translateToMazeCoords(X, Y);

        glTranslatef(-3.0f, -3.0f, 0.0f);
        drawTex(pac_tex, 14, 14, 0);
        glPopMatrix();


    }

    
    void Pacman :: checkTile()
    // Method called to check pacmans current position and, if present, eat the pill occupying that tile or translate him to other portal
    {
        switch(getTile(X, Y)) 
        {
            case o:                                                     
            // If pacman is on a small pill, increment score accordingly and remove it from the map
                maze[(int) floor(X)][(int) floor(Y)] = e;
                score += 10;
                pills--;
                break;
            case O:                                                     
            // If pacman is on a large pill, increment score accordingly and remove it from the map
                maze[(int) floor(X)][(int) floor(Y)] = E;
                score += 50;
                pills--;
                break;
            case P:
            // If pacman is on a portal tile, translate his position to the other side of the map
                if (get_X() >= 26.5)                    
                    X = 1.0f;
                 else 
                    X = 26.5f;
      
                break;
            case F:                                     
            // If pacman is on a fruit, increment score accordingly and remove it from the map
                maze[(int) floor(X)][(int) floor(Y)] = e;
                fruitCounter++; // Increment counter for fruits eaten
                // Determine how much to increment the score by
                if(fruitCounter == 1)  
                    score += 100;
                else 
                    score += 300;

        }
    }

    void Pacman :: setDirStore(direction pressedDir)
    // Used to pass the user pressed direction to the dirStore variable for later use
    {
        dirStore = pressedDir;
    }

    
    void Pacman :: move()
    /*
     * Checks what pacmans current direction is set as and translates accordingly
     * Furthermore, will not move pacman if his next tile in his current direction is a wall.
     * Also checks to see if the last pressed direction button from the user will cause pacman to face a wall, if it does not
     * move pacman in that direction.
     */
    {
        if(isAtCenter()) 
        // Only move if pacman is at the centre of the tile
        { 
            if (!isWall(dirStore)) 
            // If the direction pacman wants to go in is not a wall, set that direction
                set_currentDir(dirStore);
            else if (isWall(currentDir)) 
            // If the direction pacman wants to travel in is a wall and the direction he is currently travelling is a wall, stop his movement
                currentDir = NONE; 
        }
        if(!isAtCenter() && dirStore != NONE && start && !isWall(dirStore))
        // Check to not cause pacman to jump at the very beginning of the game
        { 
            set_currentDir(dirStore);
            start = false;
        }

        switch (currentDir) 
        {
            case LEFT:
                X -= 0.1f;
                Y = round(Y);
                break;
            case UP:
                Y += 0.1f;
                X = round(X);
                break;
            case RIGHT:
                X += 0.1f;
                Y = round(Y);
                break;
            case DOWN:
                Y -= 0.1f;
                X = round(X);
                break;
            default:
                if(!start) 
                // Do not round pacman if it is the very start as he start between two tiles
                { 
                    X = round(X);
                    Y = round(Y);
                }
        }
    }

#endif //COURSEWORK_PACMAN_H
