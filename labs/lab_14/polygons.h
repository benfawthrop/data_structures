//
// Created by Benjamin Fawthrop on 4/26/23.
//

#ifndef LAB_14_POLYGONS_H
#define LAB_14_POLYGONS_H

#include <iostream>
#include <string>
#include <vector>
#include "utilities.h"

class Polygon {
public:
    Polygon(std::string &n, std::vector<Point> &p) {
        name(n);
        points(p);
        if (points.size() < 3) {
            throw 1;
        }
    }
private:
    std::string name;
    std::vector<Point> points;
};

class Quadrilateral {
public:
    Quadrilateral(std::string &n, std::vector<Point> &p) {
        name(n);
        points(p);
        if (points.size() != 4) {
            throw 1;
        }
    }
private:
    std::string name;
    std::vector<Point> points;
};

class Triangle {
public:
    Triangle(std::string &n, std::vector<Point> &p) {
        name(n);
        points(p);
        if (points.size() != 3) {
            throw 1;
        }
    }
private:
    std::string name;
    std::vector<Point> points;
};

class IsoscelesTriangle {
public:
    IsoscelesTriangle(std::string &n, std::vector<Point> &p) {
        name(n);
        points(p);
        if (points.size() != 3) {
            throw 1;
        }
        if (!EqualSides(DistanceBetween(points[0], points[1]), DistanceBetween(points[0], points[2])) ||
            !EqualSides(DistanceBetween(points[1], points[0]), DistanceBetween(points[1], points[2])) ||
            !EqualSides(DistanceBetween(points[2], points[0]), DistanceBetween(points[2], points[1])) ) {
            throw 1;
        }
    }
private:
    std::string name;
    std::vector<Point> points;
};

class EquilateralTriangle {
public:
    EquilateralTriangle(std::string &n, std::vector<Point> &p) {
        name(n);
        points(p);
        if (points.size() != 3) {
            throw 1;
        }
        if (!EqualSides(DistanceBetween(points[0], points[1]), DistanceBetween(points[0], points[2])) &&
            !EqualSides(DistanceBetween(points[1], points[0]), DistanceBetween(points[1], points[2])) &&
            !EqualSides(DistanceBetween(points[2], points[0]), DistanceBetween(points[2], points[1])) ) {
            throw 1;
        }
    }
private:
    std::string name;
    std::vector<Point> points;
};

class Rectangle {
public:
    Rectangle(std::string &n, std::vector<Point> &p) {
        name(n);
        points(p);
        if (points.size() != 4) {
            throw 1;
        }
        if (!RightAngle(Angle(points[0], points[1], points[2])) ||
            !RightAngle(Angle(points[1], points[2], points[3]))) {
            throw 1;
        }
    }
private:
    std::string name;
    std::vector<Point> points;
};

class Square {
public:
    Square(std::string &n, std::vector<Point> &p) {
        name(n);
        points(p);
        if (points.size() != 4) {
            throw 1;
        }
        if (!RightAngle(Angle(points[0], points[1], points[2])) ||
            !RightAngle(Angle(points[1], points[2], points[3]))) {
            throw 1;
        }
        double side1 = DistanceBetween(points[0], points[1]);
        for (int i = 0; i < points.size(); i++) {
            for (int j = 0; j < points.size(); j++) {
                if (DistanceBetween(points[i], points[j]) != side1) {
                    throw 1;
                }
            }
        }
    }
private:
    std::string name;
    std::vector<Point> points;
};

#endif //LAB_14_POLYGONS_H
