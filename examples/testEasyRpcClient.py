#!/usr/bin/env python

import easypva
import random

rpc = easypva.RpcClient('exampleHelloRPC')
request = easypva.PvObject({'value' : easypva.STRING})
request.set({'value' : "World"})
print "Sending request for exampleHelloRPC:"
print request

print "Got response:"
response = rpc.invoke(request)
print response
