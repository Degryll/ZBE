#include "ludomain.h"

namespace ludo {

using json = nlohmann::json;

int ludomain(int, char** ) {

    std::ifstream i("data/test/json/testjson_001.json");

    zbe::JSONImgDefFileLoad(i, 0);

    std::cout << "--------------------------------------------------------------" << std::endl;
    std::cout << "Errors found: " << zbe::SysError::getNErrors() << std::endl;
    std::cout << "Last error: " << zbe::SysError::getFirstErrorString() << std::endl;
    std::cout << "--------------------------------------------------------------" << std::endl;

    return 0;
}

} //namespace Ludo
