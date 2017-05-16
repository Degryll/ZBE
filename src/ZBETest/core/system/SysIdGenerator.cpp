#include "gtest/gtest.h"

#include "ZBE/core/system/SysIdGenerator.h"

namespace SysIdGenerator{

const int N = 10000;

void* test(void *idvoid) {
  int *id = (int*)idvoid;
	*id = zbe::SysIdGenerator::getId();
	return (nullptr);
}

bool check(int *ids) {
  for(int i = 0; i < N-1; i++) {
    for(int j = i+1; j < N; j++) {
      if(ids[i] >= N) return (false);
      if(ids[i] == ids[j]) return (false);
    }
  }
  return (true);
}

TEST(SysIdGenerator, GenerateId) {
	pthread_t *t = new pthread_t[N];
	int *ids = new int[N];

  for(int i = 0; i < N; i++) {
    pthread_create(t+i, 0, test, ids+i);
  }

  for(int i = 0; i < N; i++) {
    pthread_join(t[i], nullptr);
  }

  EXPECT_TRUE(check(ids)) << "All unique ids.";

  delete[] t;
  delete[] ids;
}

}  // namespace SysIdGenerator
