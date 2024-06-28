#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Breakout Game");

    // Paddle setup Texture, Sprite
    sf::Texture paddleTexture;
    paddleTexture.loadFromFile("C:/Users/Noor Links/OneDrive/Desktop/Breakout/Breakout Tile Set Free/PNG/MainPaddle.png");
    sf::Sprite paddleSprite;
    paddleSprite.setTexture(paddleTexture);
    paddleSprite.setPosition(350.0f, 550.0f);
    paddleSprite.setScale(0.1f, 0.1f);

    // Ball texture and sprite setup
    sf::Texture ballTexture;
    ballTexture.loadFromFile("C:/Users/Noor Links/OneDrive/Desktop/Breakout/ball.png");
    sf::Sprite ballSprite;
    ballSprite.setTexture(ballTexture);
    ballSprite.setScale(0.1f, 0.1f);
    ballSprite.setPosition(330.0f, 530.0f);

    sf::Vector2f ballVelocity(0.1f, 0.1f);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Paddle movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddleSprite.getPosition().x > 0)
        {
            paddleSprite.move(-0.6f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddleSprite.getPosition().x + paddleSprite.getGlobalBounds().width < window.getSize().x)
        {
            paddleSprite.move(0.6f, 0.0f);
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
        if (ballSprite.getGlobalBounds().intersects(paddleSprite.getGlobalBounds()))
        {
            ballVelocity.y = -ballVelocity.y;
        }

        // Ball out of bounds (bottom)
        if (ballSprite.getPosition().y + ballSprite.getGlobalBounds().height >= window.getSize().y)
        {
            // Reset ball position
            ballSprite.setPosition(330.0f, 530.0f);
        }

        window.clear();
        window.draw(paddleSprite);
        window.draw(ballSprite);
        window.display();
    }

    return 0;
}
