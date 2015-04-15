#include "PyPvDataUtility.h"
#include "PvType.h"
#include "FieldNotFound.h"
#include "InvalidDataType.h"
#include <pv/pvAccess.h>

using std::tr1::static_pointer_cast;
using namespace epics::pvData;
using namespace epics::pvAccess;
using namespace std;

// Scalar array utilities
namespace PyPvDataUtility
{

//
// Checks
//
void checkFieldExists(const std::string& fieldName, const PVStructurePtr& pvStructurePtr)
{
    PVFieldPtr pvFieldPtr = pvStructurePtr->getSubField(fieldName);
    if (!pvFieldPtr) {
        throw FieldNotFound("Object does not have field " + fieldName);
    }
}

//
// Field retrieval
//
FieldConstPtr getField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr)
{
    PVFieldPtr pvFieldPtr = pvStructurePtr->getSubField(fieldName);
    if (!pvFieldPtr) {
        throw FieldNotFound("Object does not have field " + fieldName);
    }
    return pvFieldPtr->getField();
}

ScalarConstPtr getScalarField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr)
{
    FieldConstPtr fieldPtr = getField(fieldName, pvStructurePtr);
    ScalarConstPtr scalarPtr = std::tr1::static_pointer_cast<const Scalar>(fieldPtr);
    if (!scalarPtr) {
        throw InvalidDataType("Field " + fieldName + " is not a scalar");
    }
    return scalarPtr;
}

PVScalarArrayPtr getScalarArrayField(const std::string& fieldName, ScalarType scalarType, const PVStructurePtr& pvStructurePtr)
{
    PVScalarArrayPtr pvScalarArrayPtr = pvStructurePtr->getScalarArrayField(fieldName, scalarType);
    if (!pvScalarArrayPtr) {
        throw FieldNotFound("Object does not have scalar array field %s of type %d", fieldName.c_str(), scalarType);
    }
    return pvScalarArrayPtr; 
}

StructureConstPtr getStructure(const std::string& fieldName, const PVStructurePtr& pvStructurePtr)
{
    FieldConstPtr fieldPtr = getField(fieldName, pvStructurePtr);
    StructureConstPtr structurePtr = std::tr1::static_pointer_cast<const Structure>(fieldPtr);
    if (!structurePtr) {
        throw InvalidDataType("Field " + fieldName + " is not a structure");
    }
    return structurePtr;
}

PVStructurePtr getStructureField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr)
{
    PVStructurePtr pvStructurePtr2 = pvStructurePtr->getStructureField(fieldName);
    if (!pvStructurePtr2) {
        throw FieldNotFound("Object does not have structure field " + fieldName);
    }
    return pvStructurePtr2;
}

PVStructureArrayPtr getStructureArrayField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr)
{
    PVStructureArrayPtr pvStructureArrayPtr = pvStructurePtr->getStructureArrayField(fieldName);
    if (!pvStructureArrayPtr) {
        throw FieldNotFound("Object does not have structure array field " + fieldName);
    }
    return pvStructureArrayPtr;
}

PVUnionPtr getUnionField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr)
{
    PVUnionPtr pvUnionPtr = pvStructurePtr->getSubField<PVUnion>(fieldName);
    if (!pvUnionPtr) {
        throw FieldNotFound("Object does not have union field " + fieldName);
    }
    return pvUnionPtr;
}

PVUnionArrayPtr getUnionArrayField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr)
{
    PVUnionArrayPtr pvUnionArrayPtr = pvStructurePtr->getSubField<PVUnionArray>(fieldName);
    if (!pvUnionArrayPtr) {
        throw FieldNotFound("Object does not have union array field " + fieldName);
    }
    return pvUnionArrayPtr;
}

PVBooleanPtr getBooleanField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVBooleanPtr fieldPtr = pvStructurePtr->getBooleanField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have boolean field " + fieldName);
    }
    return fieldPtr;
}

PVBytePtr getByteField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVBytePtr fieldPtr = pvStructurePtr->getByteField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have byte field " + fieldName);
    }
    return fieldPtr;
}

PVUBytePtr getUByteField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVUBytePtr fieldPtr = pvStructurePtr->getUByteField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have unsigned byte field " + fieldName);
    }
    return fieldPtr;
}

PVShortPtr getShortField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVShortPtr fieldPtr = pvStructurePtr->getShortField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have short field " + fieldName);
    }
    return fieldPtr;
}

PVUShortPtr getUShortField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVUShortPtr fieldPtr = pvStructurePtr->getUShortField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have unsigned short field " + fieldName);
    }
    return fieldPtr;
}

PVIntPtr getIntField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVIntPtr fieldPtr = pvStructurePtr->getIntField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have int field " + fieldName);
    }
    return fieldPtr;
}

PVUIntPtr getUIntField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVUIntPtr fieldPtr = pvStructurePtr->getUIntField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have unsigned int field " + fieldName);
    }
    return fieldPtr;
}

PVLongPtr getLongField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVLongPtr fieldPtr = pvStructurePtr->getLongField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have long field " + fieldName);
    }
    return fieldPtr;
}

PVULongPtr getULongField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVULongPtr fieldPtr = pvStructurePtr->getULongField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have unsigned long field " + fieldName);
    }
    return fieldPtr;
}

PVFloatPtr getFloatField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVFloatPtr fieldPtr = pvStructurePtr->getFloatField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have float field " + fieldName);
    }
    return fieldPtr;
}

PVDoublePtr getDoubleField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVDoublePtr fieldPtr = pvStructurePtr->getDoubleField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have double field " + fieldName);
    }
    return fieldPtr;
}

PVStringPtr getStringField(const std::string& fieldName, const PVStructurePtr& pvStructurePtr) 
{
    PVStringPtr fieldPtr = pvStructurePtr->getStringField(fieldName);
    if (!fieldPtr) {
        throw FieldNotFound("Object does not have string field " + fieldName);
    }
    return fieldPtr;
}

//
// Field type retrieval
//
Type getFieldType(const std::string& fieldName, const PVStructurePtr& pvStructurePtr)
{
    FieldConstPtr fieldPtr = getField(fieldName, pvStructurePtr);
    return fieldPtr->getType();
}

ScalarType getScalarType(const std::string& fieldName, const PVStructurePtr& pvStructurePtr)
{
    ScalarConstPtr scalarPtr = getScalarField(fieldName, pvStructurePtr);
    return scalarPtr->getScalarType();
}

ScalarType getScalarArrayType(const std::string& fieldName, const PVStructurePtr& pvStructurePtr)
{
    FieldConstPtr fieldPtr = getField(fieldName, pvStructurePtr);
    Type type = fieldPtr->getType();
    if (type != scalarArray) {
        throw InvalidDataType("Object does not have scalar array field " + fieldName);
    }
    ScalarArrayConstPtr scalarArrayPtr = std::tr1::static_pointer_cast<const ScalarArray>(fieldPtr);
    ScalarType scalarType = scalarArrayPtr->getElementType();
    return scalarType;
}

//
// Conversion PY object => PV Scalar
//
void pyObjectToScalarField(const boost::python::object& pyObject, const std::string& fieldName, PVStructurePtr& pvStructurePtr)
{
    ScalarType scalarType = getScalarType(fieldName, pvStructurePtr);
    switch (scalarType) {
        case pvBoolean: {
            PVBooleanPtr fieldPtr = pvStructurePtr->getBooleanField(fieldName);
            bool value = PyUtility::extractValueFromPyObject<bool>(pyObject);
            fieldPtr->put(static_cast<boolean>(value));
            break;
        }
        case pvByte: {
            PVBytePtr fieldPtr = pvStructurePtr->getByteField(fieldName);
            char value = PyUtility::extractValueFromPyObject<char>(pyObject);
            fieldPtr->put(static_cast<int8>(value));
            break;
        }
        case pvUByte: {
            PVUBytePtr fieldPtr = pvStructurePtr->getUByteField(fieldName);
            unsigned char value = PyUtility::extractValueFromPyObject<unsigned char>(pyObject);
            fieldPtr->put(static_cast<uint8>(value));
            break;
        }
        case pvShort: {
            PVShortPtr fieldPtr = pvStructurePtr->getShortField(fieldName);
            short value = PyUtility::extractValueFromPyObject<short>(pyObject);
            fieldPtr->put(static_cast<int16>(value));
            break;
        }
        case pvUShort: {
            PVUShortPtr fieldPtr = pvStructurePtr->getUShortField(fieldName);
            unsigned short value = PyUtility::extractValueFromPyObject<unsigned short>(pyObject);
            fieldPtr->put(static_cast<uint16>(value));
            break;
        }
        case pvInt: {
            PVIntPtr fieldPtr = pvStructurePtr->getIntField(fieldName);
            int value = PyUtility::extractValueFromPyObject<int>(pyObject);
            fieldPtr->put(static_cast<int32>(value));
            break;
        }
        case pvUInt: {
            PVUIntPtr fieldPtr = pvStructurePtr->getUIntField(fieldName);
            unsigned int value = PyUtility::extractValueFromPyObject<unsigned int>(pyObject);
            fieldPtr->put(static_cast<uint32>(value));
            break;
        }
        case pvLong: {
            PVLongPtr fieldPtr = pvStructurePtr->getLongField(fieldName);
            long long value = PyUtility::extractValueFromPyObject<long long>(pyObject);
            fieldPtr->put(static_cast<int64>(value));
            break;
        }
        case pvULong: {
            PVULongPtr fieldPtr = pvStructurePtr->getULongField(fieldName);
            unsigned long long value = PyUtility::extractValueFromPyObject<unsigned long long>(pyObject);
            fieldPtr->put(static_cast<uint64>(value));
            break;
        }
        case pvFloat: {
            PVFloatPtr fieldPtr = pvStructurePtr->getFloatField(fieldName);
            float value = PyUtility::extractValueFromPyObject<float>(pyObject);
            fieldPtr->put(value);
            break;
        }
        case pvDouble: {
            PVDoublePtr fieldPtr = pvStructurePtr->getDoubleField(fieldName);
            double value = PyUtility::extractValueFromPyObject<double>(pyObject);
            fieldPtr->put(value);
            break;
        }
        case pvString: {
            PVStringPtr fieldPtr = pvStructurePtr->getStringField(fieldName);
            std::string value = PyUtility::extractValueFromPyObject<std::string>(pyObject);
            fieldPtr->put(value);
            break;
        }
        default: {
            throw PvaException("Unrecognized scalar type: %d", scalarType);
        }
    }
}

//
// Conversion PY object => PV Scalar Array
//
void pyObjectToScalarArrayField(const boost::python::object& pyObject, const std::string& fieldName, PVStructurePtr& pvStructurePtr)
{
    boost::python::list pyList = PyUtility::extractValueFromPyObject<boost::python::list>(pyObject);
    pyListToScalarArrayField(pyList, fieldName, pvStructurePtr);
}

//
// Conversion PY object => PV Structure
//
void pyObjectToStructureField(const boost::python::object& pyObject, const std::string& fieldName, PVStructurePtr& pvStructurePtr)
{
    boost::python::dict pyDict = PyUtility::extractValueFromPyObject<boost::python::dict>(pyObject);
    pyDictToStructureField(pyDict, fieldName, pvStructurePtr);
}

//
// Conversion PY object => PV Structure Array
//
void pyObjectToStructureArrayField(const boost::python::object& pyObject, const std::string& fieldName, PVStructurePtr& pvStructurePtr)
{
    boost::python::list pyList = PyUtility::extractValueFromPyObject<boost::python::list>(pyObject);
    pyListToStructureArrayField(pyList, fieldName, pvStructurePtr);
}

//
// Conversion PY object => PV Union
//
void pyObjectToUnionField(const boost::python::object& pyObject, const std::string& fieldName, PVStructurePtr& pvStructurePtr)
{
    boost::python::dict pyDict = PyUtility::extractValueFromPyObject<boost::python::dict>(pyObject);
    pyDictToUnionField(pyDict, fieldName, pvStructurePtr);
}

//
// Conversion PY object => PV Union Array
//
void pyObjectToUnionArrayField(const boost::python::object& pyObject, const std::string& fieldName, PVStructurePtr& pvStructurePtr)
{
    boost::python::list pyList = PyUtility::extractValueFromPyObject<boost::python::list>(pyObject);
    pyListToUnionArrayField(pyList, fieldName, pvStructurePtr);
}

//
// Conversion PV Scalar Array => PY List
//
void scalarArrayFieldToPyList(const std::string& fieldName, const PVStructurePtr& pvStructurePtr, boost::python::list& pyList)
{
    ScalarType scalarType = getScalarArrayType(fieldName, pvStructurePtr);
    PVScalarArrayPtr pvScalarArrayPtr = pvStructurePtr->getScalarArrayField(fieldName, scalarType);
    switch (scalarType) {
        case pvBoolean: {
            scalarArrayToPyList<PVBooleanArray, boolean>(pvScalarArrayPtr, pyList);
            break;
        }
        case pvByte: {
            scalarArrayToPyList<PVByteArray, int8>(pvScalarArrayPtr, pyList);
            break;
        }
        case pvUByte: {
            scalarArrayToPyList<PVUByteArray, uint8>(pvScalarArrayPtr, pyList);
            break;
        }
        case pvShort: {
            scalarArrayToPyList<PVShortArray, int16>(pvScalarArrayPtr, pyList);
            break;
        }
        case pvUShort: {
            scalarArrayToPyList<PVUShortArray, uint16>(pvScalarArrayPtr, pyList);
            break;
        }
        case pvInt: {
            scalarArrayToPyList<PVIntArray, int32>(pvScalarArrayPtr, pyList);
            break;
        }
        case pvUInt: {
            scalarArrayToPyList<PVUIntArray, uint32>(pvScalarArrayPtr, pyList);
            break;
        }
        case pvLong: {
            scalarArrayToPyList<PVLongArray, int64>(pvScalarArrayPtr, pyList);
            break;
        }
        case pvULong: {
            scalarArrayToPyList<PVULongArray, uint64>(pvScalarArrayPtr, pyList);
            break;
        }
        case pvFloat: {
            scalarArrayToPyList<PVFloatArray, float>(pvScalarArrayPtr, pyList);
            break;
        }
        case pvDouble: {
            scalarArrayToPyList<PVDoubleArray, double>(pvScalarArrayPtr, pyList);
            break;
        }
        case pvString: {
            scalarArrayToPyList<PVStringArray, std::string>(pvScalarArrayPtr, pyList);
            break;
        }
        default: {
            throw PvaException("Unrecognized scalar type: %d", scalarType);
        }
    }
}

//
// Conversion PY List => PV Scalar Array
//
void pyListToScalarArrayField(const boost::python::list& pyList, const std::string& fieldName, PVStructurePtr& pvStructurePtr) 
{
    ScalarType scalarType = getScalarArrayType(fieldName, pvStructurePtr);
    switch (scalarType) {
        case pvBoolean: {
            pyListToScalarArrayField<PVBooleanArray, boolean, bool>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        case pvByte: {
            pyListToScalarArrayField<PVByteArray, int8, char>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        case pvUByte: {
            pyListToScalarArrayField<PVUByteArray, uint8, unsigned char>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        case pvShort: {
            pyListToScalarArrayField<PVShortArray, int16, short>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        case pvUShort: {
            pyListToScalarArrayField<PVUShortArray, uint16, unsigned short>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        case pvInt: {
            pyListToScalarArrayField<PVIntArray, int32, int>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        case pvUInt: {
            pyListToScalarArrayField<PVUIntArray, uint32, unsigned int>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        case pvLong: {
            pyListToScalarArrayField<PVLongArray, int64, long long>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        case pvULong: {
            pyListToScalarArrayField<PVULongArray, uint64, unsigned long long>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        case pvFloat: {
            pyListToScalarArrayField<PVFloatArray, float, float>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        case pvDouble: {
            pyListToScalarArrayField<PVDoubleArray, double, double>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        case pvString: {
            pyListToScalarArrayField<PVStringArray, std::string, std::string>(pyList, fieldName, scalarType, pvStructurePtr);
            break;
        }
        default: {
            throw PvaException("Unrecognized scalar type: %d", scalarType);
        }
    }
}


//
// Conversion PY {} => PV Structure
//
void pyDictToStructure(const boost::python::dict& pyDict, PVStructurePtr& pvStructurePtr)
{
    boost::python::list keys = pyDict.keys();
    for (int i = 0; i < boost::python::len(keys); i++) {
        boost::python::object keyObject = keys[i];
        boost::python::extract<std::string> keyExtract(keyObject);
        std::string key;
        if (keyExtract.check()) {
            key = keyExtract();
        }
        else {
            throw InvalidDataType("Dictionary key must be a string");
        }

        // Got key/field name, find it in pv structure
        FieldConstPtr fieldPtr = getField(key, pvStructurePtr);
        Type type = fieldPtr->getType();
        switch (type) {
            case scalar: {
                pyObjectToScalarField(pyDict[keyObject], key, pvStructurePtr);
                break;
            }
            case structure: {
                pyObjectToStructureField(pyDict[keyObject], key, pvStructurePtr);
                break;
            }
            case scalarArray: {
                pyObjectToScalarArrayField(pyDict[keyObject], key, pvStructurePtr);
                break;
            }
            case structureArray: {
                pyObjectToStructureArrayField(pyDict[keyObject], key, pvStructurePtr);
                break;
            }
            case union_: {
                pyObjectToUnionField(pyDict[keyObject], key, pvStructurePtr);
                break;
            }
            case unionArray: {
                pyObjectToUnionArrayField(pyDict[keyObject], key, pvStructurePtr);
                break;
            }
            default: {
                throw PvaException("Unrecognized field type: %d", type);
            }
        } 
    }    
}

void pyDictToStructureField(const boost::python::dict& pyDict, const std::string& fieldName, PVStructurePtr& pvStructurePtr)
{
    PVStructurePtr pvStructurePtr2 = getStructureField(fieldName, pvStructurePtr);
    pyDictToStructure(pyDict, pvStructurePtr2);
}

void pyDictToUnionField(const boost::python::dict& pyDict, const std::string& fieldName, epics::pvData::PVStructurePtr& pvStructurePtr)
{
    PVUnionPtr pvUnion = pvStructurePtr->getSubField<PVUnion>(fieldName);
    if(!pvUnion)  throw PvaException("field is not a union");
    throw PvaException("pyDictToUnionField not implemented");
}

void pyListToUnionArrayField(const boost::python::list& pyList, const std::string& fieldName, PVStructurePtr& pvStructurePtr)
{
    PVUnionArrayPtr pvUnionArray = pvStructurePtr->getSubField<PVUnionArray>(fieldName);
    if(!pvUnionArray) throw PvaException("field is not a union array");
    throw PvaException("pyListToUnionArrayField not implemented");
}

//
// Conversion PY [{}] => PV Structure Array
//
void pyListToStructureArrayField(const boost::python::list& pyList, const std::string& fieldName, PVStructurePtr& pvStructurePtr)
{
    PVStructureArrayPtr pvStructureArrayPtr = getStructureArrayField(fieldName, pvStructurePtr);
    StructureArrayConstPtr structureArrayPtr = pvStructureArrayPtr->getStructureArray();
    StructureConstPtr structurePtr = structureArrayPtr->getStructure();
    int listSize = boost::python::len(pyList);
    PVStructureArray::svector pvStructures(listSize);
    for (int i = 0; i < listSize; i++) {
        boost::python::extract<boost::python::dict> dictExtract(pyList[i]);
        if (dictExtract.check()) {
            boost::python::dict pyDict = dictExtract();
            PVStructurePtr pvStructure = getPVDataCreate()->createPVStructure(structurePtr);
            pyDictToStructure(pyDict, pvStructure);
            pvStructures[i] = pvStructure;
        }
        else {
            throw InvalidDataType("Invalid data type for element %d", i);
        }
    }
    pvStructureArrayPtr->setCapacity(listSize);
    pvStructureArrayPtr->replace(freeze(pvStructures));
}

//
// Conversion PV Structure Array => PY [{}] 
//
void structureArrayFieldToPyList(const std::string& fieldName, const PVStructurePtr& pvStructurePtr, boost::python::list& pyList)
{
    PVStructureArrayPtr pvStructureArrayPtr = getStructureArrayField(fieldName, pvStructurePtr);
    int nDataElements = pvStructureArrayPtr->getLength();
    PVStructureArray::const_svector arrayData(pvStructureArrayPtr->view());
    for (int i = 0; i < nDataElements; ++i) {
        PVStructurePtr pvStructure = arrayData[i];
        boost::python::dict pyDict;
        structureToPyDict(pvStructure, pyDict);
        pyList.append(pyDict);
    }
}

//
// Conversion PV Structure => PY {}
//
void structureToPyDict(const PVStructurePtr& pvStructurePtr, boost::python::dict& pyDict)
{
    StructureConstPtr structurePtr = pvStructurePtr->getStructure();
    StringArray fieldNames = structurePtr->getFieldNames();
    for (unsigned int i = 0; i < fieldNames.size(); ++i) {
        std::string fieldName = fieldNames[i];
        FieldConstPtr fieldPtr = getField(fieldName, pvStructurePtr);
        Type type = fieldPtr->getType();
        switch (type) {
            case scalar: {
                ScalarConstPtr scalarPtr = std::tr1::static_pointer_cast<const Scalar>(fieldPtr);
                ScalarType scalarType = scalarPtr->getScalarType();
                addScalarFieldToDict(fieldName, scalarType, pvStructurePtr, pyDict);
                break;
            }
            case scalarArray: {
                ScalarArrayConstPtr scalarArrayPtr = std::tr1::static_pointer_cast<const ScalarArray>(fieldPtr);
                ScalarType scalarType = scalarArrayPtr->getElementType();
                addScalarArrayFieldToDict(fieldName, scalarType, pvStructurePtr, pyDict);
                break;
            }
            case structure: {
                addStructureFieldToDict(fieldName, pvStructurePtr, pyDict);
                break;
            }
            case structureArray: {
                addStructureArrayFieldToDict(fieldName, pvStructurePtr, pyDict);
                break;
            }
            case union_: {
                addUnionFieldToDict(fieldName, pvStructurePtr, pyDict);
                break;
            }
            case unionArray: {
                addUnionArrayFieldToDict(fieldName, pvStructurePtr, pyDict);
                break;
            }
            default: {
                throw PvaException("Unrecognized field type: %d", type);
            }
        }
    }
}

void structureFieldToPyDict(const std::string& fieldName, const PVStructurePtr& pvStructurePtr, boost::python::dict& pyDict)
{
    structureToPyDict(getStructureField(fieldName, pvStructurePtr), pyDict);
}

//
// Add PV Scalar => PY {}
// 
void addScalarFieldToDict(const std::string& fieldName, ScalarType scalarType, const PVStructurePtr& pvStructurePtr, boost::python::dict& pyDict)
{
    switch (scalarType) {
        case pvBoolean: {
            bool value = getBooleanField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        case pvByte: {
            char value = getByteField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        case pvUByte: {
            unsigned char value = getUByteField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        case pvShort: {
            short value = getShortField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        case pvUShort: {
            ushort value = getUShortField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        case pvInt: {
            int32_t value = getIntField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        case pvUInt: {
            uint32_t value = getUIntField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        case pvLong: {
            int64_t value = getLongField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        case pvULong: {
            uint64_t value = getULongField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        case pvFloat: {
            float value = getFloatField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        case pvDouble: {
            double value = getDoubleField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        case pvString: {
            std::string value = getStringField(fieldName, pvStructurePtr)->get();
            pyDict[fieldName] = value;
            break;
        }
        default: {
            throw InvalidDataType("Unrecognized scalar type: %d", scalarType);
        }
    }
}

//
// Add PV Scalar Array => PY {}
// 
void addScalarArrayFieldToDict(const std::string& fieldName, ScalarType scalarType, const PVStructurePtr& pvStructurePtr, boost::python::dict& pyDict)
{
    boost::python::list pyList;
    scalarArrayFieldToPyList(fieldName, pvStructurePtr, pyList);
    pyDict[fieldName] = pyList;
}

//
// Add PV Structure => PY {}
// 
void addStructureFieldToDict(const std::string& fieldName, const PVStructurePtr& pvStructurePtr, boost::python::dict& pyDict)
{
    boost::python::dict pyDict2;
    structureFieldToPyDict(fieldName, pvStructurePtr, pyDict2);
    pyDict[fieldName] = pyDict2;
}

//
// Add PV Structure Array => PY {}
// 
void addStructureArrayFieldToDict(const std::string& fieldName, const PVStructurePtr& pvStructurePtr, boost::python::dict& pyDict) 
{
    boost::python::list pyList;
    PVStructureArrayPtr structureArrayPtr = getStructureArrayField(fieldName, pvStructurePtr);
    int nDataElements = structureArrayPtr->getLength();
    PVStructureArray::const_svector arrayData(structureArrayPtr->view());
    for (int i = 0; i < nDataElements; ++i) {
        boost::python::dict pyDict2;
        structureToPyDict(arrayData[i], pyDict2);   
        pyList.append(pyDict2);   
    }
    pyDict[fieldName] = pyList;
}

//
// Add PV Union => PY {}
// 
void addUnionFieldToDict(const std::string& fieldName, const PVStructurePtr& pvStructurePtr, boost::python::dict& pyDict)
{
    boost::python::dict pyDict2;
    throw PvaException("addUnionFieldToDict not implemented");
}

//
// Add PV Union Array => PY {}
// 
void addUnionArrayFieldToDict(const std::string& fieldName, const PVStructurePtr& pvStructurePtr, boost::python::dict& pyDict) 
{
    boost::python::list pyList;
    throw PvaException("addUnionArrayFieldToDict not implemented");
}

//
// Conversion Structure => PY {}
//
void structureToPyDict(const StructureConstPtr& structurePtr, boost::python::dict& pyDict)
{
    StringArray fieldNames = structurePtr->getFieldNames();
    for (unsigned int i = 0; i < fieldNames.size(); ++i) {
        std::string fieldName = fieldNames[i];
        FieldConstPtr fieldPtr = structurePtr->getField(fieldName);
        Type type = fieldPtr->getType();
        switch (type) {
            case scalar: {
                ScalarConstPtr scalarPtr = std::tr1::static_pointer_cast<const Scalar>(fieldPtr);
                ScalarType scalarType = scalarPtr->getScalarType();
                pyDict[fieldName] = static_cast<PvType::ScalarType>(scalarType);
                break;
            }
            case scalarArray: {
                ScalarArrayConstPtr scalarArrayPtr = std::tr1::static_pointer_cast<const ScalarArray>(fieldPtr);
                ScalarType scalarType = scalarArrayPtr->getElementType();
                boost::python::list pyList;
                pyList.append(static_cast<PvType::ScalarType>(scalarType));
                pyDict[fieldName] = pyList;
                break;
            }
            case structure: {
                StructureConstPtr structurePtr2 = std::tr1::static_pointer_cast<const Structure>(fieldPtr);
                boost::python::dict pyDict2;
                structureToPyDict(structurePtr2, pyDict2);
                pyDict[fieldName] = pyDict2;
                break;
            }
            case structureArray: {
                StructureArrayConstPtr structureArrayPtr = std::tr1::static_pointer_cast<const StructureArray>(fieldPtr);
                StructureConstPtr structurePtr2 = structureArrayPtr->getStructure(); 
                boost::python::dict pyDict2;
                structureToPyDict(structurePtr2, pyDict2);
                boost::python::list pyList;
                pyList.append(pyDict2);
                pyDict[fieldName] = pyList;
                break;
            }
            case union_: {
            }
            case unionArray: {
            }
            default: {
                throw PvaException("Unrecognized field type: %d", type);
            }
        }
    }
}

//
// Copy PV Structure => PV Structure
//
void copyStructureToStructure(const PVStructurePtr& srcPvStructurePtr, PVStructurePtr& destPvStructurePtr)
{
    StructureConstPtr srcStructurePtr = srcPvStructurePtr->getStructure();
    StringArray fieldNames = srcStructurePtr->getFieldNames();
    for (unsigned int i = 0; i < fieldNames.size(); ++i) {
        std::string fieldName = fieldNames[i];
        PVFieldPtr pvFieldPtr = srcPvStructurePtr->getSubField(fieldName);
        FieldConstPtr fieldPtr = pvFieldPtr->getField();
        Type type = fieldPtr->getType();
        switch (type) {
            case scalar: {
                ScalarConstPtr scalarPtr = std::tr1::static_pointer_cast<const Scalar>(fieldPtr);
                ScalarType scalarType = scalarPtr->getScalarType();
                copyScalarToStructure(fieldName, scalarType, srcPvStructurePtr, destPvStructurePtr);
                break;
            }
            case scalarArray: {
                ScalarArrayConstPtr scalarArrayPtr = std::tr1::static_pointer_cast<const ScalarArray>(fieldPtr);
                ScalarType scalarType = scalarArrayPtr->getElementType();
                copyScalarArrayToStructure(fieldName, scalarType, srcPvStructurePtr, destPvStructurePtr);
                break;
            }
            case structure: {
                copyStructureToStructure(fieldName, srcPvStructurePtr, destPvStructurePtr);
                break;
            }
            case structureArray: {
                copyStructureArrayToStructure(fieldName, srcPvStructurePtr, destPvStructurePtr);
                break;
            }
            case union_: {
                 PVUnionPtr pvFrom = srcPvStructurePtr->getSubField<PVUnion>(fieldName);
                 PVUnionPtr pvTo = destPvStructurePtr->getSubField<PVUnion>(fieldName);
                 pvTo->copy(*pvFrom);
                 break;
            }
            case unionArray: {
                 PVUnionArrayPtr pvFrom = srcPvStructurePtr->getSubField<PVUnionArray>(fieldName);
                 PVUnionArrayPtr pvTo = destPvStructurePtr->getSubField<PVUnionArray>(fieldName);
                 pvTo->replace(pvFrom->view());
                 break;
            }
            default: {
                throw PvaException("Unrecognized field type: %d", type);
            }
        }
    }
}

void copyStructureToStructure(const std::string& fieldName, const PVStructurePtr& srcPvStructurePtr, PVStructurePtr& destPvStructurePtr)
{
    PVStructurePtr destPvStructurePtr2 = destPvStructurePtr->getStructureField(fieldName);
    if (destPvStructurePtr2) {
        PVStructurePtr srcPvStructurePtr2 = srcPvStructurePtr->getStructureField(fieldName);
        if (srcPvStructurePtr2) {
            copyStructureToStructure(srcPvStructurePtr2, destPvStructurePtr2);
        }
        else {
            throw FieldNotFound("Source structure has no structure field " + fieldName);
        }
    }
    else {
        throw FieldNotFound("Destination structure has no structure field " + fieldName);
    }
}

//
// Copy PV Structure Array => PV Structure
//
void copyStructureArrayToStructure(const std::string& fieldName, const PVStructurePtr& srcPvStructurePtr, PVStructurePtr& destPvStructurePtr)
{
    PVStructureArrayPtr destPvStructureArrayPtr = getStructureArrayField(fieldName, destPvStructurePtr);
    if (!destPvStructureArrayPtr) {
        throw FieldNotFound("Destination structure has no structure array field " + fieldName);
    }
    StructureArrayConstPtr destStructureArrayPtr = destPvStructureArrayPtr->getStructureArray();
    StructureConstPtr structurePtr = destStructureArrayPtr->getStructure();

    PVStructureArrayPtr srcPvStructureArrayPtr = getStructureArrayField(fieldName, srcPvStructurePtr);
    if (!srcPvStructureArrayPtr) {
        throw FieldNotFound("Source structure has no structure array field " + fieldName);
    }


    int nElements = srcPvStructureArrayPtr->getLength();
    PVStructureArray::const_svector srcPvStructures(srcPvStructureArrayPtr->view());
    PVStructureArray::svector destPvStructures(nElements);

    for (int i = 0; i < nElements; i++) {
        PVStructurePtr destPvStructurePtr2 = getPVDataCreate()->createPVStructure(structurePtr);
        PVStructurePtr srcPvStructurePtr2 = srcPvStructures[i];
        copyStructureToStructure(srcPvStructurePtr2, destPvStructurePtr2);
        destPvStructures[i] = destPvStructurePtr2;
    }
    destPvStructureArrayPtr->setCapacity(nElements);
    destPvStructureArrayPtr->replace(freeze(destPvStructures));
}

//
// Copy PV Scalar => PV Structure
//
void copyScalarToStructure(const std::string& fieldName, ScalarType scalarType, const PVStructurePtr& srcPvStructurePtr, PVStructurePtr& destPvStructurePtr)
{
    switch (scalarType) {
        case pvBoolean: {
            PVBooleanPtr fieldPtr = destPvStructurePtr->getBooleanField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getBooleanField(fieldName)->get());
            }
            break;
        }
        case pvByte: {
            PVBytePtr fieldPtr = destPvStructurePtr->getByteField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getByteField(fieldName)->get());
            }
            break;
        }
        case pvUByte: {
            PVUBytePtr fieldPtr = destPvStructurePtr->getUByteField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getUByteField(fieldName)->get());
            }
            break;
        }
        case pvShort: {
            PVShortPtr fieldPtr = destPvStructurePtr->getShortField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getShortField(fieldName)->get());
            }
            break;
        }
        case pvUShort: {
            PVUShortPtr fieldPtr = destPvStructurePtr->getUShortField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getUShortField(fieldName)->get());
            }
            break;
        }
        case pvInt: {
            PVIntPtr fieldPtr = destPvStructurePtr->getIntField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getIntField(fieldName)->get());
            }
            break;
        }
        case pvUInt: {
            PVUIntPtr fieldPtr = destPvStructurePtr->getUIntField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getUIntField(fieldName)->get());
            }
            break;
        }
        case pvLong: {
            PVLongPtr fieldPtr = destPvStructurePtr->getLongField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getLongField(fieldName)->get());
            }
            break;
        }
        case pvULong: {
            PVULongPtr fieldPtr = destPvStructurePtr->getULongField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getULongField(fieldName)->get());
            }
            break;
        }
        case pvFloat: {
            PVFloatPtr fieldPtr = destPvStructurePtr->getFloatField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getFloatField(fieldName)->get());
            }
            break;
        }
        case pvDouble: {
            PVDoublePtr fieldPtr = destPvStructurePtr->getDoubleField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getDoubleField(fieldName)->get());
            }
            break;
        }
        case pvString: {
            PVStringPtr fieldPtr = destPvStructurePtr->getStringField(fieldName);
            if (fieldPtr) {
                fieldPtr->put(srcPvStructurePtr->getStringField(fieldName)->get());
            }
            break;
        }
        default: {
            throw InvalidDataType("Unrecognized scalar type: %d", scalarType);
        }
    }
}
    
//
// Copy PV Scalar Array => PV Structure
//
void copyScalarArrayToStructure(const std::string& fieldName, ScalarType scalarType, const PVStructurePtr& srcPvStructurePtr, PVStructurePtr& destPvStructurePtr)
{
    PVScalarArrayPtr srcPvScalarArrayPtr = getScalarArrayField(fieldName, scalarType, srcPvStructurePtr);
    PVScalarArrayPtr destPvScalarArrayPtr = getScalarArrayField(fieldName, scalarType, destPvStructurePtr);
    switch (scalarType) {
        case pvBoolean: {
            copyScalarArrayToScalarArray<PVBooleanArray, boolean>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        case pvByte: {
            copyScalarArrayToScalarArray<PVByteArray, int8>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        case pvUByte: {
            copyScalarArrayToScalarArray<PVUByteArray, uint8>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        case pvShort: {
            copyScalarArrayToScalarArray<PVShortArray, int16>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        case pvUShort: {
            copyScalarArrayToScalarArray<PVUShortArray, uint16>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        case pvInt: {
            copyScalarArrayToScalarArray<PVIntArray, int32>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        case pvUInt: {
            copyScalarArrayToScalarArray<PVUIntArray, uint32>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        case pvLong: {
            copyScalarArrayToScalarArray<PVLongArray, int64>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        case pvULong: {
            copyScalarArrayToScalarArray<PVULongArray, uint64>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        case pvFloat: {
            copyScalarArrayToScalarArray<PVFloatArray, float>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        case pvDouble: {
            copyScalarArrayToScalarArray<PVDoubleArray, double>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        case pvString: {
            copyScalarArrayToScalarArray<PVStringArray, std::string>(srcPvScalarArrayPtr, destPvScalarArrayPtr);
            break;
        }
        default: {
            throw InvalidDataType("Unrecognized scalar type: %d", scalarType);
        }
    }
}
    
} // namespace PyPvDataUtility


