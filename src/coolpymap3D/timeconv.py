# Copyright (c) 2014-2018 Michael Hirsch, Ph.D.
# --- Convert strings to datetime ---
#--------------------------------------------
# Module name:      timeconv.py
# Created by:       geospace-code/MiguelRBF
#--------------------------------------------
'''
This module was created to convert strings to datetime.
'''

#### IMPORT STANDARD LIBRARIES ####
from datetime import datetime

####  ####

#### IMPORT DOWNLOADED LIBRARIES ####
try:
    from dateutil.parser import parse
except ImportError:
    parse = None  # type: ignore
try:
    import numpy as np
except ImportError:
    np = None  # type: ignore


####  ####

#### IMPORT MODULES ####
from .timeconv import str2dt

####  ####

#### VARIABLE DEFINITION ####

# The __all__ tells the semantically “public” names from the module.
# If there is a name in __all__, the users are expected to use it, 
# and they can expect that it will not change.
# https://appdividend.com/2021/05/09/what-is-python-__all__-and-how-to-use-it/
__all__ = ["str2dt"]

####  ####

#### FUNCTIONS DEFINITION ####
def str2dt(time: datetime) -> datetime:
    """
    Converts times in string or list of strings to datetime(s)
    Parameters
    ----------
    time : str or datetime.datetime or numpy.datetime64
    Results
    -------
    t : datetime.datetime
    """
    if isinstance(time, datetime):
        return time
    elif isinstance(time, str):
        if parse is None:
            raise TypeError("expected datetime")
        return parse(time)
    elif np is not None and isinstance(time, np.datetime64):
        return time.astype(datetime)
    else:  # some sort of iterable
        try:
            if isinstance(time[0], datetime):
                return time
            elif np is not None and isinstance(time[0], np.datetime64):
                return time.astype(datetime)
            elif isinstance(time[0], str):
                if parse is None:
                    raise TypeError("expected datetime")
                return [parse(t) for t in time]
        except (IndexError, TypeError):
            pass

        # last resort--assume pandas/xarray

        return time.values.astype("datetime64[us]").astype(datetime)

####  ####

# End of document: timeconv.py