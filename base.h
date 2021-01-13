#ifndef COURSEWORK_BASE_H
#define COURSEWORK_BASE_H

typedef enum {LEFT, UP, RIGHT, DOWN, NONE} direction;

class Character
{
public:
    float X;
    float Y;
    direction currentDir;
    int get_X();
    int get_Y();
    direction get_currentDir();
    void set_currentDir(direction);
    bool isWall(direction);
    bool isAtCenter();
    tile getTile(float,float);
    tile getFollowingTile(direction);
    virtual void draw() = 0;
    virtual void move(){};
    virtual void reset() = 0;
};


    int Character :: get_X()
    // Return pacmans x position
    {
        return (int)floor(X);
    }


    int Character :: get_Y()
    //Return pacmans y position
    {
        return (int)floor(Y);
    }
    

    direction Character :: get_currentDir()
    {
        return currentDir;
    }
    
    void Character :: set_currentDir(direction curr)
    {
     	currentDir = curr;
    }

    bool Character :: isAtCenter()
    // Checks if pacman is in the center of his current tile
    {
        return (int)(Y * 10.0f) % 10 == 0 && (int)(X * 10.0f) % 10 == 0;
    }

    
    bool Character :: isWall(direction dir)
    // Checks if the tile in the specified direction is a wall
    {
        if (getFollowingTile(dir) == W || getFollowingTile(dir) == G) 
            return true;

        return false;
    }
    
    tile Character :: getTile(float x, float y)
    // Returns the tile type that pacman is currently on
    {
        return maze[(int)floor(x)][(int)floor(y)];
    }

    tile Character :: getFollowingTile(direction dir)
    // Checks what the tile type is one ahead of pacman in the direction specified
    {
        switch(dir) {
            case LEFT: return getTile(get_X() - 1, get_Y());
            case UP: return getTile(get_X(), get_Y() + 1);
            case RIGHT: return getTile(get_X() +1, get_Y());
            case DOWN: return getTile(get_X(), get_Y() - 1);
            default: return getTile(get_X(), get_Y());
        }
    }


#endif //COURSEWORK_BASE_H
