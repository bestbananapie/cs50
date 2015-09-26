//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// Initial Average Velocity
#define VELOCITY 1.0

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
void initVelocity(double *xvel, double *yvel)
{
    *yvel = VELOCITY + drand48() - 0.5;
    *xvel = VELOCITY * (drand48() - 0.5) * 2;
}

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // Randomise initial velocity
    double xvel, yvel;
    initVelocity(&xvel, &yvel);

    // Start game, once window has focus
    waitForClick();

    // keep playing until game over while (lives > 0 && bricks > 0) {
    while (lives > 0 && bricks > 0)
    {
        // Move paddle with mouse or arrows
        GEvent event = getNextEvent(KEY_PRESSED + MOUSE_MOVED);
        if (event != NULL)
        {
            double xPaddleMove = getX(paddle);
            if (getEventType(event) == KEY_PRESSED)
            {
                // 37 is left 39 is right
                switch (getKeyCode(event))
                {
                    case LEFT_ARROW_KEY:
                        xPaddleMove = getX(paddle) - 0.8 * getWidth(paddle);
                        break;
                    case RIGHT_ARROW_KEY:
                        xPaddleMove = getX(paddle) + 0.8 * getWidth(paddle);
                        break;
                    default:
                        break;
                }
            }
            if (getEventType(event) == MOUSE_MOVED)
            {
                xPaddleMove = getX(event) - getWidth(paddle) / 2; 
            }

            // Bound limits
            xPaddleMove = xPaddleMove < 0 ? 0 : xPaddleMove ; 
            xPaddleMove = xPaddleMove > WIDTH - getWidth(paddle) ? 
                            WIDTH - getWidth(paddle) : xPaddleMove;

            setLocation(paddle, xPaddleMove, getY(paddle));
        }

        // Bounce off Walls!
        if (getX(ball) + getWidth(ball) >= getWidth(window) || //
            getX(ball) <= 0)
        {
            xvel = -xvel;
        }

        if (getY(ball) <= 0)
        {
            yvel = -yvel;
        }

        // Lose a life if ball hits bottom wall
        if (getY(ball) + getWidth(ball) >= getHeight(window))
        {
            lives--;
            removeGWindow(window, ball);
            ball = initBall(window);
            // Reset ball velocity
            initVelocity(&xvel, &yvel);
            // Extra pause to realise failure
            pause(500);
        }

        // Detect collision with paddle or brick
        GObject object = detectCollision(window, ball);
        if (object != NULL)
        {
            // Insure ball is hitting the top
            if (object == paddle && yvel > 0)
            {
                yvel = -yvel;
            }

            if (strcmp(getType(object), "GRect") == 0 && object != paddle)
            {
                removeGWindow(window, object);
                bricks--;
                updateScoreboard(window, label, points++);
                yvel = -yvel;
            }
        }

        move(ball, xvel, yvel);
        pause(2);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // Available colours
    int num_colors = 8;
    char *colors[] = {"BLUE",
                      "CYAN",
                      "GREEN",
                      "MAGENTA",
                      "ORANGE",
                      "PINK",
                      "RED",
                      "YELLOW"};


    // Space between bricks
    int padding = 4;

    // Size of a brick
    int width = floor( WIDTH / COLS ) - padding;
    int height = width / 1.618 / 2;

    // Divide up remaining horizontal space, due to rounding
    int dx = ( WIDTH - COLS * (width + padding)) / 2;
    dx += padding / 2;

    // Leave 5% gap at the top
    int dy = 0.05 * HEIGHT;

    // Do rows than columns
    for (int x = 0; x < COLS; x++)
    {
        int xpos = dx + x * (width + padding);
        for (int y = 0; y < ROWS; y++)
        {
            int ypos = dy + y * (height + padding);

            // Render Brick
            GRect brick = newGRect(xpos, ypos, width, height);
            setColor(brick, colors[y % num_colors]);
            setFilled(brick, true);
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval( 0.5 * WIDTH - RADIUS, 0.5 * HEIGHT - RADIUS
                          , RADIUS * 2, RADIUS * 2); 
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);

    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // Proportionally set paddle dimensions
    int width = 0.20 * WIDTH;
    int height = 0.02 * HEIGHT;

    GRect paddle = newGRect( 0.5 * WIDTH - width / 2, 0.8 * HEIGHT, width
                            , height);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel score = newGLabel("0");
    setFont(score, "SansSerif-36");
    setColor(score, "LIGHT_GRAY");
    double x = (getWidth(window) - getWidth(score)) / 2;
    double y = (getHeight(window) - getHeight(score)) / 2;
    setLocation(score, x, y);
    add(window, score);
    return score;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
