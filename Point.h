#ifndef CLUSTERING_POINT_H
#define CLUSTERING_POINT_H
#include <vector>
#include <iostream>
#include <bits/stl_vector.h>

#include "Exceptions.h"
namespace Clustering {
    class Point {
        unsigned int _id;
        int dim;        // number of dimensions of the point
        std::vector<double> *values; // values of the point's dimensions
        static unsigned int _generateId;
    public:
        Point(int);

        // Big three: cpy ctor, overloaded operator=, dtor
        Point(const Point &);
        Point &operator=(const Point &);
        ~Point();

        // Accessors & mutators
        int getDims() const { return dim; }
        void setValue(int, double);
        double getValue(int) const;
        unsigned int getId() const {return _id;}
        static void rewindId(){_generateId--;}
        // Functions
        double distanceTo(const Point &) const;

        // Overloaded operators

        // Members
        Point &operator*=(double);
        Point &operator/=(double);
        const Point operator*(double) const; // prevent (p1*2) = p2;
        const Point operator/(double) const;

        double &operator[](int index);

        // Friends
        friend Point &operator+=(Point &, const Point &);
        friend Point &operator-=(Point &, const Point &);
        friend const Point operator+(const Point &, const Point &);
        friend const Point operator-(const Point &, const Point &);



        friend bool operator==(const Point &,const Point &);
        friend bool operator!=(const Point &, const Point &);

        friend bool operator<(const Point &, const Point &);
        friend bool operator>(const Point &, const Point &);
        friend bool operator<=(const Point &, const Point &);
        friend bool operator>=(const Point &, const Point &);

        friend std::ostream &operator<<(std::ostream &, const Point &);
        friend std::istream &operator>>(std::istream &, Point &);
    };

}
#endif //CLUSTERING_POINT_H
