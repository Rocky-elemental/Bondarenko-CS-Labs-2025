#include "planet.h"

#include <cstring>

const int kBufferSize = 128;

namespace planet {
planet::planet() = default;

planet::planet(char* n, unsigned int diameter, bool life, unsigned int satellite)
    : diameter(diameter), life(life), satellite(satellite) {
    setName(n);
}

planet::planet(const planet& o) : diameter(o.diameter), life(o.life), satellite(o.satellite) {
    setName(o.name);
}

planet::~planet() {
    delete[] name;
}

char* planet::getName() const {
    return name;
}

unsigned int planet::getDiameter() const {
    return diameter;
}

bool planet::getContainsLife() const {
    return life;
}

unsigned int planet::getSatellite() const {
    return satellite;
}

void planet::setName(char* n) {
    delete[] name;
    name = new char[std::strlen(n) + 1];
    std::memcpy(name, n, std::strlen(n));
    name[std::strlen(n)] = '\0';
}

void planet::setDiameter(unsigned int i) {
    diameter = i;
}

void planet::setLife(bool b) {
    life = b;
}

void planet::setSatellite(unsigned int i) {
    satellite = i;
}

// void planet::print() {
//     std::cout << std::left << "Name: " << name;
//     std::cout << ", Diameter: "  << diameter;
//     std::cout << ", Contains Life: " <<  life;
//     std::cout << ", Satellite Count: " << satellite << '\n';
// }

planet& planet::operator=(const planet& p) {
    if (this == &p) {
        return *this;
    }

    this->setName(p.name);
    this->life = p.life;
    this->diameter = p.diameter;
    this->satellite = p.satellite;
    return *this;
}

bool operator==(const planet& lhs, const planet& rhs) {
    return (std::strcmp(lhs.name, rhs.name) == 0);
}

bool operator!=(const planet& lhs, const planet& rhs) {
    return !(lhs == rhs);
}

bool operator<(const planet& lhs, const planet& rhs) {
    if (std::strcmp(lhs.name, rhs.name) == 0) {
        if (lhs.diameter == rhs.diameter) {
            if (lhs.life == rhs.life) {
                return lhs.satellite < rhs.satellite;
            }
            return lhs.life < rhs.life;
        }
        return lhs.diameter < rhs.diameter;
    }
    return std::strcmp(lhs.name, rhs.name) < 0;
}

//template<typename stream>
std::istream& operator >>(std::istream& in, planet& p) {
    char name[kBufferSize];
    unsigned int diameter = 0;
    bool life = false;
    unsigned int satellite = 0;

    in >> name >> diameter >> life >> satellite;
    p.setName(name);
    p.setDiameter(diameter);
    p.setLife(life == 1);
    p.setSatellite(satellite);

    return in;
}

std::ofstream& operator << (std::ofstream& out, const planet& p) {
    out << p.getName() << ' ' << p.getDiameter() << ' ' << p.getContainsLife() << ' ' << p.getSatellite() << '\n';
    return out;
}
std::ostream& operator << (std::ostream& out, const planet& p) {
    out << p.getName() << ' ' << p.getDiameter() << ' ' << p.getContainsLife() << ' ' << p.getSatellite() << '\n';
    return out;
}

//template std::istream& operator >> (std::istream& in, planet& p);
//template std::ifstream& operator >> (std::ifstream& in, planet& p);
}  // namespace planet
