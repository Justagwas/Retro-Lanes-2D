#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <random>

int devkey = 0;
int WINDOW_WIDTH = 400;
int WINDOW_HEIGHT = 800;
double CAR_SPEED = 5.0;
double ROAD_SCROLL_SPEED = 32.0;
double SPAWN_RATE = 1.0;
const int NUM_CARS = 2;
double points = 0;
long totalScore = 0;
long best = 0;
long cash = 0;
int bet = 10;
int times = 0;
long chips = 0;
int keygen = 2 * (2 * log(exp(1)) * sqrt(log(4) * sqrt(exp(1))));
int keys = 0;
bool devmode = 0;
bool opencasino = 0;

using namespace sf;
using namespace std;

string dataFile = "data.txt";
vector<int> ownedCars = { 5,9,10,12 };
Texture carTexture;
string selectedCar = "car.png";
vector<string> carTextures = { "car1.png", "car2.png", "car4.png", "car5.png", "car6.png", "car7.png", "car8.png", "car9.png", "car10.png", "car11.png", "car12.png", "car13.png" };
vector<string> AvailableCars = { "car1.png", "car9.png", "car4.png", "car12.png" };

class Car {
public:
    Sprite sprite;
    vector<Texture> textures;

    Car(double x, double y, double width, double height) {
        for (const auto& fileName : carTextures) {
            Texture texture;
            if (!texture.loadFromFile(fileName)) {
                cerr << "Error loading texture: " << fileName << endl;
            }
            texture.setSmooth(1);
            textures.push_back(texture);
        }

        setRandomTexture();
        sprite.setPosition(x, y);
        sprite.setScale(width / sprite.getLocalBounds().width / 1.2, height / sprite.getLocalBounds().height / 1.2);
    }

    void move(double offsetX, double offsetY) {
        sprite.move(offsetX, offsetY);
    }

    void setRandomTexture() {
        int index = rand() % textures.size();
        sprite.setTexture(textures[index]);
    }
};

class PlayerCar {
public:
    Sprite sprite;

    PlayerCar(Texture& texture, double x, double y, double width, double height) {
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        sprite.setScale(width / sprite.getLocalBounds().width / 1.2, height / sprite.getLocalBounds().height / 1.2);
    }

    void moveLeft(double distance) {
        double newX = sprite.getPosition().x - distance;
        if (newX >= 0)
            sprite.setPosition(newX, sprite.getPosition().y);
    }

    void moveRight(double distance) {
        double newX = sprite.getPosition().x + distance;
        if (newX + sprite.getGlobalBounds().width <= WINDOW_WIDTH)
            sprite.setPosition(newX, sprite.getPosition().y);
    }
};

void displayMenu(RenderWindow& window, Font& font);
void displaySettings(RenderWindow& window, Font& font);
void displayShop(RenderWindow& window, Font& font);
void gameLoop(RenderWindow& window, Texture& roadTexture, Font& font);
void games();
int main();

string encryptDecrypt(const string& toEncrypt) {
    string output = toEncrypt;
    keys++;
    for (size_t i = 0; i < toEncrypt.size(); i++) {
        char key = keys + 65 + keygen;
        output[i] = toEncrypt[i] ^ key;
    }

    return output;
}

void saveScore() {
    ofstream file(dataFile);
    if (file.is_open()) {
        keys = 0;
        string encryptedScore = encryptDecrypt(to_string(static_cast<int>(totalScore)));
        string encryptedBest = encryptDecrypt(to_string(static_cast<int>(best)));
        string encryptedCash = encryptDecrypt(to_string(static_cast<int>(cash)));
        string encryptedChips = encryptDecrypt(to_string(static_cast<int>(chips)));
        string encryptedTime = encryptDecrypt(to_string(static_cast<int>(times)));
        string encryptedmode = encryptDecrypt(to_string(static_cast<bool>(devmode)));
        file << "IF DATA DOESN'T LOAD DELETE data.txt\n" << encryptedScore << endl << encryptedBest << endl << encryptedCash << endl << encryptedChips << endl << encryptedTime << endl << encryptedmode;
        for (int i = 0; i < 4; i++) {
            string encryptedCars = encryptDecrypt(to_string(static_cast<int>(ownedCars[i])));
            file << endl << encryptedCars;
        }
        file.close();
    }
    else {
        cerr << "Unable to open file for writing." << endl;
    }
}

int speed = 0;

void cls() {
    COORD pos = { 0, 0 };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void prin(vector<int> num) {

    cout << "   .----------------.    .----------------.    .----------------. \n"
        << "  | .--------------. |  | .--------------. |  | .--------------. |";

    cout << endl;

    for (int i = 0; i < 3; i++) {
        switch (num[i]) {
        case 1:
            cout << "  | |     __       | |";
            break;
        case 2:
            cout << "  | |    _____     | |";
            break;
        case 3:
            cout << "  | |    ______    | |";
            break;
        case 4:
            cout << "  | |   _    _     | |";
            break;
        case 5:
            cout << "  | |   _______    | |";
            break;
        case 6:
            cout << "  | |    ______    | |";
            break;
        case 7:
            cout << "  | |   _______    | |";
            break;
        default:
            cout << "  | |              | |";
            break;
        }
    }
    cout << endl;

    for (int i = 0; i < 3; i++) {
        switch (num[i]) {
        case 1:
            cout << "  | |    /  |      | |";
            break;
        case 2:
            cout << "  | |   / ___ `.   | |";
            break;
        case 3:
            cout << "  | |   / ____ `.  | |";
            break;
        case 4:
            cout << "  | |  | |  | |    | |";
            break;
        case 5:
            cout << "  | |  |  _____|   | |";
            break;
        case 6:
            cout << "  | |  .' ____ \\   | |";
            break;
        case 7:
            cout << "  | |  |  ___  |   | |";
            break;
        default:
            cout << "  | |              | |";
            break;
        }
    }
    cout << endl;

    for (int i = 0; i < 3; i++) {
        switch (num[i]) {
        case 1:
            cout << "  | |    `| |      | |";
            break;
        case 2:
            cout << "  | |  |_/___) |   | |";
            break;
        case 3:
            cout << "  | |   `'  __) |  | |";
            break;
        case 4:
            cout << "  | |  | |__| |_   | |";
            break;
        case 5:
            cout << "  | |  | |____     | |";
            break;
        case 6:
            cout << "  | |  | |____\\_|  | |";
            break;
        case 7:
            cout << "  | |  |_/  / /    | |";
            break;
        default:
            cout << "  | |              | |";
            break;
        }
    }
    cout << endl;

    for (int i = 0; i < 3; i++) {
        switch (num[i]) {
        case 1:
            cout << "  | |     | |      | |";
            break;
        case 2:
            cout << "  | |   .'____.'   | |";
            break;
        case 3:
            cout << "  | |   _  |__ '.  | |";
            break;
        case 4:
            cout << "  | |  |____   _|  | |";
            break;
        case 5:
            cout << "  | |  '_.____''.  | |";
            break;
        case 6:
            cout << "  | |  | '____`'.  | |";
            break;
        case 7:
            cout << "  | |      / /     | |";
            break;
        default:
            cout << "  | |              | |";
            break;
        }
    }
    cout << endl;

    for (int i = 0; i < 3; i++) {
        switch (num[i]) {
        case 1:
            cout << "  | |    _| |_     | |";
            break;
        case 2:
            cout << "  | |  / /____     | |";
            break;
        case 3:
            cout << "  | |  | \\____) |  | |";
            break;
        case 4:
            cout << "  | |      _| |_   | |";
            break;
        case 5:
            cout << "  | |  | \\____) |  | |";
            break;
        case 6:
            cout << "  | |  | (____) |  | |";
            break;
        case 7:
            cout << "  | |     / /      | |";
            break;
        default:
            cout << "  | |              | |";
            break;
        }
    }
    cout << endl;

    for (int i = 0; i < 3; i++) {
        switch (num[i]) {
        case 1:
            cout << "  | |   |_____|    | |";
            break;
        case 2:
            cout << "  | |  |_______|   | |";
            break;
        case 3:
            cout << "  | |   \\______.'  | |";
            break;
        case 4:
            cout << "  | |     |_____|  | |";
            break;
        case 5:
            cout << "  | |   \\______.'  | |";
            break;
        case 6:
            cout << "  | |  '.______.'  | |";
            break;
        case 7:
            cout << "  | |    /_/       | |";
            break;
        default:
            cout << "  | |              | |";
            break;
        }
    }
    cout << "\n  | |              | |  | |              | |  | |              | |\n"
        << "  | '--------------' |  | '--------------' |  | '--------------' |\n"
        << "   '----------------'    '----------------'    '----------------' ";

}
void hide() {
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(outputHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(outputHandle, &cursorInfo);
}
void show() {
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(outputHandle, &cursorInfo);
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(outputHandle, &cursorInfo);
}


void win(vector<int> num) {
    hide();
    Sleep(200 / speed);
    system("CLS");
    prin(num);
    cout << endl << endl << endl;
    cout << "   _    _ \n";
    cout << "  | |  | |\n";
    cout << "  | |  | |\n";
    cout << "  | |\\/| |\n";
    cout << "  \\  /\\  /\n";
    cout << "   \\/  \\/ \n";
    Sleep(500 / speed);
    cls();
    prin(num);
    cout << endl << endl << endl;
    cout << "   _    _  _____ \n";
    cout << "  | |  | ||_   _|\n";
    cout << "  | |  | |  | |  \n";
    cout << "  | |\\/| |  | |  \n";
    cout << "  \\  /\\  / _| |_ \n";
    cout << "   \\/  \\/  \\___/ \n";
    Sleep(500 / speed);
    cls();
    prin(num);
    cout << endl << endl << endl;
    cout << "   _    _  _____  _   _ \n";
    cout << "  | |  | ||_   _|| \\ | |\n";
    cout << "  | |  | |  | |  |  \\| |\n";
    cout << "  | |\\/| |  | |  | . ` |\n";
    cout << "  \\  /\\  / _| |_ | |\\  |\n";
    cout << "   \\/  \\/  \\___/ \\_| \\_/\n";
    Sleep(500 / speed);
    cls();
    prin(num);
    cout << endl << endl << endl;
    cout << "   _    _  _____  _   _  _   _ \n";
    cout << "  | |  | ||_   _|| \\ | || \\ | |\n";
    cout << "  | |  | |  | |  |  \\| ||  \\| |\n";
    cout << "  | |\\/| |  | |  | . ` || . ` |\n";
    cout << "  \\  /\\  / _| |_ | |\\  || |\\  |\n";
    cout << "   \\/  \\/  \\___/ \\_| \\_/\\_| \\_/\n";

    Sleep(500 / speed);
    cls();
    prin(num);
    cout << endl << endl << endl;
    cout << "   _    _  _____  _   _  _   _  _____ \n";
    cout << "  | |  | ||_   _|| \\ | || \\ | ||  ___|\n";
    cout << "  | |  | |  | |  |  \\| ||  \\| || |__  \n";
    cout << "  | |\\/| |  | |  | . ` || . ` ||  __| \n";
    cout << "  \\  /\\  / _| |_ | |\\  || |\\  || |___ \n";
    cout << "   \\/  \\/  \\___/ \\_| \\_/\\_| \\_/\\____/ \n";
    for (int i = 0; i < 4; i++) {
        Sleep(300);
        cls();
        prin(num);
        cout << endl << endl << endl;
        cout << "   _    _  _____  _   _  _   _  _____ ______ \n";
        cout << "  | |  | ||_   _|| \\ | || \\ | ||  ___|| ___ \\\n";
        cout << "  | |  | |  | |  |  \\| ||  \\| || |__  | |_/ /\n";
        cout << "  | |\\/| |  | |  | . ` || . ` ||  __| |    / \n";
        cout << "  \\  /\\  / _| |_ | |\\  || |\\  || |___ | |\\ \\ \n";
        cout << "   \\/  \\/  \\___/ \\_| \\_/\\_| \\_/\\____/ \\_| \\_|\n";
        Sleep(300);
        system("CLS");
        prin(num);
    }
    show();
}

int generate() {

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    default_random_engine generator(seed);

    uniform_int_distribution<int> distribution(0, 100);

    int num = distribution(generator);

    if (num <= 40) {
        return 1;
    }
    else if (num <= 60) {
        return 2;
    }
    else if (num <= 80) {
        return 3;
    }
    else if (num <= 90) {
        return 4;
    }
    else if (num <= 95) {
        return 5;
    }
    else if (num <= 98) {
        return 6;
    }
    else {
        return 7;
    }
}

void mainend();

void betchange() {
    int abc;
    system("cls");
    string temp6 = "  Choose Bet Amount (Chips):\n";
    for (int i = 0; i < temp6.size(); i++) {
        cout << temp6[i];
        Sleep(10 / speed);
    }

    cout << "  10 Chips > 1\n";
    Sleep(40);
    cout << "  20 Chips > 2\n";
    Sleep(40);
    cout << "  50 Chips > 3\n";
    Sleep(40);
    cout << "  100 Chips > 4\n";
    Sleep(40);
    cout << "  " + to_string(chips) + " Chips > 5\n";
    Sleep(40);
    cout << "> ";
    cin >> abc;
    if (abc > 5 || abc < 0) {
        cout << "The defined range is [1;5]";
        Sleep(500);
        betchange();
    }
    abc == 1 ? bet = 10 : abc;
    abc == 2 ? bet = 20 : abc;
    abc == 3 ? bet = 50 : abc;
    abc == 4 ? bet = 100 : abc;
    abc == 5 ? bet = chips : abc;
    cin.ignore(999, '\n');
    mainend();
}

void rollNumbers(vector<int>& sum, int delays, int bet) {
    hide();
    system("cls");
    sum[0] = generate();
    sum[1] = generate();
    sum[2] = generate();
    int sumold1 = sum[0];
    int sumold2 = sum[1];
    int sumold3 = sum[2];

    while (sum[0] == sum[1] || sum[0] == sum[2]) {
        sum[0] = generate();
    }
    while (sum[1] == sum[2] || sum[1] == sum[0]) {
        sum[1] = generate();
    }

    for (int i = 0; i < 71; i++) {

        Sleep(delays);
        if (i > 40) {
            if (i >= 50) {
                sum[0] = sumold1;
            }
            else if (i % 2 == 0) {
                sum[0]--;
                if (sum[0] <= 1) {
                    sum[0] = 7;
                }
            }
        }
        else {
            sum[0]--;
            if (sum[0] <= 1) {
                sum[0] = 7;
            }
        }
        Sleep(delays);
        cls();
        prin(sum);
        if (i > 50) {
            if (i >= 60) {
                sum[1] = sumold2;
            }
            else if (i % 2 == 0) {
                sum[1]--;
                if (sum[1] <= 1) {
                    sum[1] = 7;
                }
            }
        }
        else {
            sum[1]--;
            if (sum[1] <= 1) {
                sum[1] = 7;
            }
        }
        Sleep(delays);
        if (i > 60) {
            if (i >= 70) {
                sum[2] = sumold3;
            }
            else if (i % 2 == 0) {
                sum[2]--;
                if (sum[2] <= 1) {
                    sum[2] = 7;
                }
            }
        }
        else {
            sum[2]--;
            if (sum[2] <= 1) {
                sum[2] = 7;
            }
        }
        Sleep(delays);
        cls();
        prin(sum);
    }
    show();
    cout << endl << endl << endl;
    if (chips < bet) return;

    if (sum[0] == sum[1] && sum[1] == sum[2]) return;

    string temp4 = "  Press enter to spin (" + to_string(bet) + " Chips COST) || q to quit || 0 to change bet\n";

    for (int i = 0; i < temp4.size(); i++) {
        cout << temp4[i];
        Sleep(10 / speed);
    }
    cout << endl << "> ";
back:
    char input;
    cin.get(input);
    if (input == '\n' || input == '\0') {
    }
    else if (input == 48) {
        betchange();
    }
    else if (input == 'q' || input == 'Q') {
        cin.ignore();
        return;
    }
    else {
        goto back;
    }
    chips -= bet;
    times++;
    saveScore();
    sum = { 0, 0, 0 };
    delays = 10 / speed;
    rollNumbers(sum, delays, bet);
}


void mainend() {
    system("cls");

    cout << "   .----------------.  .----------------.  .----------------.  .----------------.  .----------------. \n"
        "  | .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n"
        "  | |    _______   | || |   _____      | || |     ____     | || |  _________   | || |    _______   | |\n"
        "  | |   /  ___  |  | || |  |_   _|     | || |   .'    `.   | || | |  _   _  |  | || |   /  ___  |  | |\n"
        "  | |  |  (__ \\_|  | || |    | |       | || |  /  .--.  \\  | || | |_/ | | \\_|  | || |  |  (__ \\_|  | |\n"
        "  | |   '.___`-.   | || |    | |   _   | || |  | |    | |  | || |     | |      | || |   '.___`-.   | |\n"
        "  | |  |`\\____) |  | || |   _| |__/ |  | || |  \\  `--'  /  | || |    _| |_     | || |  |`\\____) |  | |\n"
        "  | |  |_______.'  | || |  |________|  | || |   `.____.'   | || |   |_____|    | || |  |_______.'  | |\n"
        "  | |              | || |              | || |              | || |              | || |              | |\n"
        "  | '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |\n"
        "   '----------------'  '----------------'  '----------------'  '----------------'  '----------------' \n\n\n";

    string temp1 = "  Owned Chips: ";
    string temp3 = "  Owned Money ($): ";
    string temp2 = "  Times Spun: ";

    for (int i = 0; i < temp1.size(); i++) {
        cout << temp1[i];
        Sleep(10 / speed);
    }
    cout << chips << endl << endl;
    for (int i = 0; i < temp3.size(); i++) {
        cout << temp3[i];
        Sleep(10 / speed);
    }
    cout << cash << endl << endl;
    for (int i = 0; i < temp2.size(); i++) {
        cout << temp2[i];
        Sleep(10 / speed);
    }

    cout << times << endl << endl;

    string temp4 = "  Press enter to spin (" + to_string(bet) + " Chips COST) || q to quit || 0 to change bet\n";

    for (int i = 0; i < temp4.size(); i++) {
        cout << temp4[i];
        Sleep(10 / speed);
    }
    cout << endl << "> ";
back:
    char input;
    cin.get(input);
    if (input == '\n' || input == '\0') {
    }
    else if (input == 48) {
        betchange();
    }
    else if (input == 'q' || input == 'Q') {
        games();
    }
    else {
        goto back;
    }
    string temp7 = "  Insufficient Chips Amount\n";
    if (chips < bet) {
        for (int i = 0; i < temp7.size(); i++) {
            cout << temp7[i];
            Sleep(10 / speed);
        }
        Sleep(500);
        mainend();
    }
    vector<int> sum = { 0, 0, 0 };

    int initialDelay = 10 / speed;
    times++;
    chips -= bet;
    saveScore();

    rollNumbers(sum, initialDelay, bet);

    if (sum[0] == sum[1] && sum[1] == sum[2]) {

        win(sum);
        cout << endl << endl << endl;
        switch (sum[0]) {

        case 1: cash += 200 * bet / 10;
            cout << "  Money won: " << 200 * bet / 10;
            saveScore();
            Sleep(2000);
            break;

        case 2: cash += 400 * bet / 10;
            cout << "  Money won: " << 400 * bet / 10;
            saveScore();
            Sleep(2000);
            break;

        case 3: cash += 800 * bet / 10;
            cout << "  Money won: " << 800 * bet / 10;
            saveScore();
            Sleep(2000);
            break;

        case 4: cash += 2000 * bet / 10;
            cout << "  Money won: " << 2000 * bet / 10;
            saveScore();
            Sleep(2000);
            break;

        case 5: cash += 5000 * bet / 10;
            cout << "  Money won: " << 5000 * bet / 10;
            saveScore();
            Sleep(2000);
            break;

        case 6: cash += 10000 * bet / 10;
            cout << "  Money won: " << 10000 * bet / 10;
            saveScore();
            Sleep(2000);
            break;

        case 7: cash += 100000 * bet / 10;
            cout << "  Money won: " << 100000 * bet / 10;
            saveScore();
            Sleep(2000);
            break;

        default: break;
        }
    }
    mainend();
}

int slots() {

    system("cls");

    int tries = 0;

    while (true) {
        system("cls");
        tries++;
        if (tries > 3) {
            cout << "CONSOLE ERROR\n PROCEEDING WITH SPEED: 1";
            speed = 1;
            break;
        }
        cout << "   _____  ______  _______  _______  _____  _   _   _____   _____ \n";
        cout << "  / ____||  ____||__   __||__   __||_   _|| \\ | | / ____| / ____|\n";
        cout << " | (___  | |__      | |      | |     | |  |  \\| || |  __ | (___  \n";
        cout << "  \\___ \\ |  __|     | |      | |     | |  | . ` || | |_ | \\___ \\ \n";
        cout << "  ____) || |____    | |      | |    _| |_ | |\\  || |__| | ____) |\n";
        cout << " |_____/ |______|   |_|      |_|   |_____||_| \\_| \\_____||_____/ \n\n";

        string temp1 = "Define console SPEED (default: 1, max: 2, min: 1) \n0 To QUIT";
        for (int i = 0; i < temp1.size(); i++) {
            cout << temp1[i];
            Sleep(10);
        }
        cout << endl << "> ";
        cin >> speed;

        if (speed > 2 || speed < 0) {
            cout << "SPEED DECLARATION ERROR\n";
            Sleep(500);
        }
        else {
            break;
        }
    }
    if (speed == 0) games();
    cin.ignore(999, '\n');

    mainend();

    return 0;
}

void games() {
    system("cls");
    int converter;
    int abc;
    devmode == 1 ? cout << "DEVELOPER MODE ACTIVE\n" : cout << "";
    cout << "Chips > " << chips << endl;
    cout << "Cash $ > " << cash << endl;
    cout << "Choose a function 1-3:\n";
    cout << "> 1 - Slots Machine\n";
    cout << "> 2 - Point to Chip Conversion\n";
    cout << "> 3 - Quit\n> ";
    cin >> abc;
    if (abc == devkey) devmode = 1;
    if (devmode == 0 || abc < 4 && abc>0) {
        while (abc > 3 || abc < 1) {
            system("cls");
            cout << "Chips > " << chips << endl;
            cout << "Cash $ > " << cash << endl;
            cout << "NON-EXISTING FUNCTION CHOSEN\n\n";
            cout << "Choose a function 1-3:\n";
            cout << "> 1 - Slots Machine\n";
            cout << "> 2 - Point to Chip Conversion\n";
            cout << "> 3 - Quit\n> ";
            cin >> abc;
        }
        if (abc == 3) {
            system("cls");

            opencasino = 0;
            main();
        }
        if (abc == 2) {
            system("cls");
            cout << "Available Points > " << totalScore << endl;
            cout << "Chip Balanace > " << chips << endl;
            cout << "Cash > " << cash << endl;
            cout << "Points to Chips RATIO > 10:1\n";
            cout << "Points to convert (0 To Return) > ";
            cin >> converter;
            while (converter != 0) {
                while (converter<10 || converter > totalScore) {
                    system("cls");
                    cout << "ENTER EXISTING VALUES\n";
                    cout << "Available Points > " << totalScore << endl;
                    cout << "Chip Balanace > " << chips << endl;
                    cout << "Cash > " << cash << endl;
                    cout << "Points to Chips RATIO > 10:1\n";
                    cout << "Points to convert (0 To Return) > ";
                    cin >> converter;
                    if (converter == 0) break;
                }
                totalScore -= converter;
                chips += converter / 10;
                system("cls");
                cout << "Available Points > " << totalScore << endl;
                cout << "Chip Balanace > " << chips << endl;
                cout << "Cash > " << cash << endl;
                cout << "Points to Chips RATIO > 10:1\n";
                cout << "Points to convert (0 To Return) > ";
                cin >> converter;
            }
            saveScore();
            games();
        }
        if (abc == 1) {
            slots();
        }
        system("cls");
        opencasino = 0;
        main();
    }
    else {
        cout << "TotalScore\nCash\nChips\n";
        cin >> abc;
        switch (abc) {
        case 1:
            cin >> abc;
            totalScore += abc;
            saveScore();
            break;
        case 2:
            cin >> abc;
            cash += abc;
            saveScore();
            break;
        case 3:
            cin >> abc;
            chips += abc;
            saveScore();
            break;
        default: games();
            break;
        }
        games();
    }
}

void displayMenu(RenderWindow& window, Font& font) {
    Text title("Retro Lanes 2D", font, 50);
    title.setPosition(WINDOW_WIDTH / 2 - title.getLocalBounds().width / 2, 50);

    Text start("Start", font, 30);
    start.setPosition(WINDOW_WIDTH / 2 - start.getLocalBounds().width / 2, 400);

    Text settings("Settings", font, 30);
    settings.setPosition(WINDOW_WIDTH / 2 - settings.getLocalBounds().width / 2, 550);

    Text shop("Shop", font, 30);
    shop.setPosition(WINDOW_WIDTH / 2 - shop.getLocalBounds().width / 2, 450);

    Text score("Score: " + to_string(static_cast<int>(points)), font, 30);
    score.setPosition(WINDOW_WIDTH / 2 - score.getLocalBounds().width / 2, 300);

    Text ca("Cash: " + to_string(static_cast<int>(cash)) + "$", font, 30);
    ca.setPosition(WINDOW_WIDTH / 2 - ca.getLocalBounds().width / 2, 250);

    Text bestsc("High Score: " + to_string(static_cast<int>(best)), font, 30);
    bestsc.setPosition(WINDOW_WIDTH / 2 - bestsc.getLocalBounds().width / 2, 200);

    Text highScore("Total Score: " + to_string(static_cast<int>(totalScore)), font, 30);
    highScore.setPosition(WINDOW_WIDTH / 2 - highScore.getLocalBounds().width / 2, 150);

    Text casino("Casino", font, 30);
    casino.setPosition(WINDOW_WIDTH / 2 - casino.getLocalBounds().width / 2, 500);

    window.clear();
    window.draw(title);
    window.draw(start);
    window.draw(settings);
    window.draw(shop);
    window.draw(score);
    window.draw(bestsc);
    window.draw(casino);
    window.draw(ca);
    window.draw(highScore);
    window.display();

    while (true) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                exit(0);
            }
            if (event.type == Event::MouseButtonPressed) {
                if (start.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    return;
                }
                if (settings.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    displaySettings(window, font);
                    return;
                }
                if (shop.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    displayShop(window, font);
                    return;
                }
                if (casino.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    opencasino = opencasino == 1 ? opencasino = 0 : opencasino = 1;
                    window.close();
                    games();
                }
            }
        }
    }
}
void displayShop(RenderWindow& window, Font& font) {
    Texture carTexture1, carTexture2, carTexture3, carTexture4;
    if (!carTexture1.loadFromFile("car1.png") || !carTexture2.loadFromFile("car9.png") || !carTexture3.loadFromFile("car4.png") || !carTexture4.loadFromFile("car12.png")) {
        cerr << "Failed to load car textures." << endl;
        return;
    }

    Text title("Shop", font, 50);
    title.setPosition(WINDOW_WIDTH / 2 - title.getLocalBounds().width / 2, 0);

    Sprite car1(carTexture1), car2(carTexture2), car3(carTexture3), car4(carTexture4);
    car1.setScale(0.4f, 0.4f);
    car2.setScale(0.4f, 0.4f);
    car1.setPosition(30, 80);
    car2.setPosition(220, 80);

    Text car1txt("4000$", font, 30);
    car1txt.setPosition(50, 380);
    Text car2txt("12500$", font, 30);
    car2txt.setPosition(250, 380);

    car3.setScale(0.4f, 0.4f);
    car4.setScale(0.4f, 0.4f);
    car3.setPosition(30, 430);
    car4.setPosition(220, 430);

    Text car3txt("20000$", font, 30);
    car3txt.setPosition(50, 730);
    Text car4txt("70000$", font, 30);
    car4txt.setPosition(250, 730);

    Text back("Back", font, 30);
    back.setPosition(WINDOW_WIDTH / 2 - back.getLocalBounds().width / 2, 750);

    if (ownedCars[0] < 2) car1txt.setString("Select");
    if (ownedCars[1] < 6) car2txt.setString("Select");
    if (ownedCars[2] < 5) car3txt.setString("Select");
    if (ownedCars[3] < 7) car4txt.setString("Select");
    if (selectedCar == "car1.png") car1txt.setString("Selected");
    if (selectedCar == "car9.png") car2txt.setString("Selected");
    if (selectedCar == "car4.png") car3txt.setString("Selected");
    if (selectedCar == "car12.png") car4txt.setString("Selected");

    window.clear();
    window.draw(title);
    window.draw(car1);
    window.draw(car2);
    window.draw(car3);
    window.draw(car4);
    window.draw(car1txt);
    window.draw(car2txt);
    window.draw(car3txt);
    window.draw(car4txt);
    window.draw(back);
    window.display();

    while (true) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                exit(0);
            }
            if (event.type == Event::MouseButtonPressed) {
                if (back.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    displayMenu(window, font);
                    return;
                }
                if (car1txt.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (ownedCars[0] < 2) {
                        selectedCar = AvailableCars[0];
                        if (!carTexture.loadFromFile(selectedCar)) {
                            cerr << "Failed to load car texture." << endl;
                            return;
                        }
                        carTexture.setSmooth(1);
                    }
                    else if (cash > 4000) {
                        cash -= 4000;
                        selectedCar = AvailableCars[0];
                        ownedCars[0] = 1;
                        saveScore();
                        if (!carTexture.loadFromFile(selectedCar)) {
                            cerr << "Failed to load car texture." << endl;
                            return;
                        }
                        carTexture.setSmooth(1);
                    }
                }
                if (car2txt.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (ownedCars[1] < 6) {
                        selectedCar = AvailableCars[1];
                        if (!carTexture.loadFromFile(selectedCar)) {
                            cerr << "Failed to load car texture." << endl;
                            return;
                        }
                        carTexture.setSmooth(1);
                    }
                    else if (cash > 12500) {
                        cash -= 12500;
                        selectedCar = AvailableCars[1];
                        ownedCars[1] = 5;
                        saveScore();
                        if (!carTexture.loadFromFile(selectedCar)) {
                            cerr << "Failed to load car texture." << endl;
                            return;
                        }
                        carTexture.setSmooth(1);
                    }
                }
                if (car3txt.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (ownedCars[2] < 4) {
                        selectedCar = AvailableCars[2];
                        if (!carTexture.loadFromFile(selectedCar)) {
                            cerr << "Failed to load car texture." << endl;
                            return;
                        }
                        carTexture.setSmooth(1);
                    }
                    else if (cash > 20000) {
                        cash -= 20000;
                        selectedCar = AvailableCars[2];
                        ownedCars[2] = 3;
                        saveScore();
                        if (!carTexture.loadFromFile(selectedCar)) {
                            cerr << "Failed to load car texture." << endl;
                            return;
                        }
                        carTexture.setSmooth(1);
                    }
                }
                if (car4txt.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    if (ownedCars[3] < 7) {
                        selectedCar = AvailableCars[3];
                        if (!carTexture.loadFromFile(selectedCar)) {
                            cerr << "Failed to load car texture." << endl;
                            return;
                        }
                        carTexture.setSmooth(1);
                    }
                    else if (cash > 70000) {
                        cash -= 70000;
                        selectedCar = AvailableCars[3];
                        ownedCars[3] = 6;
                        saveScore();
                        if (!carTexture.loadFromFile(selectedCar)) {
                            cerr << "Failed to load car texture." << endl;
                            return;
                        }
                        carTexture.setSmooth(1);
                    }
                }
                if (ownedCars[0] < 2) car1txt.setString("Select");
                if (ownedCars[1] < 6) car2txt.setString("Select");
                if (ownedCars[2] < 5) car3txt.setString("Select");
                if (ownedCars[3] < 7) car4txt.setString("Select");
                if (selectedCar == "car1.png") car1txt.setString("Selected");
                if (selectedCar == "car9.png") car2txt.setString("Selected");
                if (selectedCar == "car4.png") car3txt.setString("Selected");
                if (selectedCar == "car12.png") car4txt.setString("Selected");
                window.clear();
                window.draw(title);
                window.draw(car1);
                window.draw(car2);
                window.draw(car3);
                window.draw(car4);
                window.draw(car1txt);
                window.draw(car2txt);
                window.draw(car3txt);
                window.draw(car4txt);
                window.draw(back);
                window.display();
            }
        }
    }
}

void displaySettings(RenderWindow& window, Font& font) {
    Text title("Settings", font, 50);
    title.setPosition(WINDOW_WIDTH / 2 - title.getLocalBounds().width / 2, 100);

    Text carSpeedText("Car Speed: " + to_string(static_cast<int>(CAR_SPEED)), font, 30);
    carSpeedText.setPosition(WINDOW_WIDTH / 2 - carSpeedText.getLocalBounds().width / 2, 300);

    Text spawnRateText("Spawn Rate: " + to_string(static_cast<double>(SPAWN_RATE)), font, 30);
    spawnRateText.setPosition(WINDOW_WIDTH / 2 - spawnRateText.getLocalBounds().width / 2 + 40, 400);
    spawnRateText.setString(spawnRateText.getString().substring(0, spawnRateText.getString().find('.') + 2));

    Text back("Back", font, 30);
    back.setPosition(WINDOW_WIDTH / 2 - back.getLocalBounds().width / 2, 500);

    Text increaseSpeed("+", font, 50);
    increaseSpeed.setPosition(WINDOW_WIDTH / 2 + carSpeedText.getLocalBounds().width / 2 + 20, 300);

    Text decreaseSpeed("-", font, 50);
    decreaseSpeed.setPosition(WINDOW_WIDTH / 2 - carSpeedText.getLocalBounds().width / 2 - 40, 300);

    Text increaseSpawn("+", font, 50);
    increaseSpawn.setPosition(WINDOW_WIDTH / 2 + spawnRateText.getLocalBounds().width / 2 + 20, 400);

    Text decreaseSpawn("-", font, 50);
    decreaseSpawn.setPosition(WINDOW_WIDTH / 2 - spawnRateText.getLocalBounds().width / 2 - 40, 400);

    window.clear();
    window.draw(title);
    window.draw(carSpeedText);
    window.draw(spawnRateText);
    window.draw(back);
    window.draw(increaseSpeed);
    window.draw(decreaseSpeed);
    window.draw(increaseSpawn);
    window.draw(decreaseSpawn);
    window.display();

    while (true) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                exit(0);
            }
            if (event.type == Event::MouseButtonPressed) {
                if (back.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    displayMenu(window, font);
                    return;
                }
                if (increaseSpeed.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    CAR_SPEED += 1;
                    if (CAR_SPEED > 20) CAR_SPEED = 20;
                    carSpeedText.setString("Car Speed: " + to_string(static_cast<int>(CAR_SPEED)));
                }
                if (decreaseSpeed.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    CAR_SPEED -= 1;
                    if (CAR_SPEED < 5) CAR_SPEED = 5;
                    carSpeedText.setString("Car Speed: " + to_string(static_cast<int>(CAR_SPEED)));
                }
                if (increaseSpawn.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    SPAWN_RATE += 0.1;
                    if (SPAWN_RATE > 2) SPAWN_RATE = 2;
                    spawnRateText.setString("Spawn Rate: " + to_string(static_cast<double>(SPAWN_RATE)));
                    spawnRateText.setString(spawnRateText.getString().substring(0, spawnRateText.getString().find('.') + 2));
                }
                if (decreaseSpawn.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    SPAWN_RATE -= 0.1;
                    if (SPAWN_RATE < 0.5) SPAWN_RATE = 0.5;
                    spawnRateText.setString("Spawn Rate: " + to_string(static_cast<double>(SPAWN_RATE)));
                    spawnRateText.setString(spawnRateText.getString().substring(0, spawnRateText.getString().find('.') + 2));
                }

                window.clear();
                window.draw(title);
                window.draw(carSpeedText);
                window.draw(spawnRateText);
                window.draw(back);
                window.draw(increaseSpeed);
                window.draw(decreaseSpeed);
                window.draw(increaseSpawn);
                window.draw(decreaseSpawn);
                window.display();
            }
        }
    }
}

void Overlay(RenderWindow& window) {
    RectangleShape overlay(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    overlay.setFillColor(Color(0, 0, 0, 150));
    window.draw(overlay);
}

void countdown(RenderWindow& window, Font& font) {
    for (int i = 3; i > 0; --i) {
        window.clear();
        Overlay(window);

        Text countDownText(to_string(i), font, 100);
        countDownText.setFillColor(Color::White);
        countDownText.setPosition(WINDOW_WIDTH / 2 - countDownText.getLocalBounds().width / 2, WINDOW_HEIGHT / 2 - countDownText.getLocalBounds().height / 2);

        window.draw(countDownText);
        window.display();

        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void gameLoop(RenderWindow& window, Texture& roadTexture, Font& font) {
    int intersections = 0;
    Sprite roadSprite(roadTexture);
    vector<Car> enemyCars;

    srand(time(NULL));
    for (int i = 0; i < NUM_CARS; i++) {
        double randX;
        double randY = -400 * ((i + 1) * 3 / SPAWN_RATE);
        if (rand() % 2 == 0) {
            randX = WINDOW_WIDTH - 380;
        }
        else {
            randX = WINDOW_WIDTH - 190;
        }
        double carWidth = WINDOW_WIDTH / 2.0;
        double carHeight = carWidth * 1.65;
        enemyCars.emplace_back(randX, randY, carWidth, carHeight);
    }

    PlayerCar playerCar(carTexture, (WINDOW_WIDTH - WINDOW_WIDTH / 2) / 1.5, WINDOW_HEIGHT - 300, WINDOW_WIDTH / 2.0, WINDOW_WIDTH / 2.0 * 1.65);

    double roadY = -210;
    Clock clock;
    points = 0;
    double startTime = clock.getElapsedTime().asSeconds();

    countdown(window, font);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        roadY += ROAD_SCROLL_SPEED;
        if (roadY >= 0) {
            roadY = -210;
        }
        roadSprite.setPosition(0, roadY);

        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
            playerCar.moveLeft(CAR_SPEED);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            playerCar.moveRight(CAR_SPEED);
        }
        if (enemyCars[0].sprite.getPosition().y > WINDOW_HEIGHT) {
            double randX;
            double randY = enemyCars[1].sprite.getPosition().y - 400 * 4 / SPAWN_RATE;
            if (rand() % 2 == 0) {
                randX = WINDOW_WIDTH - 380;
            }
            else {
                randX = WINDOW_WIDTH - 190;
            }
            enemyCars[0].setRandomTexture();
            enemyCars[0].sprite.setPosition(randX, randY);
        }
        if (enemyCars[1].sprite.getPosition().y > WINDOW_HEIGHT) {
            double randX;
            double randY = enemyCars[0].sprite.getPosition().y - 400 * 4 / SPAWN_RATE;
            if (rand() % 2 == 0) {
                randX = WINDOW_WIDTH - 380;
            }
            else {
                randX = WINDOW_WIDTH - 190;
            }
            enemyCars[1].setRandomTexture();
            enemyCars[1].sprite.setPosition(randX, randY);
        }
        enemyCars[0].move(0.0, CAR_SPEED);
        enemyCars[1].move(0.0, CAR_SPEED);
        if (playerCar.sprite.getGlobalBounds().intersects(enemyCars[0].sprite.getGlobalBounds())) {
            if (intersections < 60 / CAR_SPEED) intersections += 3;
            else {
                if (points > best) {
                    best = points;
                }
                totalScore += points;
                saveScore();
                this_thread::sleep_for(chrono::milliseconds(500));
                displayMenu(window, font);
                return;
            }
        }
        else intersections--;
        if (playerCar.sprite.getGlobalBounds().intersects(enemyCars[1].sprite.getGlobalBounds())) {
            if (intersections < 60 / CAR_SPEED) intersections += 3;
            else {
                if (points > best) {
                    best = points;
                }
                totalScore += points;
                saveScore();
                this_thread::sleep_for(chrono::milliseconds(500));
                displayMenu(window, font);
                return;
            }
        }
        else intersections--;
        intersections = intersections < 0 ? intersections = 0 : intersections;
        double currentTime = clock.getElapsedTime().asSeconds();
        points = (currentTime - startTime) * pow(SPAWN_RATE, SPAWN_RATE) * (CAR_SPEED / 5.0) * 32;

        window.clear();
        window.draw(roadSprite);
        for (const auto& enemyCar : enemyCars) {
            window.draw(enemyCar.sprite);
        }
        window.draw(playerCar.sprite);

        Text score("Score: " + to_string(static_cast<int>(points)), font, 20);
        score.setPosition(10, 10);
        window.draw(score);

        window.display();
    }
}
int dev(int n) {
    if (n == 0)
        return 1;
    return n * dev(n - 1);
}
int main() {
    double sum = 1;
    for (int i = 1; i <= 20; i++) {
        sum += 1.0 / dev(i);
    }
    devkey = sum * pow(10, 5);
    keys = 0;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Retro Lanes 2D");
    window.setFramerateLimit(60);

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return 1;
    }

    Texture roadTexture;
    if (!roadTexture.loadFromFile("road.png")) {
        return 1;
    }

    ifstream file(dataFile);
    if (file.is_open()) {
        string encryptedScore;
        string encryptedBest;
        string encryptedCash;
        string encryptedChips;
        string encryptedTime;
        string encryptedmode;
        getline(file, encryptedScore);
        getline(file, encryptedScore);
        getline(file, encryptedBest);
        getline(file, encryptedCash);
        getline(file, encryptedChips);
        getline(file, encryptedTime);
        getline(file, encryptedmode);
        totalScore = stod(encryptDecrypt(encryptedScore));
        best = stod(encryptDecrypt(encryptedBest));
        cash = stod(encryptDecrypt(encryptedCash));
        chips = stod(encryptDecrypt(encryptedChips));
        times = stod(encryptDecrypt(encryptedTime));
        devmode = stod(encryptDecrypt(encryptedmode));
        string temp;
        for (int i = 0; i < 4; i++) {
            getline(file, temp);
            int x = stod(encryptDecrypt(temp));
            ownedCars[i] = x < 0 || x > 6 ? ownedCars[i] : x;
        }
        file.close();
    }

    displayMenu(window, font);

    if (!carTexture.loadFromFile(selectedCar)) {

        return 1;
    }
    carTexture.setSmooth(1);
    while (window.isOpen()) {
        gameLoop(window, roadTexture, font);
    }

    return 0;
}
