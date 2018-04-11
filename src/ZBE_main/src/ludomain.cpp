#include "ludomain.h"

namespace ludo {

using json = nlohmann::json;

int ludomain(int, char** ) {
    json j = {
      {"pi", 3.141},
      {"happy", true},
      {"name", "Niels"},
      {"nothing", nullptr},
      {"answer", {
        {"everything", 42}
      }},
      {"list", {1, 0, 2}},
      {"object", {
        {"currency", "USD"},
        {"value", 42.99}
      }}
    };  // j

    json j2;
    j2["hola"] = "adios";

    printf("j: %s\n", j.dump().c_str());
    printf("j2: %s\n", j2.dump(4).c_str());

    json j3 = "{ \"happy\": true, \"pi\": 3.141 }"_json;

    // or even nicer with a raw string literal
    auto j4 = R"(
      {
        "happy": true,
        "pi": 3.141
      }
    )"_json;

    // read a JSON file
//    std::ifstream i("file.json");
//    json jff;
//    i >> jff;

    return 0;
}

} //namespace Ludo
