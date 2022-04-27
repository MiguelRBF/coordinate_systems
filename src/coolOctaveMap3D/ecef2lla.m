function [lat, long, alt]=ecef2lla(X, Y, Z, ell, deg)

    # This function was created to change between ECEF coordinate system to 
    # geodetic of specified ellipsoid (default WGS-84) coordinate system 
    # (longitude, latitude, height).

    # Equations taken from:
    # http://wiki.gis.com/wiki/index.php/Geodetic_system
 
    # Parameters
    # ----------
    # x
    #     target x ECEF coordinate (meters)
    # y
    #     target y ECEF coordinate (meters)
    # z
    #     target z ECEF coordinate (meters)
    # 
    # ell : Ellipsoid
    #       reference ellipsoid. ell = [a, f, b, e2, ep2, fppp]
    # deg : 0/1
    #       degrees input/output  (0: radians in/out)

    # Returns
    # -------
    # lat
    #     target geodetic latitude
    # lon
    #     target geodetic longitude
    # alt
    #     target altitude above geodetic ellipsoid (meters)
    
    # Get the ellipsoid parameters
    a = ell(1)
    f = ell(2)
    b = ell(3)
    e2 = ell(4)
    ep2 = ell(5)
    
    # Inter,mediate computations
    r2 = X.^2+Y.^2;
    r = sqrt(r2);
    E2 = a^2 - b^2;
    F = 54*b^2*Z.^2;
    G = r2 + (1-e2)*Z.^2 - e2*E2;
    c = (e2*e2*F.*r2)./(G.*G.*G);
    s = ( 1 + c + sqrt(c.*c + 2*c) ).^(1/3);
    P = F./(3*(s+1./s+1).^2.*G.*G);
    Q = sqrt(1+2*e2*e2*P);
    ro = -(e2*P.*r)./(1+Q) + sqrt((a*a/2)*(1+1./Q) - ((1-e2)*P.*Z.^2)./(Q.*(1+Q)) - P.*r2/2);
    tmp = (r - e2*ro).^2;
    U = sqrt( tmp + Z.^2 );
    V = sqrt( tmp + (1-e2)*Z.^2 );
    zo = (b^2*Z)./(a*V);

    # Now get the final coordinates: longitude, latitude and altitude
    lat = atan( (Z + ep2*zo)./r );
    long = atan2(Y,X);
    alt = U.*( 1 - b^2./(a*V));
    
    # If degrees is wanted as output
    if (deg==1)
        # Convert the units of longitude and latitude from radians to degrees
        lat = lat*180.0/pi()
        long = long*180.0/pi()
    endif
    
endfunction