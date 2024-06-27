#include <SFML/Graphics.hpp>

int main()
{
   sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout Game");

   // Paddle setup
   sf::RectangleShape paddle(sf::Vector2f(100.0f, 20.0f));
   paddle.setFillColor(sf::Color::Red);
   paddle.setPosition(350.0f, 550.0f);

   // Ball setup
   sf::CircleShape ball(10.0f);
   ball.setFillColor(sf::Color::Green);
   ball.setPosition(395.0f, 300.0f);

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
      ball.move(ballVelocity);

      if (ball.getPosition().x <= 0 || ball.getPosition().x + ball.getRadius() * 2 >= window.getSize().x)
      {
         ballVelocity.x = -ballVelocity.x;
      }
      if (ball.getPosition().y <= 0)
      {
         ballVelocity.y = -ballVelocity.y;
      }

      // Ball and paddle collision
      if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds()))
      {
         ballVelocity.y = -ballVelocity.y;
      }

      // Ball out of bounds (bottom)
      if (ball.getPosition().y + ball.getRadius() * 2 >= window.getSize().y)
      {
         // Reset ball position
         ball.setPosition(395.0f, 300.0f);
      }

      window.clear();
      window.draw(paddle);
      window.draw(ball);
      window.display();
   }

   return 0;
}
