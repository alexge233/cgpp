#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "../Node/Node.hpp"
#include "../Concept/Concept.hpp"
#include "../Relation/Relation.hpp"

#include "../rapidjson/rapidjson.h"
#include "../rapidjson/document.h"

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>



