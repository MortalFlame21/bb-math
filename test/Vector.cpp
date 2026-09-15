#include "bb/Vector.hpp"

#include <cmath>
#include <gtest/gtest.h>

TEST(VectorOperations, Vec2dMagnitude) {
    using V = bb::Vec2d;
    EXPECT_FLOAT_EQ(bb::magnitude(V{}), 0.f);
    EXPECT_FLOAT_EQ(bb::magnitude(V{1.f, 1.f}), std::sqrt(2.f));
    EXPECT_FLOAT_EQ(bb::magnitude(V{2.f, 2.f}), 2.f * std::sqrt(2.f));
    EXPECT_FLOAT_EQ(bb::magnitude(V{3.f, 4.f}), 5.f);
}

TEST(VectorOperations, Vec3dMagnitude) {
    using V = bb::Vec3d;
    EXPECT_FLOAT_EQ(bb::magnitude(V{}), 0.f);
    EXPECT_FLOAT_EQ(bb::magnitude(V{1.f, 1.f, 1.f}), std::sqrt(3.f));
    EXPECT_FLOAT_EQ(bb::magnitude(V{2.f, 3.f, 6.f}), 7.f);
    EXPECT_FLOAT_EQ(bb::magnitude(V{-4.f, 0.f, -3.}), 5.f);
    EXPECT_FLOAT_EQ(bb::magnitude(V{2.f, 0.f, 2.f}), bb::magnitude(bb::Vec2d{2.f, 2.f}));
}

TEST(VectorOperations, Vec2dScalarMultiply) {
    using V = bb::Vec2d;
    EXPECT_EQ((V{9.f, 3.f} * 2.f), (V{18.f, 6.f}));
    EXPECT_EQ((V{-12.f, -1.f} * -1.f), (V{12.f, 1.f}));
    EXPECT_EQ((V{0.67f, 0.32f}) * 100.f, (V{67.f, 32.f}));
}

TEST(VectorOperations, Vec3dScalarMultiply) {
    using V = bb::Vec3d;
    EXPECT_EQ((V{1.f, 1.f, 1.f} * 2.f), (V{2.f, 2.f, 2.f}));
    EXPECT_EQ((V{0.f, -1.f, 3.f} * 10.f), (V{0.f, -10.f, 30.f}));
    EXPECT_EQ((V{-3.f, -1.f, 6.f}) * -1.f, (-V{-3.f, -1.f, 6.f}));
    EXPECT_EQ((V{-3.f, -1.f, 6.f}) * (1.f / 2.f), (V{-3.f, -1.f, 6.f}) / 2.f);
}

TEST(VectorOperations, VecNormalise) {
    EXPECT_FLOAT_EQ(bb::magnitude(bb::normalise(bb::Vec3d{2.f, 3.f, 6.f})), 1.f);
    EXPECT_FLOAT_EQ(bb::magnitude(bb::normalise(bb::Vec2d{129.f, 197.f})), 1.f);
}