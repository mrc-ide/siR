context("test-time")

test_that("Time shift", {
  expect_equal(years_to_steps(10, 1), 365 * 10)
  expect_equal(years_to_steps(10, 10), 365 * 10 * 10)
  expect_equal(days_to_steps(10, 1), 10)
  expect_equal(days_to_steps(10, 10), 10 * 10)
})
