//
// Created by Nick on 10/25/2015.
//
#ifndef PA2_KMEANS_H
#define PA2_KMEANS_H
#include <vector>

#include "Point.h"
#include "Cluster.h"

namespace Clustering{
    typedef Cluster *ClusterPtr;
    static const double SCORE_DIFF_THRESHHOLD = 1;
    class KMeans {
        unsigned int k;
        double clusterScore;
        std::vector<Clustering::Cluster> *clusters;
        Clustering::Cluster *pointSpace;

    public:
        KMeans(unsigned int,unsigned int);
        ~KMeans();
        double computeClusteringScore();
        void displayClusters();
        void displayCentroids();
        void outputToFile();
        void perform();
        bool moveToClosestCluster(const Clustering::Point p, Cluster &);
    };
}
#endif //PA2_KMEANS_H
