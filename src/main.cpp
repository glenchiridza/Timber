#include <iostream>
#include <sstream>
#include "SFML/Graphics.hpp"

using namespace sf;

//function declaration
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

//position of player, left / right ?
enum class side {LEFT, RIGHT, NONE};
side branchPos[NUM_BRANCHES];

int main() {

    //create video mode object
    VideoMode vm(960,540);

    //Create and open a window for the game
    // RenderWindow window(vm,"Timber Game",Style::Fullscreen);

    //low resolution code
    RenderWindow window(vm,"Timber Game");
    View view(FloatRect(0,0,1920,1080));
    window.setView(view);
    //end low resolution code

    //create texture to hold graphic on GPU
    Texture textureBackground;

    //load graphic into the texture
    textureBackground.loadFromFile("graphics/background.png");

    //creat sprite
    Sprite spriteBackground;

    //attach texture to sprite
    spriteBackground.setTexture(textureBackground);

    //set sprite background to cover screen
    spriteBackground.setPosition(0,0);

    //,make a tree sprite
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810,0);

    //prepare bee
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0,800);

    //is bee currently moving
    bool beeActive = false;

    //how fast can the bee fly
    float beeSpeed = 0.0f;

    //make 3 cloud sprites from one texture
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    //3 sprites
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;

    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    //position clouds to the left of the screen
    //at different heights
    spriteCloud1.setPosition(0,0);
    spriteCloud2.setPosition(0,250);
    spriteCloud3.setPosition(0,500);

    //are clouds currently on screen
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    //how fast is the cloud
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3speed = 0.0f;

    //variable to control time itself
    Clock clock;

    //time bar
    RectangleShape timebar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timebar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timebar.setFillColor(Color::Red);
    timebar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool paused  = true;

    //draw text
    int score = 0;
    Text msg;
    Text scoreTxt;

//load font
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    //set font to our message
    msg.setFont(font);
    scoreTxt.setFont(font);

    //assign the actual message
    msg.setString("Press enter to start");
    scoreTxt.setString("Score = 0");

    //make it really big
    msg.setCharacterSize(65);
    scoreTxt.setString("Score = 0");

    //choose a color
    msg.setFillColor(Color::White);
    scoreTxt.setFillColor(Color::White);

    //position the text
    FloatRect textRect = msg.getLocalBounds();
    msg.setOrigin(textRect.left + 
        textRect.width / 2.0f,
        textRect.top +
        textRect.height / 2.0f);
        
    msg.setPosition(1920 / 2.0f,1080/2.0f);    
    scoreTxt.setPosition(20,20);
  
  //prepare 6 branches
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    //set the texture for each branch sprite
    for( int i =0; i < NUM_BRANCHES; i++){
      branches[i].setTexture(textureBranch);
      branches[i].setPosition(-2000,-2000);//hide off the screen

      //set sprite origin to dead centre, can spin it arouind without changing its position
      branches[i].setOrigin(220,20);
    }


    while(window.isOpen()){
        /*
        handle player input
        */
       Event event;
       while(window.pollEvent(event)){
       if(Keyboard::isKeyPressed(Keyboard::Escape)){
           window.close();
       }

       //start the game
       if(Keyboard::isKeyPressed(Keyboard::Return)){
         paused = false;

         //reset the time and score
         score = 0;
         timeRemaining = 6;
       }
       if(Keyboard::isKeyPressed(Keyboard::Space)){
         paused = true;
       }
       }

       /*
       update scene
       */

      if(!paused){

      //Measure time
      Time dt = clock.restart();


      //subtract from the amount of time remaining
      timeRemaining  -= dt.asSeconds();
      //size up the time bar
      timebar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

      if(timeRemaining <= 0.0f){
        //pause the game, time has run out
        paused = true;

        //change the message shown to the player
        msg.setString("out of time!");

        //reposition the text based on its new size
        FloatRect textRect = msg.getLocalBounds();
        msg.setOrigin(textRect.left + 
          textRect.width / 2.0f,
          textRect.top + 
          textRect.height / 2.0f);

          msg.setPosition(1920 / 2.0f, 1080 / 2.0f);

      }

      //setup bee
      if(!beeActive){

        //how fast is the bee
        srand((int)time(0));
        beeSpeed = (rand() % 200) +200;

        //how high is the bee
        srand((int)time(0) * 10);
        float height = (rand() % 500) + 500;
        spriteBee.setPosition(2000, height);

        beeActive = true;
      }
      else{
        spriteBee.setPosition(
          spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()),
          spriteBee.getPosition().y
        );

        //has the bee reached the left hand edge of the screen
        if(spriteBee.getPosition().x < -100){

          //set it up ready to be a whole new bee next frame
          beeActive = false;
        }
      }

      //manage the clouds
      //cloud 1

      if(!cloud1Active){

        //how fast is the cloud
        srand((int)time(0) * 10);
        cloud1Speed = (rand() % 200);

        //how high is the cloud
        srand((int)time(0) * 10);
        float height = (rand() % 150);
        spriteCloud1.setPosition(-200, height);
        cloud1Active = true;
      }else{

        spriteCloud1.setPosition(
          spriteCloud1.getPosition().x +
          (cloud1Speed * dt.asSeconds()),
          spriteCloud1.getPosition().y
        );

        //has the cloud reached the right end of the screen
        if(spriteCloud1.getPosition().x > 1920){

          //set it up ready to be a new cloud in the next frame
          cloud1Active = false;
        }
      }

      //cloud 2

      if(!cloud2Active){
        //how fast is the cloud
        srand((int)time(0) * 20);
        cloud2Speed = (rand() % 200);

        //how high is the cloud
        srand((int)time(0) * 20);
        float height = (rand() % 300) - 150;
        spriteCloud2.setPosition(-200, height);
        cloud2Active = true;
      }else{

        spriteCloud2.setPosition(
          spriteCloud2.getPosition().x +
          (cloud2Speed * dt.asSeconds()),
          spriteCloud2.getPosition().y
        );

        if(spriteCloud2.getPosition().x > 1920){
          //set it up ready to be a new cloud in next frame
          cloud2Active = false;
        }
      }

//cloud 3
      if(!cloud3Active){
        //how fast is the cloud
        srand((int)time(0) * 30);
        cloud3speed = (rand() % 200);

        //how high is the cloud
        srand((int)time(0) * 30);
        float height = (rand() % 450)-150;
        spriteCloud3.setPosition(-200, height);
        cloud3Active = true;
      }else{
        spriteCloud3.setPosition(
          spriteCloud3.getPosition().x +
          (cloud3speed * dt.asSeconds()),
          spriteCloud3.getPosition().y
        );
        if(spriteCloud3.getPosition().x > 1920){
          //set it up ready to be a new cloud in next frame
          cloud3Active = false;
        }
         }

      // update score text

      std::stringstream ss;
      ss<<"Score = " << score;
      scoreTxt.setString(ss.str());

      //update branch sprites
      for (int i=0;i<NUM_BRANCHES;i++){
        float height = i * 150;

        if(branchPos[i] == side::LEFT)
        {
          //move sprite to the left
          branches[i].setPosition(610, height);

          //flip the sprite around the other ay
          branches[i].setRotation(180);
        }else if (branchPos[i] == side::RIGHT)
        {
          
        }

      }

      } //end if pause

       /*
       draw scene
       */

      //clear window from last frame
      window.clear();

      //draw game scene
      window.draw(spriteBackground);

      //draw clouds
      window.draw(spriteCloud1);
      window.draw(spriteCloud2);
      window.draw(spriteCloud3);

      //draw tree
      window.draw(spriteTree);

      //draw insect
      window.draw(spriteBee);

      //draw the score
      window.draw(scoreTxt);

      if(paused){
        //draw message
        window.draw(msg);
      }

      //draw the timebar
      window.draw(timebar);
      
      //show drawing
      window.display();

    }


  }