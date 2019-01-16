context("test-deterministic-sir")

test_that("Determininstic SIR", {
  det <- odin_closed_sir(N = 1000, beta = 1, sigma = 0.5,
                         i0 = 10, t_final = 100, dt = 1)
  expect_type(det, "list")
  expect_equal(nrow(det), 101)
  expect_equal(ncol(det), 4)
  expect_equal(det[1,1], 0)
  expect_equal(det[1,2], 990)
  expect_equal(det[1,3], 10)
  expect_equal(det[1,4], 0)
  expect_equal(det[101,1], 100)
})
