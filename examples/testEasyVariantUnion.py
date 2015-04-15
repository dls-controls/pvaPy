#!/usr/bin/env python

from easypva import *

print '****************************'
print 'Testing variant union'
channelName = "exampleVariantUnion"
c = Channel(channelName)
pv = c.get()
print "original value",pv
isVariant = pv.unionIsVariant()
if isVariant==False :
    print channelName,"is not a variant union"
    exit
value = PvObject({ 'value' : STRING })
newval = "ccccccc"
value.setString(newval)
pv.unionSet(value)
print "putting",pv
c.put(pv)
pv = c.get()
print "received",pv
retval = pv.unionGet().getString();
if newval!=retval :
    print "newval",newval,"not equal retval",retval
value = PvObject({ 'value' : [STRING] })
newval = ["aaaa","bbbbb"]
value.setScalarArray(newval)
pv.unionSet(value)
print "putting",pv
c.put(pv)
pv = c.get()
print "received",pv
retval = pv.unionGet().getScalarArray();
if newval!=retval :
    print "newval",newval,"not equal retval",retval
