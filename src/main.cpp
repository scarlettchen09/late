#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <iostream>
int main()
{
    sf::Vector2i screenDimensions(800, 600);

    sf::RenderWindow Window;
    Window.create(sf::VideoMode(screenDimensions.x, screenDimensions.y), "My First SFML Game");
    Window.setKeyRepeatEnabled(false);
    sf::Texture bTexture;
    sf::Sprite bImage;

    if(!bTexture.loadFromFile("../resources/Background.jpg"))
      std::cout << "Could not load background image" << std::endl;

    bImage.setTexture(bTexture);
    bImage.setScale(9.0f, (float)screenDimensions.y / bTexture.getSize().y);

    sf::RectangleShape rect(sf::Vector2f(20, 20));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(40, screenDimensions.y-20);
    sf::Clock clock;

    float moveSpeed = 10000.0f;
    float xVel = 10000.0f;
    float yVel = 0.0f;

    float xAcl = 0.0f;
    float yAcl = 0.0f;

    sf::View view;

    view.reset(sf::FloatRect(0, 0, screenDimensions.x, screenDimensions.y));
    view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    sf::Vector2f position(screenDimensions.x / 2, screenDimensions.y / 2);

    while(Window.isOpen()){
      clock.restart();
      sf::Event Event;
      while(Window.pollEvent(Event)){
        switch(Event.type){
          case sf::Event::Closed:  Window.close();
            break;
            Window.close();
            break;
          case sf::Event::KeyPressed:
            if(Event.key.code == sf::Keyboard::Escape){

            
              Window.close();
              
            }
            if(Event.key.code == sf::Keyboard::Space){
              if(rect.getPosition().y == screenDimensions.y - 20)
                yAcl = 0.75f;
            }
            break;
              

          
        }
      }
      /*
      if(yAcl > 2.0f){
        yAcl = 2.0f;
      }
      */

      if(rect.getPosition().y < screenDimensions.y - 20){
        yAcl = -0.0005f;
      }

      yVel += yAcl;
      rect.setPosition(rect.getPosition().x, rect.getPosition().y - yVel);
      
      if(rect.getPosition().y > screenDimensions.y - 20){
        rect.setPosition(rect.getPosition().x, screenDimensions.y - 20);
      }
      if(rect.getPosition().y == screenDimensions.y - 20){
        yAcl = 0.0f;
        yVel = 0.0f;
      }

      position.x += .2;
      rect.setPosition(position.x + 40, rect.getPosition().y);
      /*
      //rect.move(0, yVel )
      yVel -= yAcl;
      rect.setPosition(rect.getPosition().x, rect.getPosition().y + yVel);
      /*
      if(rect.getPosition().y >= 0 ){
         yVel += yAcl;
         rect.setPosition(rect.getPosition().x, rect.getPosition().y + yVel);
      }
      
        
      //rect.position.y = rect.getPosition().y + yVel;
      
     
      if(rect.getPosition().y < screenDimensions.y - 20){
        yAcl += .5f;
      }else{
        yAcl = 0.0f;
        yVel = 0.0f;
      }
      std::cout << "yVel: " << yVel << " yPos: " << rect.getPosition().y << std::endl;
      */
      /*
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        rect.move(moveSpeed * clock.getElapsedTime().asSeconds(), 0);
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        rect.move(-moveSpeed * clock.getElapsedTime().asSeconds(), 0);
     
      if(rect.getPosition().x + 10 > screenDimensions.x / 2)
        position.x = rect.getPosition().x + 10;
      else
        position.x = screenDimensions.x / 2;
      */
      
      /*
      position.x = rect.getPosition().x + 10 - (screenDimensions.x / 2);
      position.y = rect.getPosition().y + 10 - (screenDimensions.y / 2);

      if(position.x < 0)
        position.x = 0;
      if(position.y < 0)
        position.y = 0;
      */
      //view.reset(sf::FloatRect(position.x, position.y, screenDimensions.x, screenDimensions.y));
      //if(rect.getPosition().x + 10 > screenDimensions.x / 2)

      view.setCenter(position);
      Window.setView(view);

      Window.draw(bImage);
      Window.draw(rect);

      Window.display();
      Window.clear();
    }

   

    return 0;
}