#!/usr/bin/env python

from easypva import *

print "for contrast first show non union"
alarm = PvAlarm();
pv = PvObject({ "value" : DOUBLE, "alarm" : alarm } )
print "pv",pv
print "dictionary",pv.get()
print "introspection",pv.getStructureDict()


print "\ntest variant union"
union = Union()
print "Union()\n",union
pv = PvObject({ "value" : union})
print "pv",pv
print "dictionary",pv.get()
print "introspection",pv.getStructureDict()
isVariant = pv.unionIsVariant()
if isVariant==False :
    print channelName,"is not a variant union"
    exit
value = PvObject({ 'value' : STRING })
newval = "ccccccc"
value.setString(newval)
pv.unionSet(value)
print "after setString",pv
print "dictionary",pv.get()
value = PvObject({ 'value' : [STRING] })
newval = ["aaaa","bbbbb"]
value.setScalarArray(newval)
pv.unionSet(value)
print "after setScalarArray",pv
print "dictionary",pv.get()


print "\ntest regular union"
pvtemp = PvObject({ "double" : DOUBLE, "doubleArr" : [DOUBLE]})
union = Union(pvtemp)
print "Union(pvtemp)\n",union
pv = PvObject({ "value" : union})
print "pv",pv
print "dictionary",pv.get()
print "introspection",pv.getStructureDict()
isVariant = pv.unionIsVariant()
if isVariant==True :
    print channelName,"is a variant array"
    exit
names = pv.unionGetFieldNames()
print "union fieldNames",names
value = pv.unionSelect(names[0])
value.setDouble(2.0)
print "after setDouble",pv
print "dictionary",pv.get()
value = pv.unionSelect(names[1])
value.setScalarArray([1.0,2.0,3.0,4.0])
print "after setScalarArray",pv
print "dictionary",pv.get()

print "\ntest variant union array"
union = Union()
pv = PvObject({ "value" : [union]})
print "pv",pv
print "dictionary",pv.get()
print "introspection",pv.getStructureDict()
isVariant = pv.unionArrayIsVariant()
if isVariant==False :
    print channelName,"is not a variant union"
    exit
values = []
value = PvObject({ 'value' : STRING })
newval = "ccccccc"
value.setString(newval)
values.append(value)
value = PvObject({ 'value' : [STRING] })
newval = ["aaaa","bbbbb"]
value.setScalarArray(newval)
values.append(value)
pv.unionArraySet(values)
print "after unionArraySet",pv
print "dictionary",pv.get()

print "\ntest regular union array"
pvtemp = PvObject({ "double" : DOUBLE, "doubleArr" : [DOUBLE]})
union = Union(pvtemp)
pv = PvObject({ "value" : [union]})
print "pv",pv
print "dictionary",pv.get()
print "introspection",pv.getStructureDict()
isVariant = pv.unionArrayIsVariant()
if isVariant==True :
    print channelName,"is a variant array"
    exit
names = pv.unionArrayGetFieldNames()
print "unionArray fieldNames",names
unionArray = []
value = pv.unionArrayCreateElement(names[0])
value.setDouble(10.0)
unionArray.append(value)
value = pv.unionArrayCreateElement(names[1])
value.setScalarArray([1.0,2.0,3.0])
unionArray.append(value)
print "unionArray","[",unionArray[0].getDouble(),",",unionArray[1].getScalarArray(),"]"
pv.unionArraySet(unionArray)
print "after unionArraySet",pv
print "dictionary",pv.get()



