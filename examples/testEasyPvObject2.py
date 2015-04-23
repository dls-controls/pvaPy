#!/usr/bin/env python

from easypva import *

pvtemp = PvObject({ "double" : DOUBLE, "doubleArr" : [DOUBLE]})
print pvtemp
pv = PvObject({ "value" : pvtemp})
print pv
pv = PvObject({ "value" : { "UNION" : pvtemp }})
print pv
pv = PvObject({ "value" : { "UNION" : None }})
print pv
pv = PvObject({ "value" : { "[UNION]" : pvtemp }})
print pv
pv = PvObject({ "value" : { "[UNION]" : None }})
print pv
pv = PvObject({ "value" : { "UNION" : pvtemp },
    "alarm" : { "STRUCTURE" : "alarm"},
    "timeStamp" : { "STRUCTURE" : "timeStamp"}})
print pv
pv = PvObject({ "value" : { "STRUCTURE" : pvtemp },
    "alarm" : { "STRUCTURE" : "alarm"},
    "timeStamp" : { "STRUCTURE" : "timeStamp"}})
print pv
pv = PvObject({ "value" : { "[STRUCTURE]" : pvtemp },
    "alarm" : { "STRUCTURE" : "alarm"},
    "timeStamp" : { "STRUCTURE" : "timeStamp"}})
print pv
pv = PvObject({"value" : DOUBLE,
     "alarm" : { "STRUCTURE" : "alarm"},
    "timeStamp" : { "STRUCTURE" : "timeStamp"},
     "display" : { "STRUCTURE" : "display"},
     "control" : { "STRUCTURE" : "control"}})
print pv

pv = PvObject({ "value" : { "UNION" : pvtemp }})
isVariant = pv.unionIsVariant()
if isVariant==True :
    print channelName,"is not a regular union"
    exit
names = pv.unionGetFieldNames()
print "union fieldNames",names
value = pv.unionSelect(names[0])
value.setDouble(2.0)
print "after setDouble",pv
value = pv.unionSelect(names[1])
value.setScalarArray([1.0,2.0,3.0,4.0])
print "after setScalarArray",pv


pv = PvObject({ "value" : { "UNION" : None }})
isVariant = pv.unionIsVariant()
if isVariant==False :
    print channelName,"is not a variant union"
    exit
value = PvObject({ 'value' : STRING })
newval = "ccccccc"
value.setString(newval)
pv.unionSet(value)
print "putting",pv
value = PvObject({ 'value' : [STRING] })
newval = ["aaaa","bbbbb"]
value.setScalarArray(newval)
pv.unionSet(value)
print "putting",pv

