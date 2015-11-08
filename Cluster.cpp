//
// Created by Nick on 9/20/2015.
//
#include "Cluster.h"
#include "Point.h"
#include <cmath>
#include "assert.h"
#include <sstream>


using namespace std;
namespace Clustering {
    Cluster::Cluster(int d) {
        dims = d;
        size = 0;
        points = nullptr;
        id = generateId() + 1;
        _centroid = new Point(dims);
        _centroidValid = false;
        for (int n = 0; n < dims; n++) {
            _centroid->setValue(n + 1, MAX_VALUE);
        }
    }

    Cluster::Cluster(const Cluster &c) {
        size = c.getSize();
        points = nullptr;
        _centroid = new Point(dims);
        _centroidValid = c.getCValid();
        id = generateId() + 1;
        for (LNodePtr curr = c.getPoints(); curr != nullptr; curr = curr->next) {
            Point *newP = new Point(curr->p->getDims());
            for (int n = 0; n < curr->p->getDims(); n++) {
                newP->setValue(n + 1, 0);
            }
            for (int n = 0; n < newP->getDims(); n++) {
                newP->setValue(n + 1, curr->p->getValue(n + 1));
            }
            add(newP);
        }
        size = c.getSize();
    }

    Cluster &Cluster::operator=(const Cluster &rhs) {
        if (*this == rhs)
            return *this;
        id = rhs.getId();
        *_centroid = rhs.getCentroid();
        _centroidValid = rhs.getCValid();
        for (LNodePtr curr = rhs.getPoints(); curr != nullptr; curr = curr->next) {
            add(curr->p);
        }
        return *this;
    }

    void Cluster::add(const PointPtr &ptr) {
        LNode *newP = new LNode;
        newP->p = ptr;
        setCentroidValid(false);
        size++;
        if (points == nullptr) {                           //add to empty array
            newP->next = nullptr;
            points = newP;
            return;
        }
        if (points->next == nullptr) {
            if (*points->p <= *ptr)      //add to array with 1 element
            {
                points->next = newP;
                newP->next = nullptr;
                return;
            }
            else {
                newP->next = points;
                points = newP;
                return;
            }
        }
        if (*ptr <= *points->p) {
            newP->next = points;
            points = newP;
            return;
        }
        else {
            for (LNodePtr curr = points; curr != nullptr; curr = curr->next) {
                LNodePtr next = curr->next;
                if (next == nullptr) {
                    curr->next = newP;
                    newP->next = nullptr;
                    return;
                }
                if (*ptr >= *(curr->p) && *ptr <= *(next->p)) {
                    curr->next = newP;
                    newP->next = next;
                    return;
                }
            }
        }
        size++;
        setCentroidValid(false);
    }

    const PointPtr &Cluster::remove(const PointPtr &p) {
        LNodePtr nex = points->next;
        if (points == nullptr) {
            setCentroidValid(false);
            return p;
        }
        if (points->next == nullptr && *points->p == *p) {
            points = nullptr;
            size--;
            setCentroidValid(false);
            return p;
        }

        LNodePtr curr = points;
        while (curr != nullptr) {
            if (*(curr->p) == *p) {
                points = points->next;
//                delete curr->p;
                delete curr;
                size--;
                setCentroidValid(false);
                return p;
            }
            if (nex == nullptr && *(curr->p) == *p) {
//                delete curr->p;
                delete curr;
                size--;
                setCentroidValid(false);
                return p;
            }
            if (nex == nullptr && *(curr->p) != *p) {

                setCentroidValid(false);
                return p;
            }
            if (*(nex->p) == *p) {
                curr->next = curr->next->next;
                delete nex;
                size--;
                setCentroidValid(false);
                return p;

            }
            nex = nex->next;
            curr = curr->next;
        }
            return p;
    }

    Cluster &Cluster::operator+=(const Point &rhs) {
        Point *p = new Point(rhs.getDims());
        *p = rhs;
        add(p);
        setCentroidValid(false);
        return *this;
    }

    Cluster &Cluster::operator-=(const Point &rhs) {
        Point *p = new Point(rhs.getDims());
        *p = rhs;
        remove(p);
        setCentroidValid(false);
        return *this;
    }

    void Cluster::deleteAll() {
        if (points != nullptr) {
            LNodePtr curr = points;
            if (curr->next == nullptr) {
                delete curr->p;
                delete curr;
            }
            while (curr != nullptr) {
                if (curr->next != nullptr) {
                    LNodePtr delPtr = curr;
                    curr = curr->next;
                    delete delPtr->p;
                    delete delPtr;
                }
                curr = curr->next;
            }
        }
        delete _centroid;
        points = nullptr;
        size = 0;
    }
    //use do while to avoid first

    Cluster::~Cluster() {
        deleteAll();
    }

    Cluster &Cluster::operator+=(const Cluster &rhs) {       //Adds the pointers of points not in 1 cluster to another]
        for (LNodePtr curr = rhs.getPoints(); curr != nullptr; curr = curr->next) {
            bool found = false;
            for (LNodePtr currThis = points; currThis != nullptr; currThis = currThis->next) {
                if (curr->p == currThis->p) {
                    found = true;
                    break;
                }

            }
            if (!found) {
                Point *p = new Point(curr->p->getDims());
                *p = *(curr->p);
                add(p);
            }
        }
        setCentroidValid(false);
        return *this;
    }

    Cluster &Cluster::operator-=(const Cluster &rhs) {
        for (LNodePtr curr = points; curr != nullptr; curr = curr->next) {
            bool found = false;
            for (LNodePtr currRhs = rhs.getPoints(); currRhs != nullptr; currRhs = currRhs->next) {
                if (*(curr->p) == *(currRhs->p)) {
                    found = true;
                    curr = curr->next;
                    break;
                }
            }
            if (found) {
                LNodePtr delPtr = curr;
                remove(delPtr->p);
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
        for (LNodePtr curr = c.getPoints(); curr != nullptr; curr = curr->next) {
            os << *(curr->p) << " ";
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
                c.add(p);
        }
        c.setCentroidValid(false);
        return i;
    }

    bool operator==(const Cluster &lhs, const Cluster &rhs) {
        if (lhs.getSize() != rhs.getSize())
            return false;
        LNodePtr currRhs = rhs.getPoints();
        for (LNodePtr currLhs = lhs.getPoints(); currLhs != nullptr; currLhs = currLhs->next) {
            if (*(currLhs->p) != *(currRhs->p)) {
                return false;
            }
            currRhs = currRhs->next;
        }
        return true;
    }

    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs) {
        Cluster newCluster = lhs;
        newCluster.add(rhs);
        newCluster.setCentroidValid(false);
        return newCluster;
    }

    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs) {
        Cluster newCluster = lhs;
        newCluster.remove(rhs);
        newCluster.setCentroidValid(false);
        return newCluster;
    }

    int Cluster::generateId() {
        static int id = 0;
        return id++;
    }

    const Point Cluster::getCentroid() const {
        Point p(dims);
        p = *_centroid;
        return p;
    }

    void Cluster::setCentroid(const Clustering::Point &p) {
        assert(p.getDims() == _centroid->getDims());
        for(int n = 0; n < dims; n++)
        {
            _centroid->setValue(n+1, p.getValue(n+1));
        }
        *_centroid = p;
        setCentroidValid(true);
    }

    void Cluster::computeCentroid() {
        Point *newpoint = new Point(dims);
        LNodePtr curr = points;
        Point divisionPoint(dims);
        for (int n = 0; n < dims; n++) {
            divisionPoint.setValue(n + 1, size);
        }
        while (curr != nullptr) {
            Point additionPoint(dims);
            additionPoint = (*curr->p);
            additionPoint /= dims;
            *newpoint += additionPoint;
            curr = curr->next;
        }
        setCentroid(*newpoint);
        setCentroidValid(true);
    }

    void Cluster::pickPoints(int k, PointPtr *ptarray) {
        int size = getSize();
        if(k > size)
        {
            Point *p = new Point(dims);
            LNodePtr curr = points;
            for(int n = 0; n < k; n ++)
            {
                if(curr->next == nullptr)
                {
                    *p = *curr->p;
                    ptarray[n] = p;
                }
                else
                {
                    *p = *curr->p;
                    ptarray[n] = p;
                    curr = curr->next;
                }
            }
        }
        else {
            LNodePtr curr = points;
            int frontCount = k / 2;

            int backCount = size - (k/2);
            if(k%2 != 0)
            {
                backCount--;
            }
            int count = 0;
            for (int n = 0; n < frontCount; n++) {
                Point *p = new Point(dims);
                *p = *curr->p;
                ptarray[count] = p;
                curr = curr->next;
                count++;
            }
            curr = points;
            for (int n = 0; n < backCount; n++)
            {
                curr = curr->next;
            }
            while(curr != nullptr)
            {
                Point *p = new Point(dims);
                *p = *curr->p;
                ptarray[count] = p;
                curr = curr ->next;
                count++;
            }
        }
    }
    double Cluster::intraClusterDistance() {
        LNodePtr curr = points;
        LNodePtr curr2 = points;
        double value = 0;
        while(curr != nullptr)
        {
            while(curr2 != nullptr)
            {
                value += curr->p->distanceTo(*curr2->p);
                curr2 = curr2->next;
            }
            curr = curr->next;
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
        LNodePtr curr = lhs.getPoints();
        LNodePtr curr2 = rhs.getPoints();
        while(curr != nullptr)
        {
            while(curr2 != nullptr)
            {
                value += curr->p->distanceTo(*curr2->p);
                curr2 = curr2->next;
            }
            curr= curr->next;
        }
        return value;
    }
    double interClusterEdges(const Cluster &lhs, const Cluster &rhs)
    {
        double value;
        value = lhs.getSize()*rhs.getSize();
        return value;
    }

}



