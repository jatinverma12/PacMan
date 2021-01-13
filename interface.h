#ifndef COURSEWORK_INTERFACE_H
#define COURSEWORK_INTERFACE_H

extern int score;
extern int lives;

void drawScore(int scorePrint)
// Draws current score on screen
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(15.0, 32.5); // Translate to the correct area of the screen ready for drawing
    drawTex(score_tex, 40, 8, 0); // Draw the score_tex which is the word "SCORE"
    translateToMazeCoords(4, -1.0); // Translate to below "SCORE" ready to draw numbers
    std::string str = std::to_string(scorePrint); // Convert the current score to a string to enable iteration through number

    for(int i = str.length() -1; i>=0 ; i--) 
    { 
    	// Iterate through the number and draw the correct digit
        switch(str[i]) 
        {
            case '0':
                drawTex(num_0_tex, 8, 8, 0);
                break;
            case '1':
                drawTex(num_1_tex, 8, 8, 0);
                break;
            case '2':
                drawTex(num_2_tex, 8, 8, 0);
                break;
            case '3':
                drawTex(num_3_tex, 8, 8, 0);
                break;
            case '4':
                drawTex(num_4_tex, 8, 8, 0);
                break;
            case '5':
                drawTex(num_5_tex, 8, 8, 0);
                break;
            case '6':
                drawTex(num_6_tex, 8, 8, 0);
                break;
            case '7':
                drawTex(num_7_tex, 8, 8, 0);
                break;
            case '8':
                drawTex(num_8_tex, 8, 8, 0);
                break;
            case '9':
                drawTex(num_9_tex, 8, 8, 0);
                break;
        }
        translateToMazeCoords(-1, 0); 
    }
    glPopMatrix();
}

void drawLives(int liveCount)
// Draws the number of remaining lives on screen
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(2, -2); // Translate to the correct area of the screen ready for drawing
    for(int i = 0; i < liveCount - 1; i++) 
    { 
        drawTex(pac_1_tex, 14, 14, 0);
        translateToMazeCoords(2, 0); // After drawing translate to the right ready for more potential icons to be drawn
    }
    glPopMatrix();
}

int getHighScore()
// Returns the current High Score from highscore.txt
{
    int highScore;
    std::fstream scoreFile("high_score.txt"); // Open a stream to the high score file
    if(scoreFile.good()) 
    // If the file exists get the value from inside
    { 
        scoreFile >> highScore;
        scoreFile.close(); // Close the stream
        return highScore; // Return the score
    } 
    else 
    {
        std::ofstream highScoreFile("high_score.txt"); // Creates the file
        highScoreFile << 0; // Pass in the highscore of 0
        scoreFile.close(); // close the streams
        highScoreFile.close();
    }
    return 0; // Return 0 as the file hadnt previously existed
}

void setHighScore(int score)
// If Current Score is greater than High Score then Updates the new high score
{
    int currentHigh = getHighScore(); // Store the current high score
    if(currentHigh < score) 
    // Only update the high score if the current score is higher than the previous
    { 
        std::ofstream highFile("high_score.txt"); 
        highFile.clear(); 
        highFile << score; // write the new high score to the stream
        highFile.close(); 
    }
}

void drawHigh()
/// Draws the Current High Score on Screen 
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(8.0, 32.5); // Translate to the correct area of the screen ready for drawing
    drawTex(high_tex, 32, 7, 0); // Draw the high_tex which is the word "HIGH"
    translateToMazeCoords(3, -1.0); // Translate to below "HIGH" ready to draw numbers
    std::string str = std::to_string(getHighScore()); // Convert the current score to a string to enable iteration through number

    // Iterate through the number and draw the correct digit
    for(int i = str.length() -1; i>=0 ; i--) 
    { 
        switch(str[i]) 
        {
            case '0':
                drawTex(num_0_tex, 8, 8, 0);
                break;
            case '1':
                drawTex(num_1_tex, 8, 8, 0);
                break;
            case '2':
                drawTex(num_2_tex, 8, 8, 0);
                break;
            case '3':
                drawTex(num_3_tex, 8, 8, 0);
                break;
            case '4':
                drawTex(num_4_tex, 8, 8, 0);
                break;
            case '5':
                drawTex(num_5_tex, 8, 8, 0);
                break;
            case '6':
                drawTex(num_6_tex, 8, 8, 0);
                break;
            case '7':
                drawTex(num_7_tex, 8, 8, 0);
                break;
            case '8':
                drawTex(num_8_tex, 8, 8, 0);
                break;
            case '9':
                drawTex(num_9_tex, 8, 8, 0);
                break;
        }
        translateToMazeCoords(-1, 0); 
    }
    glPopMatrix();
}

void drawReady()
// Draw Ready at begginning of game
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(11.5f, 13.0f); // Translate to the correct area of the screen ready for drawing
    drawTex(ready_tex,40, 8, 0);
    glPopMatrix();
}

void drawGameOver()
// Draw Game Over at the end of the game
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(10.0f, 12.75f); // Translate to the correct area of the screen ready for drawing
    drawTex(gameover_tex,65, 10, 0);
    glPopMatrix();
}

void drawInterface()
// Function to call functions to draw the score and lives to the screen
{
    drawHigh();
    drawScore(score);
    drawLives(lives);
}

#endif //COURSEWORK_INTERFACE_H
