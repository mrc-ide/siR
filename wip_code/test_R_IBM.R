# Currently this is pretty much a stochastic model, can include individual heterogeneity into it?
t <- 1:100
i0 <- 10

S <- vector("integer", length = length(t))
I <- vector("integer", length = length(t))
R <- vector("integer", length = length(t))

# Population size
N <- 1000
# Tranmission prob
beta <- 0.3
# Average duration of infection 10 days
sigma <- 0.1

# daily prob of infection
prob_recover <- 1 - exp(-sigma)

#set.seed(111)
# Initialise infection
first_infected <- sample(1:N, i0)

Ss <- rep(1, N)
Ss[first_infected] <- 0
Is <- rep(0, N)
Is[first_infected] <- 1
Rs <- rep(0, N)

schedule_recovery_time <- rep(NA, N)
schedule_recovery_time[first_infected] <- 1 + round(rexp(length(first_infected), prob_recover))
Ns <- 1:N

# Calculate the output variables
S[1] <- sum(Ss)
I[1] <- sum(Is)
R[1] <- sum(Rs)

for(i in 2:length(t)){
  # Sample people who get infected
  infected <- Ns[Ss == 1][rbinom(S[i - 1], 1, beta * I[i-1] / N) == 1]# sample(Ns[Ss == 1], rbinom(n = 1, size = S[i - 1], prob = prob_infect * (I[i - 1] / N)))
  # Set recovery time for those people just infected
  schedule_recovery_time[infected] <- i + round(rexp(length(infected), prob_recover))
  #print(i)
  #print(max(schedule_recovery_time, na.rm = TRUE))
  # Update status of those infected S->I
  Ss[infected] <- 0
  Is[infected] <- 1

  #  Update status of people scehduled to recover at current time point
  recovered <- schedule_recovery_time == i
  Is[recovered] <- 0
  Rs[recovered] <- 1

  # Calculate the output variables
  S[i] <- sum(Ss)
  I[i] <- sum(Is)
  R[i] <- sum(Rs)
}

#plot(NA, xlim = c(0, max(t)), ylim = c(0, N))
lines(S ~ t, lwd = 5)
lines(I ~ t, col = "red", lwd = 5)
lines(R ~ t, col = "blue", lwd = 5)

det <- odin_closed_sir(sigma = sigma, beta = beta, N = N,infected = i0, t = seq(1, max(t), 0.01))
lines(det$S ~ det$t, col = 'green', lty = 1, lwd = 2)
lines(det$I ~ det$t, col = 'green', lty = 1, lwd = 2)
lines(det$R ~ det$t, col = 'green', lty = 1, lwd = 2)

