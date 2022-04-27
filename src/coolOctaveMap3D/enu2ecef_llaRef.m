function [X, Y, Z] = enu2ecef_llaRef(refLat, refLong, refH, e, n, u, ell, deg)
    
    # This function converts local east, north, up coordinates (labeled e, n, u)
    # to ECEF coordinates.
  
    # A reference point in geodetic coordinate system
    # (latitude, longitude, height - refLat, refLong, refH)
    # must be given. Longitude and latitude can be given in decimal degrees
    # or radians (default decimal degrees). All distances are in meters.
  
    # Equations taken from:
    # http://wiki.gis.com/wiki/index.php/Geodetic_system
  
    # Parameters
    # ----------
    # e
    #     target east ENU coordinate (meters)
    # n
    #     target north ENU coordinate (meters)
    # u
    #     target up ENU coordinate (meters)
    # refX
    #     reference x ECEF coordinate (meters)
    # refY
    #     reference y ECEF coordinate (meters)
    # refZ
    #     reference z ECEF coordinate (meters)
    # ell : Ellipsoid, optional
    #       reference ellipsoid
    # deg : bool, optional
    #       degrees input/output  (0: radians in/out)
    # 
    # Returns
    # -------
    # x
    #     target x ECEF coordinate (meters)
    # y
    #     target y ECEF coordinate (meters)
    # z
    #     target z ECEF coordinate (meters)
  
    # First find reference location in LLA coordinates
    [Xr,Yr,Zr] = lla2ecef(refLat, refLong, refH, ell, 0); % location of reference point
 
    # Compute ecef coordinates (x,y,x)
    X = -sin(refLong)*e - cos(refLong)*sin(refLat)*n + cos(refLong)*cos(refLat)*u + Xr;
    Y = cos(refLong)*e - sin(refLong)*sin(refLat)*n + cos(refLat)*sin(refLong)*u + Yr;
    Z = cos(refLat)*n + sin(refLat)*u + Zr;