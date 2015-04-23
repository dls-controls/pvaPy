#include "PvObject.h"
#include "PvType.h"
#include "PvaException.h"
#include "PyPvDataUtility.h"
#include "StringUtility.h"
#include "InvalidRequest.h"
#include "InvalidDataType.h"
#include "InvalidArgument.h"
#include "boost/python/object.hpp"
#include "boost/python/tuple.hpp"
#include "boost/python/extract.hpp"
#include "boost/python/stl_iterator.hpp"
#include <pv/standardField.h>

namespace epics { namespace pvaPy {

using namespace epics::pvData;
using namespace std;


// Static constants
const char* PvObject::ValueFieldKey("value");
const char* PvObject::StructureId("structure");

// Constructors
PvObject::PvObject(const epics::pvData::PVStructurePtr& pvStructurePtr_)
    : pvStructurePtr(pvStructurePtr_)
{
}

PvObject::PvObject(const boost::python::dict& pyDict, const std::string& structureId)
    : pvStructurePtr(epics::pvData::getPVDataCreate()->createPVStructure(createStructureFromDict(pyDict, structureId)))
{
}

PvObject::PvObject(const PvObject& pvObject)
    : pvStructurePtr(pvObject.pvStructurePtr)
{
}

// Destructor
PvObject::~PvObject()
{
}

// Operators/conversion methods
epics::pvData::PVStructurePtr PvObject::getPvStructurePtr() const
{
    return pvStructurePtr;
}

epics::pvData::StructureConstPtr PvObject::getStructurePtr() const
{
    return pvStructurePtr->getStructure();
}

PvObject::operator epics::pvData::PVStructurePtr()
{
    return pvStructurePtr;
}

PvObject::operator boost::python::dict() const
{
    return toDict();
}

boost::python::dict PvObject::toDict() const
{
    boost::python::dict pyDict;
    PyPvDataUtility::structureToPyDict(pvStructurePtr, pyDict);
    return pyDict;
}

boost::python::dict PvObject::getStructureDict() 
{
    boost::python::dict pyDict;
    PyPvDataUtility::structureToPyDict(getStructurePtr(), pyDict);
    return pyDict;
}

std::ostream& operator<<(std::ostream& out, const PvObject& pvObject)
{
    out << *(pvObject.pvStructurePtr.get());
    return out;
}

epics::pvData::PVStructurePtr& operator<<(epics::pvData::PVStructurePtr& pvStructurePtr, const PvObject& pvObject)
{
    PyPvDataUtility::copyStructureToStructure(pvObject.getPvStructurePtr(), pvStructurePtr);
    return pvStructurePtr;
}

//
// Object set/get
//
void PvObject::set(const boost::python::dict& pyDict)
{
    PyPvDataUtility::pyDictToStructure(pyDict, pvStructurePtr);
}

boost::python::dict PvObject::get() const
{
    return toDict();
}

// Boolean modifiers/accessors
void PvObject::setBoolean(const std::string& key, bool value)
{
    PyPvDataUtility::getBooleanField(key, pvStructurePtr)->put(value);
}

void PvObject::setBoolean(bool value)
{
    PyPvDataUtility::getBooleanField(ValueFieldKey, pvStructurePtr)->put(value);
}

bool PvObject::getBoolean(const std::string& key) const
{
    return PyPvDataUtility::getBooleanField(key, pvStructurePtr)->get();
}

// Byte modifiers/accessors
void PvObject::setByte(const std::string& key, int8 value)
{
    PyPvDataUtility::getByteField(key, pvStructurePtr)->put(value);
}

void PvObject::setByte(int8 value)
{
    PyPvDataUtility::getByteField(ValueFieldKey, pvStructurePtr)->put(value);
}

int8 PvObject::getByte(const std::string& key) const
{
    return PyPvDataUtility::getByteField(key, pvStructurePtr)->get();
}

// UByte modifiers/accessors
void PvObject::setUByte(const std::string& key, uint8 value)
{
    PyPvDataUtility::getUByteField(key, pvStructurePtr)->put(value);
}

void PvObject::setUByte(uint8 value)
{
    PyPvDataUtility::getUByteField(ValueFieldKey, pvStructurePtr)->put(value);
}

uint8 PvObject::getUByte(const std::string& key) const
{
    return PyPvDataUtility::getUByteField(key, pvStructurePtr)->get();
}

// Short modifiers/accessors
void PvObject::setShort(const std::string& key, int16 value)
{
    PyPvDataUtility::getShortField(key, pvStructurePtr)->put(value);
}

void PvObject::setShort(int16 value)
{
    PyPvDataUtility::getShortField(ValueFieldKey, pvStructurePtr)->put(value);
}

int16 PvObject::getShort(const std::string& key) const
{
    return PyPvDataUtility::getShortField(key, pvStructurePtr)->get();
}

// UShort modifiers/accessors
void PvObject::setUShort(const std::string& key, uint16 value)
{
    PyPvDataUtility::getUShortField(key, pvStructurePtr)->put(value);
}

void PvObject::setUShort(uint16 value)
{
    PyPvDataUtility::getUShortField(ValueFieldKey, pvStructurePtr)->put(value);
}

uint16 PvObject::getUShort(const std::string& key) const
{
    return PyPvDataUtility::getUShortField(key, pvStructurePtr)->get();
}

// Int modifiers/accessors
void PvObject::setInt(const std::string& key, int32 value)
{
    PyPvDataUtility::getIntField(key, pvStructurePtr)->put(value);
}

void PvObject::setInt(int32 value)
{
    PyPvDataUtility::getIntField(ValueFieldKey, pvStructurePtr)->put(value);
}

int32 PvObject::getInt(const std::string& key) const
{
    return PyPvDataUtility::getIntField(key, pvStructurePtr)->get();
}

// UInt modifiers/accessors
void PvObject::setUInt(const std::string& key, uint32 value)
{
    PyPvDataUtility::getUIntField(key, pvStructurePtr)->put(value);
}

void PvObject::setUInt(uint32 value)
{
    PyPvDataUtility::getUIntField(ValueFieldKey, pvStructurePtr)->put(value);
}

uint32 PvObject::getUInt(const std::string& key) const
{
    return PyPvDataUtility::getUIntField(key, pvStructurePtr)->get();
}

// Long modifiers/accessors
void PvObject::setLong(const std::string& key, int64 value)
{
    PyPvDataUtility::getLongField(key, pvStructurePtr)->put(value);
}

void PvObject::setLong(int64 value)
{
    PyPvDataUtility::getLongField(ValueFieldKey, pvStructurePtr)->put(value);
}

int64 PvObject::getLong(const std::string& key) const
{
    return PyPvDataUtility::getLongField(key, pvStructurePtr)->get();
}

// ULong modifiers/accessors
void PvObject::setULong(const std::string& key, uint64 value)
{
    PyPvDataUtility::getULongField(key, pvStructurePtr)->put(value);
}

void PvObject::setULong(uint64 value)
{
    PyPvDataUtility::getULongField(ValueFieldKey, pvStructurePtr)->put(value);
}

uint64 PvObject::getULong(const std::string& key) const
{
    return PyPvDataUtility::getULongField(key, pvStructurePtr)->get();
}

// Float modifiers/accessors
void PvObject::setFloat(const std::string& key, float value)
{
    PyPvDataUtility::getFloatField(key, pvStructurePtr)->put(value);
}

void PvObject::setFloat(float value)
{
    PyPvDataUtility::getFloatField(ValueFieldKey, pvStructurePtr)->put(value);
}

float PvObject::getFloat(const std::string& key) const
{
    return PyPvDataUtility::getFloatField(key, pvStructurePtr)->get();
}

// Double modifiers/accessors
void PvObject::setDouble(const std::string& key, double value)
{
    PyPvDataUtility::getDoubleField(key, pvStructurePtr)->put(value);
}

void PvObject::setDouble(double value)
{
    PyPvDataUtility::getDoubleField(ValueFieldKey, pvStructurePtr)->put(value);
}

double PvObject::getDouble(const std::string& key) const
{
    return PyPvDataUtility::getDoubleField(key, pvStructurePtr)->get();
}

// String modifiers/accessors
void PvObject::setString(const std::string& key, const std::string& value)
{
    PyPvDataUtility::getStringField(key, pvStructurePtr)->put(value);
}

void PvObject::setString(const std::string& value)
{
    PyPvDataUtility::getStringField(ValueFieldKey, pvStructurePtr)->put(value);
}

std::string PvObject::getString(const std::string& key) const
{
    return PyPvDataUtility::getStringField(key, pvStructurePtr)->get();
}

// Scalar array modifiers/accessors
void PvObject::setScalarArray(const std::string& key, const boost::python::list& pyList)
{
    PyPvDataUtility::pyListToScalarArrayField(pyList, key, pvStructurePtr);
}

void PvObject::setScalarArray(const boost::python::list& pyList)
{
    setScalarArray(ValueFieldKey, pyList);
}

boost::python::list PvObject::getScalarArray(const std::string& key) const
{
    boost::python::list pyList;
    PyPvDataUtility::scalarArrayFieldToPyList(key, pvStructurePtr, pyList);
    return pyList;
}

// Structure modifiers/accessors
void PvObject::setStructure(const std::string& key, const boost::python::dict& pyDict)
{
    PyPvDataUtility::pyDictToStructureField(pyDict, key, pvStructurePtr);
}

void PvObject::setStructure(const boost::python::dict& pyDict)
{
    setStructure(ValueFieldKey, pyDict);
}

boost::python::dict PvObject::getStructure(const std::string& key) const
{
    boost::python::dict pyDict;
    PyPvDataUtility::structureFieldToPyDict(key, pvStructurePtr, pyDict);
    return pyDict;
}

// Union fields
bool PvObject::unionIsVariant(const std::string& key) const
{
   PVUnionPtr pvUnion = pvStructurePtr->getSubField<PVUnion>(key);
   if(!pvUnion) throw InvalidArgument("not a union field");
   return pvUnion->getUnion()->isVariant();
}

boost::python::list PvObject::unionGetFieldNames(const std::string& key) const
{
   PVUnionPtr pvUnion = pvStructurePtr->getSubField<PVUnion>(key);
   if(!pvUnion) throw InvalidArgument("not a union field");
   StringArray names = pvUnion->getUnion()->getFieldNames();
   boost::python::list pyList;
   for(size_t i=0; i<names.size(); ++i) pyList.append(names[i]);
   return pyList;
}

PvObject PvObject::unionCreate(
    const std::string& fieldName,
    const std::string& key) const
{
   PVUnionPtr pvUnion = pvStructurePtr->getSubField<PVUnion>(key);
   if(!pvUnion) throw InvalidArgument("not a union field");
   StringArray names(1);
   PVFieldPtrArray pvfields(1);
   names[0] = "value";
   FieldConstPtr field;
   UnionConstPtr u = pvUnion->getUnion();
   if(u->isVariant()) {
       field = getFieldCreate()->createVariantUnion();
   } else {
       field = u->getField(fieldName);
   }
   pvfields[0] = getPVDataCreate()->createPVField(field);
   PVStructurePtr pv = getPVDataCreate()->createPVStructure(names,pvfields);
   return PvObject(pv);
}

PvObject PvObject::unionSelect(
    const std::string& fieldName,
    const std::string& key) const
{
   PVUnionPtr pvUnion = pvStructurePtr->getSubField<PVUnion>(key);
   if(!pvUnion) throw InvalidArgument("not a union field");
   if(pvUnion->getUnion()->isVariant()) {
       throw InvalidArgument("unionSelect not valid for variant union");
   }
   PVFieldPtr pvField;
   try {
       pvField = pvUnion->select(fieldName);
   } catch (std::runtime_error e) {
       throw InvalidArgument(" illegal fieldName");
   }
   return unionGet(key);
}

PvObject PvObject::unionGet(const std::string& key) const
{
   PVUnionPtr pvUnion = pvStructurePtr->getSubField<PVUnion>(key);
   if(!pvUnion) throw InvalidArgument("not a union field");
   PVFieldPtr pvField = pvUnion->get();
   StringArray names(1);
   PVFieldPtrArray pvfields(1);
   names[0] = "value";
   pvfields[0] = pvField;
   PVStructurePtr pv = getPVDataCreate()->createPVStructure(names,pvfields);
   return PvObject(pv);
}

void PvObject::unionSet(
    const PvObject & value,
    const std::string& key)
{
   PVUnionPtr pvUnion = pvStructurePtr->getSubField<PVUnion>(key);
   if(!pvUnion) throw InvalidArgument("not a union field");
   try {
        PVFieldPtr pvFrom = value.getPvStructurePtr()->getSubField("value");
        if(pvUnion->getUnion()->isVariant()) {
            pvUnion->set(pvFrom);
        } else {
            FieldConstPtr field = pvFrom->getField();
            int32 ind = -1;
            FieldConstPtrArray fields = pvUnion->getUnion()->getFields();
            for(size_t i=0; i< fields.size(); ++i) {
                 if(fields[i]==field) {
                     ind = i;
                     break;
                 }
            }
            if(ind<0) throw InvalidArgument("illegal value for this union");
            pvUnion->set(ind,pvFrom);
        }
   } catch (std::runtime_error e) {
       throw InvalidArgument(" illegal fieldName");
   }

}

// UnionArray fields
bool PvObject::unionArrayIsVariant(const std::string& key) const
{
   PVUnionArrayPtr pvUnionArray = pvStructurePtr->getSubField<PVUnionArray>(key);
   if(!pvUnionArray) throw InvalidArgument("not a union field");
   return pvUnionArray->getUnionArray()->getUnion()->isVariant();
}

boost::python::list PvObject::unionArrayGetFieldNames(const std::string& key) const
{
   PVUnionArrayPtr pvUnionArray = pvStructurePtr->getSubField<PVUnionArray>(key);
   if(!pvUnionArray) throw InvalidArgument("not a union field");
   StringArray names = pvUnionArray->getUnionArray()->getUnion()->getFieldNames();
   boost::python::list pyList;
   for(size_t i=0; i<names.size(); ++i) pyList.append(names[i]);
   return pyList;
}

PvObject PvObject::unionArrayCreateElement(
    const std::string& fieldName,
    const std::string& key) const
{
   PVUnionArrayPtr pvUnionArray = pvStructurePtr->getSubField<PVUnionArray>(key);
   if(!pvUnionArray) throw InvalidArgument("not a union array field");
   StringArray names(1);
   PVFieldPtrArray pvfields(1);
   names[0] = "value";
   FieldConstPtr field;
   UnionConstPtr u = pvUnionArray->getUnionArray()->getUnion();
   if(u->isVariant()) {
       field = getFieldCreate()->createVariantUnion();
   } else {
       field = u->getField(fieldName);
   }
   pvfields[0] = getPVDataCreate()->createPVField(field);
   PVStructurePtr pv = getPVDataCreate()->createPVStructure(names,pvfields);
   return PvObject(pv);
}

boost::python::list PvObject::unionArrayGet(const std::string& key) const
{
    PVUnionArrayPtr pvUnionArray = pvStructurePtr->getSubField<PVUnionArray>(key);
    if(!pvUnionArray) throw InvalidArgument("not a union array field");
    PVUnionArray::const_svector data = pvUnionArray->view();
    boost::python::list pyList;
    for(size_t i=0; i<data.size(); ++i) {
        StringArray names(1);
        PVFieldPtrArray pvfields(1);
        names[0] = "value";
        pvfields[0] = data[i]->get();
        PVStructurePtr pv = getPVDataCreate()->createPVStructure(names,pvfields);
        PvObject xx(pv);
        pyList.append(PvObject(pv));
    }
    return pyList;
}

void PvObject::unionArraySet(
    const boost::python::list& pyList,
    const std::string& key)
{
    PVUnionArrayPtr pvUnionArray = pvStructurePtr->getSubField<PVUnionArray>(key);
    if(!pvUnionArray) throw InvalidArgument("not a union array field");
    UnionConstPtr u = pvUnionArray->getUnionArray()->getUnion();
    FieldConstPtrArray fields = u->getFields();
    int listSize = boost::python::len(pyList);
    PVUnionArray::svector data(listSize);
    for(size_t i=0; i<data.size(); ++i) {
        PvObject pvObject = boost::python::extract<PvObject>(pyList[i]);
        PVStructurePtr pv = pvObject.getPvStructurePtr();
        PVFieldPtr pvFrom = pv->getSubField(key);
        PVUnionPtr pvUnion = getPVDataCreate()->createPVUnion(u);
        if(u->isVariant()) {
            pvUnion->set(pvFrom);
        } else {
            FieldConstPtr field = pvFrom->getField();
            int32 ind = -1;
            for(size_t i=0; i< fields.size(); ++i) {
                 if(fields[i]==pv->getSubField(key)->getField()) {
                     ind = i;
                     break;
                 }
            }
            if(ind<0) throw InvalidArgument("an element is illegal for this union array");
            pvUnion->set(ind,pvFrom);
        }
        data[i] = pvUnion;
    }
    pvUnionArray->replace(freeze(data));
}

// Structure array modifiers/accessors
void PvObject::setStructureArray(const std::string& key, const boost::python::list& pyList)
{
    PyPvDataUtility::pyListToStructureArrayField(pyList, key, pvStructurePtr);
}

void PvObject::setStructureArray(const boost::python::list& pyList)
{
    setStructureArray(ValueFieldKey, pyList);
}

boost::python::list PvObject::getStructureArray(const std::string& key) const
{
    boost::python::list pyList;
    PyPvDataUtility::structureArrayFieldToPyList(key, pvStructurePtr, pyList);
    return pyList;
}

//
// Private helper methods.
//
epics::pvData::StructureConstPtr PvObject::createStructureFromDict(const boost::python::dict& pyDict, const std::string& structureId)
{
    epics::pvData::FieldConstPtrArray fields;
    epics::pvData::StringArray names;

    boost::python::list fieldNames = pyDict.keys();
    for (int i = 0; i < boost::python::len(fieldNames); i++) {
        boost::python::object fieldNameObject = fieldNames[i];
        boost::python::extract<std::string> fieldNameExtract(fieldNameObject);
        std::string fieldName;
        if (fieldNameExtract.check()) {
            fieldName = fieldNameExtract();
        }
        else {
            throw InvalidArgument("Dictionary key is used as field name and must be a string");
        }

        // Check for Scalar
        boost::python::object valueObject = pyDict[fieldNameObject];
        boost::python::extract<int> scalarExtract(valueObject);
        if (scalarExtract.check()) {
            epics::pvData::ScalarType scalarType = static_cast<epics::pvData::ScalarType>(scalarExtract());
            addScalarField(fieldName, scalarType, fields, names);
            continue;
        } 

        // Check for list: []
        // Type of the first element in the list will determine PV list type
        boost::python::extract<boost::python::list> listExtract(valueObject);
        if (listExtract.check()) {
            boost::python::list pyList = listExtract();
            int listSize = boost::python::len(pyList);
            if (listSize != 1) {
                throw InvalidArgument("PV type list provided for field name %s must have exactly one element.", fieldName.c_str());
            }
            else {
                // [Scalar] => ScalarArray
                boost::python::extract<int> arrayScalarExtract(pyList[0]);
                if (arrayScalarExtract.check()) {
                    epics::pvData::ScalarType scalarType = static_cast<epics::pvData::ScalarType>(arrayScalarExtract());
                    addScalarArrayField(fieldName, scalarType, fields, names);
                    continue;
                }

                // [{}] => StructureArray
                boost::python::extract<boost::python::dict> dictExtract(pyList[0]);
                if (dictExtract.check()) {
                    boost::python::dict pyDict2 = dictExtract();
                    int dictSize = boost::python::len(pyDict2);
                    if (!dictSize) {
                        throw InvalidArgument("PV type dict provided for field name %s must be non-empty.", fieldName.c_str());
                    }
                    addStructureArrayField(fieldName, pyDict2, fields, names);
                    continue;
                }

                // [PvObject] => StructureArray
                boost::python::extract<PvObject> pvObjectExtract(pyList[0]);
                if (pvObjectExtract.check()) {
                    boost::python::dict pyDict2 = static_cast<boost::python::dict>(pvObjectExtract());
                    int dictSize = boost::python::len(pyDict2);
                    if (!dictSize) {
                        throw InvalidArgument("PV object dict provided for field name %s must be non-empty.", fieldName.c_str());
                    }
                    addStructureArrayField(fieldName, pyDict2, fields, names);
                    continue;
                }
                else {
                    // Invalid request.
                    throw InvalidArgument("Unrecognized list type for field name %s", fieldName.c_str());
                }
            }
            continue;
        } 

        // Check for dict: {} => Structure
        boost::python::extract<boost::python::dict> dictExtract(valueObject);
        if (dictExtract.check()) {
            boost::python::dict pyDict2 = dictExtract();
            boost::python::list fieldNames = pyDict2.keys();
            if(boost::python::len(fieldNames)==1) {
                boost::python::object fieldNameObject = fieldNames[0];
                boost::python::extract<std::string> fieldNameExtract(fieldNameObject);
                if(fieldNameExtract.check()) {
                    string name = fieldNameExtract();
                    if(name=="UNION") {
                       boost::python::object valueObject = pyDict2[fieldNameObject];
                       if(valueObject.is_none()) {
                           fields.push_back(getFieldCreate()->createVariantUnion());
                           names.push_back(fieldName);
                           continue;
                       }
                       boost::python::extract<PvObject> pvObjectExtract(valueObject);
                       if(pvObjectExtract.check()) {
                           PvObject pv = pvObjectExtract();
                           StructureConstPtr s = pv.getStructurePtr();
                           FieldConstPtrArray f = s->getFields();
                           StringArray n = s->getFieldNames();
                           fields.push_back(getFieldCreate()->createUnion(n,f));
                           names.push_back(fieldName);
                           continue;
                       }
                    }
                    if(name=="[UNION]") {
                       boost::python::object valueObject = pyDict2[fieldNameObject];
                       if(valueObject.is_none()) {
                           fields.push_back(getFieldCreate()->createVariantUnionArray());
                           names.push_back(fieldName);
                           continue;
                       }
                       boost::python::extract<PvObject> pvObjectExtract(valueObject);
                       if(pvObjectExtract.check()) {
                           PvObject pv = pvObjectExtract();
                           StructureConstPtr s = pv.getStructurePtr();
                           FieldConstPtrArray f = s->getFields();
                           StringArray n = s->getFieldNames();
                           UnionConstPtr u = getFieldCreate()->createUnion(n,f);
                           fields.push_back(getFieldCreate()->createUnionArray(u));
                           names.push_back(fieldName);
                           continue;
                       }
                    }
                    if(name=="STRUCTURE") {
                       boost::python::object valueObject = pyDict2[fieldNameObject];
                       boost::python::extract<std::string> stringExtract(valueObject);
                       if(stringExtract.check()) {
                           string name = stringExtract();
                           if(name=="alarm") {
                               fields.push_back(getStandardField()->alarm());
                               names.push_back(fieldName);
                               continue;
                           }
                           if(name== "timeStamp") {
                               fields.push_back(getStandardField()->timeStamp());
                               names.push_back(fieldName);
                               continue;
                           }
                           if(name== "display") {
                               fields.push_back(getStandardField()->display());
                               names.push_back(fieldName);
                               continue;
                           }
                           if(name== "control") {
                               fields.push_back(getStandardField()->control());
                               names.push_back(fieldName);
                               continue;
                           }
                       }
                       boost::python::extract<PvObject> pvObjectExtract(valueObject);
                       if(pvObjectExtract.check()) {
                           PvObject pv = pvObjectExtract();
                           fields.push_back(pv.getStructurePtr());
                           names.push_back(fieldName);
                           continue;
                       }
                    }
                    if(name=="[STRUCTURE]") {
                       boost::python::object valueObject = pyDict2[fieldNameObject];
                       boost::python::extract<std::string> stringExtract(valueObject);
                       boost::python::extract<PvObject> pvObjectExtract(valueObject);
                       if(pvObjectExtract.check()) {
                           PvObject pv = pvObjectExtract();
                           fields.push_back(getFieldCreate()->createStructureArray(pv.getPvStructurePtr()->getStructure()));
                           names.push_back(fieldName);
                           continue;
                       }
                    }
                }
            }
            int dictSize = boost::python::len(pyDict2);
            if (!dictSize) {
                throw InvalidArgument("PV type dict provided for field name %s must be non-empty.", fieldName.c_str());
            }
            addStructureField(fieldName, pyDict2, fields, names);
            continue;
        }

        // Check for PvObject: PvObject => Structure
        boost::python::extract<PvObject> pvObjectExtract(valueObject);
        if (pvObjectExtract.check()) {
            PvObject pv = pvObjectExtract();
            StructureConstPtr s = pv.getStructurePtr();
            fields.push_back(s);
            names.push_back(fieldName);
            continue;
        }
        else {
            // Invalid request.
            throw InvalidArgument("Unrecognized structure type for field name %s", fieldName.c_str());
        }
    }

    std::string structureName = StringUtility::trim(structureId);
    if (structureName.length()) {
        return epics::pvData::getFieldCreate()->createStructure(structureName, names, fields);
    }
    return epics::pvData::getFieldCreate()->createStructure(names, fields);
}

void PvObject::addScalarField(const std::string& fieldName, epics::pvData::ScalarType scalarType, epics::pvData::FieldConstPtrArray& fields, epics::pvData::StringArray& names)
{
    fields.push_back(epics::pvData::getFieldCreate()->createScalar(scalarType));
    names.push_back(fieldName);
}

void PvObject::addScalarArrayField(const std::string& fieldName, epics::pvData::ScalarType scalarType, epics::pvData::FieldConstPtrArray& fields, epics::pvData::StringArray& names)
{
    fields.push_back(epics::pvData::getFieldCreate()->createScalarArray(scalarType));
    names.push_back(fieldName);
}

void PvObject::addStructureField(const std::string& fieldName, const boost::python::dict& pyDict, epics::pvData::FieldConstPtrArray& fields, epics::pvData::StringArray& names)
{
    fields.push_back(createStructureFromDict(pyDict));
    names.push_back(fieldName);
}

void PvObject::addStructureArrayField(const std::string& fieldName, const boost::python::dict& pyDict, epics::pvData::FieldConstPtrArray& fields, epics::pvData::StringArray& names)
{
    fields.push_back(epics::pvData::getFieldCreate()->createStructureArray(createStructureFromDict(pyDict)));
    names.push_back(fieldName);
}

}}


