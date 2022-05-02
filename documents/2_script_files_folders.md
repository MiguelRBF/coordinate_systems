# **2 Script files/folders**

0. [**README link**](./../README.md): Link to main README file.
1. [**Coordinate systems - Information**](./1_coordinate_systems_information.md): Link to 1_coordinate_systems_information. Description of the scripts inside the repository.
2. [**Script files/folders**](./2_script_files_folders.md): Link to 2_script_files_folders. Description of the scripts inside the repository.
3. [**Documents of interest**](./3_documents_of_interest.md): Link to 3_documents_of_interest. Some documents of interest.
4. [**Webs of interest**](./4_link_to_webs_of_interest.md): Link to 4_link_to_webs_of_interest. Some links to webs of interest.
5. [**List of references**](./5_list_references.md): List with all the references.
<br/><br/>

The repository have the following structure:

```
COORDINATE_SYSTEMS
|
|-coordinate_systems_example.py
|-LICENSE
|-README.md
|
|-documents
|   |
|   |-1_coordinate_systems_information.md
|   |-2_script_files_folders.md
|   |-3_documents_of_interest.md
|   |-4_links_to_web_of_interest.md
|   |-5_list_references.md
|   |
|   |-images
|   |   |
|   |   |-3D_Spherical.png
|   |   |-Division_of_the_Earth_into_Gauss-Krueger_zones_-_Net.png
|   |   |-ecef_enu_coordinate_systems.png
|   |   |-ellipsoid_parametric_euler_mono.png
|   |   |-geodetic_coordinates.png
|   |   |-geodetic_system.png
|   |   |-geodetic_vs_geocentric_latitude.png
|   |   |-latitude_and_longitude_graticule_on_an_ellipsoid.png
|   |   |-Malla-Universal-Transversa-Mercator-UTM.jpg
|   |   |-Rosetta_Stone.jpg
|   |   |-Utm-zones.jpg
|   |   |-WGS84_ellipsoid.png
|   |
|   |-pdf
|   |   |
|   |   |-Capitulo_5_conversion_de_coordenadas.pdf 
|   |   |-EFFICIENT TRANSFORMATION FROM CARTESIAN TO GEODETIC COORDINATES.pdf
|   |   |-Transforming Cartesian Coordinates to Geographical coordinates.pdf
|   |   |-TRF_Altamimi.pdf
|   |
|   |-licenses
|       |
|       |-geospace_code_pymap3d
|           |
|           |-license
|           |-license_github.png
|
|- scripts
|   |
|   |-
|
|- src
    |
    |-coolpymap3D
    |   |
    |   |-ecef.py
    |   |-eci.py
    |   |-ellipsoid.py
    |   |-enu.py
    |   |-lla.py
    |   |-sidereal.py
    |   |-timeconv.py
    |   |-utils.py
    |
    |-coolCppMap3D
    |   |
    |   |-ecef.h
    |   |-ecef.cpp
    |   |-ellipsoid.h
    |   |-ellipsoid.cpp
    |   |-enu.h
    |   |-enu.cpp
    |   |-lla.h
    |   |-lla.cpp
    |   |
    |   |-coordinate_systems_cpp_example.cpp
    |
    |-coolOctaveMap3D
    |   |
    |   |-ecef2enu_ecefRef.m
    |   |-ecef2enu_llaRef.m
    |   |-ecef2lla.m
    |   |-ellipsoidModel.m
    |   |-enu2ecef_ecefRef.m
    |   |-enu2ecef_llaRef.m
    |   |-lla2ecef.m
    |   |
    |   |-coordinate_systems_octave_example.m
    |
    |-coolJavaMap3D
    |   |
    |   |-ECEF
    |   |   |-ECEF.java
    |   |
    |   |-Ellipsoid
    |   |   |-Ellipsoid.java
    |   |
    |   |-LLA
    |   |   |-LLA.java
    |   |
    |   |-coordinate_systems_java_example.java
    |
    |-coolArduinoMap3D
        |
        |-ecef
        |   |-ecef.h
        |   |-ecef.cpp
        |
        |-ellipsoid
        |   |-ellipsoid.h
        |   |-ellipsoid.cpp
        |
        |-enu
        |   |-enu.h
        |   |-enu.cpp
        |
        |-lla
            |-lla.h
            |-lla.cpp

```
## **2.1 files inside COORDINATE_SYSTEMS**

### **2.1.1 coordinate_systems_example.py**
Example of use of the modules/functions inside the repository.

### **2.1.2 LICENSE**
License document.

### **2.1.3 README.md**
README document. Here is place all the important information about the repository.

## **2.2 documents**

### **2.2.1 Markdown documents README**
This are all the markdown documents linked to the README.md file
```
COORDINATE_SYSTEMS
|
|-documents
    |
    |-1_coordinate_systems_informati
    |-2_script_files_folders.md
    |-3_documents_of_interest.md
    |-4_links_to_web_of_interest.md
    |-5_list_references.md
```

### **2.2.2 images**
In this folder you will find the images of the repository. Some of them are used inside the documents linked to the README.md
```
COORDINATE_SYSTEMS
|
|-documents
    |
    |-images
```
### **2.2.3 pdf**

```
COORDINATE_SYSTEMS
|
|-documents
   |
   |-pdf
```
You will find further information about this folder at the following link:

- [**Documents of interest**](./3_documents_of_interest.md): Link to 3_documents_of_interest. Some documents of interest.

## licenses\geospace_code_pymap3d

```
COORDINATE_SYSTEMS
|
|-documents
|   |
|   |-licenses
|       |
|       |-geospace_code_pymap3d
|           |
|           |-license
|           |-license_github.png
```

## **2.3 scripts**
Now empty.

## **2.4 src/coolpymap3D**
Inside this folder you will find the modules used to do reference frames conversions. Python code.

```
COORDINATE_SYSTEMS
|
|- src
    |
    |-coolPyMap3D
        |
        |-ecef.py
        |-eci.py
        |-ellipsoid.py
        |-enu.py
        |-lla.py
        |-sidereal.py
        |-timeconv.py
        |-utils.py
```

### **2.4.1 ecef.py**
This module was created to transforms from ECEF (earth-centered, earth-fixed) frame to others.

### **2.4.2 eci.py**
This module was created to do transformations involving ECI (earth-centered inertial) reference frame.

### **2.4.3 ellipsoid.py**
This module was created to define the required ellipsoid for the LLA reference frames.

### **2.4.4 enu.py**
This module was created to transforms from ENU (East North Up) frame to others.

### **2.4.5 lla.py**
This module was created to transforms from LLA (Latitude Longitude Altitude) frame to others.

### **2.4.6 sidereal.py**
This module was created to manipulations of sidereal time.

### **2.4.7 timeconv.py**
This module was created to convert strings to datetime.

### **2.4.8 utils.py**
Some utility functions. All assume radians.

## **2.5 src/coolCppMap3D**
Inside this folder you will find the modules used to do reference frames conversions. C++ code.

```
COORDINATE_SYSTEMS
|
|- src
    |
    |-coolCppMap3D
        |
        |-ecef.h
        |-ecef.cpp
        |-ellipsoid.h
        |-ellipsoid.cpp
        |-enu.h
        |-enu.cpp
        |-lla.h
        |-lla.cpp
        |
        |-coordinate_systems_cpp_example.cpp
```

## **2.6 src/coolOctaveMap3D**
Inside this folder you will find the modules used to do reference frames conversions. Octave code.

```
COORDINATE_SYSTEMS
|
|- src
    |
    |-coolOctaveMap3D
        |
        |-ecef2enu_ecefRef.m
        |-ecef2enu_llaRef.m
        |-ecef2lla.m
        |-ellipsoidModel.m
        |-enu2ecef_ecefRef.m
        |-enu2ecef_llaRef.m
        |-lla2ecef.m
        |
        |-coordinate_systems_octave_example.m
```

## **2.7 src/coolJavaMap3D**
Inside this folder you will find the modules used to do reference frames conversions. Java code.

```
COORDINATE_SYSTEMS
|
|- src
    |
    |-coolJavaMap3D
        |
        |-ECEF
        |   |-ECEF.java
        |
        |-Ellipsoid
        |   |-Ellipsoid.java
        |
        |-LLA
        |   |-LLA.java
        |
        |-coordinate_systems_java_example.java
```

## **2.8 src/coolArduinoMap3D**
Inside this folder you will find the modules used to do reference frames conversions. Arduino code.

```
COORDINATE_SYSTEMS
|
|- src
    |
    |-coolArduinoMap3D
        |
        |-ecef
        |   |-ecef.h
        |   |-ecef.cpp
        |
        |-ellipsoid
        |   |-ellipsoid.h
        |   |-ellipsoid.cpp
        |
        |-enu
        |   |-enu.h
        |   |-enu.cpp
        |
        |-lla
            |-lla.h
            |-lla.cpp
```