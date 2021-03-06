#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <SFML/graphics.hpp>


int SCALE_FACTOR = 2;
int MINES = 20;
const int W = 16;
const int H = 16;

char map[W][H];
char opened_map[W][H];



void fillMap()
{

    for (int i = 0; i < W; i++)
        for (int j = 0; j < H; j++)
            map[i][j] = '.';

    for (int i = 0; i < MINES; i++)
    {
        int x,y;
        do {
            x = rand() % W;
            y = rand() % H;
        }
        while (map[x][y]!='.');
        map[x][y] = '*';
    }
    for (int i = 0; i < W; i++)
        for (int j = 0; j < H; j++)
        {
            opened_map[i][j] = '#';
        }
}


bool is_available(int x, int y)
{
    if (x < 0 || y < 0) return false;
    if (x >= W || y >= H) return false;
    return true;
}

bool is_bomb(int x, int y)
{
    if (is_available(x, y))
        return map[x][y]=='*';
    return false;
}

int count_bombs(int x, int y)
{
    int result = 0;
    //�������� ������� ���� ����� �����
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (is_bomb(i, j))
                result++;
        }
    }
    return result;
}
bool isFlag(int x, int y)
{
    if (is_available(x, y))
        return opened_map[x][y]=='<';
    return false;
}
bool flag(int x, int y)
{
    if (!is_available(x,y)) return true;
    if (opened_map[x][y] == '#' || opened_map[x][y] == '<')
    {
        if (isFlag(x, y))
        {
            opened_map[x][y] = '#';
        }
        else {
            opened_map[x][y] = '<';
        }
    }


    return 1;
}


void recursive_open(int x, int y)
{
    if (opened_map[x][y] == '<')
        return;
    int bombs = count_bombs(x, y);
    if (bombs == 0)
    {
        opened_map[x][y] = '.';
        for (int i = x - 1; i <= x + 1; i++)
        {
            for (int j = y - 1; j <= y + 1; j++)
            {
                if (is_available(i, j) && opened_map[i][j] != '.')
                    recursive_open(i, j);
            }
        }
    }
    else
    {
        opened_map[x][y] = '0' + bombs;
    }
    return;
}

bool checkMap()
{
    for (int i = 0; i < W; i++)
        for (int j = 0; j < H; j++)
        {
            if (opened_map[i][j] == '#' || opened_map[i][j] == '<' && is_bomb(i, j) == false)
                return false;
        }


    return true;
}
bool toggle(int i, int j)
{
    if (!is_available(i,j)) return true;
    if (is_bomb(i, j) && opened_map[i][j] != '<') {
        opened_map[i][j] = '*';
        return false;
    }
    else {
        recursive_open(i, j);
    }
    return true;
}



bool act(int x, int y, int mode)
{

    switch (mode)
    {
        case 1:
            return flag(x, y);
            break;
        default:
            return toggle(x, y);
            break;
    }
    return 1;
}

bool isLose()
{
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            if (opened_map[i][j] == '*')
            {
                return true;
            }
        }
    }
    return false;
}

void showBombs()
{
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            if (is_bomb(i, j))
            {
                opened_map[i][j] = '*';
            }
        }
    }
}

void draw_opened(sf::RenderWindow& win, sf::Sprite& spr)
{
    for (int i = 0; i < W; i++)
    {
        for (int j = 0; j < H; j++)
        {
            spr.setPosition(i*16, j*16);
            if (opened_map[i][j] == '#')
            {
                spr.setTextureRect(sf::IntRect(0,0,16,16));
                win.draw(spr);
            }
            if (opened_map[i][j] == '<')
            {
                spr.setTextureRect(sf::IntRect(16,0,16,16));
                win.draw(spr);
            }
            if (opened_map[i][j] == '.')
            {
                spr.setTextureRect(sf::IntRect(2*16,0,16,16));
                win.draw(spr);
            }
            if (opened_map[i][j] == '1')
            {
                spr.setTextureRect(sf::IntRect(3*16,0,16,16));
                win.draw(spr);
            }
            if (opened_map[i][j] == '2')
            {
                spr.setTextureRect(sf::IntRect(4*16,0,16,16));
                win.draw(spr);
            }
            if (opened_map[i][j] == '3')
            {
                spr.setTextureRect(sf::IntRect(5*16,0,16,16));
                win.draw(spr);
            }
            if (opened_map[i][j] == '4')
            {
                spr.setTextureRect(sf::IntRect(6*16,0,16,16));
                win.draw(spr);
            }
            if (opened_map[i][j] == '5')
            {
                spr.setTextureRect(sf::IntRect(0,16,16,16));
                win.draw(spr);
            }
            if (opened_map[i][j] == '6')
            {
                spr.setTextureRect(sf::IntRect(16,16,16,16));
                win.draw(spr);
            }
            if (opened_map[i][j] == '7')
            {
                spr.setTextureRect(sf::IntRect(2*16,16,16,16));
                win.draw(spr);
            }
            if (opened_map[i][j] == '8')
            {
                spr.setTextureRect(sf::IntRect(3*16,16,16,16));
                win.draw(spr);
            }
            if (opened_map[i][j] == '*')
            {
                spr.setTextureRect(sf::IntRect(4*16,16,16,16));
                win.draw(spr);
            }

        }


    }
}

bool mouseInsideWindow(sf::Window& win)
{
    return sf::Mouse::getPosition(win).x > 0 &&
           sf::Mouse::getPosition(win).y > 0 &&
           sf::Mouse::getPosition(win).x < win.getSize().x &&
           sf::Mouse::getPosition(win).y < win.getSize().y;
}


int main(int argc, char *argv[]) { //
    if (argc == 2)
    {
        MINES = atoi(argv[1]);
    }
    if (argc == 3)
    {

        SCALE_FACTOR = atoi(argv[2]);

        MINES = atoi(argv[1]);
    }
    if (SCALE_FACTOR < 1)
    {
        SCALE_FACTOR = 1;
    }

    srand(time(0));
    fillMap();
    sf::RenderWindow win(sf::VideoMode(W*16, H*16+32), "MinesweeperGUI", sf::Style::Titlebar | sf::Style::Close);
    sf::Image tilesetraw;
    tilesetraw.loadFromFile("Minesweeper_tileset.png");
    tilesetraw.createMaskFromColor(sf::Color::Green);
    sf::Texture tileset;
    tileset.loadFromImage(tilesetraw);
    sf::Sprite renderer;
    sf::Sprite smileyRenderer;
    sf::Sprite cursor;
    cursor.setTexture(tileset);
    cursor.setTextureRect(sf::IntRect(80,16,16,16));
    renderer.setTexture(tileset);
    smileyRenderer.setTexture(tileset);
    win.setFramerateLimit(60);
    win.setVerticalSyncEnabled(true);
    win.setSize(sf::Vector2u(win.getSize().x*SCALE_FACTOR, win.getSize().y*SCALE_FACTOR));
    win.setPosition(
                    sf::Vector2i
                    (
                     sf::VideoMode::getDesktopMode().width / 2 - win.getSize().x / 2,
                     sf::VideoMode::getDesktopMode().height / 2 - win.getSize().y / 2
                    )
    );
    smileyRenderer.setPosition(win.getSize().x/2/SCALE_FACTOR-8,H*16+8);

    sf::Clock time;
    bool gameEnd = false;

    while (win.isOpen())
    {
        smileyRenderer.setTextureRect(sf::IntRect(0,32,16,16));
        sf::Event e;
        while (win.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                win.close();

            }
            if (e.type == sf::Event::MouseButtonReleased)
            {
                if (!gameEnd)
                {
                    if (e.mouseButton.button == sf::Mouse::Left)
                    {
                        if (mouseInsideWindow(win))
                            act(sf::Mouse::getPosition(win).x/(16*SCALE_FACTOR), sf::Mouse::getPosition(win).y/(16*SCALE_FACTOR), 0);


                    }
                    if (e.mouseButton.button == sf::Mouse::Right )
                    {

                        if (mouseInsideWindow(win))
                            act(sf::Mouse::getPosition(win).x/(16*SCALE_FACTOR), sf::Mouse::getPosition(win).y/(16*SCALE_FACTOR), 1);
                    }
                }

                if ( smileyRenderer.getGlobalBounds().contains(sf::Mouse::getPosition(win).x/SCALE_FACTOR,sf::Mouse::getPosition(win).y/SCALE_FACTOR))
                {
                    gameEnd = false;
                    fillMap();
                    time.restart();
                }

            }

            if (e.type == sf::Event::KeyPressed && gameEnd)
            {
                if (e.key.code == sf::Keyboard::Enter)
                {
                    gameEnd = false;
                    fillMap();
                    time.restart();
                }
            }
        }
        if (mouseInsideWindow(win))
        {
            win.setMouseCursorVisible(0);
            cursor.setPosition( sf::Vector2f(sf::Mouse::getPosition(win).x/SCALE_FACTOR-4, sf::Mouse::getPosition(win).y/SCALE_FACTOR));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                cursor.setTextureRect(sf::IntRect(96, 16, 16, 16));


            }
            else
            {
                cursor.setTextureRect(sf::IntRect(80, 16, 16, 16));

            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                smileyRenderer.setTextureRect(sf::IntRect(32,32,16,16));
            }
        }
        else
        {
            win.setMouseCursorVisible(1);
        }


        if (checkMap() && !gameEnd)
        {
            std::cout << "your time was: " << time.getElapsedTime().asSeconds() << std::endl;
            std::cout << "your score is: " << MINES / time.getElapsedTime().asSeconds() / MINES * 10000 << std::endl;
            std::cout << "you win, press enter to restart" << std::endl;
            gameEnd = true;
        }

        if (isLose() && !gameEnd)
        {
            showBombs();

            std::cout << "you lose, press enter to restart" << std::endl;
            gameEnd = true;
        }
        if (isLose())
        {
            smileyRenderer.setTextureRect(sf::IntRect(16,32,16,16));
        }
        win.clear(sf::Color(216,216,216,255));
        draw_opened(win, renderer);

        win.draw(smileyRenderer);
        win.draw(cursor);
        win.display();
    }
}
