//
// Created by Nick on 10/25/2015.
//
#ifndef PA2_KMEANS_H
#define PA2_KMEANS_H
#include "Point.h"
#include "Cluster.h"

namespace Clustering{
    typedef Cluster *ClusterPtr;
    static const double SCORE_DIFF_THRESHHOLD = 1;
    class KMeans {
        unsigned int k;
        double clusterScore;
        Clustering::ClusterPtr *clusters;
        Clustering::Cluster *pointSpace;
        void moveToClosestCluster(const PointPtr p, Cluster &);
    public:
        KMeans(int, int);
        ~KMeans();
        double computeClusteringScore();
        void displayClusters();
        void displayCentroids();
        void outputToFile();
        void perform();
    };
}
#endif //PA2_KMEANS_H
