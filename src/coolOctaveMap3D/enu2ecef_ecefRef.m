function [X, Y, Z] = enu2ecef_ecefRef(Xr, Yr, Zr, e, n, u, ell, deg)
    #This function converts local east, north, up coordinates (labeled e, n, u) to ECEF coordinates.
 
    #A reference point in ECEF coordinates (x, y, z - refX, refY, refZ)
    #must be given. All distances are in meters.
 
    #Equations taken from:
    #http://wiki.gis.com/wiki/index.php/Geodetic_system
 
    #Parameters
    #----------
    #e
    #    target east ENU coordinate (meters)
    #n
    #    target north ENU coordinate (meters)
    #u
    #    target up ENU coordinate (meters)
    #refX
    #    reference x ECEF coordinate (meters)
    #refY
    #    reference y ECEF coordinate (meters)
    #refZ
    #    reference z ECEF coordinate (meters)
    #ell : Ellipsoid
    #      reference ellipsoid
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

    # First find reference location in LLA coordinates
    [refLat, refLong, refH] = ecef2lla(Xr, Yr, Zr, ell, 0); % location of reference point
 
    # Compute ecef coordinates (x,y,x)
    X = -sin(refLong)*e - cos(refLong)*sin(refLat)*n + cos(refLong)*cos(refLat)*u + Xr;
    Y = cos(refLong)*e - sin(refLong)*sin(refLat)*n + cos(refLat)*sin(refLong)*u + Yr;
    Z = cos(refLat)*n + sin(refLat)*u + Zr;