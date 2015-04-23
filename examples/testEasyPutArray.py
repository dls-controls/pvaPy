#!/usr/bin/env python

from easypva import Channel

print "----- exampleDoubleArray---"
c = Channel('exampleDoubleArray')
pv = c.get();
print pv
c.put([1.0,2.0,3.0])
pv = c.get();
print pv
print "----- exampleStringArray---"
c = Channel('exampleStringArray')
pv = c.get();
print pv
c.put(['one','two','three'])
pv = c.get();
print pv

