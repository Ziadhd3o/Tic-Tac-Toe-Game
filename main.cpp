#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;
class XOShape {
    public:
    Text txt;
    RectangleShape rect;

    XOShape(const Font &f): txt(f,"") {
        txt.setCharacterSize(70);
        txt.setFillColor(sf::Color::White);
        rect.setSize({150,150});
        rect.setOrigin({rect.getLocalBounds().size.x/2,rect.getLocalBounds().size.y/2});
    }
    ~XOShape() = default;
};
struct Player {
    Text Sign;
    int c_row=0;
    int c_col=0;
    int c_main_diag=0;
    int c_sub_diag=0;
    int Score=0;
};
void ClearTheBoard(vector<vector<XOShape>> &Board,int &counter) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Board[i][j].txt.setString("");
        }
    }
    counter = 0;
}
int main() {
    int DrawScore = 0;
    // Create the window
    ContextSettings settings;
    settings.antiAliasingLevel = 8;
    Cursor cur(Cursor::Type::Arrow);
    RenderWindow window(VideoMode({800, 800}), "Tic Tac Toe",Style::None);
    // Load Font File
    Music xplay("xplay.wav"),oplay("oplay.wav"),drawplay("draw.mp3"),winnerplay("winner.mp3");
    Image image;
    if (!image.loadFromFile("icon.png"))
        cout << "File Not Existed";
    window.setIcon(image);
    Font font;
    if (!font.openFromFile("futura.otf"))
        cout << "File Not Existed";
    // 2D Array (Board Of The Game)
    Player Signs[2] = {{Text(font,"X")},{Text(font,"O")}};
    // Score Bar
    // X Score
    Signs[0].Sign.setFillColor(Color(230, 81, 82));
    Signs[0].Sign.setPosition({150,50});
    Signs[0].Sign.setCharacterSize(70);
    Signs[0].Sign.setOrigin(Signs[0].Sign.getLocalBounds().getCenter());
    Text XScore(font);
    XScore.setPosition({210,45});
    XScore.setCharacterSize(50);
    XScore.setString(to_string(Signs[0].Score));
    XScore.setOrigin(XScore.getLocalBounds().getCenter());
    // O Score
    Signs[1].Sign.setFillColor(Color(69, 147, 213));
    Signs[1].Sign.setPosition({550,50});
    Signs[1].Sign.setCharacterSize(70);
    Signs[1].Sign.setOrigin(Signs[1].Sign.getLocalBounds().getCenter());
    Text OScore(font);
    OScore.setPosition({610,50});
    OScore.setCharacterSize(50);
    OScore.setString(to_string(Signs[1].Score));
    OScore.setOrigin(OScore.getLocalBounds().getCenter());
    // Draw Score
    Text Drawdraw(font);
    Drawdraw.setPosition({(Signs[0].Sign.getPosition().x+Signs[1].Sign.getPosition().x)/2,50});
    Drawdraw.setCharacterSize(50);
    Drawdraw.setString("/ "+to_string(DrawScore));
    Drawdraw.setOrigin(OScore.getLocalBounds().getCenter());
    vector <vector <XOShape>> Board(3,vector<XOShape>(3,XOShape(font)));
    // Set Positions Of Board Elements

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++) {
            Board[i][j].txt.setOrigin({Board[i][j].txt.getLocalBounds().size.x/2,Board[i][j].txt.getLocalBounds().size.y/2});
            Board[i][j].rect.setPosition({225+ j * (Board[i][j].rect.getSize().x / 2 + 100),250+(Board[i][j].rect.getSize().y/2+100)*i});
            auto x = Board[i][j].rect.getPosition();
            x.y -= 50;
            x.x -= 25;
            Board[i][j].txt.setPosition(x);
            Board[i][j].rect.setFillColor(sf::Color::Red);
        }
    }
    // Vertical Lines
    RectangleShape VerticalLine[2];
    for (int i = 0; i < 2; i++) {
        VerticalLine[i].setSize({25,500});
        VerticalLine[i].setPosition({225+(Board[0][0].rect.getSize().x/2)+175*i,175});
        VerticalLine[i].setFillColor(Color(240, 217, 192));
    }
    // Horizontal Lines
    RectangleShape HorizontalLine[2];
    for (int i = 0; i < 2; i++) {
        HorizontalLine[i].setSize({500,25});
        HorizontalLine[i].setPosition({150,250+(Board[0][0].rect.getSize().y/2)+175*i});
        HorizontalLine[i].setFillColor(Color(240, 217, 192));
    }
    int sign = 0;
    int BoardIsFull = 0;
    Color WindowColor = Color(44, 36, 53);
    while (window.isOpen())
    {

        // check all the window's events that were triggered since the last iteration of the loop
        Player CurrentPlayer = Signs[sign];
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
            if (Mouse::isButtonPressed(Mouse::Button::Left)) {
                auto pos = Mouse::getPosition(window);
                bool flag = true;
                for (int i = 0; i < 3 && flag; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (Board[i][j].rect.getGlobalBounds().contains(Vector2<float>(pos)) && Board[i][j].txt.getString() == "") {
                            Board[i][j].txt.setString(Signs[sign].Sign.getString());
                            Board[i][j].txt.setFillColor(Signs[sign].Sign.getFillColor());
                            Board[i][j].txt.getString() == "X" ? xplay.play() : oplay.play();
                            BoardIsFull++;
                            for (int k = 0,l=2; k< 3; k++,l--) {
                                if ((Board[i][k].txt.getString() == CurrentPlayer.Sign.getString()))
                                    CurrentPlayer.c_row++;
                                if ((Board[k][j].txt.getString() == CurrentPlayer.Sign.getString()))
                                    CurrentPlayer.c_col++;
                                if ((Board[k][k].txt.getString() == CurrentPlayer.Sign.getString()))
                                    CurrentPlayer.c_main_diag++;
                                if ((Board[k][l].txt.getString() == CurrentPlayer.Sign.getString()))
                                    CurrentPlayer.c_sub_diag++;
                            }
                            sign = (sign+1)%2;
                            flag = false;
                            break;
                        }
                    }
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Key::Num1)) {
                XScore.setFillColor(Color(240, 217, 192));
                OScore.setFillColor(Color(240, 217, 192));
                Drawdraw.setFillColor(Color::White);
                for (int i = 0; i < 2; i++) {
                    HorizontalLine[i].setFillColor(Color(240, 217, 192));
                    VerticalLine[i].setFillColor(Color(240, 217, 192));
                }
                WindowColor = Color(44, 36, 53);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::Num2)) {
                XScore.setFillColor(Color(245, 173, 100));
                OScore.setFillColor(Color(245, 173, 100));
                Drawdraw.setFillColor(Color(245, 173, 100));
                for (int i = 0; i < 2; i++) {
                    HorizontalLine[i].setFillColor(Color(22, 184, 177));
                    VerticalLine[i].setFillColor(Color(22, 184, 177));
                }
                WindowColor = Color(27, 70, 79);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Key::Num3)) {
                XScore.setFillColor(Color(42, 41, 40));
                OScore.setFillColor(Color(42, 41, 40));
                Drawdraw.setFillColor(Color(42, 41, 40));
                for (int i = 0; i < 2; i++) {
                    HorizontalLine[i].setFillColor(Color(42, 41, 40));
                    VerticalLine[i].setFillColor(Color(42, 41, 40));
                }
                WindowColor = Color(248, 241, 228);

            }
        }
        if (CurrentPlayer.c_row == 3 || CurrentPlayer.c_col == 3 || CurrentPlayer.c_main_diag == 3 || CurrentPlayer.c_sub_diag == 3) {
            string winner = CurrentPlayer.Sign.getString();
            CurrentPlayer.Sign.getString() == "X"? Signs[0].Score++ : Signs[1].Score++;
            ClearTheBoard(Board,BoardIsFull);
            winnerplay.play();
        }
        else if (BoardIsFull == 9) {
            ClearTheBoard(Board,BoardIsFull);
            drawplay.play();
            DrawScore++;
        }

        Drawdraw.setString("/ "+to_string(DrawScore));
        OScore.setString(to_string(Signs[1].Score));
        XScore.setString(to_string(Signs[0].Score));
        window.clear(WindowColor);
        window.draw(Signs[0].Sign);
        window.draw(Signs[1].Sign);
        // clear the window with black color
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // window.draw((Board[i][j].rect));
                window.draw((Board[i][j].txt));
            }
        }
        for (int i = 0; i < 2; i++) {
            window.draw(VerticalLine[i]);
            window.draw(HorizontalLine[i]);
        }

        window.draw(XScore);
        window.draw(OScore);
        window.draw(Drawdraw);
        window.display();
    }
}