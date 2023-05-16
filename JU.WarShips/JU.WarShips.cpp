#include <iostream>             
#include <stdlib.h>         // расшифровка значений массивов: 1(2,3,4)(#) - палубный корабль; 7 - временная метка вокруг "раненых" палуб; -1(X) - убит; 
#include <time.h>           //                                8(~) - "мимо" или метка вокруг убитых; 9(@) - ранен (так же нужна, чтобы помечать 7). 
#include "windows.h"       

using namespace std;
int metka_dir = 0;

void print_map_user(int array[][12], int size, int gamer);
void print_map_pc(int array[][12], int size, int gamer);
void construct_ships(int array[][12], int size);
void hand_construct_ships(int array[][12], int size, int gamer);
int& shot_user(int array[][12], int size, int& lot, int array2[][12], int gamer, int& stop_game);
int& shot_pc(int array[][12], int size, int& lot, int flag_smart, int array2[][12], int gamer);

int main()
{
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    const int n = 12;
    int map_User[n][n] = { 0 };     // Массив поля игрока
    int map_Pc[n][n] = { 0 };       // Массив поля компьютера
    int lot_user_ship = 10, lot_pc_ship = 10, placement, gamer, flag_smart, flag_smart2, stop_game = 0;
    bool check;

    system("cls");
    cout << "\t\tДОБРО ПОЖАЛОВАТЬ В ИГРУ 'МОРСКОЙ БОЙ'\n";
    do {
        check = true;
    cout << "\nВыберите режим игры: 1 - человек-компьютер; 2 - компьютер-компьютер. ";
    cin >> gamer;
    if (gamer != 1 && gamer != 2) {
        check = false;
        cout << "\nНекорректный ввод. Попробуйте еще раз\n";
        // Очистка буфера в случае ввода знаков
        cin.clear();
        while (cin.get() != '\n')
        {
            continue;
        }
    }
    } while (!check);
    // Очистка буфера в случае ввода дробного числа
    while (cin.get() != '\n')
    {
        continue;
    }

    // РЕЖИМ ИГРЫ ЧЕЛОВЕК - КОМПЬЮТЕР
    if (gamer == 1) {
        do {
            check = true;
        cout << "\nВыберите уровень сложности: 1 - Случайный выстрел; 2 - Интеллектуальная игра. ";
        cin >> flag_smart;

        if (flag_smart != 1 && flag_smart != 2) {
            check = false;
            cout << "\nНекорректный ввод. Попробуйте еще раз\n";
            // Очистка буфера в случае ввода знаков
            cin.clear();
            while (cin.get() != '\n')
            {
                continue;
            }
        }
        } while (!check);
        // Очистка буфера в случае ввода дробного числа
        while (cin.get() != '\n')
        {
            continue;
        }

        do {
            cout << "\nРасставить корабли: 1 - самостоятельно; 2 - автоматически. ";
            check = true;
            cin >> placement;
            if (placement < 1 || placement > 2) {
                check = false;
                // Очистка буфера в случае ввода знаков
                cin.clear();
                while (cin.get() != '\n')
                {
                    continue;
                }
            }
        } while (!check);
        // Очистка буфера в случае ввода дробного числа
        while (cin.get() != '\n')
        {
            continue;
        }

        if (placement == 1) hand_construct_ships(map_User, n, gamer);
        else if (placement == 2) construct_ships(map_User, n);
        construct_ships(map_Pc, n);
        system("cls");
        print_map_user(map_User, n, gamer);
        print_map_pc(map_Pc, n, gamer);
        
        while (lot_user_ship > 0 && lot_pc_ship > 0 && stop_game == 0) {
            lot_pc_ship = shot_user(map_Pc, n, lot_pc_ship, map_User, gamer, stop_game);
            if (lot_pc_ship > 0 && stop_game == 0)
                lot_user_ship = shot_pc(map_User, n, lot_user_ship, flag_smart, map_Pc, gamer);
        }
    }

    // РЕЖИМ ИГРЫ КОМПЬЮТЕР - КОМПЬЮТЕР
    if (gamer == 2) {
        do {
            check = true;
            cout << "\nВыберите уровень сложности первого компьютера: 1 - Случайный выстрел; 2 - Интеллектуальная игра. ";
            cin >> flag_smart;
            if (flag_smart != 1 && flag_smart != 2) {
                check = false;
                cout << "Некорректный ввод. Попробуйте еще раз\n";
                // Очистка буфера в случае ввода знаков
                cin.clear();
                while (cin.get() != '\n')
                {
                    continue;
                }
            }
        } while (!check);
        // Очистка буфера в случае ввода дробного числа
        while (cin.get() != '\n')
        {
            continue;
        }

        do {
            check = true;
            cout << "\nВыберите уровень сложности второго компьютера: 1 - Случайный выстрел; 2 - Интеллектуальная игра. ";
            cin >> flag_smart2;
            if (flag_smart2 != 1 && flag_smart2 != 2) {
                check = false;
                cout << "Некорректный ввод. Попробуйте еще раз\n";
                // Очистка буфера в случае ввода знаков
                cin.clear();
                while (cin.get() != '\n')
                {
                    continue;
                }
            }
        } while (!check);
        // Очистка буфера в случае ввода дробного числа
        while (cin.get() != '\n')
        {
            continue;
        }

        system("cls");
        construct_ships(map_User, n);
        construct_ships(map_Pc, n);
        print_map_user(map_User, n, gamer);
        print_map_pc(map_Pc, n, gamer);

        while (lot_user_ship > 0 && lot_pc_ship > 0) {
            lot_pc_ship = shot_pc(map_Pc, n, lot_pc_ship, flag_smart2, map_User, gamer);
            system("cls");
            print_map_user(map_User, n, gamer);
            print_map_pc(map_Pc, n, gamer);
            
            if (lot_pc_ship > 0)
                lot_user_ship = shot_pc(map_User, n, lot_user_ship, flag_smart, map_Pc, gamer);
            system("cls");
            print_map_user(map_User, n, gamer);
            print_map_pc(map_Pc, n, gamer);
        }
    }

    // ВЫВОД РЕЗУЛЬТАТОВ ИГРЫ
    if (stop_game == 99) cout << "\nДо свидания.\n\n"; // игрок остановил игру
    else {
        if (gamer == 1 && lot_pc_ship == 0) cout << "\nВЫ ВЫИГРАЛИ! ПОЗДРАВЛЯЮ!\n\n";
        else if (gamer == 1 && lot_user_ship == 0) cout << "\nВы проиграли.\n\n";
        else if (gamer == 2 && lot_pc_ship == 0) cout << "\nВыиграл компьютер №2\n\n";
        else if (gamer == 2 && lot_user_ship == 0) cout << "\nВыиграл компьютер №1\n\n";
        
        int restart;
        do {
            cout << "Сыграть еще раз? 1 - Да; 2 - Нет. ";
            check = true;
            cin >> restart;
            if (restart != 1 && restart != 2) {
                check = false;
                // Очистка буфера в случае ввода знаков
                cin.clear();
                while (cin.get() != '\n')
                {
                    continue;
                }
                system("cls");
            }
        } while (!check);
        // Очистка буфера в случае ввода дробного числа
        while (cin.get() != '\n')
        {
            continue;
        }

        if (restart == 1) return main();
        else cout << "\nДо свидания.\n\n";
    }
}

void print_map_user(int array[][12], int size, int gamer) {
    if (gamer == 1) cout << "\nВаши корабли\n";
    else if (gamer == 2) cout << "\nКомпьютер №2\n";
    cout << "\t" << "1 2 3 4 5 6 7 8 9 10" << endl;
    for (int i = 1; i < size - 1; i++) {
        cout << i << "\t";
        for (int j = 1; j < size - 1; j++) {
            if (array[i][j] == 0 || array[i][j] == 7)
                cout << "_|";
            else if (array[i][j] > 0 && array[i][j] < 5)
                cout << "#|";
            if (array[i][j] == -1)
                cout << "X|";
            if (array[i][j] == 8)
                cout << "~|";
            if (array[i][j] == 9)
                cout << "@|";
        }
        cout << endl;
    }
}

void print_map_pc(int array[][12], int size, int gamer) {
    if (gamer == 1) {
        cout << "\nКорабли компьютера\n";
        cout << "\t" << "1 2 3 4 5 6 7 8 9 10" << endl;
        for (int i = 1; i < size - 1; i++) {
            cout << i << "\t";
            for (int j = 1; j < size - 1; j++) {
                if (array[i][j] == 0 || array[i][j] == 7)
                    cout << "_|";
                else if (array[i][j] > 0 && array[i][j] < 5)
                    cout << "_|";

                if (array[i][j] == -1)
                    cout << "X|";
                if (array[i][j] == 8)
                    cout << "~|";
                if (array[i][j] == 9)
                    cout << "@|";
            }
            cout << endl;
        }
    }
    else if (gamer == 2) {
        cout << "\nКомпьютер №1\n";
        cout << "\t" << "1 2 3 4 5 6 7 8 9 10" << endl;
        for (int i = 1; i < size - 1; i++) {
            cout << i << "\t";
            for (int j = 1; j < size - 1; j++) {
                if (array[i][j] == 0 || array[i][j] == 7)
                    cout << "_|";
                else if (array[i][j] > 0 && array[i][j] < 5)
                    cout << "#|";
                if (array[i][j] == -1)
                    cout << "X|";
                if (array[i][j] == 8)
                    cout << "~|";
                if (array[i][j] == 9)
                    cout << "@|";
            }
            cout << endl;
        }
    }
    }

// ФУНКЦИЯ АВТОМАТИЧЕСКОГО РАЗМЕЩЕНИЯ КОРАБЛЕЙ
void construct_ships(int array[][12], int size)
{
    int x, y, direct, lot_ships; // координата начальной точки, направление построения и количество кораблей
    int temp_x, temp_y;
    bool orient, orient2 = true;
    for (int z = 4; z > 0; z--)         // цикл перебирающий размерности кораблей
    {
        lot_ships = (z == 1) ? 4 :
            (z == 2) ? 3 :
            (z == 3) ? 2 : 1;
        int lot = 0; // количество установленных кораблей данного типа
        while (lot < lot_ships)     // цикл определяющий количество кораблей 
        {
            x = rand() % 10 + 1;
            y = rand() % 10 + 1;
            temp_x = x, temp_y = y;
            if (z > 1) {
                do { // защита от выхода корабля за пределы поля
                    orient = true;
                    direct = rand() % 4;
                    if ((x > 11 - z ) && direct == 0) orient = false;
                    else if ((y > 11 - z ) && direct == 1) orient = false;
                    else if ((x < z) && direct == 2) orient = false;
                    else if ((y < z) && direct == 3) orient = false;
                } while (!orient);
            }
            for (int i = 1; i <= z; i++)         // цикл для проверки соприкосновения клеток корабля с другими кораблями
            {
                orient2 = true;
                if (array[x][y] != 0 || array[x + 1][y] != 0 || array[x - 1][y] != 0 ||
                    array[x][y + 1] != 0 || array[x][y - 1] != 0 || array[x + 1][y + 1] != 0 ||
                    array[x - 1][y - 1] != 0 || array[x + 1][y - 1] != 0 || array[x - 1][y + 1] != 0)
                {
                    orient2 = false;
                    break;
                }
                    // пристройка следующей палубы корабля
                    switch (direct) {
                    case 0:
                        x++;
                        break;
                    case 1:
                        y++;
                        break;
                    case 2:
                        x--;
                        break;
                    case 3:
                        y--;
                        break;
                    }
            }
            // если проверка прошла, строим корабль
            if (orient2) {
                x = temp_x, y = temp_y;
                array[x][y] = z;
                for (int i = 1; i < z; i++)         // цикл для построения корабля
                {
                    switch (direct) {
                    case 0:
                        x++;
                        array[x][y] = z;
                        break;
                    case 1:
                        y++;
                        array[x][y] = z;
                        break;
                    case 2:
                        x--;
                        array[x][y] = z;
                        break;
                    case 3:
                        y--;
                        array[x][y] = z;
                        break;
                    }
                }
                lot++;
            }
        }
    }
    for (int i = 0; i < size; i++) {        // цикл, присваивающий всем элементам массива в буферной зоне значение 8("промах")
        for (int j = 0; j < size; j++) {
            if (i == 0 || j == 0 || i == 11 || j == 11) array[i][j] = 8;
        }
    }
}

// ФУНКЦИЯ РУЧНОГО РАЗМЕЩЕНИЯ КОРАБЛЕЙ
void hand_construct_ships(int array[][12], int size, int gamer)
{
    int x, y, direct, lot_ships; // координата начальной точки, направление построения и количество кораблей
    int temp_x, temp_y;
    bool orient, orient2 = true, orient3;
    for (int z = 4; z > 0; z--)         // цикл перебирающий размерности кораблей
    {
        lot_ships = (z == 1) ? 4 :
            (z == 2) ? 3 :
            (z == 3) ? 2 : 1;
        int lot = 0; // количество установленных кораблей данного типа
        while (lot < lot_ships)     // цикл определяющий количество кораблей 
        {
            //print_map_user(array, size);
            cout << "Строительство " << z << "-палубных кораблей: построено " << lot << " из " << lot_ships << endl;

            do {        // защита от некорректного ввода координат нач.точ. корабля пользователем
                orient3 = true;
                cout << "Введите координату начальной точки корабля по вертикали: ";
                cin >> x;
                if (x < 1 || x > 10 || x == 0)
                {
                    cout << "Некорректный ввод. Попробуйте еще раз\n";
                    orient3 = false;
                    // Очистка буфера в случае ввода знаков
                    cin.clear();
                    while (cin.get() != '\n')
                    {
                        continue;
                    }
                }
            } while (!orient3);
            // Очистка буфера в случае ввода дробного числа
            while (cin.get() != '\n')
            {
                continue;
            }

            do {
                orient3 = true;
                cout << "Введите координату начальной точки корабля по горизонтали: ";
                cin >> y;
                if (y < 1 || y > 10 || y == 0)
                {
                    cout << "Некорректный ввод. Попробуйте еще раз\n";
                    orient3 = false;
                    // Очистка буфера в случае ввода знаков
                    cin.clear();
                    while (cin.get() != '\n')
                    {
                        continue;
                    }
                }
            } while (!orient3);
            // Очистка буфера в случае ввода дробного числа
            while (cin.get() != '\n')
            {
                continue;
            }

            temp_x = x, temp_y = y;
            if (z > 1) {
                do { // защита от выхода корабля за пределы поля и некорректного ввода направления пользователем 
                    orient = true;
                    cout << "Выберите направление постройки корабля (корабли не должны соприкасаться!): \n1 - вниз; 2 - вправо; 3 - вверх; 4 - влево. ";
                    cin >> direct;
                    if (direct > 0 && direct <= 4)
                    {
                        if ((x > 11 - z) && direct == 1) orient = false;
                        else if ((y > 11 - z) && direct == 2) orient = false;
                        else if ((x < z) && direct == 3) orient = false;
                        else if ((y < z) && direct == 4) orient = false;
                        if (!orient) cout << "Корабль не должен выходить за пределы поля\n";
                    }
                    else
                    {
                        cout << "Некорректный ввод. Попробуйте еще раз\n";
                        orient = false;
                        // Очистка буфера в случае ввода знаков
                        cin.clear();
                        while (cin.get() != '\n')
                        {
                            continue;
                        }
                    }
                } while (!orient);
                // Очистка буфера 
                while (cin.get() != '\n')
                {
                    continue;
                }

            }
            for (int i = 1; i <= z; i++)         // цикл для проверки соприкосновения клеток корабля с другими кораблями
            {
                orient2 = true;
                if (array[x][y] != 0 || array[x + 1][y] != 0 || array[x - 1][y] != 0 ||
                    array[x][y + 1] != 0 || array[x][y - 1] != 0 || array[x + 1][y + 1] != 0 ||
                    array[x - 1][y - 1] != 0 || array[x + 1][y - 1] != 0 || array[x - 1][y + 1] != 0)
                {
                        system("cls");
                        cout << "Ваш корабль соприкасается с уже построенным. Попробуйте построить по-другому\n";
                        orient2 = false;
                        break;
                }
                    // пристройка следущей палубы корабля
                    switch (direct) {
                    case 1:
                        x++;
                        break;
                    case 2:
                        y++;
                        break;
                    case 3:
                        x--;
                        break;
                    case 4:
                        y--;
                        break;
                    }
            }
            // если проверка прошла, строим корабль
            if (orient2) {
                x = temp_x, y = temp_y;
                array[x][y] = z;
                for (int i = 1; i < z; i++)         // цикл для построения корабля
                {
                    switch (direct) {
                    case 1:
                        x++;
                        array[x][y] = z;
                        break;
                    case 2:
                        y++;
                        array[x][y] = z;
                        break;
                    case 3:
                        x--;
                        array[x][y] = z;
                        break;
                    case 4:
                        y--;
                        array[x][y] = z;
                        break;
                    }
                }
                lot++;
                system("cls");
            }
            print_map_user(array, size, gamer);
        }
    }
    for (int i = 0; i < size; i++) {        // цикл, присваивающий всем элементам массива в буферной зоне значение 8("промах")
        for (int j = 0; j < size; j++) {
            if (i == 0 || j == 0 || i == 11 || j == 11) array[i][j] = 8;
        }
    }
}

// ФУНКЦИЯ ВЫСТРЕЛОВ ИГРОКОМ
int& shot_user(int array[][12], int size, int& lot, int array2[][12], int gamer, int& stop_game) {
    int vertic, horiz, hit = 0;
    bool check, check2;
    do {
        check2 = true;
        cout << "\nСделайте ваш выстрел\n";
        do {            // проверка, если игрок уже стрелял в эту клетку
            check = true;
            cout << "Введите число для наведения выстрела по вертикали (введите 99 для остановки игры): ";
            cin >> vertic;
            if (vertic < 1 || vertic > 10) {
                check = false;
                // Очистка буфера в случае ввода знаков
                cin.clear();
                while (cin.get() != '\n')
                {
                    continue;
                }
            }
            if (vertic == 99) {
                check = true;
                stop_game = vertic;
                goto exit_game;
            }
        } while (!check);
        // Очистка буфера в случае ввода дробного числа
        while (cin.get() != '\n')
        {
            continue;
        }

        do {
            check = true;
            cout << "Введите число для наведения выстрела по горизонтали: ";
            cin >> horiz;
            if (horiz < 1 || horiz > 10) {
                check = false;
                // Очистка буфера в случае ввода знаков
                cin.clear();
                while (cin.get() != '\n')
                {
                    continue;
                }
            }
        } while (!check);
        // Очистка буфера в случае ввода дробного числа
        while (cin.get() != '\n')
        {
            continue;
        }

        if (array[vertic][horiz] == 8 || array[vertic][horiz] == 9 || array[vertic][horiz] == -1) {
            cout << "\nВы сюда уже стреляли! Попробуйте еще раз...\n";
            check2 = false;
        }
    } while (!check2);

    system("cls");
    if (array[vertic][horiz] == 0 || array[vertic][horiz] == 7) {
        cout << "\n\tПРОМАХ\n";
        array[vertic][horiz] = 8;
    }
    else if (array[vertic][horiz] == 1) {
        cout << "\n\tУБИЛ\n";
        array[vertic][horiz] = -1;
        // если корабль уничтожен, все клетки вокруг него выделяются (для однопалубных)
        if (array[vertic + 1][horiz] == 0) array[vertic + 1][horiz] = 8;
        if (array[vertic - 1][horiz] == 0) array[vertic - 1][horiz] = 8;
        if (array[vertic][horiz + 1] == 0) array[vertic][horiz + 1] = 8;
        if (array[vertic][horiz - 1] == 0) array[vertic][horiz - 1] = 8;
        if (array[vertic + 1][horiz + 1] == 0) array[vertic + 1][horiz + 1] = 8;
        if (array[vertic - 1][horiz - 1] == 0) array[vertic - 1][horiz - 1] = 8;
        if (array[vertic + 1][horiz - 1] == 0) array[vertic + 1][horiz - 1] = 8;
        if (array[vertic - 1][horiz + 1] == 0) array[vertic - 1][horiz + 1] = 8;
        // если уничтоженный корабль был многопалубным, то 'раненые' палубы становятся 'убитыми'
        if (array[vertic + 1][horiz] == 9)
        {
            array[vertic + 1][horiz] = -1;
            if (array[vertic + 2][horiz] == 9) {
                array[vertic + 2][horiz] = -1;
                if (array[vertic + 3][horiz] == 9) array[vertic + 3][horiz] = -1;
            }
        }
        if (array[vertic - 1][horiz] == 9) {
            array[vertic - 1][horiz] = -1;
            if (array[vertic - 2][horiz] == 9) {
                array[vertic - 2][horiz] = -1;
                if (array[vertic - 3][horiz] == 9) array[vertic - 3][horiz] = -1;
            }
        }
        if (array[vertic][horiz + 1] == 9)
        {
            array[vertic][horiz + 1] = -1;
            if (array[vertic][horiz + 2] == 9) {
                array[vertic][horiz + 2] = -1;
                if (array[vertic][horiz + 3] == 9) array[vertic][horiz + 3] = -1;
            }
        }
        if (array[vertic][horiz - 1] == 9)
        {
            array[vertic][horiz - 1] = -1;
            if (array[vertic][horiz - 2] == 9) {
                array[vertic][horiz - 2] = -1;
                if (array[vertic][horiz - 3] == 9) array[vertic][horiz - 3] = -1;
            }
        }
        // если корабль уничтожен, то клетки вокруг него выделяются
        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                if (array[i][j] == 7)
                {
                    if (array[i + 1][j] == -1 || array[i - 1][j] == -1 || array[i][j + 1] == -1 || array[i][j - 1] == -1 ||
                        array[i + 1][j + 1] == -1 || array[i - 1][j - 1] == -1 || array[i + 1][j - 1] == -1 || array[i - 1][j + 1] == -1)
                        array[i][j] = 8;
                }
            }
        }
        lot--;
        hit = 1;
    }
    else if (array[vertic][horiz] == 2 || array[vertic][horiz] == 3 || array[vertic][horiz] == 4) {
        cout << "\n\tРАНИЛ\n";
        array[vertic][horiz] = 9;
        // уменьшение значений всех палуб раненого корабля
        for (int i = 1; i < 4; i++) {
            if (array[vertic + i][horiz] == 2 || array[vertic + i][horiz] == 3 || array[vertic + i][horiz] == 4) array[vertic + i][horiz]--;
            else if (array[vertic + i][horiz] == 0 || array[vertic + i][horiz] == 7 || array[vertic + i][horiz] == 8) break;
        }
        for (int i = 1; i < 4; i++) {
            if (array[vertic - i][horiz] == 2 || array[vertic - i][horiz] == 3 || array[vertic - i][horiz] == 4) array[vertic - i][horiz]--;
            else if (array[vertic - i][horiz] == 0 || array[vertic - i][horiz] == 7 || array[vertic - i][horiz] == 8) break;
        }
        for (int i = 1; i < 4; i++) {
            if (array[vertic][horiz + i] == 2 || array[vertic][horiz + i] == 3 || array[vertic][horiz + i] == 4) array[vertic][horiz + i]--;
            else if (array[vertic][horiz + i] == 0 || array[vertic][horiz + i] == 7 || array[vertic][horiz + i] == 8) break;
        }
        for (int i = 1; i < 4; i++) {
            if (array[vertic][horiz - i] == 2 || array[vertic][horiz - i] == 3 || array[vertic][horiz - i] == 4) array[vertic][horiz - i]--;
            else if (array[vertic][horiz - i] == 0 || array[vertic][horiz - i] == 7 || array[vertic][horiz - i] == 8) break;
        }
        // все клетки вокруг "раненых" палуб корабля помечаются (будут выделены после гибели корабля)
        if (array[vertic][horiz] = 9) {
            if (array[vertic + 1][horiz] == 0) array[vertic + 1][horiz] = 7;
            if (array[vertic - 1][horiz] == 0) array[vertic - 1][horiz] = 7;
            if (array[vertic][horiz + 1] == 0) array[vertic][horiz + 1] = 7;
            if (array[vertic][horiz - 1] == 0) array[vertic][horiz - 1] = 7;
            if (array[vertic + 1][horiz + 1] == 0) array[vertic + 1][horiz + 1] = 7;
            if (array[vertic - 1][horiz - 1] == 0) array[vertic - 1][horiz - 1] = 7;
            if (array[vertic + 1][horiz - 1] == 0) array[vertic + 1][horiz - 1] = 7;
            if (array[vertic - 1][horiz + 1] == 0) array[vertic - 1][horiz + 1] = 7;
        }
        hit = 1;
    }    
    print_map_user(array2, size, gamer);
    print_map_pc(array, size, gamer);
    if (hit == 1 && lot > 0) return shot_user(array, size, lot, array2, gamer, stop_game);
    else return lot;
exit_game: return stop_game;
}

// ФУНКЦИЯ ВЫСТРЕЛОВ КОМПЬЮТЕРОМ
int& shot_pc(int array[][12], int size, int& lot, int flag_smart, int array2[][12], int gamer) {
    int vertic, horiz, hit = 0, direct_shot, temp_v, temp_h, metka_v = 0, metka_h = 0;
    bool orient, metka = false;
    if (flag_smart == 1) {      // случайный выбор координат выстрела при обычном режиме игры компьютера
        do {
            orient = true;
            vertic = rand() % 10 + 1;
            horiz = rand() % 10 + 1;
            if (array[vertic][horiz] == 9 || array[vertic][horiz] == -1 || array[vertic][horiz] == 8) orient = false;
        } while (!orient);
    }
    else if (flag_smart == 2) {                      // выбор координат выстрела при умном режиме игры компьютера. пк ищет "раненые" клетки
        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                if (array[i][j] == 9) {
                    metka = true;
                    vertic = i;
                    horiz = j;
                    temp_v = vertic;
                    temp_h = horiz;
                    do {
                        if (array[vertic][horiz] == 8) { // если при смещении от "раненой" клетки мы натыкаемся на клетку, куда уже стреляли, то возвращаем первоначальные координаты
                            vertic = temp_v, horiz = temp_h, metka_v = 0, metka_h = 0;
                        }
                        if (::metka_dir == 1) {         // если корабль повторно был ранен по горизонтали, то поиск будет производится только по горизонтали
                            for (int i = 1; i < 4; i++) {
                                if (array[vertic + i][horiz] == 2 || array[vertic + i][horiz] == 3 || array[vertic + i][horiz] == 1) {
                                    vertic += i;
                                    break;
                                }
                                else if (array[vertic + i][horiz] == 0 || array[vertic + i][horiz] == 7 || array[vertic + i][horiz] == 8) break;
                            }
                            for (int i = 1; i < 4; i++) {
                                if (array[vertic - i][horiz] == 2 || array[vertic - i][horiz] == 3 || array[vertic - i][horiz] == 1) {
                                    vertic -= i;
                                    break;
                                }
                                else if (array[vertic - i][horiz] == 0 || array[vertic - i][horiz] == 7 || array[vertic - i][horiz] == 8) break;
                            }
                        }
                        else if (::metka_dir == 2) {    // если корабль повторно был ранен по вертикали, то поиск будет производится только по вертикали
                            for (int i = 1; i < 4; i++) {
                                if (array[vertic][horiz + i] == 2 || array[vertic][horiz + i] == 3 || array[vertic][horiz + i] == 1) {
                                    horiz += i;
                                    break;
                                }
                                else if (array[vertic][horiz + i] == 0 || array[vertic][horiz + i] == 7 || array[vertic][horiz + i] == 8) break;
                            }
                            for (int i = 1; i < 4; i++) {
                                if (array[vertic][horiz - i] == 2 || array[vertic][horiz - i] == 3 || array[vertic][horiz - i] == 1) {
                                    horiz -= i;
                                    break;
                                }
                                else if (array[vertic][horiz - i] == 0 || array[vertic][horiz - i] == 7 || array[vertic][horiz - i] == 8) break;
                            }
                        }
                        else if (::metka_dir == 0) {    // если повторного ранения корабля не было
                            direct_shot = rand() % 4;
                            switch (direct_shot) {
                            case 0:
                                vertic++;
                                metka_v = 1;
                                break;
                            case 1:
                                vertic--;
                                metka_v = 1;
                                break;
                            case 2:
                                horiz++;
                                metka_h = 1;
                                break;
                            case 3:
                                horiz--;
                                metka_h = 1;
                                break;
                            }
                        }
                        // проверка, чтобы компьютер не стрелял повторно по клеткам
                    } while (array[vertic][horiz] == 9 || array[vertic][horiz] == 8);
                    goto exit;
                }
            }
        }
    exit:
        if (metka == false) {      // если "раненных" клеток нет, просто генерируем значение
            do {
                orient = true;
                vertic = rand() % 10 + 1;
                horiz = rand() % 10 + 1;
                if (array[vertic][horiz] == 9 || array[vertic][horiz] == -1 || array[vertic][horiz] == 8) orient = false;
            } while (!orient);
        }
    }
    // проверка по массиву куда попал выстрел
    Sleep(1500);  
    if (gamer == 1) system("cls");
    if (array[vertic][horiz] == 0 || array[vertic][horiz] == 7) {
        cout << "\n\tПРОМАХ\n";
        array[vertic][horiz] = 8;
    }
    else if (array[vertic][horiz] == 1) {
        cout << "\n\tУБИЛ\n";
        array[vertic][horiz] = -1;
        ::metka_dir = 0;        // после потопления обнуляем направление расположения корабля
        // если корабль уничтожен, все клетки вокруг него выделяются (для однопалубных)
        if (array[vertic + 1][horiz] == 0) array[vertic + 1][horiz] = 8;
        if (array[vertic - 1][horiz] == 0) array[vertic - 1][horiz] = 8;
        if (array[vertic][horiz + 1] == 0) array[vertic][horiz + 1] = 8;
        if (array[vertic][horiz - 1] == 0) array[vertic][horiz - 1] = 8;
        if (array[vertic + 1][horiz + 1] == 0) array[vertic + 1][horiz + 1] = 8;
        if (array[vertic - 1][horiz - 1] == 0) array[vertic - 1][horiz - 1] = 8;
        if (array[vertic + 1][horiz - 1] == 0) array[vertic + 1][horiz - 1] = 8;
        if (array[vertic - 1][horiz + 1] == 0) array[vertic - 1][horiz + 1] = 8;
        // если уничтоженный корабль был многопалубным, то 'раненые' палубы становятся 'убитыми'
        if (array[vertic + 1][horiz] == 9)
        {
            array[vertic + 1][horiz] = -1;
            if (array[vertic + 2][horiz] == 9) {
                array[vertic + 2][horiz] = -1;
                if (array[vertic + 3][horiz] == 9) array[vertic + 3][horiz] = -1;
            }
        }
        if (array[vertic - 1][horiz] == 9) {
            array[vertic - 1][horiz] = -1;
            if (array[vertic - 2][horiz] == 9) {
                array[vertic - 2][horiz] = -1;
                if (array[vertic - 3][horiz] == 9) array[vertic - 3][horiz] = -1;
            }
        }
        if (array[vertic][horiz + 1] == 9)
        {
            array[vertic][horiz + 1] = -1;
            if (array[vertic][horiz + 2] == 9) {
                array[vertic][horiz + 2] = -1;
                if (array[vertic][horiz + 3] == 9) array[vertic][horiz + 3] = -1;
            }
        }
        if (array[vertic][horiz - 1] == 9)
        {
            array[vertic][horiz - 1] = -1;
            if (array[vertic][horiz - 2] == 9) {
                array[vertic][horiz - 2] = -1;
                if (array[vertic][horiz - 3] == 9) array[vertic][horiz - 3] = -1;
            }
        }
        // если корабль уничтожен, то клетки вокруг него выделяются
        for (int i = 1; i < size - 1; i++) {
            for (int j = 1; j < size - 1; j++) {
                if (array[i][j] == 7)
                {
                    if (array[i + 1][j] == -1 || array[i - 1][j] == -1 || array[i][j + 1] == -1 || array[i][j - 1] == -1 ||
                        array[i + 1][j + 1] == -1 || array[i - 1][j - 1] == -1 || array[i + 1][j - 1] == -1 || array[i - 1][j + 1] == -1)
                        array[i][j] = 8;
                }
            }
        }
        lot--;
        hit = 1;
    }
    else if (array[vertic][horiz] == 2 || array[vertic][horiz] == 3 || array[vertic][horiz] == 4) {
        cout << "\n\tРАНИЛ\n";
        if (metka_v == 1)  ::metka_dir = 1;         // найдено направление расположения корабля
        else if (metka_h == 1) ::metka_dir = 2;
        array[vertic][horiz] = 9;
        // уменьшение значений всех палуб раненого корабля
        for (int i = 1; i < 4; i++) {
            if (array[vertic + i][horiz] == 2 || array[vertic + i][horiz] == 3 || array[vertic + i][horiz] == 4) array[vertic + i][horiz]--;
            else if (array[vertic + i][horiz] == 0 || array[vertic + i][horiz] == 7 || array[vertic + i][horiz] == 8) break;
        }
        for (int i = 1; i < 4; i++) {
            if (array[vertic - i][horiz] == 2 || array[vertic - i][horiz] == 3 || array[vertic - i][horiz] == 4) array[vertic - i][horiz]--;
            else if (array[vertic - i][horiz] == 0 || array[vertic - i][horiz] == 7 || array[vertic - i][horiz] == 8) break;
        }
        for (int i = 1; i < 4; i++) {
            if (array[vertic][horiz + i] == 2 || array[vertic][horiz + i] == 3 || array[vertic][horiz + i] == 4) array[vertic][horiz + i]--;
            else if (array[vertic][horiz + i] == 0 || array[vertic][horiz + i] == 7 || array[vertic][horiz + i] == 8) break;
        }
        for (int i = 1; i < 4; i++) {
            if (array[vertic][horiz - i] == 2 || array[vertic][horiz - i] == 3 || array[vertic][horiz - i] == 4) array[vertic][horiz - i]--;
            else if (array[vertic][horiz - i] == 0 || array[vertic][horiz - i] == 7 || array[vertic][horiz - i] == 8) break;
        }
        // все клетки вокруг "раненых" палуб корабля помечаются (будут выделены после гибели корабля)
        if (array[vertic][horiz] = 9) {
            if (array[vertic + 1][horiz] == 0) array[vertic + 1][horiz] = 7;
            if (array[vertic - 1][horiz] == 0) array[vertic - 1][horiz] = 7;
            if (array[vertic][horiz + 1] == 0) array[vertic][horiz + 1] = 7;
            if (array[vertic][horiz - 1] == 0) array[vertic][horiz - 1] = 7;
            if (array[vertic + 1][horiz + 1] == 0) array[vertic + 1][horiz + 1] = 7;
            if (array[vertic - 1][horiz - 1] == 0) array[vertic - 1][horiz - 1] = 7;
            if (array[vertic + 1][horiz - 1] == 0) array[vertic + 1][horiz - 1] = 7;
            if (array[vertic - 1][horiz + 1] == 0) array[vertic - 1][horiz + 1] = 7;
        }
        hit = 1;
    }
    if (gamer == 1) {
        print_map_user(array, size, gamer);
        print_map_pc(array2, size, gamer);
    }
    if (hit == 1 && lot > 0) return shot_pc(array, size, lot, flag_smart, array2, gamer);
    else return lot;
}