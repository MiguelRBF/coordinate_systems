function [X,Y,Z] = lla2ecef(lat,long, h, ell, deg)

    #Convert lat, long, altitude in geodetic of specified ellipsoid (default WGS-84)
    #to ECEF X,Y,Z. Longitude and latitude can be given in decimal degrees or radians 
    #(default decimal degrees). Altitude must be given in meters.
 
    #Equations taken from:
    #http://wiki.gis.com/wiki/index.php/Geodetic_system
 
    #Parameters
    #----------
    #lat
    #    target geodetic latitude
    #lon
    #    target geodetic longitude
    #alt
    #    target altitude above geodetic ellipsoid (meters)
    #
    #ell : Ellipsoid
    #      reference ellipsoid. ell = [a, f, b, e2, ep2, fppp]
    #deg : bool
    #      degrees input  (0: radians input)
 
    #Returns
    #-------
    #x
    #    target x ECEF coordinate (meters)
    #y
    #    target y ECEF coordinate (meters)
    #z
    #    target z ECEF coordinate (meters)
    
    # Get the ellipsoid parameters
    a = ell(1);
    f = ell(2);
    b = ell(3);
    e2 = ell(4);
    ep2 = ell(5);
    
    # If degrees is wanted as input
    if (deg==1)
        lat = lat/180*pi(); %converting to radians
        long = long/180*pi(); %converting to radians
    endif
    
    e2
    lat
    
    # Compute chi parameter
    chi = sqrt(1.0-e2*(sin(lat))^2);
    
    # Compute ecef coordinates (x,y,x)
    X = (a/chi +h)*cos(lat)*cos(long);
    Y = (a/chi +h)*cos(lat)*sin(long);
    Z = (a*(1.0-e2)/chi + h)*sin(lat);
    
endfunction