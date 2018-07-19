#include "gtest/gtest.h"

#include <vector>
#include "ZBE/core/system/SysIdGenerator.h"

namespace SysIdGenerator{

const int N = 10;

void* test(void *idvoid) {
  int *id = (int*)idvoid;
	*id = zbe::SysIdGenerator::getId();
	return (nullptr);
}

bool check(std::vector<int> ids, int offset) {
  for(int i = 0; i < N-1; i++) {
    for(int j = i+1; j < N; j++) {
      if(ids[j] > N+offset) return (false);
      if(ids[i] == ids[j]) return (false);
    }
  }
  return (ids[0] < N+offset);
}

TEST(SysIdGenerator, GenerateId) {

  int offset = zbe::SysIdGenerator::getId();
  std::vector<pthread_t> t(N);
  std::vector<int> ids(N);

  for(int i = 0; i < N; i++) {
    pthread_create(&(t[i]), nullptr, test, &(ids[i]));
  }

  for(int i = 0; i < N; i++) {
    pthread_join(t[i], nullptr);
  }

  EXPECT_TRUE(check(ids, offset)) << "All unique ids.";
}

}  // namespace SysIdGenerator
