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

TEST(VectorOperations, VecNormaliseMagnitude) {
    EXPECT_FLOAT_EQ(bb::magnitude(bb::normalise(bb::Vec3d{2.f, 3.f, 6.f})), 1.f);
    EXPECT_FLOAT_EQ(bb::magnitude(bb::normalise(bb::Vec2d{129.f, 197.f})), 1.f);
}

TEST(VectorOperations, Vec2dAddition) {
    using V = bb::Vec2d;
    EXPECT_EQ((V{-1.f, -3.f} + V{1.f, 3.f}), (V{}));
    EXPECT_EQ((V{5.f, 3.f} + V{1.f, 2.f}), (V{6.f, 5.f}));
    EXPECT_EQ((V{-100.f, 100.f} + V{101.f, -101.f}), (V{1.f, -1.f}));
}

TEST(VectorOperations, Vec3dAddition) {
    using V = bb::Vec3d;
    EXPECT_EQ((V{-1.f, 2.f, -3.f} + V{1.f, -1.f, 5.f}), (V{0.f, 1.f, 2.f}));
    EXPECT_EQ((V{3.f, 1.f, 4.f} + V{2.f, 7.f, 1.f}), (V{5.f, 8.f, 5.f}));
    EXPECT_EQ((V{1.f, 0.f, 0.f} + V{0.f, 0.f, 1.0f}), (V{1.f, 0.f, 1.f}));
}

TEST(VectorOperations, Vec2dSubtraction) {
    using V = bb::Vec2d;
    EXPECT_EQ((V{-2.f, 7.f} - V{1.f, -1.f}), (V{-3.f, 8.f}));
    EXPECT_EQ((V{-19.f, 11.f} - V{-18.f, 3.f}), (V{-1.f, 8.f}));
    EXPECT_EQ((V{6.f, 7.f} - V{6.f, 9.f}), (V{0.f, -2.f}));
}

TEST(VectorOperations, Vec3dSubtraction) {
    using V = bb::Vec3d;
    EXPECT_EQ((V{} - V{1.f, 1.f, 1.f}), (V{-1.f, -1.f, -1.f}));
    EXPECT_EQ((V{4.f, 2.0, 0.f} - V{9.f, 5.f, 9.}), (V{-5.f, -3.f, -9.f}));
    EXPECT_EQ((V{1.f, 4.f, 7.f} - V{}), (V{1.f, 4.f, 7.f}));
}

TEST(VectorOperations, Vec2dPropertyAssociativeLaw) {
    using V = bb::Vec2d;
    EXPECT_EQ(((V{1.f, 1.f} + V{}) + V{0.f, -1.f}),
               (V{1.f, 1.f} + (V{} + V{0.f, -1.f})));
}

TEST(VectorOperations, Vec3dPropertyAssociativeLaw) {
    using V = bb::Vec3d;
    EXPECT_EQ(((V{1.f, 1.f, 1.f} + V{}) + V{-1.f, 0.f, -1.f}),
               (V{1.f, 1.f, 1.f} + (V{} + V{-1.f, 0.f, -1.f})));
}

TEST(VectorOperations, Vec2dCommutativeLaw) {
    constexpr bb::Vec2d a{0.391f, 0.123f};
    constexpr bb::Vec2d b{0.719f, 0.987f};
    EXPECT_EQ(a + b, b + a);
}

TEST(VectorOperations, Vec3dCommutativeLaw) {
    constexpr bb::Vec3d a{0.391f, 0.123f, 1.f};
    constexpr bb::Vec3d b{0.719f, 0.987f, 0.f};
    EXPECT_EQ(a + b, b + a);
}

TEST(VectorOperations, Vec2dAssociativeLawScalar) {
    constexpr bb::Vec2d v{0.420f, 0.777f};
    EXPECT_EQ((3.f * 2.f) * v, 3.f * (2.f * v));
}

TEST(VectorOperations, Vec3dAssociativeLawScalar) {
    constexpr bb::Vec3d v{0.420f, 0.699f, 0.777f};
    EXPECT_EQ((3.f * 2.f) * v, 3.f * (2.f * v));
}

TEST(VectorOperations, Vec2dAssociativeLaw) {
    constexpr bb::Vec2d v{0.420f, 0.777f};
    EXPECT_EQ(2.f * v, 2.f * v);
}

TEST(VectorOperations, Vec3dAssociativeLaw) {
    constexpr bb::Vec3d v{0.420f, 0.699f, 0.777f};
    EXPECT_EQ(2.f * v, v * 2.f);
}

TEST(VectorOperations, Vec2dDistrubutiveLaw) {
    constexpr bb::Vec2d a{0.391f, 0.123f};
    EXPECT_EQ((4.f + 1.f) * a, 4.f * a + 1.f * a);
}

TEST(VectorOperations, Vec3dDistrubutiveLaw) {
    constexpr bb::Vec3d a{0.391f, 0.123f, 1.f};
    EXPECT_EQ((4.f + 1.f) * a, 4.f * a + 1.f * a);
}