#include <vector>

#include "core.h"
#include "gtest/gtest.h"

TEST(/*Topic*/ Core, /*Subtopic*/ SawTest) {
	std::vector<int> vec = { 12, 13, 10, 15, 18, 13, 10, 12 };
	auto a = Core::saw(vec);
	ASSERT_EQ(a, 8);
}