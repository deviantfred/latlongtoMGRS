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

double calcUTMeast(double lat, double longitude){
    int utmzone = int((longitude+180)/6)+1;
    double CentralMeridian = (utmzone-1)*6-180+3;
    double N = EqatorialRadius / sqrt(1-EccentricitySquared*pow(sin(lat*3.141592658979/180),2.0));
    double T = pow(tan(lat*3.141592658979/180), 2.0);
    double C = pow(EccentricitySquared * cos(lat*3.141592658979/180),2.0);
    double A = cos(lat*3.141592658979/180)*(longitude-CentralMeridian)*3.141592658979/180;
    double M = EqatorialRadius*((1-EccentricitySquared/4-3*pow(EccentricitySquared,2.0)/64-5*pow(EccentricitySquared,3.0)/256)*lat*3.141592658979/180-(3*EccentricitySquared/8+3*pow(EccentricitySquared,2.0)/32+45*pow(EccentricitySquared,3.0)/1024)*sin(2*lat*3.141592658979/180)+(15*pow(EccentricitySquared,2.0)/256+45*pow(EccentricitySquared,3.0)/1024)*sin(4*lat*3.141592658979/180)-(35*pow(EccentricitySquared,3.0)/3072)*sin(6*lat*3.141592658979/180));
    double utmeast = ScaleFactor*N*(A+(1-T+C)*pow(A,3.0)/6+(5-18*T+pow(T,2.0)+72*C-58*EccentricitySquared)*pow(A,5.0)/120)+500000;
    return utmeast;
}

double calcUTMnorth(double lat, double long){
    
}


int main(){
    mgrs coords;
    coords.squareid = "test";
    //test coords mgrs for it is: 15R VQ 90816 46052  UTM:15R 490816.69 3446052.01
    double lat = 31.14839523291297;
    double longitude = -93.09634421104477;
    
    printf("%f\n", calcUTMeast(lat, longitude));
    
    
    return 0;
}
