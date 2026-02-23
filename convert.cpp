#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//definitions of fixed values
#define EqatorialRadius 6378137 //radius of the equator in m
#define ScaleFactor .9996 
#define EccentricitySquared .00669438


struct mgrs{
    string gsd;
    string squareid;
    int easting;
    int northing;
};

int calcUTMeast(double lat, double longitude){
    double N = EqatorialRadius/sqrt(1-EccentricitySquared*sin(lat*3.141592658979/180)^2)
}



int main(double lat, double longitude){
    mgrs coords;
    coords.squareid = "test";
    
    
    
    
    
    return 0;
}
