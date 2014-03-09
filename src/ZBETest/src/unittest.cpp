#include "unittest.h"

TEST(pruebatest, algo) {
    ClaseTest t(1);
  EXPECT_EQ(1, t.getValue());
  EXPECT_NE(2, t.getValue());
  t.setValue(6);
  EXPECT_GT(7, t.getValue());
  //comentario chungo
}
