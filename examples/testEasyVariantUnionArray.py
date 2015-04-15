#!/usr/bin/env python

from easypva import *

print '****************************'
print 'Testing variant union array'
c = Channel('exampleVariantUnionArray')
pv = c.get()
print pv
isVariant = pv.unionArrayIsVariant()
if isVariant==False :
    print channelName,"is not a variant union array"
    exit
unionArray = []
value = PvObject({ 'value' : STRING })
value.setString("ccccccc")
unionArray.append(value)
value = PvObject({ 'value' : [STRING] })
value.setScalarArray(["xxxxxx","yyyyyy"])
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
