#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

struct Point{
    vector<double> values;
    int cluster;
    double manhattanDist;
    double EucledeanDist;

    Point () :
        values({0,0,0}),
        cluster(-1),
        manhattanDist(__DBL_MAX__),
        EucledeanDist(__DBL_MAX__)  {}

    Point (vector<double> values) :
        values({values[0],values[1],values[2], values[3]}),
        cluster(-1),
        manhattanDist(__DBL_MAX__),
        EucledeanDist(__DBL_MAX__)  {}

    Point (double A, double B, double C, double D) :
        values({A, B, C, D}),
        cluster(-1),
        manhattanDist(__DBL_MAX__),
        EucledeanDist(__DBL_MAX__)  {}


    void print(){
        cout<<"value_1:"<<values[0]<<"\tvalue_2:"<<values[1]<<"\t value_3:"<<values[2]<<"\t value_4:"<<values[3]<<"\t cluster:"<<cluster<<"\n";

    }


    double  manhattanDistance(Point p){
        double manhattandistance = abs(p.values[0] - values[0]) + abs(p.values[1] - values[1]) + abs(p.values[2] - values[2]) + abs(p.values[3] - values[3]);
        return manhattandistance;

    }
    double  eucledeanDistance(Point p){
         double eucledeandistance = (p.values[1] - values[1])*(p.values[1] - values[1])+(p.values[2] - values[2])*(p.values[2] - values[2])+(p.values[3] - values[3])*(p.values[3] - values[3])+(p.values[4] - values[4])*(p.values[4] - values[4]);
         return sqrt(eucledeandistance);

    }

};
    

vector<Point> readfile() {
    vector<Point> points;
    string line;
    ifstream file("iris_flower_dataset.txt");

    cout<<"read file running..."<<'\n';
    while (getline(file, line)) {
        stringstream lineStream(line);
        string bit,l;
        vector<double> values;

        while(getline(lineStream, bit, '\t')){
            //cout<<stoi(bit)<<'\t';
            values.push_back(stod(bit));

        };

        //cout<<"\n";
        points.push_back(Point(values));

        
        
    }
    int len = points.size();
        cout<<len<<"\n";
        
        for(int i = 0; i <= points.size()-1; i++){
            cout<<"point:"<<i+1<<"\t";
            points.at(i).print();
        }
        
    return points;
}


void kMeansClustering(vector<Point>* points, int epochs, int k) {
    int n = points->size();

    // Randomly initialise centroids
    // The index of the centroid within the centroids vector
    // represents the cluster label.
    vector<Point> centroids;
    srand(time(0));
    for (int i = 0; i < k; ++i) {
        centroids.push_back(points->at(rand() % n));    //picking k number of random points
    }

    for (int i = 0; i < epochs; ++i) {
        // For each centroid, compute distance from centroid to each point
        // and update point's cluster if necessary
        for (vector<Point>::iterator c = begin(centroids); c != end(centroids);
             ++c) {
            int clusterId = c - begin(centroids);

            for (vector<Point>::iterator it = points->begin();
                 it != points->end(); ++it) {
                Point p = *it;
                double manDist = c->manhattanDistance(p);
                double euDist = c->eucledeanDistance(p);
                if (manDist < p.manhattanDist) {
                    p.manhattanDist = manDist;
                    p.cluster = clusterId;
                }
                 if (euDist < p.manhattanDist) {
                    p.manhattanDist = manDist;
                    p.cluster = clusterId;
                }
                *it = p;
            }
        }

        // Create vectors to keep track of data needed to compute means
        vector<int> nPoints;
        vector<double> dataPoints1, dataPoints2, dataPoints3, dataPoints4;
        for (int j = 0; j < k; ++j) {

            //initialise the points with zero
            nPoints.push_back(0);
            dataPoints1.push_back(0.0);
            dataPoints2.push_back(0.0);
            dataPoints3.push_back(0.0);
            dataPoints4.push_back(0.0);

        }

        // Iterate over points to append data to centroids
        for (vector<Point>::iterator it = points->begin(); it != points->end();
             ++it) {
            int clusterId = it->cluster;
            nPoints[clusterId] += 1;
            dataPoints1[clusterId] += it->values[0];
            dataPoints2[clusterId] += it->values[1];
            dataPoints3[clusterId] += it->values[2];
            dataPoints3[clusterId] += it->values[3];



            it->manhattanDist = __DBL_MAX__;  // reset manhattan distance
            it->EucledeanDist = __DBL_MAX__;  // reset manhattan distance

        }
        // Compute the new centroids
        for (vector<Point>::iterator c = begin(centroids); c != end(centroids);
             ++c) {
            int clusterId = c - begin(centroids);
            c->values[0] = dataPoints1[clusterId] / nPoints[clusterId];
            c->values[1] = dataPoints2[clusterId] / nPoints[clusterId];
            c->values[2] = dataPoints3[clusterId] / nPoints[clusterId];
            c->values[3] = dataPoints3[clusterId] / nPoints[clusterId];


        }
    }
    // Write to output file
    ofstream myfile;
    myfile.open("iris_flower_dataset[output].txt");
    myfile << "epochs:"<< epochs <<"\t Clusters:" << k << endl;

    for (vector<Point>::iterator it = points->begin(); it != points->end();
         ++it) {
        myfile<<"value_1:" << it->values[0] << "\tvalue_2:" << it->values[1]<<"\t value_3:" << it->values[2] <<"\t value_4:" << it->values[3] << "\t cluster:" << it->cluster << endl;

    }
    myfile.close();
}

int main(){
    cout<<"Hello"<<"\n";
    vector<Point>* points;
    vector<Point> mypoints;

    mypoints = readfile();

    points = &mypoints;

    kMeansClustering(points, 3, 20);
    return 0;
}