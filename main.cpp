#include "mainwindow.h"
#include "core.h"
#include <iostream>
#include <vector>

#include <QApplication>
#include <QDialog>

class Animal {
public:
    virtual void makeSound() = 0;
};

class Cat : public Animal {
    virtual void makeSound() override {
        qDebug() << "Meow";
    }


};

class Leg {
public:
    std::string color;
    float length;

    Leg(std::string _color,
        float _length) : color(_color), length(_length) {}
    Leg() : color(""), length(0) {}
};

class Dog : public Animal {
public:
    int numLegs = 4;
    Leg *leg;
    virtual void makeSound() override {
        qDebug() << "Woof";
    }

    Dog& operator =(const Dog &dog) {
        if (this == &dog) return *this;
        numLegs = dog.numLegs;
        *leg = *dog.leg;
        return *this;
    }

    ~Dog() {
        delete leg;
    }
};

class Point {
public:
    int x;
    int y;

    Point(int _x, int _y) : x(_x), y(_y) {}

    Point& operator +(const Point &point) {
        qDebug() << "operator +";
        x += point.x;
        y += point.y;
        return *this;
    }
    Point& operator -(const Point &point) {
        x -= point.x;
        y -= point.y;
        return *this;
    }

    Point& operator =(const Point &point) {
        if (this == &point) return *this;
        qDebug() << "operator =";
        x = point.x;
        y = point.y;
        return *this;
    }

    void print() {
        qDebug() << "X:" << x << " Y:" << y;
    }
};

int main(int argc, char *argv[])
{
    Point p1(5, 6);
    Point p2(3, 5);
    p1.print();
    p2.print();

    p1 = p2 + p2;

    p1.print();

    //return 0;


    Dog dog;
    dog.numLegs = 3;
    dog.leg = new Leg("Black", 0.5);

    Dog dog2;
    dog2.numLegs = 4;
    dog2.leg = new Leg("White", 0.4);

    dog2 = dog;
    qDebug() << dog.numLegs << dog2.numLegs;
    std::cout << dog.leg->color << dog2.leg->color << std::endl;

    //return 0;
    //i = i2;

    // std::vector<Token> vec = tokenize("4.5/(6+4*(1-6))");

    // Parser* parser = new Parser(vec);
    // double res = parser->parse();
    // qDebug() << res;
    // delete parser;
    // return 0;
    /*std::vector <Animal*> animals;

    animals.push_back(new Cat);
    animals.push_back(new Dog);

     Dog *dog = dynamic_cast<Dog*>(animals[1]);
     if (dog != nullptr) qDebug() << dog->numLegs;
     return 0;
     for (unsigned long i = 0; i < animals.size(); i++) {

         animals[i]->makeSound();
     }*/

     //return 0;


    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}
