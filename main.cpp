#include <SFML/Graphics.hpp>
#include <iostream>

void GameEventsFunction(sf::RenderWindow &window) {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                std::cout << "Mouse clicked at: (" << event.mouseButton.x << ", " << event.mouseButton.y << ")\n";
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
    }
}

void PaddleMovementFunction(sf::Sprite &paddleSprite, float paddleSpeed, int windowWidth) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddleSprite.getPosition().x > 147) {
        paddleSprite.move(-paddleSpeed, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddleSprite.getPosition().x + paddleSprite.getGlobalBounds().width < windowWidth) {
        paddleSprite.move(paddleSpeed, 0.0f);
    }
}

void BallMovementFunction(sf::Sprite &ballSprite, sf::Vector2f &ballVelocity, const sf::Sprite &paddleSprite, int windowWidth, int windowHeight) {
    ballSprite.move(ballVelocity);

    if (ballSprite.getPosition().x <= 140 || ballSprite.getPosition().x + ballSprite.getGlobalBounds().width >= windowWidth) {
        ballVelocity.x *= -1;
    }
    if (ballSprite.getPosition().y <= 160) {
        ballVelocity.y *= -1;
    }

    if (ballSprite.getGlobalBounds().intersects(paddleSprite.getGlobalBounds())) {
        ballVelocity.y *= -1;
    }

    if (ballSprite.getPosition().y + ballSprite.getGlobalBounds().height >= windowHeight) {
        ballSprite.setPosition(330.0f, 530.0f);
    }
}

void BallAndCollisionFunction(sf::Sprite &ballSprite, sf::Vector2f &ballVelocity, sf::Sprite tiles[6][6]) {
    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (ballSprite.getGlobalBounds().intersects(tiles[row][col].getGlobalBounds())) {
                sf::FloatRect ballBounds = ballSprite.getGlobalBounds();
                sf::FloatRect tileBounds = tiles[row][col].getGlobalBounds();

                // Calculates the intersection element
                sf::FloatRect intersection;
                ballBounds.intersects(tileBounds, intersection);

                // Determines the collision side
                if (intersection.width < intersection.height) {
                    // Collision is on the left or right side
                    ballVelocity.x *= -1;
                } else {
                    // Collision is on the top or bottom side
                    ballVelocity.y *= -1;
                }
                tiles[row][col].setPosition(900, 1100); // Makes the tile invisible by removing it
                return;
            }
        }
    }
}


int main() {
    // Some Data
    const int WINDOW_HEIGHT = 1000;
    const int WINDOW_WIDTH = 800;
    const float PADDLE_SPEED = 0.6f;
    const float TEXT_SIZE = 20.0f;

    // Data For Tiles
    float tileSize = 50.0f;
    float Tile_Width = 200.0f; // Changes the starting X
    float Tile_Height = 250.0f;// Changes the starting Y
    float Tile_Spacing_h = 40.0f; // Horizontal Tile Spacing
    float Tile_Spacing_v = 20.0f; // Vertical Tile Spacing

    // Creating the Window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Breakout", sf::Style::Titlebar | sf::Style::Close);

    // Heading Font
    sf::Font headingFont;
    headingFont.loadFromFile("C:/Fonts/Horizon.otf");

    // Heading Text
    sf::Text heading;
    heading.setFont(headingFont);
    heading.setString("BREAKOUT");
    heading.setCharacterSize(50);
    heading.setFillColor(sf::Color(255, 133, 152));
    heading.setPosition(270, 30);

    // Level Text + Font
    int level = 0;
    sf::Text level_text;
    sf::Font level_font;
    level_font.loadFromFile("C:/Fonts/Poppins-Medium.ttf");
    level_text.setFont(level_font);
    level_text.setString("Level: " + std::to_string(level));
    level_text.setCharacterSize(40);
    level_text.setFillColor(sf::Color(60, 108, 168));
    level_text.setPosition(374, 100);

    // Vertical and Horizontal Lines
    sf::RectangleShape h_line(sf::Vector2f(WINDOW_WIDTH, 3)); // Horizontal Line
    h_line.setFillColor(sf::Color(60, 108, 168));
    h_line.setPosition(140, 160);

    sf::RectangleShape v_line(sf::Vector2f(7, WINDOW_HEIGHT)); // Vertical Line
    v_line.setFillColor(sf::Color(60, 108, 168));
    v_line.setPosition(140, 0);

    // Paddle Setup
    sf::Texture paddleTexture;
    paddleTexture.loadFromFile("C:/Breakout/Assets/MainPaddle.png");
    sf::Sprite paddleSprite;
    paddleSprite.setTexture(paddleTexture);
    paddleSprite.setPosition((WINDOW_WIDTH / 2.0f) + 30, WINDOW_HEIGHT - 40);
    paddleSprite.setScale(0.2f, 0.2f);

    // Ball Setup
    sf::Texture ballTexture;
    ballTexture.loadFromFile("C:/Breakout/Assets/Ball.png");
    sf::Sprite ballSprite;
    ballSprite.setTexture(ballTexture);
    ballSprite.setScale(0.2f, 0.2f);
    ballSprite.setPosition(330.0f, 900.0f);
    // Speed of ball
    sf::Vector2f ballVelocity(0.2f, 0.2f);

    // Declare textures for different colored tiles
    sf::Texture blueTileTexture;
    sf::Texture redTileTexture;
    sf::Texture greenTileTexture;

    // Load textures from files
    blueTileTexture.loadFromFile("C:/Breakout/Assets/BlueTile.png");
    redTileTexture.loadFromFile("C:/Breakout/Assets/RedTile.png");
    greenTileTexture.loadFromFile("C:/Breakout/Assets/GreenTile.png");

    sf::Sprite tiles[6][6];

    for (int row = 0; row < 6; ++row) {
        for (int col = 0; col < 6; ++col) {
            if (row < 2) {
                tiles[row][col].setTexture(redTileTexture);
            } else if (row < 4) {
                tiles[row][col].setTexture(blueTileTexture);
            } else {
                tiles[row][col].setTexture(greenTileTexture);
            }
            tiles[row][col].setScale(0.2f, 0.2f);
            tiles[row][col].setPosition(Tile_Width + col * (tileSize + Tile_Spacing_h), Tile_Height + row * (tileSize + Tile_Spacing_v));
        }
    }

    // Player Information + Some Game Instructions

    // Player Name Font + Text
    sf::Text PlayerNameText;
    PlayerNameText.setFont(level_font);
    PlayerNameText.setCharacterSize(TEXT_SIZE);
    PlayerNameText.setFillColor(sf::Color(60, 108, 168));
    PlayerNameText.setPosition(10, 180);
    std::string PlayerName = "Noor";
    PlayerNameText.setString("Player:\n" + PlayerName);

    // Score Text + Font
    sf::Text ScoreText;
    ScoreText.setFont(level_font);
    ScoreText.setCharacterSize(TEXT_SIZE);
    ScoreText.setFillColor(sf::Color(60, 108, 168));
    ScoreText.setPosition(10, 290);

    int Score = 0;
    ScoreText.setString("Score:\n" + std::to_string(Score));

    // High Score Text + Font
    sf::Text HighScoreText;
    HighScoreText.setFont(level_font);
    HighScoreText.setCharacterSize(TEXT_SIZE);
    HighScoreText.setFillColor(sf::Color(60, 108, 168));
    HighScoreText.setPosition(10, 400);
    int HighScore = 100;
    HighScoreText.setString("High\nScore:\n" + std::to_string(HighScore));
    // Menu Text
    sf::Text MenuText;
    MenuText.setFont(level_font);
    MenuText.setCharacterSize(TEXT_SIZE);
    MenuText.setFillColor(sf::Color(60, 108, 168));
    MenuText.setPosition(10, 510);
    MenuText.setString("\nFor Menu\nPress M");

    // Pause/Resume Text
    sf::Text PauseResumeText;
    PauseResumeText.setFont(level_font);
    PauseResumeText.setCharacterSize(TEXT_SIZE);
    PauseResumeText.setFillColor(sf::Color(60, 108, 168));
    PauseResumeText.setPosition(10, 620);
    PauseResumeText.setString("\nPause/\nResume\n(P)");

    while (window.isOpen()) {
        GameEventsFunction(window);
        PaddleMovementFunction(paddleSprite, PADDLE_SPEED, WINDOW_WIDTH);
        BallMovementFunction(ballSprite, ballVelocity, paddleSprite, WINDOW_WIDTH, WINDOW_HEIGHT);
        BallAndCollisionFunction(ballSprite, ballVelocity, tiles); // Check for ball and tile collisions

        window.clear(sf::Color(212, 237, 244));
        window.draw(paddleSprite);
        window.draw(ballSprite);

        // Draw tiles
        for (int row = 0; row < 6; ++row) {
            for (int col = 0; col < 6; ++col) {
                if (tiles[row][col].getTexture() != nullptr) { // Only draw visible tiles
                    window.draw(tiles[row][col]);
                }
            }
        }

      window.clear();
      window.draw(shape);
      window.display();
   }

   return 0;
}