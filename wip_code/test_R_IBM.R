# Currently this is pretty much a stochastic model, can include individual heterogeneity into it?
t <- 1:100
i0 <- 1
S <- vector("integer", length = length(t))
I <- vector("integer", length = length(t))
R <- vector("integer", length = length(t))

# Population size
N <- 1000
# Contact 2 people a day
contact_rate = 1 / 0.5
# Prob of infection on infectious contact
prob_infection = 0.5
# Average duration of infection 10 days
sigma_R = 1 / 10

# Input transmission pars
beta <- prob_infection * (1 - exp(- contact_rate))
sigma <- 1 - exp(- sigma_R)

#set.seed(111)
# Initialise infection
first_infected <- sample(1:N, i0)

Ss <- rep(1, N)
Ss[first_infected] <- 0
Is <- rep(0, N)
Is[first_infected] <- 1
Rs <- rep(0, N)

schedule_recovery_time <- rep(NA, N)
schedule_recovery_time[first_infected] <- i + round(rexp(1, sigma))
Ns <- 1:N

for(i in seq_along(t)){
  S[i] <- sum(Ss)
  I[i] <- sum(Is)
  R[i] <- sum(Rs)

  infected <- sample(Ns[Ss == 1], rbinom(n = 1, size = S[i], prob = beta * (I[i] / N)))
  schedule_recovery_time[infected] <- i + round(rexp(length(infected), sigma))

  recovered <- which(schedule_recovery_time == i)

  Ss[infected] <- 0
  Is[infected] <- 1
  Is[recovered] <- 0
  Rs[recovered] <- 1
}

plot(S ~ t, t = "l", ylim = c(0, N))
lines(I ~ t, col = "red")
lines(R ~ t, col = "blue")




