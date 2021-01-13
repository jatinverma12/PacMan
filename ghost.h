#ifndef COURSEWORK_GHOST_H
#define COURSEWORK_GHOST_H


extern int gameTick;
extern Pacman pacman;
extern bool frighten;
extern int eatenCount;

typedef enum {SCATTER, CHASE, FRIGHTEN, LEAVE, DEATH, PEN} movement;

typedef enum {RED, BLUE, PINK, YELLOW} colour;
direction tempDir = NONE;

class Ghost : public Character
{
    colour ghostColour;
    movement moveType;
    float speed;
    bool eaten;
public:
    Ghost(float x, float y, colour ghost) ;
    movement get_moveType();
    bool check_eaten();
    void drawEatScore(float x, float y);
    void draw();
    void setSpeed();
    void move(Ghost);
    void set_eaten(bool);
    void set_moveType(movement);
    void reset();
    int checkJuncs(float, float);
    float getDistance(int,int,colour,Ghost); 
    void cornerHandler();
    void penMove();
    void setDeath(colour colGhost, Ghost ghost);
    void moveTargetTile(colour,Ghost);
    void setFrighten();
    void setMove(colour,Ghost);
    bool isOnlyWall(direction);
    void penMove(int);
    void portalCheck();
    void leaveMove();
    vector<int> getTargetTile(colour);
 };
 
    Ghost :: Ghost(float x, float y, colour ghost) 
    // Constructor sets the x and y co-ordinate of ghost and the colour of ghost
    {
        X = x;
        Y = y;
        switch (ghost) 
        {
            case RED:
                currentDir = LEFT;
                moveType = SCATTER;
                break;
            case PINK:
                currentDir = DOWN;
                moveType = PEN;
                break;
            case BLUE:
                currentDir = UP;
                moveType = PEN;
                break;
            case YELLOW:
                currentDir = UP;
                moveType = PEN;
                break;
        }
        eaten = false;
        ghostColour = ghost;
        setSpeed();
    }
    
    bool Ghost :: check_eaten()
    {
    	return eaten;
    }
     
    void Ghost :: set_eaten(bool res)
    {
    	eaten=res;
    }
    
    movement Ghost :: get_moveType()
    {
        return moveType;
    }
     
    void Ghost :: set_moveType(movement move)
    {
        moveType=move;
    }

    void Ghost :: drawEatScore(float x, float y)
    // Draws the score added to the game when pacman eats the ghost. This is drawn at the ghosts x and y position at the time of eating
    // and the score also depends on how many ghosts, if any, had been eaten before it
    {
        glPushMatrix();

        unsigned int eat_score_tex;

        switch(eatenCount) 
        // Pick which texture to draw depending on which number ghost is beign eaten
        { 
            case 1: eat_score_tex = score_200_tex;
                break;
            case 2: eat_score_tex = score_400_tex;
                break;
            case 3: eat_score_tex = score_800_tex;
                break;
            case 4: eat_score_tex = score_1600_tex;
                break;
        }

        translateBottomLeft();
        translateToMazeCoords(x, y); // Translate to correct part of the screen for drawing
        glTranslatef(-2.0f, 0.0f, 0.0f);

        if(eatenCount != 0) 
        // Only draw if a ghost has been eaten
            drawTex(eat_score_tex, 10, 8, 0);

        glPopMatrix();
    }

    void Ghost :: draw() 
    // draw the ghost
    {
        glPushMatrix();

        unsigned int ghost_tex;
        unsigned int ghost_eye_tex;

        if (moveType != FRIGHTEN && moveType != DEATH) 
        // As long as the ghost is not in death or frighten mode, then draw
        { 
            int tickDiv = gameTick % 20;
            if (tickDiv % 20 < 10) 
            {
                switch (ghostColour) 
                { 
                    case RED:
                        ghost_tex = ghost_r_0_tex;
                        break;
                    case BLUE:
                        ghost_tex = ghost_b_0_tex;
                        break;
                    case PINK:
                        ghost_tex = ghost_p_0_tex;
                        break;
                    case YELLOW:
                        ghost_tex = ghost_y_0_tex;
                        break;
                }
            } 
            else 
            {
                switch (ghostColour) 
                {
                    case RED:
                        ghost_tex = ghost_r_1_tex;
                        break;
                    case BLUE:
                        ghost_tex = ghost_b_1_tex;
                        break;
                    case PINK:
                        ghost_tex = ghost_p_1_tex;
                        break;
                    case YELLOW:
                        ghost_tex = ghost_y_1_tex;
                        break;
                }
            }

            switch (currentDir) 
            // 
            { 
                case LEFT:
                    ghost_eye_tex = eye_left_tex;
                    break;
                case UP:
                    ghost_eye_tex = eye_up_tex;
                    break;
                case RIGHT:
                    ghost_eye_tex = eye_right_tex;
                    break;
                case DOWN:
                    ghost_eye_tex = eye_down_tex;
                    break;
            }
        } 
        else if(moveType == FRIGHTEN)
        // If the ghost is frightened, then draw
        { 
            int tickDiv = gameTick % 40;
            if (tickDiv % 40 < 10) {
                ghost_tex = ghost_scared_0_tex;
            } 
            else if (tickDiv % 40 < 20) {
                ghost_tex = ghost_scared_1_tex;
            } 
            else if (tickDiv % 40 < 30) {
                ghost_tex = ghost_scared_2_tex;
            } 
            else {
                ghost_tex = ghost_scared_3_tex;
            }
        } 
        else  if(moveType == DEATH) 
        {
            switch (currentDir) 
            // Change Eye position to direction the ghost is moving
            { 
                case LEFT:
                    ghost_eye_tex = eye_left_tex;
                    break;
                case UP:
                    ghost_eye_tex = eye_up_tex;
                    break;
                case RIGHT:
                    ghost_eye_tex = eye_right_tex;
                    break;
                case DOWN:
                    ghost_eye_tex = eye_down_tex;
                    break;
            }
        }


        translateBottomLeft(); // Translate to bottom left of screen
        translateToMazeCoords(X, Y);

        glTranslatef(-3.0f, -3.0f, 0.0f);

        if(moveType != DEATH) 
        // If the ghost is not dead then draw
        { 
            drawTex(ghost_tex, 14, 14, 0);
        }

        if (moveType != FRIGHTEN) 
        // If the ghost is not frightened then draw 
        { 
            drawTex(ghost_eye_tex, 14, 14, 0);
        }

        glPopMatrix();

    }

    void Ghost :: reset() 
    // Reset the ghosts to their initial settings/ positions when the game is restarted
    {
        switch (ghostColour) 
        // Different settings depending on the colour of the ghost
        { 
            case RED:
                X = 13.5f;
                Y = 19.0f;
                currentDir = LEFT;
                moveType = SCATTER;
                break;
            case BLUE:
                X = 11.5f;
                Y = 16.0f;
                currentDir = UP;
                if (pills <= 163) 
                    moveType = LEAVE;
                else 
                    moveType = PEN;                
                break;
            case YELLOW:
                X = 15.5f;
                Y = 16.0f;
                currentDir = UP;
                if (pills <= 214) 
                    moveType = LEAVE;
                else 
                    moveType = PEN;
                break;
            case PINK:
                X = 13.5f;
                Y = 16.0f;
                currentDir = DOWN;
                moveType = LEAVE;
                break;
        }
        eaten = false; // Upon reset no ghost has been eaten
    }

    void Ghost :: setSpeed()
    // Sets the speed accordingly to what mode ghosts are in
    {
        if (moveType == FRIGHTEN) 
        { // Move slower if frightened
            speed = 0.5f;
        } 
        else {
            speed = 0.1f;
        }
    }

    void Ghost :: move(Ghost ghost) 
    // Assigns the relevant movement technique to each ghost
    {
        setSpeed();
        if(ghostColour == BLUE)
    	{
    	    if(pills == 163)
                moveType = LEAVE;
        }
        else if(ghostColour == YELLOW)
    	{
    	    if(pills == 214)
                moveType = LEAVE;
        }
            
    	switch(moveType)
    	{
            case SCATTER:
                portalCheck();
                setMove(ghostColour, ghost);
                break;
            case CHASE:
                portalCheck();
                setMove(ghostColour, ghost);
                break;
            case FRIGHTEN:
                portalCheck();
                setFrighten();
                break;
            case DEATH:
                setDeath(ghostColour, ghost);
                break;
            case LEAVE:
                leaveMove();
                break;
            case PEN: 
                penMove(1);
                break;
        }
    }

    int Ghost :: checkJuncs(float x, float y)  
    // Returns the number of possible exits from the specified position
    {
        int exit = 0;
        // Check all directions and if its not a wall in that direction, increment the counter
        if (!isWall(LEFT)) 
            exit++;
        if (!isWall(UP)) 
            exit++;
        if (!isWall(RIGHT))
            exit++;
        if (!isWall(DOWN))
            exit++;

        return exit;
    }

    float Ghost :: getDistance(int x, int y, colour ghostCol, Ghost ghost)  
    // Returns the distance from the point given to the target tile
    {
        vector<int> v = getTargetTile(ghostCol);
        int targetX = v.at(0);
        int targetY = v.at(1);

        if (ghostCol == BLUE && moveType == CHASE) {
            float tempX = ghost.get_X() - targetX;
            float tempY = ghost.get_Y() - targetY;
            targetX = ghost.get_X() + 2 * tempX;
            targetY = ghost.get_Y() + 2 * tempY;
        }

        return (sqrt(((targetX - x) * (targetX - x)) + ((targetY - y) * (targetY - y))));
    }

    void Ghost :: cornerHandler() 
    // If Ghost encounters a corner then
    {
        if (isAtCenter()) 
        // Checks it is at the centre of its tile
        { 
            if (isWall(currentDir)) 
            // Checks whether if it were to keep moving in it current direction if it would hit a wall
            { 
            // Checks its new direction wouldnt make it hit a wall AND that its not reversing direction
                if (!isWall(LEFT) && currentDir != RIGHT)  
                    currentDir = LEFT;
                else if (!isWall(UP) && currentDir != DOWN) 
                    currentDir = UP;
                else if (!isWall(RIGHT) && currentDir != LEFT) 
                    currentDir = RIGHT;
                else 
                    currentDir = DOWN;
            }
        }
    }

    void Ghost :: penMove()
    // Used to move ghosts back into the pen for the final move during the DEATH moveType.
    {
        if (X <= 13.55 && X >= 13.45) 
        // Checks if it has the correct X coordinates
        { 
            // Then move up or down 
            if (Y >= 18.95f) 
                currentDir = DOWN;
            else if (Y <= 17.0f)
                moveType = LEAVE;
        } 
        else 
        {
            // Th
            if (X < 13.5f) { // Determine if they need to move left or right
                currentDir = RIGHT;
            } else if (X > 13.5f) {
                currentDir = LEFT;
            }
        }
        // As on the final call to this method the moveType is changed they could still move 0.1f in a direciton when not needed, so necessary check for moveType
        switch (currentDir) 
        {
            case LEFT:
                X -= speed;
                break;
            case UP:
                Y += speed;
                break;
            case RIGHT:
                X += speed;
                break;
            case DOWN:
                Y -= speed;
                break;
        }
    }

    void Ghost :: setDeath(colour colGhost, Ghost ghost)
    // Sets the route for the ghost to take on death
    {
        float distance = 999.0f;
        bool move = true;
        if(X <= 13.55 && X >= 13.45 && Y >= 15.5f && Y <= 20.0f) 
        {
            penMove();
        } 
        else 
        {
            if (checkJuncs(X, Y) >= 3 && isAtCenter()) 
            {
                if (currentDir != DOWN && !isOnlyWall(UP)) {
                    float d = getDistance(get_X(), get_Y() + 1, colGhost, ghost);
                    if (d < distance) 
                    {
                        tempDir = UP;
                        distance = d;
                    }
                }
                if (currentDir != LEFT && !isOnlyWall(RIGHT)) 
                {
                    float d = getDistance(get_X() + 1, get_Y(), colGhost, ghost);
                    if (d < distance) 
                    {
                        tempDir = RIGHT;
                        distance = d;
                    }
                }
                if (currentDir != RIGHT && !isOnlyWall(LEFT)) 
                {
                    float d = getDistance(get_X() - 1, get_Y(), colGhost, ghost);
                    if (d < distance) 
                    {
                        tempDir = LEFT;
                        distance = d;
                    }
                }
                if (currentDir != UP && !isOnlyWall(DOWN)) {
                    float d = getDistance(get_X(), get_Y() - 1, colGhost, ghost);
                    if (d < distance) 
                    {
                        tempDir = DOWN;
                        distance = d;
                    }
                }
                currentDir = tempDir;
            } 
            else 
                cornerHandler();

            if(move) 
            {
                switch (currentDir) 
                {
                    case LEFT:
                        X -= speed;
                        Y = round(Y);
                        break;
                    case UP:
                        Y += speed;
                        X = round(X);
                        break;
                    case RIGHT:
                        X += speed;
                        Y = round(Y);
                        break;
                    case DOWN:
                        Y -= speed;
                        X = round(X);
                        break;
                }
            }
        }


    };

    void Ghost :: moveTargetTile(colour colGhost, Ghost ghost)
    // Determines which direction to move by checking all potential moves around itself and comparing how close each potential move will put it to the target tile. It then selects the move which puts it the closest to the target tile
    {
        float distance = 999.0f;
        if (checkJuncs(X, Y) >= 3 && isAtCenter()) 
        {
            if (currentDir != DOWN && !isWall(UP)) 
            {
                float d = getDistance(get_X(), get_Y()+1, colGhost, ghost);
                if(d < distance)
                {
                    tempDir = UP;
                    distance = d;
                }
            }
            if (currentDir != LEFT && !isWall(RIGHT)) 
            {
                float d = getDistance(get_X()+1, get_Y(), colGhost, ghost);
                if(d < distance)
                {
                    tempDir = RIGHT;
                    distance = d;
                }
            }
            if (currentDir != RIGHT && !isWall(LEFT) ) 
            {
                float d = getDistance(get_X()-1, get_Y(), colGhost, ghost);
                if(d < distance)
                {
                    tempDir = LEFT;
                    distance = d;
                }
            }
            if (currentDir != UP && !isWall(DOWN)) 
            {
                float d = getDistance(get_X(), get_Y()-1, colGhost, ghost);
                if(d < distance)
                {
                    tempDir = DOWN;
                    distance = d;
                }
            }
            currentDir = tempDir;
        } 
        else
            cornerHandler();


        switch (currentDir) 
        {
            case LEFT:
                X -= speed;
                Y = round(Y);
                break;
            case UP:
                Y += speed;
                X = round(X);
                break;
            case RIGHT:
                X += speed;
                Y = round(Y);
                break;
            case DOWN:
                Y -= speed;
                X = round(X);
                break;
        }
    }

    void Ghost :: setFrighten()
    // Sets the ghosts movement during FRIGHTEN
    {
        direction chosenDir = NONE;
        if (checkJuncs(X, Y) >= 3) 
        // checks if at a junction
        { 
            do 
            {
                int randNum = rand() % checkJuncs(X, Y) - 1; 
                if(randNum == 0 && currentDir != RIGHT) 
                    chosenDir = LEFT;
                else if(randNum == 1 && currentDir != DOWN)
                    chosenDir = UP;
                else if(randNum == 2 && currentDir != LEFT)
                    chosenDir = RIGHT;
                else if(currentDir != UP)
                    chosenDir = DOWN;
            } 
            while (isWall(chosenDir) && currentDir != NONE); // Only select the direction if it is not in a wall and the ghost is currently moving
        } 
        else 
            cornerHandler();

        if(isAtCenter() && chosenDir != NONE) 
        {
            if(!isWall(chosenDir))
                currentDir = chosenDir; // Only apply chosen direction if the ghost is at its centre, the chosen direction is NONE and the chosen direciton doesnt take it into a wal
        }


        switch (currentDir) 
        { 
            case LEFT:
                X -= speed;
                Y = round(Y);
                break;
            case UP:
                Y += speed;
                X = round(X);
                break;
            case RIGHT:
                X += speed;
                Y = round(Y);
                break;
            case DOWN:
                Y -= speed;
                X = round(X);
                break;
        }
    }

    void Ghost :: setMove(colour col, Ghost ghost)
    // Sets the movements for ghost of colour col
    {
        float distance = getDistance(X, Y, RED, ghost); // Get the distance between the ghost and pacman
        switch(col) 
        {
            case RED:
                moveTargetTile(RED, ghost);
                break;
            case PINK:
                moveTargetTile(PINK, ghost);
                break;
            case YELLOW:
                if (distance >= 8.0f) 
                // Yellows movement switches depending on how close he is to pacman
                    moveTargetTile(RED, ghost);
                else
                    moveTargetTile(YELLOW, ghost);
                break;
            case BLUE:
                moveTargetTile(BLUE, ghost);
                break;
        }
    }

    bool Ghost :: isOnlyWall(direction dir)
    // Checks if wall is present in prefered direction
    {
        if (getFollowingTile(dir) == W) 
            return true;

        return false;
    }

    void Ghost :: penMove(int i)
    // Ghost moves up or down inside pen area
    {
        if(Y <= 15.5f && currentDir == DOWN) 
        {
            if(ghostColour == PINK && moveType == PEN) 
                moveType = LEAVE;
            else
                currentDir = UP;
        } 
        else if(Y >= 16.5f && currentDir == UP) 
            currentDir = DOWN;

        switch (currentDir) 
        {
            case UP:
                Y += speed;
                break;
            case DOWN:
                Y -= speed;
                break;
        }
    }

    void Ghost :: portalCheck()
    // Checks if ghost is on a portal tile
    {
        switch(getTile(X, Y))
        {
            case P: if(get_X() >= 26.5) 
                        X = 1.0f;
                    else 
                        X = 26.5;
        }
    }

    void Ghost :: leaveMove()
    // Ghost to leave pen and enter maze
    {
        if (X <= 13.55 && X >= 13.45) 
        // Check if it has correct X coordinates
        { 
            // Then move up and out of the gate
            if (Y < 19.0f) 
                currentDir = UP;
        } 
        else 
        { 
            // Determine if they need to move left or right
            if (X < 13.5f) 
                currentDir = RIGHT;
            else if (X > 13.5f) 
                currentDir = LEFT;
        }

        if(Y >= 19.0f) 
        {
            currentDir = LEFT;
            if(isAtCenter())
                moveType = SCATTER;
        }

        if(moveType == LEAVE) 
        { 
            switch (currentDir) 
            {
                case LEFT:
                    X -= speed;
                    break;
                case UP:
                    Y += speed;
                    break;
                case RIGHT:
                    X += speed;
                    break;
                case DOWN:
                    Y -= speed;
                    break;
            }
        }
    }

    vector<int> Ghost :: getTargetTile(colour ghostCol)
    // Returns vector containing the x and y coordinate of the target tile
    {
        vector<int> v;
        switch(moveType) 
        {
            case CHASE:
                        switch (ghostCol) 
                        {
                            case RED:
                                v.push_back(pacman.get_X());
                                v.push_back(pacman.get_Y());
                                break;
                            case BLUE:
                                switch(pacman.get_currentDir()) 
                                {
                                    case LEFT:
                                        v.push_back(pacman.get_X() - 2);
                                        v.push_back(pacman.get_Y());
                                        break;
                                    case UP:
                                        v.push_back(pacman.get_X() );
                                        v.push_back(pacman.get_Y() + 2);
                                        break;
                                    case RIGHT:
                                        v.push_back(pacman.get_X() + 2);
                                        v.push_back(pacman.get_Y());
                                        break;
                                    case DOWN:
                                        v.push_back(pacman.get_X());
                                        v.push_back(pacman.get_Y() - 2);
                                        break;
                                    default:
                                        v.push_back(pacman.get_X());
                                        v.push_back(pacman.get_Y());
                                }
                                break;
                            case YELLOW:
                                v.push_back(0);
                                v.push_back(0);
                                break;
                            case PINK:
                                switch(pacman.get_currentDir()) 
                                {
                                    case LEFT:
                                        v.push_back(pacman.get_X() - 4);
                                        v.push_back(pacman.get_Y());
                                        break;
                                    case UP:
                                        v.push_back(pacman.get_X() );
                                        v.push_back(pacman.get_Y() + 4);
                                        break;
                                    case RIGHT:
                                        v.push_back(pacman.get_X() + 4);
                                        v.push_back(pacman.get_Y());
                                        break;
                                    case DOWN:
                                        v.push_back(pacman.get_X());
                                        v.push_back(pacman.get_Y() - 4);
                                        break;
                                    default:
                                        v.push_back(pacman.get_X());
                                        v.push_back(pacman.get_Y());
                                }
                                break;
                        }
                break;
            case SCATTER:
                    switch (ghostColour) 
                    {
                        case RED:
                            v.push_back(100);
                            v.push_back(100);
                            break;
                        case BLUE:
                            v.push_back(20);
                            v.push_back(0);
                            break;
                        case YELLOW:
                            v.push_back(0);
                            v.push_back(0);
                            break;
                        case PINK:
                            v.push_back(0);
                            v.push_back(100);
                            break;
                    }
                break;
            case DEATH:
                v.push_back(13.5);
                v.push_back(19);
                break;
        }

        return v;
    }

#endif //COURSEWORK_GHOST_H
