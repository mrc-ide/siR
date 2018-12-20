context("test-conditional_age")

test_that("Equilibrium death age", {
  set.seed(100)
  expect_equal(draw_equilibrium_death_age(2000, 0:89, age_of_death, 89), 22360)
  expect_equal(draw_equilibrium_death_age(0, 0:89, age_of_death, 89), 25571)
  expect_equal(draw_equilibrium_death_age(90 * 365 - 1, 0:89, age_of_death, 89), 365 * 90 -1)
  expect_error(draw_equilibrium_death_age(90 * 365, 0:89, age_of_death, 89))
})
