0. [**README link**](./../README.md): Link to main README file.
1. [**Coordinate systems - Information**](./1_coordinate_systems_information.md): Link to 1_coordinate_systems_information. Description of the most commonly used coordinate systems.
2. [**Coordinate systems - Transformation**](./2_coordinate_systems_transformation.md): Link to 2_coordinate_systems_transformation. Description of the most commonly used transformation between coordinate systems.
3. [**Script files/folders**](./3_script_files_folders.md): Link to 2_script_files_folders. Description of the scripts inside the repository.
4. [**Documents of interest**](./4_documents_of_interest.md): Link to 3_documents_of_interest. Some documents of interest.
5. [**Webs of interest**](./5_link_to_webs_of_interest.md): Link to 4_link_to_webs_of_interest. Some links to webs of interest.
6. [**List of references**](./6_list_references.md): List with all the references.
<br/><br/>

# **1 Coordinate systems - Information**

Here is going to be shown some coordinate systems commonly used in engineering or physics. They are not the only ones to be used, but they are presented here for their relevance.

## 1.1 Terrestrial Reference Systems (TRS)

A terrestrial reference system (TRS) is a reference system co-rotating with the Earth in its diurnal motion in space. In such a system, coordinates of points attached to the solid surface of the Earth are time-invariant, neglecting geophysical effects such as tectonic or tidal deformations. [[**6**]](./6_list_references.md) [[**7**]](./6_list_references.md)

### **1.1.1 World Geodetic System (WGS): A geodetic datum or geodetic system**

<p align="center">
    <img src="./images/geodetic_system.png" width="400">
</p>
<br/>

A geodetic datum or geodetic system (also: geodetic reference datum, geodetic reference system, or geodetic reference frame) is a global datum reference or reference frame for precisely representing the position of locations on Earth or other planetary bodies by means of geodetic coordinates. Datums are crucial to any technology or technique based on spatial location, including geodesy, navigation, surveying, geographic information systems, remote sensing, and cartography. A horizontal datum is used to measure a location across the Earth's surface, in latitude and longitude or another coordinate system; a vertical datum is used to measure the elevation or depth relative to a standard origin, such as mean sea level (MSL). Since the rise of the global positioning system (GPS), the ellipsoid and datum WGS84 it uses has supplanted most others in many applications. The WGS84 is intended for global use, unlike most earlier datums. [[**2**]](./6_list_references.md)
<br/><br/>

#### **1.1.1.1 Geodetic VS Geocentric Coordinate System**

Both coordinate systems share the **longitude** definition, but they differ in the definition of **latitude**.

<br/>
<p align="center">
    <img src="./images/latitude_and_longitude_graticule_on_an_ellipsoid.png" width="400">
</p>
<br/>

The graticule on the ellipsoid is constructed in exactly the same way as on the sphere. The normal at a point on the surface of an ellipsoid does not pass through the centre, except for points on the equator or at the poles, but the definition of latitude remains unchanged as the angle between the normal and the equatorial plane. The terminology for latitude must be made more precise by distinguishing:

- **Geodetic latitude**: the angle between the normal and the equatorial plane. The standard notation in English publications is $\phi$. This is the definition assumed when the word latitude is used without qualification. The definition must be accompanied with a specification of the ellipsoid.

- **Geocentric latitude** (also known as spherical latitude, after the 3D polar angle): the angle between the radius (from centre to the point on the surface) and the equatorial plane. (Figure below). There is no standard notation, examples from various texts include: θ, ψ, q, $\phi'$, $\phi_{c}$, $\phi_{g}$. This article uses θ.

<br/>
<p align="center">
    <img src="./images/geodetic_vs_geocentric_latitude.png">
</p>

The definition of **geodetic** **latitude (phi)** and **longitude (lambda)** on an ellipsoid. By definition the normal to the surface does not pass through the centre, except at the equator and at the poles.

**Geographic latitude** must be used with care, as some authors use it as a synonym for geodetic latitude whilst others use it as an alternative to the astronomical latitude. **Latitude** (unqualified) should normally refer to the **geodetic latitude**.

[[**4**]](./6_list_references.md)

<br/><br/>

#### **1.1.1.2 The Geodetic (Lat/Long) Coordinate System**

<br/>
<p align="center">
    <img src="./images/geodetic_coordinates.png" width="400">
</p>
<br/>

The **geodetic** coordinate system is known to most as the **Latitude** and **Longitude** coordinate system. The geodetic grid for the planet is comprised of parallel East/West lines of latitude and North/South lines of longitude that intersect at the poles. Latitude and longitude lines are labeled by the angle they subtend with respect to a reference. For latitude, that 0 reference is the Equator and for longitude that 0 reference is the Prime Meridian.

Since the longitude lines are not parallel, the horizontal distance for a degree of longitude depends on your location. Therefore, the geodetic location does not have intuitive understanding of distance that other coordinate systems have. However, the geodetic coordinate system is globally consistent and therefore is a good coordinate system for positioning high altitude and space-based platforms. [[**5**]](./6_list_references.md)

In geodetic coordinates the Earth's surface is approximated by an ellipsoid and locations near the surface are described in terms of latitude, longitude  and height. The ellipsoid is completely parameterized by the semi-major axis **a** and the flattening **f**.

#### **1.1.1.3 The geometry of the ellipsoid**

The shape of an ellipsoid of revolution is determined by the shape of the ellipse which is rotated about its minor (shorter) axis. Two parameters are required. One is invariably the equatorial radius, which is the semi-major axis, **a**. The other parameter is usually the *polar radius* or *semi-minor axis*, **b**; or the (first) *flattening*, **f**; or the (first) *eccentricity*, **e**. These parameters are not independent, they are related by:

- **f = (a-b)/a**

- **e^2 = (2-f)·f**

- **b = a·(1-f) = a·sqrt(1-e^2)**

[[**3**]](./6_list_references.md)

<br/>
<p align="center">
    <img src="./images/ellipsoid_parametric_euler_mono.png">
</p>
<br/><br/>

#### **1.1.1.4 WGS84 Ellipsoidal model: World Geodetic System 1984**

The Global Positioning System (GPS) uses the world geodetic system 1984 (WGS84) to determine the location of a point near the surface of the Earth.

<br/>
<p align="center">
    <img src="./images/WGS84_ellipsoid.png">
</p>
<br/>

##### **1.1.1.4.1 WGS 84 defining parameters**

| Constant                  | Notation  | Value        |
|:--------------------------|:---------:|:------------:|
|Semi-minor axis            | a         |6378137.0 m   |
|Reciprocal of flattening   | 1/f       |298.257223563 |
<br/>

##### **1.1.1.4.2 WGS84 derived geometric constants**

| Constant                   | Notation  | Value            | Approximation     |
|:---------------------------|:----------|:----------------:|:-----------------:|
|Semi-minor axis             | b         |a·(1-f)           |6356752.3142 m     |
|First eccentricity squared  | e^2       |(2-f)·f           |6.69437999014·10^-3|
|Second eccentricity squared | e'^2      |f·(2-f)/(1-f)^2   |6.73949674228·10^-3|

<br/><br/>

### **1.1.2 Earth-Centered, Earth-Fixed (ECEF XYZ) Coordinate System**

<br/>
<p align="center">
    <img src="./images/ecef_enu_coordinate_systems.png">
</p>
<br/>

The Earth-Centered, Earth-Fixed (ECEF XYZ) coordinate system is also known as the "conventional terrestrial" coordinate system or Geocentric coordinate system. It is a simple Cartesian coordinate system with the center of the earth at it’s origin. The Z+ axis is identical to the direction of the earth's rotation axis defined by the Conventional Terrestrial Pole (CTP). The X+ axis is defined as the intersection of the orthogonal plane to Z+ axis (fundamental plane) and Greenwich mean meridian. The +Y axis is orthogonal to +X and +Z. As a result, this coordinate system rotates with the earth. The distances used along each axis are meters.

Since the entire ECEF reference frame rotates with the earth, this coordinate system is useful for positioning geo-stationary objects such as satellites. In fact, the Global Positioning System (GPS) uses ECEF as it’s primary coordinate system and derives all other coordinates from it. However, since ECEF has an origin that is very far from most locations on the surface of the earth, it would be awkward for a small scene with a platform located at a small distance away because all the coordinates will be biased by the large offset to the center of the earth. [[**5**]](./6_list_references.md)

<br/><br/>

### **1.1.3 The Scene East-North-Up (Scene ENU) coordinate system**

<br/>
<p align="center">
    <img src="./images/ecef_enu_coordinate_systems.png">
</p>
<br/>

The "scene" or "local" coordinate system is the most basic coordinate system. The "scene" coordinate system is essentially an arbitrary, Cartesian coordinate system. By definition, the coordinate system is a "flat earth" system that uses linear X, Y and Z coordinates to locate elements with respect to the coordinate systems origin. This coordinate system is best used for smaller area extents where the curvature of the earth is not a concern (less than 4 km).

Although the coordinate system is itself arbitrary, the "scene" coordinate system still supports geolocation because the origin of this arbitrary coordinate system is tied to a geolocation. When translated to this geolocated "tie point", the scene +Y axis corresponds to North and the scene +X corresponds to East. This makes the scene coordinate system an "East North Up" (ENU) coordinate system.

Because the scene coordinate system assumes a flat earth, it is not a good coordinate system to use over large distances. For example, unless your platform is directly overhead, using the scene coordinate system for a high altitude or space-based platform would not be suggested. However, it is a convenient coordinate system for small areas because it allows for the use of Euclidean geometry. [[**5**]](./6_list_references.md)

<br/><br/>

### **1.1.4 The Universal Transverse Mercator (UTM) Coordinate System**

<br/>
<p align="center">
    <img src="./images/Malla-Universal-Transversa-Mercator-UTM.jpg">
</p>
<br/>

<p align="center">
    <img src="./images/Utm-zones.jpg">
</p>
<br/>

The Universal Transverse Mercator (UTM) coordinate system is a geographic coordinate system which utilizes a conformal projection that preserves angles locally. This is achieved by breaking the entire globe into a sequence of small conformal projections. These local projections are called "grid zones" which are defined by a longitude "zone" (the earth is divided into 60 zones, each 6 degrees wide and number sequentially) and a latitude "band" (the earth is divided into 20 latitude bands, each 8 degrees wide and labeled with a lettering scheme). The horizontal location offsets within a given grid zone are referred to as the "Easting" and "Northing" and are generally measured in meters.

The key advantage of the UTM coordinate system is that distances and angles can be computed using Euclidean geometry over short distances. This makes is very easy to compute distances and angles. And coordinate units are in meters, making the coordinates intuitive to interpret. However, the UTM projections suffer from ambiguities at the meeting of two grids zones and general distortions for large areas and distances. Although UTM could be used to position a plane or satellite, as it moved from one grid zone to another, the relative position will be prone to errors. [[**5**]](./6_list_references.md)

<br/><br/>

## 1.2 Celestial Reference System (CRS) - Earth Centered

## **1.2.1 ECI (Earth Center Inertial) Coordinate System**

<br/>
<p align="center">
    <img src="./images/CRS_reference_system.png" width="500">
</p>
<br/>

These coordinate system is a quasi-inertial reference system. It has its origin at the earth's centre of mass. X+ axis points in the direction of the mean equinox at J2000.0 epoch, Z+ axis is orthogonal to the plane defined by the mean equator at J2000.0 epoch (fundamental plane) and Y+ axis is orthogonal to the former ones, so the system is directly (right handed) oriented. The practical implementation is called (conventional) Celestial Reference Frame (CRF)[footnotes 2] and it is determined from a set of precise coordinates of extragalactic radio sources (i.e., it is fixed with respect to distant objects of the universe). The mean equator and equinox J2000.0 were defined by International Astronomical Union (IAU) agreements in 1976, with 1980 nutation series (Seildelmann, 1982 and Kaplan, 1981), which are valid analytic expressions for long time intervals (the former reference epoch was 1950.0). [[**6**]](./6_list_references.md)
