#ifndef BIKE_H
#define BIKE_H

#include <iostream>
#include <string>

using namespace std;

class BikeError {
private:
    string message;
public:
    BikeError(string msg) { message = msg; }
    string what() { return message; }
};

class SpeedError : public BikeError {
public:
    SpeedError(string msg) : BikeError(msg) {}
};

class ChoiceError : public BikeError {
public:
    ChoiceError(string msg) : BikeError(msg) {}
};

class Bike {
protected:
    string* name;
    int* speeds;
    double* wheel;
    bool* brake;
public:
    Bike();
    Bike(string n, int s, double w, bool b);
    virtual ~Bike();

    string getName();
    int getSpeeds();
    double getWheel();
    bool getBrake();

    void setName(string n);
    void setSpeeds(int s);
    void setWheel(double w);
    void setBrake(bool b);

    virtual void ride() = 0;
};

class MountainBike : public Bike {
private:
    bool* suspension;
public:
    MountainBike();
    MountainBike(string n, int s, double w, bool b, bool susp);
    ~MountainBike() override;

    bool getSuspension();
    void setSuspension(bool s);

    void ride() override;
};

class CityBike : public Bike {
private:
    bool* basket;
public:
    CityBike();
    CityBike(string n, int s, double w, bool b, bool bas);
    ~CityBike() override;

    bool getBasket();
    void setBasket(bool b);

    void ride() override;
};

class BikeShop {
private:
    string* shopName;
    Bike* mainBike;
public:
    BikeShop();
    BikeShop(string shop, int type);
    ~BikeShop();

    BikeShop(const BikeShop&) = delete;
    BikeShop& operator=(const BikeShop&) = delete;

    string getShopName();
    void showMainBike();
    void printMainBikeInfo();

    void changeBikeName(string n);
    void changeBikeSpeeds(int s);
    void changeBikeWheel(double w);
    void changeBikeBrake(bool b);

    bool changeSuspension(bool s);
    bool changeBasket(bool b);

    static BikeShop* create(string shop, int type);
};

#endif
