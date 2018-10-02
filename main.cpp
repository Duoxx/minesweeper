#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <SFML/graphics.hpp>


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
    //дописать подсчет бомб около точки
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



    srand(time(0));
    fillMap();
    sf::RenderWindow win(sf::VideoMode(W*16, H*16), "MinesweeperGUI", sf::Style::Titlebar | sf::Style::Close);
    sf::Image tilesetraw;
    tilesetraw.loadFromFile("Minesweeper_tileset.png");
    tilesetraw.createMaskFromColor(sf::Color::Green);
    sf::Texture tileset;
    tileset.loadFromImage(tilesetraw);
    sf::Sprite renderer;
    sf::Sprite cursor;
    cursor.setTexture(tileset);
    cursor.setTextureRect(sf::IntRect(80,16,16,16));
    renderer.setTexture(tileset);
    win.setVerticalSyncEnabled(true);
    win.setSize(sf::Vector2u(W*16*2, H*16*2));
    win.setPosition(
                    sf::Vector2i
                    (
                     sf::VideoMode::getDesktopMode().width / 2 - win.getSize().x / 2, sf::VideoMode::getDesktopMode().height / 2 - win.getSize().y / 2
                    )
    );

    win.setMouseCursorVisible(0);
    sf::Clock time;
    bool gameEnd = false;
    while (win.isOpen())
    {
        sf::Event e;
        while (win.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                win.close();

            }
            if (e.type == sf::Event::MouseButtonReleased && !gameEnd)
            {
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    if (sf::Mouse::getPosition(win).x > 0 && sf::Mouse::getPosition(win).y > 0)
                        act(sf::Mouse::getPosition(win).x/32, sf::Mouse::getPosition(win).y/32, 0);
                }
                if (e.mouseButton.button == sf::Mouse::Right )
                {

                    if (sf::Mouse::getPosition(win).x > 0 && sf::Mouse::getPosition(win).y > 0)
                        act(sf::Mouse::getPosition(win).x/32, sf::Mouse::getPosition(win).y/32, 1);
                }
                else
                {

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
            cursor.setPosition( sf::Vector2f(sf::Mouse::getPosition(win).x/2-4, sf::Mouse::getPosition(win).y/2));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                cursor.setTextureRect(sf::IntRect(96, 16, 16, 16));
            }
            else
            {
                cursor.setTextureRect(sf::IntRect(80, 16, 16, 16));
            }
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
        win.clear();
        draw_opened(win, renderer);
        win.draw(cursor);
        win.display();
    }
}
