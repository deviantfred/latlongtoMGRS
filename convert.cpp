#include <iostream>
#include <string>
#include <math.h>

using namespace std;

struct mgrs{
    string gsd;
    string sqareid;
    int easting;
    int northing;
};

//function to find the grid zone
int findGridZone(float lat , float longitude){
    int zoneNum = (longitude + 180) / 2;
    



}



// convert the lat long into mgrs coords
int latlongtoMGRS(mgrs coords, float lat, float longitude){
    

    cout << "MGRS: " << mgrs.gsd << " " << mgrs.sqareid << " " << mgrs.easting << " " << mgrs.northing << endl;

    return 0;
}




int main(float lat, float longitude){
    mgrs coords;

    latlongtoMGRS(coords, lat, longitude);
    
    
    
    
    
    return 0;
}
