//
// Created by Nick on 9/20/2015.
//
#include <cmath>
#include "assert.h"
#include <stdlib.h>

#include "Point.h"
#include "Exceptions.h"
using namespace std;

namespace Clustering {
    //Constructors
    unsigned int Point::_generateId = 0;

    Point::Point(int d) {
        _id = _generateId++;
        if (d == 0)
            dim = 2;
        else
            dim = d;
        values = new vector<double>(dim, 0);
    }


    //Big3
    Point::Point(const Point &p) {
        _id = p._id;
        dim = p.dim;
        values = new vector<double>(dim, 0);
        for (int n = 0; n < dim; n++)
            setValue(n, p.getValue(n));
    }

    Point &Point::operator=(const Point &rhs) {        //Throws exception dim mismatch
        if (dim != rhs.dim) {
            throw DimensionalityMismatchEx(dim, rhs.dim);
        }
        _id = rhs._id;
        bool equal = true;
        for (int n = 0; n < rhs.getDims(); n++)
            if (getValue(n) != rhs.getValue(n)) {
                equal = false;
                break;
            }
        if (equal)
            return *this;
        else {
            for (int n = 0; n < dim; n++)
                setValue(n, rhs.getValue(n));
        }
        return *this;
    }

    Point::~Point() {
        if (values != nullptr)
            delete values;
    }

    //Accessors/Mutators
    void Point::setValue(int d, double v) {
        (*values)[d] = v;
    }

    double Point::getValue(int d) const {
        return (*values)[d];
    }

    //Functions
    double Point::distanceTo(const Point &p) const {
        int size = p.getDims();
        int sum = 0;

        for (int n = 0; n < size; n++) {
            double diff = (*values)[n] - (*p.values)[n];
            sum += diff * diff;
        }
        return sqrt(sum);
    }

    //Operators
    const Point Point::operator/(double i) const {
        Point temp(dim);
        assert(i > 0);
        for (int n = 0; n < dim; n++)
            temp.setValue(n, ((*values)[n] / i));
        return temp;
    }

    const Point Point::operator*(double i) const {
        Point temp(dim);

        for (int n = 0; n < dim; n++)
            temp.setValue(n, ((*values)[n] * i));
        return temp;
    }

    Point &Point::operator/=(double i) {
        assert(i > 0);
        for (int n = 0; n < dim; n++)
            (*values)[n] = (*values)[n] / i;
        return *this;
    }

    Point &Point::operator*=(double i) {
        for (int n = 0; n < dim; n++)
            (*values)[n] *= i;
        return *this;
    }

    //Friend Operators
    const Point operator+(const Point &lhs, const Point &rhs)  //Throws exception dim mismatch
    {
        if (lhs.dim != rhs.dim) {
            throw DimensionalityMismatchEx(lhs.dim, rhs.dim);
        }
        Point temp(rhs.getDims());
        for (int n = 0; n < rhs.getDims(); n++)
            temp.setValue(n, (lhs.getValue(n) + rhs.getValue(n)));
        return temp;
    }

    const Point operator-(const Point &lhs, const Point &rhs)  //Throws exception dim mismatch
    {
        if (lhs.dim != rhs.dim) {
            throw DimensionalityMismatchEx(lhs.dim, rhs.dim);
        }
        Point temp(rhs.getDims());

        for (int n = 0; n < rhs.getDims(); n++)
            temp.setValue(n, (lhs.getValue(n) - rhs.getValue(n)));
        return temp;
    }

    Point &operator+=(Point &rhs, const Point &lhs)        //Throws exception dim mismatch
    {
        if (lhs.dim != rhs.dim) {
            throw DimensionalityMismatchEx(lhs.dim, rhs.dim);
        }
        rhs = rhs + lhs;
        return rhs;
    }

    Point &operator-=(Point &rhs, const Point &lhs)    //Throws exception dim mismatch
    {
        if (lhs.getDims() != rhs.getDims()) {
            throw DimensionalityMismatchEx(lhs.getDims(), rhs.getDims());
        }
        rhs = rhs - lhs;
        return rhs;
    }

    bool operator==(const Point &lhs, const Point &rhs) {
        if (lhs.getDims() != rhs.getDims() || lhs._id != rhs._id) {
            return false;
        }
        for (int n = 0; n < lhs.getDims(); n++) {
            if (lhs.getValue(n) != rhs.getValue(n)) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Point &lhs, const Point &rhs) {
        if (!(lhs == rhs))
            return true;
        return false;
    }

    bool operator<(const Point &lhs, const Point &rhs) {
        if (lhs.dim != rhs.dim) {
            throw DimensionalityMismatchEx(lhs.dim, rhs.dim);
        }
        if (lhs == rhs)
            return false;

        for (int n = 0; n < rhs.getDims();) {
            if (lhs.getValue(n) > rhs.getValue(n))
                return false;
            if (lhs.getValue(n) == rhs.getValue(n)) {
                n++;
            }
            if (lhs.getValue(n) < rhs.getValue(n))
                return true;

        }

    }

    bool operator<=(const Point &lhs, const Point &rhs) {
        if (lhs.dim != rhs.dim) {
            throw DimensionalityMismatchEx(lhs.dim, rhs.dim);
        }
        if (lhs == rhs)
            return true;

        for (int n = 0; n < rhs.getDims();) {
            if (lhs.getValue(n) > rhs.getValue(n))
                return false;
            if (lhs.getValue(n) == rhs.getValue(n))
                n++;
            if (lhs.getValue(n) < rhs.getValue(n))
                return true;
        }
    }

    bool operator>(const Point &lhs, const Point &rhs) {
        if (lhs.dim != rhs.dim) {
            throw DimensionalityMismatchEx(lhs.dim, rhs.dim);
        }
        if (!(lhs <= rhs))
            return true;
        return false;

    }

    bool operator>=(const Point &lhs, const Point &rhs) {
        if (lhs.dim != rhs.dim) {
            throw DimensionalityMismatchEx(lhs.dim, rhs.dim);
        }
        if (lhs == rhs)
            return true;
        if (!(lhs < rhs))
            return true;
        return false;

    }

    std::ostream &operator<<(std::ostream &os, const Point &p) {
        os << "(";
        for (int n = 0; n < p.getDims(); n++)
            if (n != p.getDims() - 1)
                os << p.getValue(n) << ",";
            else
                os << p.getValue(n);
        os << ")";
        return os;
    }

    std::istream &operator>>(std::istream &is, Point &p) {
        string value;
        double dval;

        for (int n = 0; n < p.getDims(); n++) {
            if (is.eof()) {
                p.setValue(n, 0);
            }
            if (getline(is, value, ',')) {
                dval = atof(value.c_str());
                p.setValue(n, dval);
            }
//                if(!is.eof()) {
//                    throw DimensionalityMismatchEx(p.getDims(), 0);
//                    }
        }
        return is;
    }

    double &Point::operator[](int index) {     //Throws out of bounds exception
        if (index < 0 || index > dim) {
            throw OutOfBoundsEx(dim, index);
        }
        return (*values)[index];
    }

}
