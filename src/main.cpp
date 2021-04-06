#include <iostream>
#include "SFML/Graphics.hpp"

using namespace sf;

int main() {

    //create video mode object
    VideoMode vm(1920,1080);

    //Create and open a window for the game
    RenderWindow window(vm,"Timber Game",Style::Fullscreen);

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

      
      //show drawing
      window.display();

    }


  }