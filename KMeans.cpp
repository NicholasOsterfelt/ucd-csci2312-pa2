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
        double newscore, scoreDiff;
        k = ki;
        clusters = new Clustering::ClusterPtr[k];
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
        PointPtr *pickedPoints = new PointPtr[k];
        clusters[0] = pointSpace;
        pointSpace->pickPoints(k, pickedPoints);
        for(int n = 0; n < k; n++)
        {
                clusters[n]->setCentroid(*pickedPoints[n]);
        }
        scoreDiff = SCORE_DIFF_THRESHHOLD+1;

        while((scoreDiff < SCORE_DIFF_THRESHHOLD))
        {
            for(int n = 0; n < k; n++)
            {
                LNodePtr curr = clusters[n]->getPoints();
                while(curr != nullptr)
                {
                    moveToClosestCluster(curr->p, *clusters[n]);
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
    void KMeans::moveToClosestCluster(const PointPtr p, Cluster & c) {
        int smallestIndex;
        double temp = p->distanceTo(c.getCentroid());
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
            return;
        }
        else
        {
            Cluster:: Move m(p,&c,clusters[smallestIndex]);
        }

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
        cout << "These are the KMeans Clusters with " << k << "clusters:" << endl;
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
