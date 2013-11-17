#include<iostream>
#include<string>
#include<stdio.h>
#include<cstdlib>
#include<cmath>
#include<set>
#include<vector>
#include<ctime>
#include<algorithm>
#include<utility>
using namespace std;

void randPointInSpace(vector<vector<double> >& points, int spaceDimension, int numberOfPoints);
pair<pair<vector<double>, vector<double> >, double> 
bruteForceAlghoritm(vector<vector<double> >& points);

pair<pair<vector<double>, vector<double> >, double> twoDimAlg(vector<vector<double> > xpoints, vector<vector<double> >);

double dist(vector<double> &a, vector<double> &b);

