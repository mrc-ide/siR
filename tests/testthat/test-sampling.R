context("test-sampling")

test_that("Single sampling", {
  expect_equal(sample_int(1,1), 1)
  sample_double(1,1)

  int_samp <- rep(NA, 1000)
  double_samp <- rep(NA, 1000)
  w_int_samp <- rep(NA, 1000)
  w_int_samp_min <- rep(NA, 1000)
  for(i in 1:1000){
    int_samp[i] <- sample_int(1, 10)
    double_samp[i] <- sample_double(1, 10)
    w_int_samp[i] <- weighted_sample_int(1:10, seq(0.1, 1, 0.1))
    w_int_samp_min[i] <-  weighted_sample_min_int(1:10, seq(0.1, 1, 0.1), 5)
  }
  expect_equal(max(int_samp), 10)
  expect_equal(min(int_samp), 1)
  expect_lt(max(double_samp), 10)
  expect_gt(max(double_samp), 9.9)
  expect_lt(min(double_samp), 1.1)
  expect_gt(min(double_samp), 1)
  expect_gt(sum(w_int_samp == 10), sum(w_int_samp == 1))
  expect_equal(max(w_int_samp), 10)
  expect_equal(min(w_int_samp), 1)
  expect_equal(min(w_int_samp_min), 5)
  expect_equal(max(w_int_samp_min), 10)
})
