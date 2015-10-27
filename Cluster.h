#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include <limits>
#include "Point.h"

namespace Clustering {

    typedef Point *PointPtr;
    typedef struct LNode *LNodePtr;
    static const double MAX_VALUE = std::numeric_limits<double>::max();
//    struct LNode;
//    typedef LNode *LNodePtr;

    struct LNode {
        PointPtr p;
        LNodePtr next;
    };

    class Cluster {

        unsigned int dims;
        Point *_centroid;
        int id = 0;
        int size;
        LNodePtr points;
        bool _centroidValid;


    public:
        class Move {
            PointPtr p;
            Cluster *f, *t;
        public:
            Move(const PointPtr &ptr, Cluster *from, Cluster *to) {
                p = ptr;
                f = from;
                t = to;
                perform();
                from->setCentroidValid(false);
                to->setCentroidValid(false);
            }
            void perform() {
                t->add(f->remove(p));
            }
        };
        Cluster(int);
        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();
        //accessor
        int generateId();
        int getSize() const {return size;}
        LNodePtr getPoints() const {return points;}
        int getDims() const {return dims;}
        const Point getCentroid() const;
        bool getCValid() const {return _centroidValid;}
        int getId() const {return id;}

        // Set functions: They allow calling c1.add(c2.remove(p));
        void setCentroid(const Point &);
        void setCentroidValid(bool v){_centroidValid = v;}
        void computeCentroid();
        void pickPoints(int k, PointPtr *ptarray);
        double intraClusterDistance();
        int getClusterEdges();
        friend double interClusterDistance(const Cluster &, const Cluster &);
        friend double interClusterEdges(const Cluster &, const Cluster &);
        void add(const PointPtr &);
        const PointPtr &remove(const PointPtr &);
        void deleteAll();

        // Overloaded operators

        // IO
        friend std::ostream &operator<<(std::ostream &, const Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);

        // Set-preserving operators (do not duplicate points in the space)
        // - Friends
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        // - Members
        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference

        Cluster &operator+=(const Point &rhs); // add point
        Cluster &operator-=(const Point &rhs); // remove point

        // Set-destructive operators (duplicate points in the space)
        // - Friends
        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);


    };

}
#endif //CLUSTERING_CLUSTER_H

