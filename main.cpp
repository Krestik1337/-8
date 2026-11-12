#include <iostream>
#include "bike.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Горный велосипед:" << endl;
    MountainBike* m = new MountainBike("Trek", 21, 29.0, false, true);
    m->ride();
    delete m;

    cout << endl << "Городской велосипед:" << endl;
    CityBike* c = new CityBike("Aist", 7, 28.0, false, true);
    c->ride();
    delete c;

    cout << endl << "Выберите велосипед (2-MountainBike, 3-CityBike): ";
    int choice;
    cin >> choice;

    Bike* userBike = nullptr;
    try {
        if (choice == 2) {
            userBike = new MountainBike("UserMountain", 21, 29.0, false, true);
        }
        else if (choice == 3) {
            userBike = new CityBike("UserCity", 7, 28.0, false, true);
        }
        else {
            throw ChoiceError("Неверный выбор: нужно 2 или 3");
        }
        userBike->ride();
    }
    catch (ChoiceError& e) {
        cout << "Ошибка выбора: " << e.what() << endl;
        cout << "Создан MountainBike по умолчанию." << endl;
        userBike = new MountainBike();
        userBike->ride();
    }
    delete userBike;

    cout << endl << "Раннее связывание:" << endl;
    MountainBike staticMountain("StaticMountain", 18, 29.0, false, true);
    CityBike staticCity("StaticCity", 3, 28.0, true, true);
    staticMountain.ride();
    staticCity.ride();

    cout << endl << "Демонстрация класса BikeShop" << endl;

    BikeShop shop1;
    cout << "Название: " << shop1.getShopName() << endl;
    shop1.showMainBike();
    shop1.printMainBikeInfo();

    cout << endl;

    BikeShop shop2("Велоцентр", 3);
    cout << "Название: " << shop2.getShopName() << endl;
    shop2.showMainBike();
    shop2.printMainBikeInfo();

    cout << endl << "Изменение параметров (shop1)" << endl;
    try {
        shop1.changeBikeName("Новое имя");
        shop1.changeBikeSpeeds(27);
        shop1.changeBikeWheel(27.5);
        shop1.changeBikeBrake(true);
        shop1.changeSuspension(true);
        shop1.showMainBike();
        shop1.printMainBikeInfo();
    }
    catch (BikeError& e) {
        cout << "Ошибка параметров: " << e.what() << endl;
    }

    cout << endl << "Изменение параметров (shop2)" << endl;
    try {
        shop2.changeBikeName("Городской+");
        shop2.changeBikeSpeeds(5);
        shop2.changeBikeWheel(27.0);
        shop2.changeBikeBrake(true);
        shop2.changeBasket(false);
        shop2.changeSuspension(true);
        shop2.showMainBike();
        shop2.printMainBikeInfo();
    }
    catch (BikeError& e) {
        cout << "Ошибка параметров: " << e.what() << endl;
    }

    cout << endl << "Демонстрация исключений" << endl;

    cout << "1) SpeedError (наследник BikeError):" << endl;
    try {
        shop1.changeBikeSpeeds(0);
    }
    catch (SpeedError& e) {
        cout << "   Поймано SpeedError: " << e.what() << endl;
    }

    cout << "2) BikeError:" << endl;
    try {
        BikeShop badShop("", 2);
    }
    catch (BikeError& e) {
        cout << "   Поймано BikeError: " << e.what() << endl;
    }

    cout << "3) ChoiceError:" << endl;
    try {
        BikeShop badShop2("Тест", 99);
    }
    catch (ChoiceError& e) {
        cout << "   Поймано ChoiceError: " << e.what() << endl;
    }

    cout << "4) Общий перехват через BikeError:" << endl;
    try {
        shop1.changeBikeWheel(-5.0);
    }
    catch (BikeError& e) {
        cout << "   Поймано BikeError: " << e.what() << endl;
    }

    cout << endl << "Статический метод BikeShop::create" << endl;
    BikeShop* shop3 = nullptr;
    try {
        shop3 = BikeShop::create("Статик-магазин", 2);
        cout << "Название: " << shop3->getShopName() << endl;
        shop3->showMainBike();
    }
    catch (BikeError& e) {
        cout << "Ошибка при создании: " << e.what() << endl;
    }
    delete shop3;
    
    cout << endl << "Выход из main — деструкторы:" << endl;
    return 0;
}
