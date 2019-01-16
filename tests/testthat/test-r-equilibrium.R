context("test-r-equilibrium")

test_that("R current age draw", {
  set.seed(100)
  expect_equal(current_age(1, age_of_death), 29294)
  draws <- current_age(10000, age_of_death)
  expect_gt(min(draws), -1)
  expect_lt(max(draws), 89 * 365 + 365)
})

test_that("R conditional age of death draw", {
  set.seed(100)
  expect_equal(conditional_lifespan(1, age_of_death, max_age = 89), 29295)
})
