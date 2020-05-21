#include <stan/math/prim.hpp>
#include <test/unit/math/prim/fun/expect_matrix_eq.hpp>
#include <gtest/gtest.h>

#define EXPECT_MATRIX_NEAR(A, B, DELTA) \
  for (int i = 0; i < A.size(); i++)    \
    EXPECT_NEAR(A(i), B(i), DELTA);

TEST(MathMatrixPrim, mdivide_left_tri_low_val) {
  using stan::math::mdivide_left_tri_low;

  stan::math::matrix_d I = Eigen::MatrixXd::Identity(2, 2);
  stan::math::matrix_d Ad(2, 2);
  Ad << 2.0, 0.0, 5.0, 7.0;
  expect_matrix_eq(I, mdivide_left_tri_low(Ad, Ad));

  stan::math::matrix_d A_Ainv = Ad * mdivide_left_tri_low(Ad);
  EXPECT_MATRIX_NEAR(I, A_Ainv, 1e-15);

  I = Eigen::MatrixXd::Identity(1, 1);
  Ad.resize(1, 1);
  Ad << 2;
  expect_matrix_eq(I, mdivide_left_tri_low(Ad, Ad));

  A_Ainv = Ad * mdivide_left_tri_low(Ad);
  EXPECT_MATRIX_NEAR(I, A_Ainv, 1e-15);
}

TEST(MathMatrixPrim, mdivide_left_tri_low_size_zero) {
  using stan::math::mdivide_left_tri_low;
  stan::math::matrix_d Ad(0, 0);
  stan::math::matrix_d b0(0, 2);
  stan::math::matrix_d I;

  I = mdivide_left_tri_low(Ad, Ad);
  EXPECT_EQ(0, I.rows());
  EXPECT_EQ(0, I.cols());

  I = mdivide_left_tri_low(Ad);
  EXPECT_EQ(0, I.rows());
  EXPECT_EQ(0, I.cols());

  I = mdivide_left_tri_low(Ad, b0);
  EXPECT_EQ(0, I.rows());
  EXPECT_EQ(b0.cols(), I.cols());
}
