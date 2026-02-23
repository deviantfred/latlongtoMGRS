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


//function to calculate all the background functions
void calcBackground (double lat, double longitude, double arr[7]){
    //utmzone
    arr[0] = (longitude+180)/6+1;
    //centralMeridian    
    arr[1] = (arr[0]-1)*6-180+3;
    //N
    arr[2] = EqatorialRadius / sqrt(1-EccentricitySquared*pow(sin(lat*3.141592658979/180),2.0));
    //T
    arr[3] = pow(tan(lat*3.141592658979/180), 2.0);
    //C
    arr[4] = pow(EccentricitySquared * cos(lat*3.141592658979/180),2.0);
    
    //A
    arr[5] = cos(lat*3.141592658979/180)*(longitude-arr[1])*3.141592658979/180;
    //M
    arr[6] = EqatorialRadius*((1-EccentricitySquared/4-3*pow(EccentricitySquared,2.0)/64-5*pow(EccentricitySquared,3.0)/256)*lat*3.141592658979/180-(3*EccentricitySquared/8+3*pow(EccentricitySquared,2.0)/32+45*pow(EccentricitySquared,3.0)/1024)*sin(2*lat*3.141592658979/180)+(15*pow(EccentricitySquared,2.0)/256+45*pow(EccentricitySquared,3.0)/1024)*sin(4*lat*3.141592658979/180)-(35*pow(EccentricitySquared,3.0)/3072)*sin(6*lat*3.141592658979/180));
}

//function to calclate the easting
double calcUTMeast(double lat, double longitude, double arr[7]){
    
    int utmzone = int((longitude+180)/6)+1;
    double CentralMeridian = (utmzone-1)*6-180+3;
    double N = EqatorialRadius / sqrt(1-EccentricitySquared*pow(sin(lat*3.141592658979/180),2.0));
    double T = pow(tan(lat*3.141592658979/180), 2.0);
    double C = pow(EccentricitySquared * cos(lat*3.141592658979/180),2.0);
    double A = cos(lat*3.141592658979/180)*(longitude-CentralMeridian)*3.141592658979/180;
    double M = EqatorialRadius*((1-EccentricitySquared/4-3*pow(EccentricitySquared,2.0)/64-5*pow(EccentricitySquared,3.0)/256)*lat*3.141592658979/180-(3*EccentricitySquared/8+3*pow(EccentricitySquared,2.0)/32+45*pow(EccentricitySquared,3.0)/1024)*sin(2*lat*3.141592658979/180)+(15*pow(EccentricitySquared,2.0)/256+45*pow(EccentricitySquared,3.0)/1024)*sin(4*lat*3.141592658979/180)-(35*pow(EccentricitySquared,3.0)/3072)*sin(6*lat*3.141592658979/180));
    
    double utmeast = ScaleFactor * (arr[2]) * ((arr[5]) + (1 - (arr[3]) + (arr[4])) * pow((arr[5]),3.0) / 6 + (5 - 18 * (arr[3]) + pow((arr[3]),2.0) + 72 * (arr[4]) - 58 * EccentricitySquared) * pow((arr[5]),5.0) / 120) + 500000;
    return utmeast;
}

//function to calcluate the northing
double calcUTMnorth(double lat, double longitude){
    int utmzone = int((longitude+180)/6)+1;
    double CentralMeridian = (utmzone-1)*6-180+3;
    int falsenorth;
    if(lat<0){
        falsenorth=10000000;
    }else{
        falsenorth=0;
    }
    double N = EqatorialRadius / sqrt(1-EccentricitySquared*pow(sin(lat*3.141592658979/180),2.0));
    double T = pow(tan(lat*3.141592658979/180), 2.0);
    double C = pow(EccentricitySquared * cos(lat*3.141592658979/180),2.0);
    double A = cos(lat*3.141592658979/180)*(longitude-CentralMeridian)*3.141592658979/180;
    double M = EqatorialRadius*((1-EccentricitySquared/4-3*pow(EccentricitySquared,2.0)/64-5*pow(EccentricitySquared,3.0)/256)*lat*3.141592658979/180-(3*EccentricitySquared/8+3*pow(EccentricitySquared,2.0)/32+45*pow(EccentricitySquared,3.0)/1024)*sin(2*lat*3.141592658979/180)+(15*pow(EccentricitySquared,2.0)/256+45*pow(EccentricitySquared,3.0)/1024)*sin(4*lat*3.141592658979/180)-(35*pow(EccentricitySquared,3.0)/3072)*sin(6*lat*3.141592658979/180));
    double utmnorth = ScaleFactor*(M+N*tan(lat*3.141592658979/180)*(pow(A,2.0)/2+(5-T+9*C+4*pow(C,2.0))*pow(A, 4.0)/24+(61-58*T+pow(T,2.0)+600*C-330*EccentricitySquared)*pow(A,6.0)/720))+falsenorth;
    return utmnorth;
}


int main(){
    mgrs coords;
    coords.squareid = "test";
    //test coords mgrs for it is: 15R VQ 90816 46052  UTM:15R 490816.69 3446052.01
    double lat = 31.14839523291297;
    double longitude = -93.09634421104477;
    
    //array for background calculations
    double backgroundarr[7]; //utmzone, meridian, N, T, C, A, M
    calcBackground(lat, longitude, backgroundarr);

    
    
    
    
    printf("%f\n", calcUTMeast(lat, longitude, backgroundarr));
    
    
    return 0;
}
