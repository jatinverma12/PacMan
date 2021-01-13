#ifndef COURSEWORK_MAZE_H
#define COURSEWORK_MAZE_H

extern unsigned int maze_tex;
extern unsigned int pill_tex;
extern unsigned int bigPill_tex;
extern int gameTick;
extern int fruitSpawned;
extern int fruitCounter;

/**
 * Tile defined as an enum where each type is defined as:
 *      W: Wall
 *      G: Ghost Pen Gate
 *      P: Portal
 *      u: Empty path
 *      o: Pill
 *      e: Eaten Pill
 *      O: Big Pill
 *      E: Eaten Big Pill
 */
typedef enum {W, G, P, u, o, e, O, E, F} tile;

// 2D array defines the size of the maze and also what each tile contains
tile maze[28][31] =
        {
                {W,W,W,W,W,W,W,W,W,W,W,W,u,u,u,W,P,W,u,u,u,W,W,W,W,W,W,W,W,W,W},
                {W,o,o,o,o,W,W,O,o,o,o,W,u,u,u,W,u,W,u,u,u,W,o,o,o,o,O,o,o,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,W,u,W,W,W,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,u,u,u,u,u,u,u,u,u,W,W,o,o,o,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,W,W,W,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,u,u,u,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,o,o,o,W,W,o,o,o,o,W,W,u,W,u,u,u,W,u,u,u,o,W,W,o,o,o,o,o,W},
                {W,o,W,W,W,W,W,u,W,W,W,W,W,u,W,u,u,u,G,u,W,W,W,W,W,o,W,W,W,W,W},
                {W,o,W,W,W,W,W,u,W,W,W,W,W,u,W,u,u,u,G,u,W,W,W,W,W,o,W,W,W,W,W},
                {W,o,o,o,o,W,W,o,o,o,o,W,W,u,W,u,u,u,W,u,u,u,o,W,W,o,o,o,o,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,u,u,u,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,W,W,W,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,u,u,u,u,u,u,u,u,u,W,W,o,o,o,o,W,W,W,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,W,u,W,W,W,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,o,o,o,W,W,O,o,o,o,W,u,u,u,W,u,W,u,u,u,W,o,o,o,o,O,o,o,o,W},
                {W,W,W,W,W,W,W,W,W,W,W,W,u,u,u,W,P,W,u,u,u,W,W,W,W,W,W,W,W,W,W}
        };

void translateToMazeCoords(float x, float y)
// Translates objects x and y coordinates into translatable values to be placed on the maze
{
    glTranslatef(x * 8, y * 8, 0.0f);
}

void translateBottomLeft()
// Translates the current position of drawing to the bottom left corner of the map.
{
    glTranslatef(38.0f, 26.0f, 0.0f);
}

tile getTile(float x, float y)
// Returns the type of tile on (x,y)
{
    return maze[(int) floor(x)][(int) floor(y)];
}

void eatFruitScore(int x, int y)
// Draws the score when fruit is eaten
{
    glPushMatrix();


    unsigned int eat_score_tex;
    
    // Pick which texture to draw depending on which number fruit is being eaten
    switch(fruitCounter) 
    { 
        case 1: eat_score_tex = score_100_tex;
            break;
        case 2: eat_score_tex = score_300_tex;
            break;
    }

    translateBottomLeft();
    translateToMazeCoords(x, y); // Translate to correct part of the screen for drawing
    glTranslatef(-2.0f, 0.0f, 0.0f);

    if(fruitCounter != 0) 
     // Only draw the fruit score if the fruit has been eaten
        drawTex(eat_score_tex, 15, 8, 0);
        
    glPopMatrix();
}


void fruitReset()
// Resets the fruit if Pacman dies and fruit is not eaten
{
    for(int x=0;x<28;x++) 
    {            
        for(int y=0;y<31;y++) 
        {
            if (maze[x][y] == F) 
            {
                    maze[x][y] = e; // If a fruit tile is found reset it
                    break;
            }
        }
    }
}

void locationFruit()
// Randomly spawns a Fruit in the maze
{
    int x, y;
    do 
    {
        x = rand() % 27;
        y = rand() % 12;
    } 
    while(getTile(x, y) != e);

    // Set the new tile type to be F
    maze[(int) floor(x)][(int) floor(y)] = F; 
    fruitSpawned++; 
}

void drawFruit()
// Draw the fruit
{
    glTranslatef(-2.0f, -2.0f, 0.0f); 
    if(fruitCounter == 0) 
        drawTex(cherry_tex, 14, 14, 0);
    else 
        drawTex(strawberry_tex, 14, 14, 0);
    glTranslatef(2.0f, 2.0f, 0.0f); 
}


void drawMaze()
// draw maze 
{
    glPushMatrix();

    translateBottomLeft();              // Translate to bottom left of screen
    drawTex(maze_tex, 224, 248, 0);     // Draw the map walls using the sprite
    for(int x=0;x<28;x++) 
    {             
        glPushMatrix();

        for(int y=0;y<31;y++) 
        {
            switch(maze[x][y]) 
            {
                case o:                 
                // Draw pills as sprites
                    drawTex(pill_tex, 8, 8, 0);
                    break;
                case O:                 
                // Draw big pills as sprites
                    if(gameTick % 30 <= 15) 
                        drawTex(bigPill_tex, 8, 8, 0);
                    break;
                case F:
                    drawFruit();
                    break;
            }

            glTranslatef(0.0f, 8.0f, 0.0f); // Increment Y position
        }
        glPopMatrix();

        glTranslatef(8.0f, 0.0f, 0.0f);     // Increment X position
    }
    glPopMatrix();
}

void resetMaze()
// Refill all pills on Game reset
{
    for(int x=0;x<28;x++) 
    {            
        for (int y = 0; y < 31; y++) 
        {
            switch (maze[x][y]) 
            {
                case e:                 
                // Draw small pills
                    maze[x][y] = o;
                    break;
                case E:                 
                // Draw big pills 
                    maze[x][y] = O;
                    break;
            }
        }
    }
}

#endif //COURSEWORK_MAP_H
