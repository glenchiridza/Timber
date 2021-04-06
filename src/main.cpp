#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;

int main() {

    //create video mode object
    VideoMode vm(1920,1080);

    //Create and open a window for the game
    RenderWindow window(vm,"Timber Game",Style::Fullscreen);

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



    while(window.isOpen()){
        /*
        handle player input
        */
       if(Keyboard::isKeyPressed(Keyboard::Escape)){
           window.close();
       }

       /*
       update scene
       */

       /*
       draw scene
       */

      //clear window from last frame
      window.clear();

      //draw game scene
      window.draw(spriteBackground);
      
      //show drawing
      window.display();

    }


  }