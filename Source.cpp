//SFML C++ Bullet Hell
// Created by Dr. Mo Jan 2022
//dynamicsofanasteroid.com

#include<iostream>
#include<vector>
#include"SFML/Graphics.hpp"
#include"globals.h"
#include"missiles.h"
#include"bullets.h"
#include"stars.h"
using namespace std;

int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(SCREEN_W, SCREEN_H), "Bullet Hell"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    screen.setFramerateLimit(60); //set FPS



    //player setup------------------------------------------------
    sf::Texture ship;
    ship.loadFromFile("ship.png");
    sf::IntRect playerImg(0, 0, 30, 30); //select portion of image to draw (our ship is 30x30)
    sf::Sprite player(ship, playerImg);
    int ticker = 0;
    int frameNum = 0;
    // player.setTexture(ship); //use this instead of the lines above for static images
    int xpos = 400;
    int ypos = 700;
    int vx = 0;
    int vy = 0;
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false, false };

    //missile setup
    int justShot = 0;
    sf::Texture MissileImg;
    MissileImg.loadFromFile("missile.png");
    sf::Sprite MissilePic;
    MissilePic.setTexture(MissileImg);

    sf::Texture BulletImg;
    BulletImg.loadFromFile("bullet.png");
    sf::Sprite BulletPic;
    BulletPic.setTexture(BulletImg);

    //bullet setup
    double minBullets = 60;
    int counter = 0;
    int moveTimer = 0;

    //vector for missiles
    vector<missile*> missiles; //Creates a VECTOR, that POINTS to CLASS missiles
    vector<missile*>::iterator iter2; //Creates an ITERATOR, that will iterate through the missiles VECTOR
    for (int i = 0; i < 5; i++) {
        missile* newMissile = new missile(xpos, ypos, MissilePic); //using class constructor to instantiate missiles
        missiles.push_back(newMissile); //puts these missiles into the back of the vector
    }

    //vector for bullets
    vector<bullet*> bullets; 
    vector<bullet*>::iterator iter3;

    //vector for stars
    vector<star*> stars; 
    vector<star*>::iterator iter4; 
    for (int i = 0; i < 400; i++) {
        star* newStar = new star(); 
        stars.push_back(newStar);
    }


    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        //animate player 
        ticker += 1; //ship's engines are always animating 
        if (ticker % 10 == 0) //make this number bigger to slow down animations
            frameNum += 1; 
        if (frameNum > 4)
            frameNum = 0;
            


        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();
            //KEYBOARD INPUT 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                keys[SPACE] = true;
            }
            else keys[SPACE] = false;

        }//end event loop---------------------------------------------------------------

        //movement stuff
        if (keys[LEFT] == true) {
            vx = -5;
            playerImg = sf::IntRect((frameNum + 5) * 32, 0, -30, 30); //NEGATIVE width flips the image for us 
        }
        else if (keys[RIGHT] == true) {
            vx = 5;
            playerImg = sf::IntRect((frameNum + 5) * 32, 0, 30, 30);
        }
        else {
            vx = 0;
            playerImg = sf::IntRect(frameNum * 32, 0, 30, 30);
        }

        if (keys[UP] == true) {
            vy = -5;
        }
        else if (keys[DOWN] == true) {
            vy = 5;
        }
        else
            vy = 0;

        //bullet stuff
        counter++;
        minBullets -= .001; 
        if (counter > minBullets) {
            bullet* newbullet = new bullet(500,100, 0, BulletPic); 
            bullets. push_back(newbullet); 
            bullet* newbullet2 = new bullet(500, 100, 3.14, BulletPic); 
            bullets.push_back(newbullet2); 
            bullet* newbullet3 = new bullet(500, 100, 3.14 / 2, BulletPic); 
            bullets. push_back(newbullet3); 
            bullet* newbullet4 = new bullet(500, 100, 3 * 3.14 / 2, BulletPic); 
            bullets. push_back(newbullet4); 
            counter = 0;
        }

        //missile stuff
        justShot++;
        if (keys[SPACE] == true) {
            for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
                if (((*iter2)->isAlive()) == false && justShot > 5) {
                    (*iter2)->shoot(xpos, ypos);
                    justShot = 0;
                }
            }
        }

        sf::Sprite player(ship, playerImg);
        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);

        //move da missiles
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            if ((*iter2)->isAlive())
                (*iter2)->move();
        }

        //move da bullets
        moveTimer += 2; 
        if (moveTimer > 2400) 
            moveTimer = 0; 
        for (iter3 = bullets.begin(); iter3 != bullets.end(); iter3++) {
            if (moveTimer < 600) {
                (*iter3)->move1();
            }
            else if (moveTimer < 1200) {
                (*iter3)->move2();
            }
            else if (moveTimer < 1800) {
                (*iter3)->move3();
            }
            else if (moveTimer < 2400) {
                (*iter3)->move4();
            }
        }

        //move da stars(so pretty)
        for (iter4 = stars.begin(); iter4 != stars.end(); iter4++) {
            (*iter4)->reposition();
            (*iter4)->move();
        }

        //kiel da missiles
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
            if ((*iter2)->offScreen())
                (*iter2)->kill();
        }

        //kiel da bullets
        for (iter3 = bullets.begin(); iter3 != bullets.end(); iter3++) {
            if ((*iter3)->offScreen()) {
                (*iter3)->~bullet(); //#destroyed
                iter3 = bullets.erase(iter3); //remove from vector
            }
        }


        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear

        screen.draw(player); //draw player

        //draw missiles
        for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
                (*iter2)->draw(screen);
        }

        //draw bullets
        for (iter3 = bullets.begin(); iter3 != bullets.end(); iter3++) {
            (*iter3)->draw(screen);
        }

        //draw stars?
        for (iter4 = stars.begin(); iter4 != stars.end(); iter4++) {
            (*iter4)->draw(screen);
        }

        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

} //end of main