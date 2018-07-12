context("IBM closed sir")

test_that("Model runs", {
  m1 <- ibm_closed_sir()
  expect_type(m1, "list")
  expect_named(m1, c("t", "S", "I", "R"))
  expect_equal(m1[1, 2], 999)
  expect_equal(m1[1, 3], 1)
  expect_equal(m1[1, 4], 0)
})

test_that("Internal functions", {
  expect_equal(rate_to_prob(0, 1), 0)
  expect_equal(rate_to_prob(Inf, 1), 1)

  expect_equal(sort(draw_sample(1:100, 1)), 1:100)
  expect_length(draw_sample(1:10, 1), 10)
  expect_length(draw_sample(1:10, 0), 0)
})
