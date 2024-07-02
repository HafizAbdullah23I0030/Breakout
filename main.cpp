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

void PaddleMovemntFunction(sf::Sprite &paddleSprite, float paddleSpeed, int windowWidth) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && paddleSprite.getPosition().x > 147) {
        paddleSprite.move(-paddleSpeed, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && paddleSprite.getPosition().x + paddleSprite.getGlobalBounds().width < windowWidth) {
        paddleSprite.move(paddleSpeed, 0.0f);
    }
}

void BallMovemebtFunction(sf::Sprite &ballSprite, sf::Vector2f &ballVelocity, const sf::Sprite &paddleSprite, int windowWidth, int windowHeight) {
    ballSprite.move(ballVelocity);

    if (ballSprite.getPosition().x <= 140 || ballSprite.getPosition().x + ballSprite.getGlobalBounds().width >= windowWidth) {
        ballVelocity.x = -ballVelocity.x;
    }
    if (ballSprite.getPosition().y <= 160) {
        ballVelocity.y = -ballVelocity.y;
    }

    if (ballSprite.getGlobalBounds().intersects(paddleSprite.getGlobalBounds())) {
        ballVelocity.y = -ballVelocity.y;
    }

    if (ballSprite.getPosition().y + ballSprite.getGlobalBounds().height >= windowHeight) {
        ballSprite.setPosition(330.0f, 530.0f);
    }
}

int main() {
    // Some Data
    const int WINDOW_HEIGHT = 900;
    const int WINDOW_WIDTH = 700;
    const float PADDLE_SPEED = 0.6f;
    const float TEXT_SIZE = 20.0f;

    // Creating the Window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Breakout Game", sf::Style::Titlebar | sf::Style::Close);

    // Heading Font
    sf::Font headingFont;
    headingFont.loadFromFile("C:/Fonts/Horizon.otf");

    // Heading Text
    sf::Text heading;
    heading.setFont(headingFont);
    heading.setString("BREAKOUT");
    heading.setCharacterSize(50);
    heading.setFillColor(sf::Color(255,133,152));
    heading.setPosition(270, 30);

    // Level Text + Font
    int level = 0;
    sf::Text level_text;
    sf::Font level_font;
    level_font.loadFromFile("C:/Fonts/Poppins-Medium.ttf");
    level_text.setFont(level_font);
    level_text.setString("Level: " + std::to_string(level));
    level_text.setCharacterSize(40);
    level_text.setFillColor(sf::Color(60,108,168));
    level_text.setPosition(374, 100);


    // Verical and Horizontal Lines
    sf::RectangleShape h_line(sf::Vector2f(WINDOW_WIDTH, 3)); // Horizontal Line
    h_line.setFillColor(sf::Color(60,108,168));
    h_line.setPosition(140, 160);

    sf::RectangleShape v_line(sf::Vector2f(7, WINDOW_HEIGHT)); // Vertical Line
    v_line.setFillColor(sf::Color(60,108,168));
    v_line.setPosition(140, 0);

    // Paddle Setup
    sf::Texture paddleTexture;
    paddleTexture.loadFromFile("C:/Breakout/Assets/MainPaddle..png");
    sf::Sprite paddleSprite;
    paddleSprite.setTexture(paddleTexture);
    paddleSprite.setPosition(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT - 40);
    paddleSprite.setScale(0.2f, 0.2f);

    // Ball Setup
    sf::Texture ballTexture;
    ballTexture.loadFromFile("C:/Breakout/Assets/Ball.png");
    sf::Sprite ballSprite;
    ballSprite.setTexture(ballTexture);
    ballSprite.setScale(0.2f, 0.2f);
    ballSprite.setPosition(330.0f, 530.0f);
    // Speed of ball
    sf::Vector2f ballVelocity(0.2f, 0.2f);


    // Player Information + Some Game Instructions

    // Player Name Font + Text
    sf:: Text PlayerNameText;
    PlayerNameText.setFont(level_font);
    PlayerNameText.setCharacterSize(TEXT_SIZE);
    PlayerNameText.setFillColor(sf::Color(60,108,168));
    PlayerNameText.setPosition(10,180);
    std::string PlayerName;
    PlayerName = "Noor";
    PlayerNameText.setString("Player:\n" + PlayerName);

    // Score Text + Font
    sf::Text ScoreText;
    ScoreText.setFont(level_font);
    ScoreText.setCharacterSize(TEXT_SIZE);
    ScoreText.setFillColor(sf::Color(60,108,168));
    ScoreText.setPosition(10, 290);

    int Score = 0;
    ScoreText.setString("Score:\n" + std::to_string(Score));


    // High Score Text + Font
    sf::Text HighScoreText;
    HighScoreText.setFont(level_font);
    HighScoreText.setCharacterSize(TEXT_SIZE);
    HighScoreText.setFillColor(sf::Color(60,108,168));
    HighScoreText.setPosition(10, 400);
    int HighScore = 100;
    HighScoreText.setString("High\nScore:\n" + std::to_string(HighScore) );

    // Menu Text
    sf::Text MenuText;
    MenuText.setFont(level_font);
    MenuText.setCharacterSize(TEXT_SIZE);
    MenuText.setFillColor(sf::Color(60,108,168));
    MenuText.setPosition(10, 510);
    MenuText.setString("\nFor Menu\nPress M");

    // Pause/Resume Text
    sf::Text PauseResumeText;
    PauseResumeText.setFont(level_font);
    PauseResumeText.setCharacterSize(TEXT_SIZE);
    PauseResumeText.setFillColor(sf::Color(60,108,168));
    PauseResumeText.setPosition(10, 620);
    PauseResumeText.setString("\nPause/\nResume\n(P)");


    while (window.isOpen()) {
        GameEventsFunction(window);
        PaddleMovemntFunction(paddleSprite, PADDLE_SPEED, WINDOW_WIDTH);
        BallMovemebtFunction(ballSprite, ballVelocity, paddleSprite, WINDOW_WIDTH, WINDOW_HEIGHT);

        window.clear(sf::Color(212,237,244));
        window.draw(paddleSprite);
        window.draw(ballSprite);
        window.draw(heading);
        window.draw(level_text);
        window.draw(v_line);
        window.draw(h_line);
        window.draw(PlayerNameText);
        window.draw(ScoreText);
        window.draw(HighScoreText);
        window.draw(MenuText);
        window.draw(PauseResumeText);
        window.display();
    }

    return 0;
}
