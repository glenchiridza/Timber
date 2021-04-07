#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;

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


    while(window.isOpen()){
        /*
        handle player input
        */
       Event event;
       while(window.pollEvent(event)){
       if(Keyboard::isKeyPressed(Keyboard::Escape)){
           window.close();
       }
       }

       /*
       update scene
       */

      //Measure time
      Time dt = clock.restart();

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

      
      //show drawing
      window.display();

    }


  }