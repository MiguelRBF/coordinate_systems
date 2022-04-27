function [e,n,u] = ecef2enu_llaRef(refLat, refLong, refA, X, Y, Z, ell, deg)
    #This function converts ECEF coordinates to local east, north, up coordinates.

    #A reference point in geodetic coordinate system 
    #(latitude, longitude, height - refLat, refLong, refA)
    #must be given. All distances are in meters.

    #Equations taken from:
    #http://wiki.gis.com/wiki/index.php/Geodetic_system

    #Parameters
    #----------
    #
    #refLat
    #    reference geodetic latitude
    #refLong
    #    reference geodetic longitude
    #refAlt
    #    reference altitude above geodetic ellipsoid (meters)
    #x
    #    target x ECEF coordinate (meters)
    #y
    #    target y ECEF coordinate (meters)
    #z
    #    target z ECEF coordinate (meters)
    #
    #ell : Ellipsoid
    #      reference ellipsoid. ell = [a, f, b, e2, ep2, fppp]
    #deg : bool, optional
    #      degrees input (0: radians input)

    #Returns
    #-------
    #e
    #    target east ENU coordinate (meters)
    #n
    #    target north ENU coordinate (meters)
    #u
    #    target up ENU coordinate (meters)
 
    # First find reference location in ECEF coordinates
    [Xr,Yr,Zr] = lla2ecef(refLat, refLong, refA, ell, deg);
 
    e = -sin(refLong).*(X-Xr) + cos(refLong).*(Y-Yr);
    n = -sin(refLat).*cos(refLong).*(X-Xr) - sin(refLat).*sin(refLong).*(Y-Yr) + cos(refLat).*(Z-Zr);
    u = cos(refLat).*cos(refLong).*(X-Xr) + cos(refLat).*sin(refLong).*(Y-Yr) + sin(refLat).*(Z-Zr);