#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

#include <assert.h>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/regex.hpp>
#include <boost/serialization/singleton.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/extended_type_info.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include "../Node/Node.hpp"
#include "../Concept/Concept.hpp"
#include "../Relation/Relation.hpp"
#include "../Edge/Edge.hpp"

#include "../rapidjson/rapidjson.h"
#include "../rapidjson/document.h"
