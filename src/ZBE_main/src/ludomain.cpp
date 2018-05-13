#include "ludomain.h"

namespace ludo {

int ludomain(int, char** ) {
    std::multiset<int> msint;

    msint.insert(7);
    std::multiset<int>::iterator iter = msint.insert(8);
    msint.insert(9);

    for(int e : msint){
      printf("%d\n", e);
    }

    if(iter == msint.end()){
      printf("YEP\n");
    } else {
      printf("NOPE\n");
    }

    msint.erase(iter);

    for(int e : msint){
      printf("%d\n", e);
    }

    if(iter == msint.end()){
      printf("YEP\n");
    } else {
      printf("NOPE\n");
    }

    printf("%d\n", (*iter) );

    return 0;
}

} //namespace Ludo
