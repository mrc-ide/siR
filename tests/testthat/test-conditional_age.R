context("test-conditional_age")

test_that("Equilibrium death age", {
  set.seed(100)
  expect_equal(draw_equilibrium_death_age(2000, 0:89, age_of_death, 89), 22360)
  expect_equal(draw_equilibrium_death_age(0, 0:89, age_of_death, 89), 25571)
  expect_equal(draw_equilibrium_death_age(90 * 365 - 1, 0:89, age_of_death, 89), 365 * 90)
  expect_error(draw_equilibrium_death_age(90 * 365, 0:89, age_of_death, 89))
})

test_that("Equilibrium age", {
  set.seed(100)
  expect_equal(draw_equilibrium_age(0:89, equilibrium_age), 7394)
  max_age <- -Inf
  min_age <- Inf
  for(i in 1:100000){
    temp <- draw_equilibrium_age(0:89, equilibrium_age)
    max_age <- max(max_age, temp)
    min_age <- min(min_age, temp)
  }
  expect_gt(min_age, -1)
  expect_lt(max_age, 89 * 365 + 365)
})
