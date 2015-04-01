#!/usr/bin/env python

from easypva import *

c = Channel("examplePowerSupply")
pvout =  PvObject({
     "power" : { "value" : DOUBLE},
     "voltage" : { "value" : DOUBLE}
})
pvout.setDouble("power.value",1.0)
pvout.setDouble("voltage.value",2.0)
c.put(pvout,"power.value,voltage.value")
pvin = c.get("current.value")
print "sent ",pvout
print "receved ",pvin
value = { "power" : { "value" : 4.0} , "voltage" : { "value" : 6.0} }
pvout.set(value)
c.put(pvout,"power.value,voltage.value")
pvin = c.get("current.value")
print "sent ",pvout
print "receved ",pvin
value["power"]["value"] = 5.0
value["voltage"]["value"] = 5.0
pvout.set(value)
c.put(pvout,"power.value,voltage.value")
pvin = c.get("current.value")
print "sent ",pvout
print "receved ",pvin

