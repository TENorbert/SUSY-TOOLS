#!/bin/tcsh

# This Small tool almost gave me the hwole day to know how to use it.

# It actually Puts the input root files in the way accepted  by CMS Modules:

# Author TEN

 sed -e s/"\/uscms_data"/"'file:\/uscms_data"/  -e  s/"root"/"root',"/  < ctau250.log >& ctauSim250.log&
