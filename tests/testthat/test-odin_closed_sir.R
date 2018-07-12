context("odin closed sir")

test_that("Model runs", {
  m1 <- odin_closed_sir()
  expect_type(m1, "list")
  expect_named(m1, c("t", "S", "I", "R"))
  expect_equal(m1[1, 2], 999)
  expect_equal(m1[1, 3], 1)
  expect_equal(m1[1, 4], 0)
})
