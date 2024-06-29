#include <SFML/Graphics.hpp>

int main()
{
   sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout Game");

   // Paddle setup
   sf::RectangleShape paddle(sf::Vector2f(100.0f, 20.0f));
   paddle.setFillColor(sf::Color::Red);
   paddle.setPosition(350.0f, 550.0f);

   // Ball texture and sprite setup
   sf::Texture ballTexture;
   ballTexture.loadFromFile("./resources/assets/ball.png");
   sf::Sprite ballSprite;
   ballSprite.setTexture(ballTexture);
   ballSprite.setScale(0.1f, 0.1f);
   ballSprite.setPosition(395.0f, 300.0f);

   sf::Vector2f ballVelocity(0.3f, 0.3f);

   while (window.isOpen())
   {
      sf::Event event{};
      while (window.pollEvent(event))
      {
         if (event.type == sf::Event::Closed)
            window.close();
      }

      // Paddle movement
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddle.getPosition().x > 0)
      {
         paddle.move(-0.6f, 0.0f);
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddle.getPosition().x + paddle.getSize().x < window.getSize().x)
      {
         paddle.move(0.6f, 0.0f);
      }

      // Ball movement and bouncing logic
      ballSprite.move(ballVelocity);

      if (ballSprite.getPosition().x <= 0 || ballSprite.getPosition().x + ballSprite.getGlobalBounds().width >= window.getSize().x)
      {
         ballVelocity.x = -ballVelocity.x;
      }
      if (ballSprite.getPosition().y <= 0)
      {
         ballVelocity.y = -ballVelocity.y;
      }

      // Ball and paddle collision
      if (ballSprite.getGlobalBounds().intersects(paddle.getGlobalBounds()))
      {
         ballVelocity.y = -ballVelocity.y;
      }

      // Ball out of bounds (bottom)
      if (ballSprite.getPosition().y + ballSprite.getGlobalBounds().height >= window.getSize().y)
      {
         // Reset ball position
         ballSprite.setPosition(395.0f, 300.0f);
      }

      window.clear();
      window.draw(paddle);
      window.draw(ballSprite);
      window.display();
   }

   return 0;
}
