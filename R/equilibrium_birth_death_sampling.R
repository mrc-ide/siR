#' Draw current age
#'
#' Make draw(s) of current age (in days) at equilbrium
#'
#' @param N Number of people
#' @param equilbrium_age Equilirium age distribution
#'
#' @return A vector of N age draws
#' @export
current_age <- function(N, equilbrium_age){
  current_age_years <- sample(0:89, N, replace = TRUE, prob = equilbrium_age)
  current_age_additional_days <- sample(0:364, N, replace = TRUE)
  current_age_years * 365 + current_age_additional_days
}

#' Draw conditional lifespan
#'
#' Makes a draw of the lifespan (in days), given a current age
#'
#' @param age Current age (days)
#' @param equilbrium_age Equilirium probability of death
#' @param max_age Maximum age (in years, actual maximum is this + 364 days)
#'
#' @return A single conditioned lifespan draw
#' @export
conditional_death_age <- function(age, age_of_death, max_age = 89){
  y <- floor (age / 365)
  d <- age %% 365

  # Options left to sample from
  full_years_available <- max_age - y
  full_days_available <- 365 - d

  # Probability of death in future years (including current year)
  conditional_probs <- tail(age_of_death, full_years_available + 1)
  # Downgrade probability in current year as some has been "lived" already
  conditional_probs[1] <- conditional_probs[1] * (full_days_available / 365)

  # Sample lifespan
  if(y == max_age){
    live_for_years <- max_age
  } else {
    live_for_years <- sample(y:max_age, 1, prob = conditional_probs)
  }

  # If death will occur in current year
  if(live_for_years == y){
    return(y * 365 + sample(d:365, 1))
  }
  # Otherwise
  live_for_days <- sample(1:365, 1)
  lifespan <- live_for_years * 365 + live_for_days
  return(lifespan)
}
