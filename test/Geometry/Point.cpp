#include "pch.h"

#include "Geometry/Point.hpp"
#include "Geometry/Vector.hpp"

using namespace Geometry;

TEST(Point, Constructor_DefaultValues) {
	Point<float> point;

	ASSERT_EQ(0.0f, point.getX());
	ASSERT_EQ(0.0f, point.getY());
}

TEST(Point, Constructor_SetValues) {
	Point<int> point(1, 2);

	ASSERT_EQ(1, point.getX());
	ASSERT_EQ(2, point.getY());
}

TEST(Point, Constructor_SetGetX) {
	Point<int> point(1);

	point.setX(5);
	ASSERT_EQ(5, point.getX());
}

TEST(Point, Constructor_SetGetY) {
	Point<int> point(1);

	point.setY(5);
	ASSERT_EQ(5, point.getY());
}

TEST(Point, Constructor_CmpEqualOperator) {
	Point<float> point0;
	Point<float> point1(1, 1);

	ASSERT_TRUE(point0 == point0);
	ASSERT_TRUE(point1 == point1);
	ASSERT_FALSE(point0 == point1);
}

TEST(Point, Constructor_AddAsignVectorOperator) {
	Point<int> point0;
	Vector<int> vector1(1, 1);

	point0 += vector1;
	ASSERT_EQ(Point<int>(1, 1), point0);
}

TEST(Point, Constructor_AddPointOperator) {
	Point<int> point0;
	Point<int> point1(1, 1);

	ASSERT_EQ(Point<int>(1, 1), point0 + point1);
}

TEST(Point, Constructor_AddVectorOperator) {
	Point<int> point0;
	Vector<int> vector1(1, 1);

	ASSERT_EQ(Point<int>(1, 1), point0 + vector1);
}

TEST(Point, Constructor_SubtractPointOperator) {
	Point<int> point0;
	Point<int> point1(1, 1);

	ASSERT_EQ(Vector<int>(-1, -1), point0 - point1);
}
