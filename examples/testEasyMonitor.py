#!/usr/bin/env python

import time
import random

from easypva import *

c = Channel('double01')
m = Monitor(c)
#m = Monitor(c,"value,alarm,timeStamp")
#m = Monitor(c,"value,alarm,timeStamp",False)
#m.start()
result = m.waitEvent(0.0)
print "result",result
if result==True :
    print m.getData()
    m.releaseEvent()
print "calling putDouble"
c.putDouble(1.0);
print "calling m.waitEvent"
result = m.waitEvent(1.0)
if result==False :
    print "failure"
    exit
print m.getData()
m.releaseEvent()
c.putDouble(2.0);
result = m.waitEvent(1.0)
if result==False :
    print "failure"
    exit
print m.getData()
m.releaseEvent()
res = m.poll();
if res==True :
    print "got an unexpected poll"
    m.releaseEvent()
print "following will throw"
try:
    m.releaseEvent()
except Exception, ex:
    print ex

print "all done"
m = None
c = None

    
