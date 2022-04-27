function[ell]=ellipsoidModel(model)

    # Create ellipsoid defining parameters
    if (model == "wgs84")
        # https://en.wikipedia.org/wiki/World_Geodetic_System#WGS84
        a = 6378137.0
        f = 1/298.257223563
        b = a*(1-f)
    elseif (model == "wgs72")
        a = 6378135.0
        b = 6356750.52001609
    elseif (model == "grs80")
        # https://en.wikipedia.org/wiki/GRS_80"
        a = 6378137.0
        b = 6356752.31414036
    elseif (model == "clarke1866")
        a = 6378206.4
        b = 6356583.8
    elseif (model == "mars")
        # https://tharsis.gsfc.nasa.gov/geodesy.html 
        a = 3396900.0
        b = 3376097.80585952
    elseif (model == "moon")
        a = 1738000.0
        b = a
    elseif (model == "venus")
        a = 6051000.0
        b = a
    elseif (model == "jupiter")
        a = 71492000.0
        b = 66770054.3475922
    elseif (model == "io")
        #https://doi.org/10.1006/icar.1998.5987
        a = 1829.7
        b = 1815.8
    elseif (model == "pluto")
        a = 1187000.0
        b = a
    else
        fprintf("{%s} model not implemented, let us know and we will add it \
        (or make a pull request)",model)
    endif
    
    # In wgs84 the flattening is a defining parameter. In the other ellipsoids
    #  the semiminor_axis is the second defining parameter.
    if (model != "wgs84")
        f = (a - b) / a;
    endif
    
    # Create the rest of the ellipsoid derived geometric constants
    e2 = 2 * f - f ** 2
    ep2 = f*(2-f)/(1-f)**2
    fppp = (a - b) / (a + b)
    
    ell = [a, f, b, e2, ep2, fppp]

endfunction