// Import coolArduinoMap3D libraries
#include "ellipsoid.h"
#include "lla.h"
#include "ecef.h"
#include "enu.h"

// Define degrees as input/output
bool deg=true;

// Define the model of ellipsoid to be used (WGS84)
Ellipsoid ell_wgs84("wgs84");
double a;

// Define Bern lla (latitude, longitude, altitude) coordinates 
double lla[]={46.9480900, 7.4474400, 549};
// Define Bern ecef (x, y, z) coordinates 
double xyz[]={0, 0, 0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  
  // put your main code here, to run repeatedly:

  // Print ellipsoid parameters
  Serial.print("Print ellipsoid parameters:");
  Serial.print("\n");
  Serial.print(ell_wgs84.a,4);
  Serial.print("\n");
  Serial.print(ell_wgs84.f,4);
  Serial.print("\n");
  Serial.print(ell_wgs84.b,4);
  Serial.print("\n");
  Serial.print(ell_wgs84.e2,4);
  Serial.print("\n");
  Serial.print(ell_wgs84.ep2,4);
  Serial.print("\n");
  Serial.print("\n");

  // Compute Bern ecef coordinates
  Serial.print("Compute Bern ecef coordinates");
  Serial.print("\n");
  lla2ecef(lla, ell_wgs84, deg, xyz);
  Serial.print("x:\t");
  Serial.print(xyz[0],8);
  Serial.print("\n");
  Serial.print("y:\t");
  Serial.print(xyz[1],8);
  Serial.print("\n");
  Serial.print("z:\t");
  Serial.print(xyz[2],8);
  Serial.print("\n");
  Serial.print("\n");

  // Bern ecef (x, y, z) coordinates 
  //xyz[]={4325481.828902193, 565424.2388267403, 4638228.339585699};

  // Compute Bern lla coordinates
  Serial.print("Compute Bern lla coordinates");
  Serial.print("\n");
  ecef2lla(xyz, ell_wgs84, deg, lla);
  Serial.print("Latitude:\t");
  Serial.print(lla[0],8);
  Serial.print("\n");
  Serial.print("Longitude:\t");
  Serial.print(lla[1],8);
  Serial.print("\n");
  Serial.print("Altitude:\t");
  Serial.print(lla[2],8);
  Serial.print("\n");
  Serial.print("\n");

  //  Supose a reference GNSS station in Bern with and ENU error of:
  // E=1.0m , N=0.798654m and U=1.6543m
  double enu[]={1.0, 0.798654, 1.6543};

  // Define xyz coordinates from enu coordinates
  double xyzenu[]={0,0,0};

  // Compute xyz coordinates from enu
  Serial.print("Compute xyz coordinates from enu");
  Serial.print("\n");
  enu2ecef_ecefRef(xyz, enu, ell_wgs84, xyzenu);
  Serial.print("x:\t");
  Serial.print(xyzenu[0],8);
  Serial.print("\n");
  Serial.print("y:\t");
  Serial.print(xyzenu[1],8);
  Serial.print("\n");
  Serial.print("z:\t");
  Serial.print(xyzenu[2],8);
  Serial.print("\n");
  Serial.print("\n");

  // Compute enu coordinates from ecef (xyz)
  Serial.print("Compute enu coordinates from ecef (xyz):");
  Serial.print("\n");
  ecef2enu_ecefRef(xyzenu, xyz, ell_wgs84, enu);
  Serial.print("e:\t");
  Serial.print(enu[0],8);
  Serial.print("\n");
  Serial.print("n:\t");
  Serial.print(enu[1],8);
  Serial.print("\n");
  Serial.print("u:\t");
  Serial.print(enu[2],8);
  Serial.print("\n");
  Serial.print("\n");
  
  delay(1000);
}
