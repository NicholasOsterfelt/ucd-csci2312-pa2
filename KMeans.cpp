//
// Created by Nick
// on 10/25/2015.
#include "KMeans.h"
#include "fstream"
#include "cmath"


using namespace std;
namespace Clustering {
    KMeans:: KMeans(int ki, int d)
    {
        k = ki;
        double newscore, scoreDiff;
        clusters = new Clustering::ClusterPtr[k];
        PointPtr *pickedPoints = new PointPtr[k];
        for(int n =0; n < k; n++)
        {
            pickedPoints[n] = new Point(d);
        }

        for(int n = 0; n < k; n++)
        {
            Cluster *newcluster = new Cluster(d);
            clusters[n] = newcluster;
        }
        pointSpace = new Cluster(d);
        ifstream is;
        is.open("input.txt");
        istream & id = is;
        is >> *pointSpace;
        is.close();

        clusters[0] = pointSpace;
        pointSpace->pickPoints(k, pickedPoints);
        for(int n = 0; n < k; n++)
        {
                clusters[n]->setCentroid(*pickedPoints[n]);
        }
        scoreDiff = SCORE_DIFF_THRESHHOLD+1;

        while(scoreDiff > SCORE_DIFF_THRESHHOLD)
        {
            for(int n = 0; n < k; n++)
            {
                LNodePtr curr = clusters[n]->getPoints();
                while(curr != nullptr)
                {
                    if(moveToClosestCluster(curr->p, *clusters[n]))
                    {
                        curr = clusters[n]->getPoints();
                    }
                    curr= curr->next;
                }
            }
            for(int n =0; n < k; n++)
            {
                if(!clusters[n]->getCValid())
                {
                    clusters[n]->computeCentroid();
                }
            }
            newscore = computeClusteringScore();
            scoreDiff = abs(clusterScore - newscore);
            clusterScore = newscore;
        }
        perform();
        outputToFile();
    }

    double KMeans:: computeClusteringScore()
    {
        double score = 0;
        double din= 0;
        double dout = 0;
        double pin = 0;
        double pout = 0;
        for(int n = 0; n < k; n++)
        {
            din += clusters[n]->intraClusterDistance();
        }
        for(int n = 0; n < k; n++)
        {
            for(int i = 0; i < k; i++)
            {
                dout += interClusterDistance(*clusters[n], *clusters[i]);
            }
        }
        for(int n = 0; n < k; n++)
        {
            pin += clusters[n]->getClusterEdges();
        }
        for(int n = 0; n < k-1; n++)
        {
            for(int i = n+1; i < k; i++)
            {
                pout = interClusterEdges(*clusters[n],*clusters[i]);
            }
        }
        score = (din*pout)/(dout*pin);
        return score;
    }
    KMeans::~KMeans()
    {
        delete [] clusters;
    }
    void KMeans:: displayClusters() {
        cout << "These are the KMeans clusters" << endl;
        for(int n = 0; n < k; n++)
        {

            cout << *clusters[n] << endl;
        }
    }
    bool KMeans::moveToClosestCluster(const PointPtr p, Cluster & c) {
        int smallestIndex;
        double temp = p->distanceTo(c.getCentroid());
        if(temp == 0)
        {
            return false;
        }
        for(int n = 0; n < k; n++)
        {
            if(temp > p->distanceTo(clusters[n]->getCentroid()))
            {
                temp = p->distanceTo(clusters[n]->getCentroid());
                smallestIndex = n;
            }
        }
        if(temp == p->distanceTo(c.getCentroid()))
        {
            return false;
        }

            Cluster:: Move m(p,&c,clusters[smallestIndex]);
            return true;

    }
    void KMeans::displayCentroids()
    {
        cout << "These are the KMeans Centroids:" << endl;
        for(int n =0; n < k; n++)
        {
            cout << clusters[n]->getCentroid();
        }
    }
    void KMeans::outputToFile()
    {
        ofstream myfile;
        myfile.open("ouput.txt");
        for(int n = 0; n < k; n++)
        {
            myfile << *clusters[n] << std::endl;
        }
        myfile.close();
    }
    void KMeans::perform()
    {
        cout << "These are the KMeans Clusters with " << k << " clusters:" << endl;
        cout << "Clustering Score: " << clusterScore << endl;
        for(int n = 0; n < k; n++)
        {
            cout << *clusters[n] << endl;
        }
        cout << "KMeans Centroids: " << endl;
        for(int n = 0; n < k; n++)
        {
            cout << clusters[n]->getCentroid() << endl;
        }
    }
}
