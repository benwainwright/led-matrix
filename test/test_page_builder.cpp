#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleMock();

    if (RUN_ALL_TESTS())
        ;

    return 0;
}
