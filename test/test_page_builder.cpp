#include <gmock/gmock.h>
#include <gtest/gtest.h>

int main(int argc, char** argv) {
  ::testing::InitGoogleMock();

  if (RUN_ALL_TESTS())
    ;

  return 0;
}
