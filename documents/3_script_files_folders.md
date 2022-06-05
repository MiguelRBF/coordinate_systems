0. [**README link**](./../README.md): Link to main README file.
1. [**Coordinate systems - Information**](./1_coordinate_systems_information.md): Link to 1_coordinate_systems_information. Description of the most commonly used coordinate systems.
2. [**Coordinate systems - Transformation**](./2_coordinate_systems_transformation.md): Link to 2_coordinate_systems_transformation. Description of the most commonly used transformation between coordinate systems.
3. [**Script files/folders**](./3_script_files_folders.md): Link to 2_script_files_folders. Description of the scripts inside the repository.
4. [**Documents of interest**](./4_documents_of_interest.md): Link to 3_documents_of_interest. Some documents of interest.
5. [**Webs of interest**](./5_link_to_webs_of_interest.md): Link to 4_link_to_webs_of_interest. Some links to webs of interest.
6. [**List of references**](./6_list_references.md): List with all the references.
<br/><br/>

# **3 Script files/folders**

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
|   |-2_coordinate_systems_transformation.md
|   |-3_script_files_folders.md
|   |-4_documents_of_interest.md
|   |-5_links_to_web_of_interest.md
|   |-6_list_references.md
|   |
|   |-images
|   |
|   |-pdf
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
    |   |-body.py
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
    |   |-body.h
    |   |-body.cpp
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
    |   |-BODY
    |   |   |-BODY.java
    |   |
    |   |-ECEF
    |   |   |-ECEF.java
    |   |
    |   |-ellipsoidDefinition
    |   |   |-Ellipsoid.java
    |   |
    |   |-ENU
    |   |   |-ENU.java
    |   |
    |   |-LLA
    |   |   |-LLA.java
    |   |
    |   |-MatVec
    |   |   |-MatVec.java
    |   |
    |   |-coordinate_systems_java_example.java
    |
    |-coolArduinoMap3D
        |
        |-coordinate_systems_example
        |   |-coordinate_systems_example.ino
        |
        |-libraries
            |
            |-body
            |   |-body.h
            |   |-body.cpp
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
            |   |-lla.h
            |   |-lla.cpp
            |
            |-multiplyMatVec
                |-multiplyMatVec.h
                |-multiplyMatVec.cpp

```
## **3.1 files inside COORDINATE_SYSTEMS**

### **3.1.1 coordinate_systems_example.py**
Example of use of the modules/functions inside the repository.

### **3.1.2 LICENSE**
License document.

### **3.1.3 README.md**
README document. Here is place all the important information about the repository.

## **3.2 documents**

### **3.2.1 Markdown documents README**
This are all the markdown documents linked to the README.md file
```
COORDINATE_SYSTEMS
|
|-documents
    |
    |-1_coordinate_systems_information.md
    |-2_coordinate_systems_transformation.md
    |-3_script_files_folders.md
    |-4_documents_of_interest.md
    |-5_links_to_web_of_interest.md
    |-6_list_references.md
```

### **3.2.2 images**
In this folder you will find the images of the repository. Some of them are used inside the documents linked to the README.md
```
COORDINATE_SYSTEMS
|
|-documents
    |
    |-images
```
### **3.2.3 pdf**

```
COORDINATE_SYSTEMS
|
|-documents
   |
   |-pdf
```
You will find further information about this folder at the following link:

- [**Documents of interest**](./3_documents_of_interest.md): Link to 3_documents_of_interest. Some documents of interest.

### licenses\geospace_code_pymap3d

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

## **3.3 scripts**
Now empty.

## **3.4 src/coolpymap3D**
Inside this folder you will find the modules used to do reference frames conversions. Python code.

### **3.4.1 ecef.py**
This module was created to transforms from ECEF (earth-centered, earth-fixed) frame to others.

### **3.4.2 eci.py**
This module was created to do transformations involving ECI (earth-centered inertial) reference frame.

### **3.4.3 ellipsoid.py**
This module was created to define the required ellipsoid for the LLA reference frames.

### **3.4.4 enu.py**
This module was created to transforms from ENU (East North Up) frame to others.

### **3.4.5 lla.py**
This module was created to transforms from LLA (Latitude Longitude Altitude) frame to others.

### **3.4.6 sidereal.py**
This module was created to manipulations of sidereal time.

### **3.4.7 timeconv.py**
This module was created to convert strings to datetime.

### **3.4.8 utils.py**
Some utility functions. All assume radians.

## **3.5 src/coolCppMap3D**
Inside this folder you will find the modules used to do reference frames conversions. C++ code.

## **3.6 src/coolOctaveMap3D**
Inside this folder you will find the modules used to do reference frames conversions. Octave code.

## **3.7 src/coolJavaMap3D**
Inside this folder you will find the modules used to do reference frames conversions. Java code.

## **3.8 src/coolArduinoMap3D**
Inside this folder you will find the modules used to do reference frames conversions. Arduino code.
