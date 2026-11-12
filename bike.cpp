#include "bike.h"

Bike::Bike() {
    cout << "[Bike] конструктор без параметров" << endl;
    name = new string("NoName");
    speeds = new int(1);
    wheel = new double(26.0);
    brake = new bool(false);
}

Bike::Bike(string n, int s, double w, bool b) {
    cout << "[Bike] конструктор с параметрами" << endl;
    if (n == "") throw BikeError("Имя велосипеда не может быть пустым");
    if (s < 1) throw SpeedError("Количество скоростей должно быть >= 1");
    if (w <= 0) throw BikeError("Диаметр колеса должен быть > 0");

    name = new string(n);
    speeds = new int(s);
    wheel = new double(w);
    brake = new bool(b);
}

Bike::~Bike() {
    cout << "[Bike] деструктор" << endl;
    delete name;
    delete speeds;
    delete wheel;
    delete brake;
}

string Bike::getName() { return *name; }
int Bike::getSpeeds() { return *speeds; }
double Bike::getWheel() { return *wheel; }
bool Bike::getBrake() { return *brake; }

void Bike::setName(string n) {
    if (n == "") throw BikeError("Имя не может быть пустым");
    *name = n;
}

void Bike::setSpeeds(int s) {
    if (s < 1) throw SpeedError("Скоростей должно быть >= 1");
    *speeds = s;
}

void Bike::setWheel(double w) {
    if (w <= 0) throw BikeError("Диаметр колеса должен быть > 0");
    *wheel = w;
}

void Bike::setBrake(bool b) { *brake = b; }

MountainBike::MountainBike() : Bike() {
    cout << "[MountainBike] конструктор" << endl;
    suspension = new bool(false);
}

MountainBike::MountainBike(string n, int s, double w, bool b, bool susp)
    : Bike(n, s, w, b) {
    cout << "[MountainBike] конструктор с параметрами" << endl;
    suspension = new bool(susp);
}

MountainBike::~MountainBike() {
    cout << "[MountainBike] деструктор" << endl;
    delete suspension;
}

bool MountainBike::getSuspension() { return *suspension; }
void MountainBike::setSuspension(bool s) { *suspension = s; }

void MountainBike::ride() {
    cout << "Горный велосипед " << *name
        << ", амортизация: " << (*suspension ? "есть" : "нет") << endl;
}

CityBike::CityBike() : Bike() {
    cout << "[CityBike] конструктор" << endl;
    basket = new bool(false);
}

CityBike::CityBike(string n, int s, double w, bool b, bool bas)
    : Bike(n, s, w, b) {
    cout << "[CityBike] конструктор с параметрами" << endl;
    basket = new bool(bas);
}

CityBike::~CityBike() {
    cout << "[CityBike] деструктор" << endl;
    delete basket;
}

bool CityBike::getBasket() { return *basket; }
void CityBike::setBasket(bool b) { *basket = b; }

void CityBike::ride() {
    cout << "Городской велосипед " << *name
        << ", корзина: " << (*basket ? "есть" : "нет") << endl;
}

BikeShop::BikeShop() {
    cout << "[BikeShop] конструктор без параметров" << endl;
    shopName = new string("Без названия");
    try {
        mainBike = new MountainBike();
    }
    catch (...) {
        delete shopName;
        throw;
    }
}

BikeShop::BikeShop(string shop, int type) {
    cout << "[BikeShop] конструктор с параметрами" << endl;
    if (shop == "") throw BikeError("Название магазина не может быть пустым");

    shopName = new string(shop);
    try {
        if (type == 2) {
            mainBike = new MountainBike("Trek", 21, 29.0, false, true);
        }
        else if (type == 3) {
            mainBike = new CityBike("Aist", 7, 28.0, false, true);
        }
        else {
            throw ChoiceError("Неверный тип велосипеда: должен быть 2 или 3");
        }
    }
    catch (...) {
        delete shopName;
        throw;
    }
}

BikeShop::~BikeShop() {
    cout << "[BikeShop] деструктор" << endl;
    delete mainBike;
    delete shopName;
}

string BikeShop::getShopName() { return *shopName; }

void BikeShop::showMainBike() {
    cout << "Главный велосипед магазина: ";
    mainBike->ride();
}

void BikeShop::printMainBikeInfo() {
    cout << "Информация о главном велосипеде:" << endl;
    cout << "  Имя: " << mainBike->getName() << endl;
    cout << "  Скоростей: " << mainBike->getSpeeds() << endl;
    cout << "  Диаметр колеса: " << mainBike->getWheel() << endl;
    cout << "  Тормоз: " << (mainBike->getBrake() ? "есть" : "нет") << endl;
}

void BikeShop::changeBikeName(string n) { mainBike->setName(n); }
void BikeShop::changeBikeSpeeds(int s) { mainBike->setSpeeds(s); }
void BikeShop::changeBikeWheel(double w) { mainBike->setWheel(w); }
void BikeShop::changeBikeBrake(bool b) { mainBike->setBrake(b); }

bool BikeShop::changeSuspension(bool s) {
    MountainBike* mb = dynamic_cast<MountainBike*>(mainBike);
    if (mb == nullptr) {
        cout << "Не MountainBike — амортизацию не изменить." << endl;
        return false;
    }
    mb->setSuspension(s);
    return true;
}

bool BikeShop::changeBasket(bool b) {
    CityBike* cb = dynamic_cast<CityBike*>(mainBike);
    if (cb == nullptr) {
        cout << "Не CityBike — корзину не изменить." << endl;
        return false;
    }
    cb->setBasket(b);
    return true;
}

BikeShop* BikeShop::create(string shop, int type) {
    return new BikeShop(shop, type);
}
