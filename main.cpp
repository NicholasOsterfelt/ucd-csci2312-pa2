#include <iostream>
#include <assert.h>
#include <fstream>

#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"
#include "Exceptions.h"
using namespace std;
using namespace Clustering;
        //function Prototypes
void pTestConstructor1();
void pTestConstructor2();
void pTestCopyConstructor();
void pTestAssignmentOperator();
void pTestGetDims();
void pTestSetValue();
void pTestGetValue();
void pTestDistanceTo();
void pTestMultiplyOperator1();
void pTestDivideOperator1();
void pTestMultiplyEqualOperator();
void pTestDivideEqualOperator();
void pTestAdditionOperator();
void pTestSubtractionOperator();
void pTestAdditionEqualOperator();
void pTestSubtractionEqualOperator();
void pTestCEqualOperator();
void pTestCNEqualOperator();
void pTestCLessOperator();
void pTestCGreaterOperator();
void pTestCLessEqualOperator();
void pTestCGreaterEqualOperator();
void pTestOstreamOperator();

int main() {
//    pTestConstructor1();
//    pTestCopyConstructor();
//    pTestAssignmentOperator();
//    pTestGetDims();
//    pTestSetValue();
//    pTestGetValue();
//    pTestDistanceTo();
//    pTestMultiplyOperator1();
//    pTestDivideOperator1();
//    pTestMultiplyEqualOperator();
//    pTestDivideEqualOperator();
//    pTestAdditionOperator();
//    pTestSubtractionOperator();
//    pTestAdditionEqualOperator();
//    pTestSubtractionEqualOperator();
//    pTestCEqualOperator();
//    pTestCNEqualOperator();
//    pTestCLessOperator();
//    pTestCGreaterOperator();
//    pTestCLessEqualOperator();
//    pTestCGreaterEqualOperator();
//    pTestOstreamOperator();
    Cluster c1 = Cluster(3);
//    Cluster *cone = &c1;
//    Cluster *ctwo = &c2;
//    cout << "this is c1 " << c1;
//    Point *p2 = new Point(3);
//    Point *p3 = new Point(3);
//    Point *p4 = new Point(3);
//    Point *p5 = new Point(3);
//    Point *p6 = new Point(3);
    Point p1(3);
//    p1.setValue(1,1);
////    p4->setValue(1,4);
////    p5->setValue(1,5);
//    p6->setValue(1,6);
////    c2.add(p6);
////    c2.add(p5);
////    c2.add(p4);
////    c1.add(p1);
//    c1.add(p2);
//    c1.add(p3);
//    *p2 = *p3;
//    Point p7(*p1);
//    cout << p1->getId() << endl;
//    Cluster c3(c1);
//
//    cout << p6->getId() << endl;
//    cout << "this is c1" << endl << c1 << endl;
    Point p(3);
    p.setValue(0,1);
    p.setValue(1,2);
    p.setValue(2,3);
//    c1.generatePoints(5);
//    c2.generatePoints(5);
    c1.add(p);
   Cluster c2(c1);
    cout << "this is c1" << endl << c1 << endl;

//    cout << "this is c2" << endl << c2 << endl;
//    c2.add(c1.remove(p1));
//    Cluster::Move m(p1,con

//    ifstream is;
//    is.open("input.txt");
//    istream & id = is;
//    is >> c1;
//    cout << "this is c1" << endl << c1 << endl;
    KMeans k(3,3);
    KMeans k1(5,4);
//    c1.computeCentroid();
//
//
//    PointPtr *ptArray = new PointPtr[5];
//    c1.pickPoints(5,ptArray);
//    cout << "These are the centroid picked points " << endl;
//    for(int n = 0; n < 5; n++)
//    {
//        cout << *(*(ptArray+n)) << endl;
//    }
//    cout << "this is c1 centroid: " << c1.getCentroid() << endl;
//    Cluster c3(c1);

//    c2.remove(p5);
//
//    cout << "this is c1" << endl << c1 << endl;
//    cout << "this is c1 centroid " << c1.getCentroid() << endl;
//    c1.setCentroid(*p1);
//    cout << "this is c1 centroid now " << c1.getCentroid() << endl;
////    c2.add(c1.remove(p1));
//
////    c2+=c1;
//
//    cout << c1 + c2 << endl;
//
//    cout << "this is c1" << endl << c1 << endl;
//    cout << "this is c2" << endl << c2 << endl;
//    c2-=c1;
//    cout << "this is c2" << endl << c2 << endl;
    return 0;
}
void pTestConstructor1() {
    Point p(2);
    assert(p.getDims() == 2);
    assert(p.getValue(1) == 0 && p.getValue(2) == 0);
}
void pTestCopyConstructor() {
    Point p(3);
    p.setValue(1, 1);
    p.setValue(2,2);
    p.setValue(3,3);
    Point p1(p);
    assert(p == p1);
}
void pTestAssignmentOperator(){
    Point p(3);
    p.setValue(1, 1);
    p.setValue(2,2);
    p.setValue(3,3);
    Point p1 = p;
    assert(p == p1);
}
void pTestGetDims() {
    Point p(3);
    assert(p.getDims() == 3);
}
void pTestSetValue() {
    Point p(3);
    p.setValue(1, 5);
    p.setValue(2, -5);
    assert(p.getValue(1) == 5 && p.getValue(2) == -5);
}
void pTestGetValue() {
    Point p(3);
    p.setValue(1,2);
    assert(p.getValue(1) == 2);
}
void pTestDistanceTo() {
    Point p(2);
    p.setValue(1, 27);
    p.setValue(2, 9);
    Point p1(2);
    p.setValue(1, 3);
    p.setValue(2, 2);
    assert(p.distanceTo(p1) != 25 );
}
void pTestMultiplyOperator1()
{
    Point p(2);
    p.setValue(1, 2);
    p.setValue(2, 3);
    Point p1(2);
    p1 = p*2;
    assert(p1.getValue(1) == 4 && p1.getValue(2) == 6);
}
void pTestDivideOperator1()
{
    Point p(2);
    p.setValue(1, 4);
    p.setValue(2, 6);
    Point p1(2);
    p1 = p/2;
    assert(p1.getValue(1) == 2 && p1.getValue(2) == 3);
}
void pTestMultiplyEqualOperator() {
    Point p(2);
    p.setValue(1, 2);
    p.setValue(2, 3);
    p*=2;
    assert(p.getValue(1) == 4 && p.getValue(2) == 6);
}
void pTestDivideEqualOperator() {
    Point p(2);
    p.setValue(1, 4);
    p.setValue(2, 6);
    p/=2;
    assert(p.getValue(1) == 2 && p.getValue(2) == 3);
}
void pTestAdditionOperator() {
    Point p(2);
    p.setValue(1, 2);
    p.setValue(2, 3);
    Point p1(2);
    p1.setValue(1, 2);
    p1.setValue(2, 3);
    Point p3(2);
    p3 = p+p1;
    assert(p3.getValue(1) == 4 && p3.getValue(2) == 6);
}
void pTestSubtractionOperator() {
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 9);
    Point p1(2);
    p1.setValue(1, 2);
    p1.setValue(2, 3);
    Point p3(2);
    p3 = p-p1;
    assert(p3.getValue(1) == 4 && p3.getValue(2) == 6);
}
void pTestAdditionEqualOperator() {
    Point p(2);
    p.setValue(1, 2);
    p.setValue(2, 3);
    Point p1(2);
    p1.setValue(1, 2);
    p1.setValue(2, 3);

    p += p1;
    assert(p.getValue(1) == 4 && p.getValue(2) == 6);
}
void pTestSubtractionEqualOperator() {
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 9);
    Point p1(2);
    p1.setValue(1, 2);
    p1.setValue(2, 3);
    p-=p1;
    assert(p.getValue(1) == 4 && p.getValue(2) == 6);
}
void pTestCEqualOperator()
{
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 9);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 9);
    assert(p == p1);
}
void pTestCNEqualOperator()
{
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 10);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 9);
    assert(p != p1);
}
void pTestCLessOperator(){
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 5);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 9);
    assert(p < p1);
}
void pTestCGreaterOperator(){
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 10);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 9);
    assert(p > p1);
}
void pTestCLessEqualOperator(){
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 5);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 9);
    Point p2(2);
    p2.setValue(1,6);
    p2.setValue(2,5);
    assert(p <= p1 && p <= p2);
}
void pTestCGreaterEqualOperator(){
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 5);
    Point p1(2);
    p1.setValue(1, 6);
    p1.setValue(2, 4);
    Point p2(2);
    p2.setValue(1,6);
    p2.setValue(2,5);
    assert(p >= p1 && p >= p2);
}
void pTestOstreamOperator(){
    Point p(2);
    p.setValue(1, 6);
    p.setValue(2, 5);
    cout <<"Point p has values (6,5)" << endl;
    cout <<"This is p using Ostream Operator: " << p << endl;
}

