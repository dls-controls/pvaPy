#!/usr/bin/env python

from easypva import *

print '****************************'
print 'Testing union array'
c = Channel('exampleRegularUnionArray')
pv = c.get()
print "original value",pv
isVariant = pv.unionArrayIsVariant()
if isVariant==True :
    print channelName,"is not a regular union"
    exit
names = pv.unionArrayGetFieldNames()
print "union fieldNames",names
unionArray = []
value = pv.unionArrayCreateElement(names[0])
value.setString("new value")
unionArray.append(value)
value = pv.unionArrayCreateElement(names[1])
value.setScalarArray(["xxxxxx","yyyyyyyy"])
unionArray.append(value)
pv.unionArraySet(unionArray)
print "putting",pv
c.put(pv)
pv = c.get()
print "received",pv
unionArray = pv.unionArrayGet()
unionArray[0].setString("last value")
unionArray[1].setScalarArray(["aaa","bbb"])
pv.unionArraySet(unionArray)
print "putting",pv
c.put(pv)
pv = c.get()
print "received",pv
