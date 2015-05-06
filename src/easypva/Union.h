#ifndef UNION_H
#define UNION_H

#include "pv/pvData.h"
//#include "boost/python/dict.hpp"
//#include "boost/python/list.hpp"
#include "PvObject.h"

namespace epics { namespace pvaPy {

class Union 
{
public:
    // Constructors
    Union();
    Union(const PvObject&);

    // Destructor
    virtual ~Union() {}
    friend std::ostream& operator<<(std::ostream& out, const Union& u);
private:
   epics::pvData::UnionConstPtr union_p;
public:
    epics::pvData::UnionConstPtr getUnion() const {return union_p;}
};

}}


#endif

