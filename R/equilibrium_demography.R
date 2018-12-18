#' Equilibrium age distribution
#'
#' Estimate the equilbrium age distribution given a lifetable (probability, of death in each year).
#' Life table raw data can be obtained from http://apps.who.int/gho/data/node.main.687?lang=en. The input
#' used is the "nqx - probability of dying between ages x and x+n" column, which is then smoothly
#' extrapolated to yearly probabilities.
#'
#' @param life_table Vector of yearly death probability for 0-90.
#'
#' @return Proportion of popution in each age group (at equilibrium)
#' @export
equilibrium_age_distribution <- function(life_table){
  n <- length(life_table)
  if(n != 90) stop("There should be 90 age groups: has the raw data been smoothed?")
  # convert life table to transition matrix
  m <- lifetable_to_transtion_matrix(life_table)

  # convert to rates
  r = m - diag(n)

  # compute Eigenvalues of the rate matrix
  E = eigen(t(r))

  # there should be one Eigenvalue that is zero (up to limit of computational
  # precision). Find which Eigenvalue this is
  w <- which.min(abs(E$values))

  # the stable solution is the corresponding Eigenvector, suitably normalised
  age_stable <- Re(E$vectors[,w] / sum(E$vectors[,w]))

  return(age_stable)
}

#' Equilibrium age of death
#'
#' @inheritParams equilibrium_age_distribution
#'
#' @return
#' @export
#'
#' @examples
equilibrium_age_death <- function(life_table){
  n <- length(life_table)
  age_death <- rep(0, n)
  remaining <- 1
  for (i in 1:n) {
    age_death[i] <- remaining * life_table[i]
    remaining <- remaining * (1 - life_table[i])
  }
  return(age_death)
}

#' Lifetable to transition matrix
#'
#' @inheritParams equilibrium_age_distribution
#'
#' @return Transition matrix
lifetable_to_transtion_matrix <- function(life_table){
  n <- length(life_table)
  m <- matrix(0, n, n)
  m[col(m) == (row(m) + 1)] <- 1 - life_table[1:(n - 1)]
  m[,1] <- 1 - rowSums(m)
  return(m)
}

#' Smooth WHO life table death probabilites
#'
#' Life table raw data can be obtained from http://apps.who.int/gho/data/node.main.687?lang=en.
#'
#' @param probability_of_death Column: "nqx - probability of dying between ages x and x+n"
#'
#' @return Smoothed probability of death
prob_death_who_to_annual <- function(probability_of_death, spar = 0.2){
  start_year <- c(0, 1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85)
  # Age bands (mid-point of the age band)
  age_widths <- c(diff(start_year), 5)
  # Ages (for smoothing input)
  ages_raw <- start_year + age_widths / 2
  # Spline to estimate smoothed death probability as a function of age
  sm_p_death <- smooth.spline(x = ages_raw, y = probability_of_death, spar = spar)
  # All ages
  ages <- 0:89
  # Predicted smoothed death probability for all ages
  smooth_prob <- predict(sm_p_death, ages)$y / (rep(age_widths, age_widths))
  # Final age group must have prob = 1
  smooth_prob[length(smooth_prob)] <- 1
  return(smooth_prob)
}
