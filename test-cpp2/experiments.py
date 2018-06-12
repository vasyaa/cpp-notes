#!/usr/bin/env python

from pandas import HDFStore
import os
import time
import pandas as pd

fd = HDFStore("data.hdf5")

# ts = pd.Series([10,20,30,40,50], index = [1,2,3,4,5])
# df = pd.DataFrame(ts)
# fd['df'] = df
# fd['ts'] = ts

ts = fd['ts']

print(ts)
