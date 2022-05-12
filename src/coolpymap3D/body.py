# --- Origin Body coordinate system ---
#--------------------------------------------
# Module name:      body.py
# Created by:       MiguelRBF
#--------------------------------------------
'''
This module was created to transforms from body reference frame to others.
'''

#### IMPORT STANDARD LIBRARIES ####
from math import pi

####  ####

#### IMPORT DOWNLOADED LIBRARIES ####
import numpy as np

####  ####

#### IMPORT MODULES ####

####  ####

#### VARIABLE DEFINITION ####

# The __all__ tells the semantically “public” names from the module.
# If there is a name in __all__, the users are expected to use it, 
# and they can expect that it will not change.
# https://appdividend.com/2021/05/09/what-is-python-__all__-and-how-to-use-it/
__all__ = [
    "body2ecef"
]

####  ####

#### FUNCTIONS DEFINITION ####

def body2ecef(
    xb: np.float64,
    yb: np.float64,
    zb: np.float64,
    x0b: np.float64,
    y0b: np.float64,
    z0b: np.float64,
    ib: np.float64,
    jb: np.float64,
    kb: np.float64,
    ):
    
    '''
    This function was created to change between Body coordinate system to 
    ECEF coordinate system (x, y, z).

    np arrays can be given as inputs.

    Parameters
    ----------
    xb
        target x body coordinate (meters)
    yb
        target y body coordinate (meters)
    zb
        target z body coordinate (meters)

    x0b
        x body coordinate origin (ecef reference, meters)
    y0b
        y body coordinate origin (ecef reference, meters)
    z0b
        z body coordinate origin (ecef reference, meters)

    ib
        x body axis unitary vector (ecef reference)
    jb
        y body axis unitary vector (ecef reference)
    kb
        z body axis unitary vector (ecef reference)


    Returns
    -------
    x = xyz[0]
        target x ECEF coordinate (meters)
    y = xyz[1]
        target y ECEF coordinate (meters)
    z = xyz[2]
        target z ECEF coordinate (meters)

    '''  

    # Get the rotation matrix R[θ]
    R = np.array([ib[0],jb[0],kb[0],
                  ib[1],jb[1],kb[1],
                  ib[2],jb[2],kb[2]], np.float64)
    R = R.reshape(3,3)

    # Get the length of input target coordinates array
    inputShape = xb.shape

    # Get body coordinate system origin
    body_origin = np.array([x0b[0], y0b[0], z0b[0]])

    # Define the output np array shape
    xyz = np.zeros((inputShape[0], 3), np.float64)

    # Loop for all the coordinates given as input
    for nCoor in range(inputShape[0]):

        # Get the body coordinates np array
        bodyCoor = np.array([xb[nCoor], yb[nCoor], zb[nCoor]])

        # Get the coordinates after rotation
        rotCoor = np.matmul(R, bodyCoor)

        # Compute the coordinates in the new reference frame (ecef)
        xyz[nCoor] = body_origin + rotCoor

    return xyz

####  ####

# End of document: body.py