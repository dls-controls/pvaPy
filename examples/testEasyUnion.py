#!/usr/bin/env python

from easypva import Channel

print '****************************'
print 'Testing union'
c = Channel('exampleRegularUnion')
pv = c.get()
print "original value",pv
isVariant = pv.unionIsVariant()
if isVariant==True :
    print channelName,"is not a regular union"
    exit
names = pv.unionGetFieldNames()
print "union fieldNames",names
value = pv.unionSelect(names[0])
value.setString("new value")
value = pv.unionGet()
print "putting",pv
c.put(pv)
pv = c.get()
print "received",pv
value = pv.unionSelect(names[1])
value.setScalarArray(["aaaa","bbbbb","ccccc"])
print "putting",pv
c.put(pv)
pv = c.get()
print "received",pv
