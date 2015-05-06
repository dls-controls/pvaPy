TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================


#=============================

LOADABLE_LIBRARY_HOST += easypva
LOADABLE_SHRLIB_PREFIX = 

#PROD_HOST_linux-x86_64 += testClient
PROD_HOST += $(PROD_HOST_$(T_A))

CXXFLAGS += -g  -I$(BOOST_DIR)/include $(PVA_PY_CPPFLAGS) 
LDFLAGS += $(PVA_PY_LDFLAGS)


easypva_SRCS += Union.cpp
easypva_SRCS += Channel.cpp
easypva_SRCS += Monitor.cpp
easypva_SRCS += ChannelTimeout.cpp
easypva_SRCS += FieldNotFound.cpp
easypva_SRCS += InvalidArgument.cpp
easypva_SRCS += InvalidDataType.cpp
easypva_SRCS += InvalidRequest.cpp
easypva_SRCS += InvalidState.cpp
easypva_SRCS += NtType.cpp
easypva_SRCS += ObjectNotFound.cpp
easypva_SRCS += PvaClient.cpp
easypva_SRCS += PvaException.cpp
easypva_SRCS += PvaExceptionTranslator.cpp
easypva_SRCS += PvaPyLogger.cpp
easypva_SRCS += PvAlarm.cpp
easypva_SRCS += PvBoolean.cpp
easypva_SRCS += PvByte.cpp
easypva_SRCS += PvDouble.cpp
easypva_SRCS += PvFloat.cpp
easypva_SRCS += PvInt.cpp
easypva_SRCS += PvLong.cpp
easypva_SRCS += PvObject.cpp
easypva_SRCS += PvProvider.cpp
easypva_SRCS += PvScalar.cpp
easypva_SRCS += PvScalarArray.cpp
easypva_SRCS += PvShort.cpp
easypva_SRCS += PvString.cpp
easypva_SRCS += PvTimeStamp.cpp
easypva_SRCS += PvUByte.cpp
easypva_SRCS += PvUInt.cpp
easypva_SRCS += PvULong.cpp
easypva_SRCS += PvUShort.cpp
easypva_SRCS += PvUtility.cpp
easypva_SRCS += PyPvDataUtility.cpp
easypva_SRCS += PyUtility.cpp
easypva_SRCS += RpcClient.cpp
easypva_SRCS += RpcTimeout.cpp
easypva_SRCS += StringUtility.cpp
easypva_SRCS += easypva.cpp

easypva_LIBS += pvData
easypva_LIBS += pvAccess
easypva_LIBS += nt
easypva_LIBS += easyPVA
easypva_LIBS += Com
USR_SYS_LIBS += $(BOOST_PYTHON_LIB)

testClient_SRCS += testClient.cpp
testClient_LIBS += easypva
testClient_LIBS += python
testClient_LIBS += boost_python
testClient_LIBS += pvData pvAccess nt easyPVA Com

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE


