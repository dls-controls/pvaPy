Comments about easypva vs pvaccess
=================================

These comments are mostly for Sinisa Veseli.

In branch feature/easyPVACPP the directory structure is as follows:

    src
        pvaccess
        easypva
    examples

* pvaccess has no changes.
* easypva has code that has been copied from pvaccess and modified.
* examples has new files with names \*Easy\*.py. Old files are unmodified

This was done so that it is easier to compare existing code with
proposed changes and additions.

It is NOT meant to be the final structure for the code.
Assuming Sinisa agrees with many of the changes, I see some possibilities:

* replace pvaccess with easypva, i. e. only easypva exists.
* keep both with a warning that pvaccess will become deprecated
* rename easypva to pvapy.
* ???

The rest of these notes describe what has been done in easypva.

easypva - general comments
-------

The following is a summary of changes:

* All code has been put in namespace epics::pvaPy
* PvObject now supports union and unionArray
* Channel now uses easyPVA
* Monitors are implemented via easyMonitor
* RpcClent is like pvaccess
* normativeTypes has not been implemented.
* RpcServer has not been implemented.
* For byte, ubyte, ..., the typedefs epics::pvData::int8, etc are use almost
everywhere.
The exceptions I know about are PvScalar and PyUtility.cpp
* easypva.cpp The doc strings have been broken up into multiple lines.
* PVA_RPC_API_VERSION no longer supported.

I have not had time to think about normativeTypes and RpcServer.

Also support should be developed for channelArray, channelPutGet, and multiChannel.


easypva - PyObject
------------------

This is similar to what is in pvaccess except for:

* namespace is now epics::pvaPy
* now supports union and unionArray
* uses pvData definitions for int8, ..., uint64 almost everywhere.

pvaPy only wraps the pvData data interfaces and not
the introspection interfaces.
Thus the support for union uses the following convention:
for python access to the union fields:

* For variant unions the python code can create PvObjects itself
but for regular unions the PvObject are always created by the C++ code.
* Values for a union field are always presented to the python code
as a structure with a single subfield with the name value.

A regular union looks like:

     structure
         union value
     
A variant union looks like:
     
     structure
         any value


Look at testEasyPvObject2.py for an example and at Channel.h and Channel.cpp
to see how union is impemented.

<b>Suggestion:</b>

* A PvObject is always a wapper for a PVStructure.
So rename PvObject to Structure.
In the C++ code the name PVAPYStructure can be used.
This is similar to PVAPYMonitor and Monitor.
* Put PvBoolean,... PvScalarArray code in PVAPYStructure.h and PVAPYStructure.cpp instead of separate files.

easypva - Channel
------------------
:
The main changes to Channel are:

* Monitor is now handled by class Monitor.
* Channel now uses easyPVA instead of implementing the channel methods itself.
* The method names have been changed for the boost::python Channel class in easypva.cpp.

easypva - Monitor
------------------


Instead of being implemented by Channel it is now a separate class.
To the python client the name is Monitor.
In the C++ code it is PVAPYMonitor.
This is so that there is no conflict with class Monitor in pvData.

Monitor does not implement subscribe like the original Channel did.
My thought is that if a python client wants to do this it
can create a python thead and in it call waitEvent.

Monitor is implemented via easyMonitor.

easypva - easypva.cpp
---------------------

I spent a lot of time on this since it was a chance to come up to speed on
boost::python.
It has many changes from pvaaccess.cpp.

Look in particular look at the implementation of class Channel.

* I think it is easier to understand
then using static_cast for the method definitions.
This is the class on which I spent a lot of time.
* The doc strings for the Channel class has been changed.
Take a look and see what You think.
* Only putObject, putList, putDouble and putString  have two python names.
Note that pvaccess.cpp also has two python names for putByte, etc.
But the put method for all numeric scalar types will always call putDouble.


examples - new for easypva
-------------------------

testEasyPut.py has the changes

* import is from easypva instead of pvaccess
* test for string resets value to original.
If this is not done and the test is run many times it will fail
because it is a V3 channel which limits the array length.
* chr and ord are now longer used. Note that use of chr is NOT the same as byte.
* added tests for long and unsigned long

The other tests are:

* testEasyPvObject.py is identical to testPvObject.py except for import
* testEasyRpcClient.py acceses exampleHelloRPC from test database.
* testEasyMonitor.py accesses new Monitor class.
* testEasyPvObject2.py tests union and arrays.
* testEasyUnion.py accesses union in test database.
* testEasyUnionArray.py accesses union array in test database.
* testEasyVariantUnion.py accesses variant union in test database.
* testEasyVariantUnionArray.py accesses variant union in test database.


NOTE that the union tests required the latest exampleDatabaseEasyPVA.zip
from pvDatabaseCPP.
