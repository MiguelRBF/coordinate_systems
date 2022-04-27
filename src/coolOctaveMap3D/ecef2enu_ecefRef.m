function [e,n,u] = ecef2enu_ecefRef(Xr, Yr, Zr, X, Y, Z, ell)
    #This function convert ECEF coordinates to local east, north, up coordinates (ENU).
 
    #A reference point in ECEF coordinates (x, y, z - refX, refY, refZ)
    #must be given. All distances are in meters.

    #Equations taken from:
    #http://wiki.gis.com/wiki/index.php/Geodetic_system
 
    #Parameters
    #----------
    #refX
    #    reference x ECEF coordinate (meters)
    #refY
    #    reference y ECEF coordinate (meters)
    #refZ
    #    reference z ECEF coordinate (meters)
    #x
    #    target x ECEF coordinate (meters)
    #y
    #    target y ECEF coordinate (meters)
    #z
    #    target z ECEF coordinate (meters)
    #ell : Ellipsoid
    #      reference ellipsoid. ell = [a, f, b, e2, ep2, fppp]
 
    #Returns
    #-------
    #e
    #    target east ENU coordinate (meters)
    #n
    #    target north ENU coordinate (meters)
    #u
    #    target up ENU coordinate (meters)
 
    # First find reference location in LLA coordinates (radians)
    [refLat,refLong,refA] = ecef2lla(Xr, Yr, Zr, ell, 0);
 
    # Compute ENU coordinates
    e = -sin(refLong).*(X-Xr) + cos(refLong).*(Y-Yr);
    n = -sin(refLat).*cos(refLong).*(X-Xr) - sin(refLat).*sin(refLong).*(Y-Yr) + cos(refLat).*(Z-Zr);
    u = cos(refLat).*cos(refLong).*(X-Xr) + cos(refLat).*sin(refLong).*(Y-Yr) + sin(refLat).*(Z-Zr);