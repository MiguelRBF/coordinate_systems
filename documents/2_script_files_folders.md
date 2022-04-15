# **2 Script files/folders**

0. [**README link**](./../README.md): Link to main README file.
1. [**Coordinate systems - Information**](./1_coordinate_systems_information.md): Link to 1_coordinate_systems_information. Description of the scripts inside the repository.
2. [**Script files/folders**](./2_script_files_folders.md): Link to 2_script_files_folders. Description of the scripts inside the repository.
3. [**Documents of interest**](./3_documents_of_interest.md): Link to 3_documents_of_interest. Some documents of interest.
4. [**Webs of interest**](./4_links_to_web_of_interest.md): Link to 4_links_to_web_of_interest. Some links to webs of interest.
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
|   |
|   |-images
|   |   |
|   |   |-3D_Spherical.png
|   |   |-ecef_enu_coordinate_systems.png
|   |   |-ellipsoid_parametric_euler_mono.png
|   |   |-geodetic_coordinates.png
|   |   |-geodetic_system.png
|   |   |-latitude_and_longitude_graticule_on_an_ellipsoid.png
|   |   |-Malla-Universal-Transversa-Mercator-UTM.jpg
|   |   |-Utm-zones.jpg
|   |   |-WGS84_ellipsoid.png
|   |
|   |-pdf
|       |
|       |-Capitulo_5_conversion_de_coordenadas.pdf
|       |-Transforming Cartesian Coordinates to Geographical coordinates.pdf
|       |-TRF_Altamimi.pdf
|
|- scripts
|   |
|   |-¿coordinate_systems_example.py?
|   |-¿Best way to import the modules placing the script file here?
|
|- src
    |
    |-coolpymap3D
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
Further information about this folder at the following link:
- [**Documents of interest**](./3_documents_of_interest.md): Link to 3_documents_of_interest. Some documents of interest.

## **2.3 scripts**
Now empty.

## **2.4 src/coolpymap3D**
Inside this folder you will find the modules used to do reference frames conversions.

```
COORDINATE_SYSTEMS
|
|- src
    |
    |-coolpymap3D
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
