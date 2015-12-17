//
// Created by Nick on 9/20/2015.
//
#include <cmath>
#include "assert.h"
#include <sstream>
#include <cstdlib>
#include <forward_list>

#include "Cluster.h"
#include "Point.h"

using namespace std;
namespace Clustering {
    unsigned int Cluster:: _generateId = 0;
    Cluster::Cluster(unsigned int d) {
        dims = d;
        size = 0;
        points = new forward_list<Point>;
        id = _generateId++;
        _centroid = new Point(dims);
        _centroidValid = false;
        _centroid->rewindId();
        for (int n = 0; n < dims; n++) {
            _centroid->setValue(n, 0);
        }
    }

    Cluster::Cluster(const Cluster &c) {
        dims = c.getDims();
        size = c.getSize();
        points = new forward_list<Point>;
        id = c.getId();
        _centroid = new Point(dims);
        _centroidValid = c.getCValid();
        id = c.getId();
        for (auto it = c.getPoints().begin(); it != c.getPoints().end(); it++) {
            Point *newP = new Point(dims);
            for (int n = 0; n < c.getDims(); n++) {
                newP->setValue(n, 0);
            }
            *newP = *it;
            add(*newP);
        }
        size = c.getSize();
    }

    Cluster &Cluster::operator=(const Cluster &rhs) {
        if (*this == rhs)
            return *this;
        id = rhs.id;
        dims = rhs.getDims();
        size = rhs.getSize();
        *_centroid = rhs.getCentroid();
        _centroidValid = rhs.getCValid();
        for (auto it = rhs.getPoints().begin(); it != rhs.getPoints().end(); it++) {
            add(*it);
        }
        return *this;
    }

    void Cluster::add(const Point &p) {
        setCentroidValid(false);
        size++;
        if (points->empty()) {                           //add to empty array
            points->push_front(p);
            return;
        }
        auto iter = points->begin();
        iter++;
        if (iter == points->end()) {
            if (*(points->begin()) <= p)      //add to array with 1 element
            {
                points->insert_after(points->begin(), p);
                return;
            }
            else {
                points->push_front(p);
                return;
            }
        }
        if (p <= *(points->begin())) {
            points->push_front(p);
            return;
        }
        else {
            for (auto it = points->begin(); it != points->end(); it++) {
                auto next = points->begin();
                next = it;
                next++;
                if (next == points->end()) {
                    points->insert_after(it,p);
                    return;
                }
                if (p >= *it && p <= *next) {
                    points->insert_after(it,p);
                    return;
                }
            }
        }
        size++;
    }

    const Point&Cluster::remove(const Point &p) {
        bool contains = false;
        if (points == nullptr) {
           throw RemoveFromEmptyEx(id);
        }
        if(this->contains(p))
        {
            points->remove(p);
            setCentroidValid(false);
            size--;
        }
        return p;
//        if (size == 1 && *(points->begin()) == p) {
//            points->pop_front();
//            return p;
//        }
//        for(auto it = points->begin(); it != points->end(); it++) {
//            auto next = it;
//            next++;
//            if (*(next) == p) {
//                points = points->next;
////                delete curr->p;
//                delete curr;
//                size--;
//                setCentroidValid(false);
//                return p;
//            }
//            if (nex == nullptr && *(curr->p) == p) {
////                delete curr->p;
//                delete curr;
//                size--;
//                setCentroidValid(false);
//                return p;
//            }
//            if (nex == nullptr && *(curr->p) != p) {
//
//                setCentroidValid(false);
//                return p;
//            }
//            if (*(nex->p) == p) {
//                curr->next = curr->next->next;
//                delete nex;
//                size--;
//                setCentroidValid(false);
//                return p;
//
//            }
//
//        }

//            return p;
    }

    Cluster &Cluster::operator+=(const Point &rhs) {
        try {

            Point *p = new Point(rhs.getDims());
            *p = rhs;
            add(*p);
            setCentroidValid(false);
        }
        catch(DimensionalityMismatchEx e) {
            cout << "Exception thrown in Cluster:: +=  operator: " << e << endl;
        }

            return *this;


    }
    Cluster &Cluster::operator-=(const Point &rhs) {
        try{
            Point *p = new Point(rhs.getDims());
            *p = rhs;
            remove(*p);
            setCentroidValid(false);
        }
        catch(DimensionalityMismatchEx e) {
            cout << "Exception thrown in Cluster:: +=  operator: " << e << endl;
        }
        return *this;
    }

    void Cluster::deleteAll() {
        points->clear();
//        if (points != nullptr) {
//            LNodePtr curr = points;
//            if (curr->next == nullptr) {
//                delete curr->p;
//                delete curr;
//            }
//            while (curr != nullptr) {
//                if (curr->next != nullptr) {
//                    LNodePtr delPtr = curr;
//                    curr = curr->next;
//                    delete delPtr->p;
//                    delete delPtr;
//                }
//                curr = curr->next;
//            }
//        }
        delete _centroid;
        size = 0;
    }
    //use do while to avoid first

    Cluster::~Cluster() {
        deleteAll();
    }

    Cluster &Cluster::operator+=(const Cluster &rhs) {       //Adds the pointers of points not in 1 cluster to another]
        for (auto rhsit = rhs.getPoints().begin(); rhsit != rhs.getPoints().end(); rhsit++) {
            bool found = false;
            for (auto it = points->begin(); it != points->end(); it++) {
                if (*rhsit == *it) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                Point *p = new Point(dims);
                *p = *(rhsit);
                add(*p);
            }
        }
        setCentroidValid(false);
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &rhs) {
        for (auto it = points->begin(); it != points->end(); it++) {
            bool found = false;
            for (auto rhsit = rhs.getPoints().begin(); rhsit != rhs.getPoints().end(); rhsit++) {
                if (*it == *rhsit) {
                    found = true;
                    break;
                }
            }
            if (found) {
                remove(*it);
            }
        }
        setCentroidValid(false);
        return *this;
    }

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {
        Cluster newCluster = Cluster(lhs.getDims());
        newCluster += lhs;
        newCluster += rhs;
        return newCluster;
    }

    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {
        Cluster newCluster = Cluster(lhs.getDims());
        newCluster = lhs;
        newCluster -= rhs;
        return newCluster;
    }

    std::ostream &operator<<(std::ostream &os, const Cluster &c) {
        for (auto it = c.getPoints().begin(); it != c.getPoints().end(); it++) {
            os << *it << " ";
        }
        os << " ID: " << c.getId();
        return os;
    }

    std::istream &operator>>(std::istream &is, Cluster &c) {
        istream &i = is;
        string line;
        while (getline(is, line)) {

            Point *p = new Clustering::Point(c.getDims());
            std::istringstream lineStream(line);
            lineStream >> *p;
            c.add(*p);
        }

        c.setCentroidValid(false);

//        catch(DimensionalityMismatchEx e)
//        {
//            if(e.getCurrDims() == 0)
//            {
//                cerr << "Warning, possible loss of data due to insufficent dimensionality of point" << endl;
//
//            }
//
//        }
        return i;
    }

    bool operator==(const Cluster &lhs, const Cluster &rhs) {
        if (lhs.getSize() != rhs.getSize())
            return false;
        auto rhsit = rhs.getPoints().begin();
        for (auto it = lhs.getPoints().begin(); it != lhs.getPoints().end(); it++) {
            if (*it != *rhsit) {
                return false;
            }
            rhsit++;
        }
        return true;
    }

    const Cluster operator+(const Cluster &lhs, const Point &rhs) {
        Cluster newCluster = lhs;
        newCluster.add(rhs);
        newCluster.setCentroidValid(false);
        return newCluster;
    }

    const Cluster operator-(const Cluster &lhs, const Point &rhs) {
        Cluster newCluster = lhs;
        newCluster.remove(rhs);
        newCluster.setCentroidValid(false);
        return newCluster;
    }

    const Point Cluster::getCentroid() const {
        Point p(dims);
        p = *_centroid;
        return p;
    }

    void Cluster::setCentroid(const Clustering::Point &p) {
        try
        {
            *_centroid = p;
            setCentroidValid(true);
        }
        catch(DimensionalityMismatchEx & e)
        {
            cerr << "Exception thrown when setting centroid:" << e << endl;
        }
    }

    void Cluster::computeCentroid() {
        if(points == nullptr)
        {
            throw RemoveFromEmptyEx(id);
        }
        Point *newpoint = new Point(dims);
        auto it = points->begin();
        Point divisionPoint(dims);

        for (int n = 0; n < dims; n++) {
            divisionPoint.setValue(n, size);
        }
        while (it != points->end()) {
            Point additionPoint(dims);
            additionPoint = (*it);
            additionPoint /= dims;
            *newpoint += additionPoint;
            it++;
        }
        setCentroid(*newpoint);
        setCentroidValid(true);
    }

    void Cluster::pickPoints(int k, std::vector<Point*> &ptarray) {
        int size = getSize();

        if(k > size)
        {
            if(points == nullptr)
            {
                return;
            }
            auto next = points->begin();
            next++;
            auto curr = points->begin();
            for(int n = 0; n < k; n++)
            {
                if(next == points->end())
                {
                    Point *p = new Point(dims);
                    *p = *curr;
                    ptarray.push_back(p);
                }
                else
                {

                    Point *p = new Point(dims);
                    *p = *curr;
                    ptarray.push_back(p);
                    next++;
                    curr++;
                }

            }
        }
        else {
            auto curr = points->begin();
            int frontCount = k / 2;

            int backCount = size - (k/2);
            if(k%2 != 0)
            {
                backCount--;
            }
            int count = 0;
            for (int n = 0; n < frontCount; n++) {
                Point *p = new Point(dims);
                *p = *curr;
                ptarray.push_back(p);
                curr++;
                count++;
            }
            curr = points->begin();
            for (int n = 0; n < backCount; n++)
            {
                curr++;
            }
            while(curr != points->end())
            {
                Point *p = new Point(dims);
                *p = *curr;
                ptarray.push_back(p);
                curr++;
                count++;
            }
        }
    }
    double Cluster::intraClusterDistance() {
        auto curr = points->begin();
        auto curr2 = points->begin();
        double value = 0;
        while(curr != points->end())
        {
            while(curr2 != points->end())
            {
                value += curr->distanceTo(*curr2);
                curr2++;
            }
            curr++;
        }
        value /= 2;
        return value;
    }

    int Cluster::getClusterEdges() {
        int value = 0;
        value = (size)*(size-1)/2;
        return value;
    }
    double interClusterDistance(const Cluster &lhs, const Cluster &rhs) {
        double value = 0;
        auto curr = lhs.getPoints().begin();
        auto curr2 = rhs.getPoints().begin();
        while(curr != lhs.getPoints().end())
        {
            while(curr2 != rhs.getPoints().end())
            {
                value += curr->distanceTo(*curr2);
                curr2++;
            }
            curr++;
        }
        return value;
    }
    double interClusterEdges(const Cluster &lhs, const Cluster &rhs)
    {
        double value;
        value = lhs.getSize()*rhs.getSize();
        return value;
    }
    Point &Cluster::operator[](int index){
        if(index > size || index < 0){
            throw OutOfBoundsEx(size, index);
        }
        auto curr = points->begin();
        for(int n = 0; n < index; n++){
            curr++;
        }
        return *curr;
    }
    void Cluster::generatePoints(int num)
        {
            for(int n = 0; n < num; n++)
            {
                Point *p = new Point(dims);
                for(int i = 0; i < dims; i++)
                {
                    p->setValue(i,rand()%100);
                }
                this->add(*p);
            }
        }

    bool Cluster::contains(const Point &point) {
        auto curr = points->begin();
        while(curr != points->end())
        {
            if(*curr == point)
            {
                return true;
            }
            curr++;
        }
        return false;
    }
}



