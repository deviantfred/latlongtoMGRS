#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//definitions of fixed values
#define EqatorialRadius 6378137 //radius of the equator in m
#define ScaleFactor .9996 
#define EccentricitySquared .00669438



//function to calclate the easting
double calcUTMeast(double arr[7]){
    double utmeast = ScaleFactor * arr[2] * (arr[5] + (1 - arr[3] + arr[4]) * pow(arr[5],3.0) / 6 + (5 - 18 * arr[3] + pow(arr[3],2.0) + 72 * arr[4] - 58 * EccentricitySquared) * pow(arr[5],5.0) / 120) + 500000;
    return utmeast;
}

//function to calcluate the northing
double calcUTMnorth(double lat, double arr[7]){
    int falsenorth;
    if(lat<0){
        falsenorth=10000000;
    }else{
        falsenorth=0;
    }
    double utmnorth = ScaleFactor*(arr[6]+arr[2]*tan(lat*3.141592658979/180)*(pow(arr[5],2.0)/2+(5-arr[3]+9*arr[4]+4*pow(arr[4],2.0))*pow(arr[5], 4.0)/24+(61-58*arr[3]+pow(arr[3],2.0)+600*arr[4]-330*EccentricitySquared)*pow(arr[5],6.0)/720))+falsenorth;
    return utmnorth;
}


int main(){
    //test coords mgrs for it is: 15R VQ 90816 46052  UTM:15R 490816.69 3446052.01
    double lat = 31.14839523291297;
    double longitude = -93.09634421104477;
    
    //array for background calculations
    double backgroundarr[7]; //utmzone, meridian, N, T, C, A, M

    //below are some calulations that several of the equations contain, only doing the math once to save compute cycles
    double latpidiv = lat*3.141592658979/180;


    //background calculations for the easting and northing
    //utmzone
    backgroundarr[0] = int((longitude+180)/6)+1;
    //centralMeridian    
    backgroundarr[1] = (backgroundarr[0]-1)*6-180+3;
    //N
    backgroundarr[2] = EqatorialRadius / sqrt(1-EccentricitySquared*pow(sin(latpidiv),2.0));
    //T
    backgroundarr[3] = pow(tan(latpidiv), 2.0);
    //C
    backgroundarr[4] = pow(EccentricitySquared * cos(latpidiv),2.0);
    //A
    backgroundarr[5] = cos(latpidiv)*(longitude-backgroundarr[1])*3.141592658979/180;
    //M
    backgroundarr[6] = EqatorialRadius*((1-EccentricitySquared/4-3*pow(EccentricitySquared,2.0)/64-5*pow(EccentricitySquared,3.0)/256)*latpidiv-(3*EccentricitySquared/8+3*pow(EccentricitySquared,2.0)/32+45*pow(EccentricitySquared,3.0)/1024)*sin(2*latpidiv)+(15*pow(EccentricitySquared,2.0)/256+45*pow(EccentricitySquared,3.0)/1024)*sin(4*latpidiv)-(35*pow(EccentricitySquared,3.0)/3072)*sin(6*latpidiv));

    //calculate lattitude
    char latband ='a';
    //key for lattitude bands counts from the eqator up, then from the equator down
    char latbandkey[20] = {/*equator->up*/'N','P','Q','R','S','T','U','V','W','X',/*equator->down*/'M','L','K','J','H','G','F','E','D','C'};
    int latpos = lat;
    if(lat<0){
        
        latpos =(latpos*-1)+80;
    }
    latband = latbandkey[latpos/8];

    //calculate easting and northing
    double easting = calcUTMeast(backgroundarr);
    double northing = calcUTMnorth(lat, backgroundarr);
    
    //keys to identify the 100,000m zone 
    char vertzonedesignatorkey[24] = {'A','B','C','D','E','F','G','H','J','K','L','M','N','P','Q','R','S','T','U','V'};
    char horzonedesignatorkey[3][8] = {{'A','B','C','D','E','F','G','H'},{'J','K','L','M','N','P','Q','R'},{'S','T','U','V','W','X','Y','Z'}};

    char squareId[2];
    squareId[0] = horzonedesignatorkey[(int(backgroundarr[0])-1)%3][int(easting/100000)-1];
    squareId[1] = vertzonedesignatorkey[(int(northing)%2000000)/100000];

    printf("%d %d\n",(int(backgroundarr[0])-1)%3, int(easting/100000)-1);
    printf("%c%c\n", squareId[0], squareId[1]);
    
    
    return 0;
}
