#' Closed SIR (IBM)
#'
#' @param sigma Recovery rate (1 / mean duration of infection)
#' @param beta  Transmission parameter
#' @param N Population size
#' @param i0 Number of infected people at time = 0
#' @param t_final End time
#' @param dt time step
#'
#' @return IBM closed SIR model output
#' @export
ibm_closed_sir <- function(sigma = 2, beta = 6, N = 1000, i0 = 1,
                           t_final = 100, dt = 0.01){

  # Create vector of times
  t <- seq(0, t_final, dt)

  # daily prob of infection
  prob_recover <- rate_to_prob(sigma, dt)

  # State variables
  S <- vector("integer", length = length(t))
  I <- vector("integer", length = length(t))
  R <- vector("integer", length = length(t))

  # Individual variables
  susceptible <- rep(1, N)
  infected <- rep(0, N)
  recovered <- rep(0, N)
  schedule_recovery_time <- rep(0, N)
  Ns <- 1:N
  N_inv <- 1 / N

  # Initialise infection
  first_infected <- sample(Ns, i0)
  susceptible[first_infected] <- 0
  infected[first_infected] <- 1

  # Calculate the output variables
  S[1] <- sum(susceptible)
  I[1] <- sum(infected)
  R[1] <- sum(recovered)

  for(i in 2:length(t)){
    # Sample people who get infected
    prob_inf <- infection_probability(beta = beta, I_prev = I[i - 1], N_inv = N_inv, dt = dt)
    infected_t <- draw_sample(people = Ns[susceptible == 1],prob = prob_inf)
    # Sample people who recover
    recovered_t <- draw_sample(people = Ns[infected == 1], prob = prob_recover)

    # Update status of those infected S->I
    susceptible[infected_t] <- 0
    infected[infected_t] <- 1

    # Update status of people scehduled to recover at current time point
    infected[recovered_t] <- 0
    recovered[recovered_t] <- 1

    # Calculate the output variables
    S[i] <- sum(susceptible)
    I[i] <- sum(infected)
    R[i] <- sum(recovered)
  }
  out <- data.frame(t = t, S = S, I = I, R = R)
  return(out)
}

#' Calculate the current probability of infection
#'
#' @param I_prev Number of infected people in previous timestep
#' @param N_inv  Inverse of the number of people
#' @inheritParams ibm_closed_sir
#'
#' @return Probability of infection
infection_probability <- function(beta, I_prev, N_inv, dt){
  rate_to_prob(rate = beta * I_prev * N_inv, dt = dt)
}

#' Sample events for a group of individuals from binomial
#'
#' @param people index of individuals
#' @param prob Binomial probability
#'
#' @return Sampled successes from people
draw_sample <- function(people, prob){
  sample(people, rbinom(n = 1, size = length(people), prob = prob))
}

#' Convert a rate to a probability
#'
#' @param rate Rate
#' @param timestep
#'
#' @return A probability
rate_to_prob <- function(rate, dt){
  1 - exp(-rate * dt)
}

