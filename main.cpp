#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <fstream>
using namespace std;

string reset = "\033[0m";
string blue = "\033[34m";
string yellow = "\033[33m";
string red = "\033[91m";
string green = "\033[32m";
string gray = "\033[30m";
char key;
int i = 999;
int world = 1;
double level = 1;
int max_bullet = 3;
int shotgun_rang = 5;
int max_health = 3;
int vaccine = 0;
int credit = 0;
int round_game = 0;
int health = max_health;
int bullet = 3;
int ammo = 0;
int kill = 0;
bool bullet_checker = true;
bool Shooting_checker = true;
bool IsMute = false;
int key_counter = 0;
int player_Location[2] = {1, 1};
int x = 0;
int y = 0;
char ground[15][15];
bool start = false;
bool game_over = false;
int end_game = 10;
string sound = "unmute";
void Setting();
void Credits();
void Exit();
void Shooting();
void kill_sentence();
void Player_Move();
void NewGame();
void Vaccine();
void Distonation();
void Ammo();
void Z();
void kill_sentence();
void Save_Load();
void Help();

void getch()
{
    cin >> key;
}
void Get_Ammo()
{
    if (ground[player_Location[0]][player_Location[1]] == 'A')
    {
        ammo = ammo + 1;
        cout << yellow << "Ammo collected!" << reset << endl;
    }
}
void Get_Vaccine()
{
    if (ground[player_Location[0]][player_Location[1]] == 'V')
    {
        vaccine = vaccine + 1;
        credit = credit + level + 1;
        cout << green << "Vaccine collected!" << reset << endl;
        cout << credit << " credit gained!" << endl;
    }
}
void Show()
{
    cout << "~Level: " << level << " ~Vaccine: " << vaccine << " ~Credit: " << credit << " ~Round: " << key_counter << endl;
    cout << "~Health:[";
    for (int i = 0; i < health; i++)
    {
        cout << " | ";
    }
    cout << "] ";
    cout << "~Ammo: " << bullet << "/" << ammo << " ~Kill: " << kill << endl;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (ground[i][j] == 'Z')
                cout << red << ground[i][j] << reset;
            else if (ground[i][j] == 'V')
                cout << green << ground[i][j] << reset;
            else if (ground[i][j] == 'A')
                cout << yellow << ground[i][j] << reset;
            else if (ground[i][j] == 'P' || ground[i][j] == 'D')
                cout << ground[i][j];
            else
                cout << gray << ground[i][j] << reset;
        }
        cout << endl;
    }
    Distonation();
}
void Board()
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (i == 0 || i == 14)
            {
                ground[i][j] = '-';
            }
            else
            {
                if (j == 0 || j == 14)
                {
                    ground[i][j] = '|';
                }
                else if (ground[i][j] != 'V' && ground[i][j] != 'A' && ground[i][j] != 'P' && ground[i][j] != 'Z')
                {
                    ground[i][j] = ' ';
                }
            }
        }
    }
    if (key_counter == 0)
    {
        ground[1][1] = 'P';
        Ammo();
        Vaccine();
        Z();
    }

    ground[13][13] = 'D';
}
void Distonation()
{
    if (player_Location[0] == 13 && player_Location[1] == 13)
    {
        if (vaccine == level)
        {
            level++;
            cout << "You Won! You have reached level " << level;
            end_game = 0;
            kill = 0;
        }
        else
        {
            cout << "First get all the vaccines.";
        }
    }
}
class Vaccine1
{
public:
    int x;
    int y;
};
Vaccine1 Vaccine_place[10];
void Vaccine()
{
    x = rand() % 13 + 1;
    y = rand() % 13 + 1;
    for (int i = 0; i < level; i++)
    {
        while (ground[y][x] == 'A' || ground[y][x] == 'V' || ground[y][x] == 'P' || ground[y][x] == 'D' || ground[y][x] == 'Z')
        {
            x = rand() % 13 + 1;
            y = rand() % 13 + 1;
        }
        ground[y][x] = 'V';
        Vaccine_place[i].x = x;
        Vaccine_place[i].y = y;
    }
}
class Ammo1
{
public:
    int x;
    int y;
};
Ammo1 Ammo_place[10];
void Ammo()
{
    for (int i = 0; i < level / 2; i++)
    {
        x = rand() % 13 + 1;
        y = rand() % 13 + 1;
        while (ground[y][x] == 'A' || ground[y][x] == 'V' || ground[y][x] == 'P' || ground[y][x] == 'D' || ground[y][x] == 'Z' || ground[y][x] == '|' || ground[y][x] == '-')
        {
            x = rand() % 13 + 1;
            y = rand() % 13 + 1;
        }
        ground[y][x] = 'A';
        Ammo_place[i].x = x;
        Ammo_place[i].y = y;
    }
}
class Zombie
{
public:
    int x;
    int y;
    bool life;
};
Zombie zombies[20];
void Z()
{
    if (key_counter == 0)
    {
        x = rand() % 11 + 2;
        y = rand() % 11 + 3;
        for (int i = 0; i < level; i++)
        {
            while (ground[y][x] == 'V' || ground[y][x] == 'A' || ground[y][x] == 'Z')
            {
                x = rand() % 11 + 2;
                y = rand() % 11 + 3;
            }
            zombies[i].x = x;
            zombies[i].y = y;
            zombies[i].life = true;
            ground[y][x] = 'Z';
        }
    }
    else
    {
        for (int i = 0; i < level; i++)
        {
            if (zombies[i].life == true)
            {
                x = zombies[i].x;
                y = zombies[i].y;
                if (ground[y][x] != 'A' && ground[y][x] != 'V')
                    ground[y][x] = 'Z';
            }
        }
    }
}
void Zombie_Move()
{
    if (key_counter % 2 == 0 && key_counter != 0)
    {
        for (int i = 0; i < level; i++)
        {
            if (zombies[i].life == true)
            {
                if (ground[zombies[i].y][zombies[i].x] != 'A' && ground[zombies[i].y][zombies[i].x] != 'V')
                    ground[zombies[i].y][zombies[i].x] = ' ';
                if (zombies[i].x < player_Location[1])
                    zombies[i].x++;
                else if (zombies[i].x > player_Location[1])
                    zombies[i].x--;
                else if (zombies[i].y > player_Location[0])
                    zombies[i].y--;
                else if (zombies[i].y < player_Location[0])
                    zombies[i].y++;
            }
        }
        Z();
    }
}
void Shooting()
{
    if (key == 't' || key == 'T')
    {
        if (bullet > 0 && IsMute==false)
        {
            system("canberra-gtk-play -f gunShot.ogg");
        }
        int min = 999;
        for (int k = 0; k < level; k++)
        {

            if (player_Location[0] - zombies[k].y <= min && player_Location[0] - zombies[k].y >= 0 && player_Location[0] - zombies[k].y < shotgun_rang && player_Location[1] == zombies[k].x && zombies[k].life == true)
            {
                min = player_Location[0] - zombies[k].y;
                i = k;
            }
        }

        if (player_Location[0] - zombies[i].y < shotgun_rang && player_Location[0] - zombies[i].y >= 0 && player_Location[1] == zombies[i].x && zombies[i].life == true && bullet > 0)
        {
            kill_sentence();
            if (bullet_checker == true)
            {
                bullet--;
                bullet_checker = false;
            }
            zombies[i].life = false;
            for (int j = 0; j < level; j++)
            {
                if (Vaccine_place[j].x == zombies[i].x && Vaccine_place[j].y == zombies[i].y)
                {
                    Shooting_checker = false;
                }
            }
            if (Shooting_checker == true)
            {
                for (int j = 0; j < level / 2; j++)
                {
                    if (Ammo_place[j].x == zombies[i].x && Ammo_place[j].y == zombies[i].y)
                    {
                        Shooting_checker = false;
                    }
                    else if (player_Location[1] == zombies[i].x && player_Location[0] == zombies[i].y)
                    {
                        Shooting_checker = false;
                    }
                }
            }
            if (Shooting_checker == true)
            {
                for (int j = 0; j < level; j++)
                {
                    if (j != i)
                    {
                        if (zombies[i].x == zombies[j].x && zombies[i].y == zombies[j].y && zombies[j].life == true)
                        {
                            Shooting_checker = false;
                        }
                    }
                }
            }
            if (Shooting_checker == true)
            {
                ground[zombies[i].y][zombies[i].x] = ' ';
            }
            Shooting_checker = true;
            kill++;
            credit = credit + level + 1;
        }
        else
        {
            if (bullet_checker == true && bullet > 0)
            {
                bullet--;
                bullet_checker = false;
                cout << red << "Zombie is not in range! come closer" << reset << endl;
            }
            else if (bullet_checker == true && bullet <= 0)
            {
                cout << red << "No charged ammo!" << reset << endl;
            }
        }
        bullet_checker = true;
    }
    else if (key == 'g' || key == 'G')
    {
        if (bullet > 0&& IsMute==false)
        {
            system("canberra-gtk-play -f gunShot.ogg");
        }
        int min = 999;
        for (int k = 0; k < level; k++)
        {
            if (zombies[k].y - player_Location[0] >= 0 && zombies[k].y - player_Location[0] < shotgun_rang && player_Location[1] == zombies[k].x && zombies[k].life == true)
            {
                if (zombies[k].y - player_Location[0] <= min)
                {
                    min = zombies[k].y - player_Location[0];
                    i = k;
                }
            }
        }
        if (zombies[i].y - player_Location[0] < shotgun_rang && zombies[i].y - player_Location[0] >= 0 && player_Location[1] == zombies[i].x && zombies[i].life == true && bullet > 0)
        {
            kill_sentence();
            if (bullet_checker == true)
            {
                bullet--;
                bullet_checker = false;
            }
            zombies[i].life = false;
            for (int j = 0; j < level; j++)
            {
                if (Vaccine_place[j].x == zombies[i].x && Vaccine_place[j].y == zombies[i].y)
                {
                    Shooting_checker = false;
                }
            }
            if (Shooting_checker == true)
            {
                for (int j = 0; j < level / 2; j++)
                {
                    if (Ammo_place[j].x == zombies[i].x && Ammo_place[j].y == zombies[i].y)
                    {
                        Shooting_checker = false;
                    }
                    else if (player_Location[1] == zombies[i].x && player_Location[0] == zombies[i].y)
                    {
                        Shooting_checker = false;
                    }
                }
            }
            if (Shooting_checker == true)
            {
                for (int j = 0; j < level; j++)
                {
                    if (j != i)
                    {
                        if (zombies[i].x == zombies[j].x && zombies[i].y == zombies[j].y && zombies[j].life == true)
                        {
                            cout << "hello";
                            sleep(2);
                            Shooting_checker = false;
                        }
                    }
                }
            }
            if (Shooting_checker == true)
            {
                if (zombies[i].x == 13 && zombies[i].y == 13)
                {
                    ground[zombies[i].y][zombies[i].x] = 'D';
                    Shooting_checker = false;
                }
            }
            if (Shooting_checker == true)
            {
                ground[zombies[i].y][zombies[i].x] = ' ';
            }
            Shooting_checker = true;
            kill++;
            credit = credit + level + 1;
        }
        else
        {
            if (bullet_checker == true && bullet > 0)
            {
                bullet--;
                bullet_checker = false;
                cout << red << "Zombie is not in range! come closer" << reset << endl;
            }
            else if (bullet_checker == true && bullet <= 0)
            {
                cout << red << "No charged ammo!" << reset << endl;
            }
        }
        bullet_checker = true;
    }
    else if (key == 'f' || key == 'F')
    {
        if (bullet > 0&&IsMute==false)
        {
            system("canberra-gtk-play -f gunShot.ogg");
        }
        int min = 999;
        for (int k = 0; k < level; k++)
        {

            if (player_Location[1] - zombies[k].x <= min && player_Location[1] - zombies[k].x < shotgun_rang && player_Location[0] == zombies[k].y && zombies[k].life == true)
            {
                min = player_Location[1] - zombies[k].x;
                i = k;
            }
        }
        if (player_Location[1] - zombies[i].x < shotgun_rang && player_Location[0] == zombies[i].y && zombies[i].life == true && bullet > 0)
        {
            kill_sentence();
            if (bullet_checker == true)
            {
                bullet--;
                bullet_checker = false;
            }
            zombies[i].life = false;
            for (int j = 0; j < level; j++)
            {
                if (Vaccine_place[j].x == zombies[i].x && Vaccine_place[j].y == zombies[i].y)
                {
                    Shooting_checker = false;
                }
            }
            if (Shooting_checker == true)
            {
                for (int j = 0; j < level / 2; j++)
                {
                    if (Ammo_place[j].x == zombies[i].x && Ammo_place[j].y == zombies[i].y)
                    {
                        Shooting_checker = false;
                    }
                    else if (player_Location[1] == zombies[i].x && player_Location[0] == zombies[i].y)
                    {
                        Shooting_checker = false;
                    }
                }
            }
            if (Shooting_checker == true)
            {
                for (int j = 0; j < level; j++)
                {
                    if (j != i)
                    {
                        if (zombies[i].x == zombies[j].x && zombies[i].y == zombies[j].y && zombies[j].life == true)
                        {
                            // ground[zombies[i].y][zombies[i].x] = 'Z';
                            Shooting_checker = false;
                        }
                    }
                }
            }
            if (Shooting_checker == true)
            {
                if (zombies[i].x == 13 && zombies[i].y == 13)
                    ground[zombies[i].y][zombies[i].x] = 'D';
            }
            if (Shooting_checker == true)
            {
                ground[zombies[i].y][zombies[i].x] = ' ';
            }
            Shooting_checker = true;
            kill++;
            credit = credit + level + 1;
        }
        else
        {
            if (bullet_checker == true && bullet > 0)
            {
                bullet--;
                bullet_checker = false;
                cout << red << "Zombie is not in range! come closer" << reset << endl;
            }
            else if (bullet_checker == true && bullet <= 0)
            {
                cout << red << "No charged ammo!" << reset << endl;
            }
        }
        bullet_checker = true;
    }
    else if (key == 'h' || key == 'H')
    {
        if (bullet > 0&&IsMute==false)
        {
            system("canberra-gtk-play -f gunShot.ogg");
        }
        int min = 999;
        for (int k = 0; k < level; k++)
        {

            if (zombies[k].x - player_Location[1] <= min && zombies[k].x - player_Location[1] < shotgun_rang && player_Location[0] == zombies[k].y && zombies[k].life == true)
            {
                min = zombies[k].x - player_Location[1];
                i = k;
            }
        }

        if (zombies[i].x - player_Location[1] < shotgun_rang && player_Location[0] == zombies[i].y && zombies[i].life == true && bullet > 0)
        {
            kill_sentence();
            if (bullet_checker == true)
            {
                bullet--;
                bullet_checker = false;
            }
            zombies[i].life = false;
            for (int j = 0; j < level; j++)
            {
                if (Vaccine_place[j].x == zombies[i].x && Vaccine_place[j].y == zombies[i].y)
                {
                    Shooting_checker = false;
                }
            }
            if (Shooting_checker == true)
            {
                for (int j = 0; j < level / 2; j++)
                {
                    if (Ammo_place[j].x == zombies[i].x && Ammo_place[j].y == zombies[i].y)
                    {
                        Shooting_checker = false;
                    }
                    else if (player_Location[1] == zombies[i].x && player_Location[0] == zombies[i].y)
                    {
                        Shooting_checker = false;
                    }
                }
            }
            if (Shooting_checker == true)
            {
                for (int j = 0; j < level; j++)
                {
                    if (j != i)
                    {
                        if (zombies[i].x == zombies[j].x && zombies[i].y == zombies[j].y && zombies[j].life == true)
                        {
                            Shooting_checker = false;
                        }
                    }
                }
            }
            if (Shooting_checker == true)
            {
                if (zombies[i].x == 13 && zombies[i].y == 13)
                {
                    ground[zombies[i].y][zombies[i].x] = 'D';
                    Shooting_checker = false;
                }
            }
            if (Shooting_checker == true)
            {
                ground[zombies[i].y][zombies[i].x] = ' ';
            }
            Shooting_checker = true;
            kill++;
            credit = credit + level + 1;
        }
        else
        {
            if (bullet_checker == true && bullet > 0)
            {
                bullet--;
                bullet_checker = false;
                cout << red << "Zombie is not in range! come closer" << reset << endl;
            }
            else if (bullet_checker == true && bullet <= 0)
            {
                cout << red << "No charged ammo!" << reset << endl;
            }
        }
    }
    bullet_checker = true;
}
void Reload()
{

    if (key == 'r' || key == 'R')
    {
        if (ammo == 0)
        {
            cout << "No Ammo!";
        }
        else if (bullet == 3)
        {
            cout << "The gun is already Charged";
        }
        else
        {
            bullet = 3;
            ammo--;
            cout << green << "Reloaded!" << reset;
        }
    }
}
void Death()
{
    for (int i = 0; i < level; i++)
    {
        if (abs(zombies[i].x - player_Location[1]) <= 1 && abs(zombies[i].y - player_Location[0]) <= 1 && zombies[i].life == true)
        {
            cout << "The zombie is eating you! You lost one of your healths!\n";
            health--;
            if (health == 0)
            {
                cout << "You Died!\nYou Lose! Would you like to try again?(y / n)\n";
                while (true)
                {
                    getch();
                    if (key == 'y' || key == 'Y' || key == 'N' || key == 'n')
                        break;
                }
                if (key == 'n' || key == 'N')
                {
                    end_game = 1;
                    break;
                }
                else if (key == 'y' || key == 'Y')
                {
                    end_game = 0;
                    level = 1;
                    credit = 0;
                    ammo = 0;
                    bullet = 3;
                    kill = 0;
                    break;
                }
            }
        }
    }
}
void Welcome()
{

    cout << blue << " ######   #######  ##      ## #### ########     #######    #######    #######    ######" << endl;
    cout << "##    ## ##     ## ##      ##  ##  ##     ##   ##     ##  ##     ##  ##     ##  ##    ##" << endl;
    cout << "##       ##     ## ##      ##  ##  ##     ##          ## ##       ##        ## ##      ##" << endl;
    cout << "##       ##     ## ##      ##  ##  ##     ##    #######  ##       ##   ######  ##      ##" << endl;
    cout << "##       ##     ##  ##    ##   ##  ##     ##   ##        ##       ##        ## ##      ##" << endl;
    cout << "##    ## ##     ##   ##  ##    ##  ##     ##   ##         ##     ##  ##     ##  ##    ##" << endl;
    cout << " ######   #######     ####    #### ########    ########    #######    #######    ######" << reset << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << yellow << "Welcome to Covid 2030 game!" << reset << endl;
}
void Menu()
{
    cout << "1.New Game\n2.Setting\n3.Credits\n4.Load\n5.Help\n6.Exit\n";
    getch();
    system("clear");
    if (key == '1')
        NewGame();
    else if (key == '2')
        Setting();
    else if (key == '3')
        Credits();
    else if (key == '4')
        Save_Load();
    else if (key == '5')
        Help();
    else if (key == '6')
        Exit();
    system("clear");
}
void Save_Load()
{
    if (level==1)
    {
        ifstream load("game.txt", ios::in);
        if (!load)
        {
            cout << "Error...";
        }
        load >> level;
        load.close();
    }
    else
    {
        start = true;
        ofstream save("game.txt", ios::ate);
        if (!save)
        {
            cout << "Error...";
        }
        save << level;
        save.close();
    }
}
void Help()
{
    cout << "The keyboard function:\n\nPLAYER:   W/w->Go up\tA/a->Go left\tS/s->Go down\tD/d->Go rigth\n\n";
    cout << "SHOOTING: F/f->Shoot left   T/t->Shott up   G/g->Shoot down   H/h->Shoot rigth\n\n";
    cout << "E/e->Exit\nR/r->Reload\nM/m->Go to Menu\nU/u->Upgrade menu";
    sleep(10);
}
void Game_menu()
{
    if (key == 'm' || key == 'M')
    {
        while (true)
        {
            cout << "0.Return to game\n1.New Game\n2.Setting\n3.Save\n4.Exit\n";
            getch();
            system("clear");
            if (key == '1')
            {
                end_game = 0;
                break;
            }
            else if (key == '2')
                Setting();
            else if (key == '3')
                Save_Load();
            else if (key == '4')
                Exit();
            else if (key == '0')
                break;
            system("clear");
        }
    }
    else if (key == 'e')
    {
        end_game = 1;
    }
}
void Setting()
{
    cout << "Final Level Is: 20\n";
    if (IsMute == false)
    {
        cout << "Sound is not mute\nDo you want to mute the sound? (y / n)\n";
        getch();
        if (key == 'y' || key == 'Y')
            IsMute = true;   
    }

    else if (IsMute == true)
    {
        cout << "Sound is mute\nDo you want to unmute the sound? (y / n)\n";
        getch();
        if(key=='y'||key=='Y')
            IsMute = false;  
    }
}
void Credits()
{
    cout << "Farzad Dehghan Manshdi\nAli Naghi Njad\n";
    sleep(1);
}
void Exit()
{
    cout << "Are you sure you want to exit the game?(y / n)";
    getch();
    if (key == 'n')
        ;
    else if (key == 'y')
    {
        system("clear");
        cout << "Good bay!";
        sleep(1);
        exit(EXIT_SUCCESS);
    }
}
void NewGame()
{
    start = true;
    if (key_counter != 0)
    {
        key_counter = 0;
        cout << "The game will restart in 5 seconds";
        sleep(2);
        health = 3;
        bullet = 3;
        vaccine = 0;
        player_Location[0] = 1;
        player_Location[1] = 1;
        end_game = 10;
        for (int i = 0; i < 15; i++)
            for (int j = 0; j < 15; j++)
                ground[i][j] = ' ';
    }
}
void Player_Move()
{
    if (key_counter != 0)
    {
        if (key == 'w' || key == 'W')
        {
            if (player_Location[0] != 1)
            {
                if (ground[player_Location[0]][player_Location[1]] != 'D' && ground[player_Location[0]][player_Location[1]] != 'Z')
                    ground[player_Location[0]][player_Location[1]] = ' ';
                player_Location[0]--;
                Get_Ammo();
                Get_Vaccine();
                ground[player_Location[0]][player_Location[1]] = 'P';
            }
        }
        else if (key == 's' || key == 'S')
        {
            if (player_Location[0] != 13)
            {
                if (ground[player_Location[0]][player_Location[1]] != 'D' && ground[player_Location[0]][player_Location[1]] != 'Z')
                    ground[player_Location[0]][player_Location[1]] = ' ';
                player_Location[0]++;
                Get_Ammo();
                Get_Vaccine();
                ground[player_Location[0]][player_Location[1]] = 'P';
            }
        }
        else if (key == 'a' || key == 'A')
        {
            if (player_Location[1] != 1)
            {
                if (ground[player_Location[0]][player_Location[1]] != 'D' && ground[player_Location[0]][player_Location[1]] != 'Z')
                    ground[player_Location[0]][player_Location[1]] = ' ';
                player_Location[1]--;
                Get_Ammo();
                Get_Vaccine();
                ground[player_Location[0]][player_Location[1]] = 'P';
            }
        }
        else if (key == 'd' || key == 'D')
        {
            if (player_Location[1] != 13)
            {
                if (ground[player_Location[0]][player_Location[1]] != 'D' && ground[player_Location[0]][player_Location[1]] != 'Z')
                    ground[player_Location[0]][player_Location[1]] = ' ';
                player_Location[1]++;
                Get_Ammo();
                Get_Vaccine();
                ground[player_Location[0]][player_Location[1]] = 'P';
            }
        }
    }
}
void Upgrade()
{
    int x = 0;
    if (key == 'u' || key == 'U')
    {
        while (true)
        {
            cout << "0 - Return to game.\n\n";
            cout << "1 - Upgrade capacity of magazine : 1 bullet (maximum is 7 bullets, now is " << max_bullet << " ) ,Credit required: " << max_bullet * level << endl
                 << endl;
            cout << "2 - Upgrade range of shotgun : 1 times the size of the person himself (maximum is 10 times, now is " << shotgun_rang << " ) ,credit required: " << shotgun_rang + level << endl
                 << endl;
            cout << "3 - get an additional health (maximum is 5 healths, now is " << max_health << " ) ,credit required: " << max_health * (level + 1) << endl
                 << endl;

            while (true)
            {
                getch();
                x++;
                if (key == '0' || key == '1' || key == '2' || key == '3')
                    break;
                if (x >= 1)
                    cout << "Please just enter the numbers in the menu:\n";
            }
            if (key == '0')
                break;
            else if (key == '1')
            {
                if (max_bullet == 7)
                {
                    cout << "The selected item is maximum." << endl;
                }
                else if (credit >= max_bullet * level)
                {
                    cout << "Upgrade done successfully.\nYour magazine capacity is now " << ++max_bullet << endl;
                    bullet = max_bullet;
                    credit -= (max_bullet * level);
                }
                else
                {
                    cout << "Unfortunately, your credit is not enough to get this item. Please gain " << (max_bullet * level) - credit << " more credit by playing.\n";
                }
            }
            else if (key == '2')
            {
                if (shotgun_rang == 10)
                {
                    cout << "The selected item is maximum.\n";
                }
                else if (credit >= shotgun_rang + level)
                {
                    cout << "Upgrade done successfully.\nYour shotgun range is now " << ++shotgun_rang << endl;
                    credit -= (shotgun_rang + level);
                }
                else
                {
                    cout << "Unfortunately, your credit is not enough to get this item. Please gain " << (max_bullet + level) - credit << " more credit by playing.\n";
                }
            }
            else if (key == '3')
            {
                if (max_health == 5)
                {
                    cout << "The selected item is maximum.\n";
                }
                else if (credit >= max_health * (level + 1))
                {
                    cout << "Additional health received successfully.\nYour health is now " << ++max_health << endl;
                    health = max_health;
                    credit -= (max_health * (level + 1));
                }

                else
                {
                    cout << "Unfortunately, your credit is not enough to get this item. Please gain " << (max_health * (level + 1)) - credit << " more credit by playing.\n";
                }
            }
            sleep(1);
            system("clear");
        }
    }
}
void kill_sentence()
{
    if (kill % 14 == 0)
        cout << red << "First Blood" << reset;
    else if (kill % 14 == 1)
        cout << red << "Double Kill" << reset;
    else if (kill % 14 == 2)
    {
        if ((int)(level) % 2 == 0)
            cout << red << "Triple Kill" << reset;
        else
            cout << red << "Hattrick" << reset;
    }
    else if (kill % 14 == 3)
        cout << red << "Team Killer" << reset;
    else if (kill % 14 == 4)
        cout << red << "Headshot" << reset;
    else if (kill % 14 == 5)
        cout << red << "Rampage" << reset;
    else if (kill % 14 == 6)
        cout << red << "Killing Spree" << reset;
    else if (kill % 14 == 7)
        cout << red << "Unstoppable" << reset;
    else if (kill % 14 == 8)
        cout << red << "Monster Kill" << reset;
    else if (kill % 14 == 9)
        cout << red << "Multi Kill" << reset;
    else if (kill % 14 == 10)
        cout << red << "Ludicrouskill" << reset;
    else if (kill % 14 == 11)
        cout << red << "Ultra Kill" << reset;
    else if (kill % 14 == 12)
        cout << red << "Dominating" << reset;
    else if (kill % 14 == 13)
        cout << red << "Godlike" << reset;
}
int main()
{
    srand(time(NULL));
    Welcome();
    sleep(1);

    while (true)
    {
        system("clear");
        while (!start)
        {
            Menu();
        }
        Board();
        Shooting();
        Player_Move();
        Zombie_Move();
        Upgrade();
        Game_menu();
        Show();
        Reload();
        key_counter++;
        Death();
        if (end_game == 1)
        {
            start = false;
            continue;
        }
        else if (end_game == 0)
        {
            key_counter = 0;
            cout << "The game will restart in 5 seconds";
            sleep(2);
            health = max_health;
            bullet = max_bullet;
            vaccine = 0;
            player_Location[0] = 1;
            player_Location[1] = 1;
            end_game = 10;
            for (int i = 0; i < 15; i++)
                for (int j = 0; j < 15; j++)
                    ground[i][j] = ' ';
            continue;
        }
        getch();
    }
}