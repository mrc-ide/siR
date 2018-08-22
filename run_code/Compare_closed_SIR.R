# Comparing closed SIR models

# 50 Years
t_f <- 50
# Week timestep
dt = 1/52
# Pop size
N <- 10000
# Initial infected
i0 <- 20
# Transmission parameters
beta <- 1
sigma <- 0.5


plot(NA, xlim = c(0, t_f), ylim = c(0, N), xlab = "Time", ylab = "N")
ind <- seq(1, t_f/dt, length.out = 100)

for(i in 1:10){
  t1 <- ibm_closed_sir(N = N, beta = beta, sigma = sigma, i0 = i0, t_final = t_f, dt = dt)
  t1 <- lapply(t1, function(x){x[ind]})
  lines(t1$S ~ t1$t, col = scales::alpha("black", 0.2))
  lines(t1$I ~ t1$t, col = scales::alpha("black", 0.2))
  lines(t1$R ~ t1$t, col = scales::alpha("black", 0.2))
}

for(i in 1:10){
  t1 <- ibm_closed_sir_rcpp(N = N, beta = beta, sigma = sigma, i0 = i0, t_final = t_f, dt = dt)
  t1 <- lapply(t1, function(x){x[ind]})
  lines(t1$S ~ t1$t, col = scales::alpha("purple", 0.5))
  lines(t1$I ~ t1$t, col = scales::alpha("purple", 0.5))
  lines(t1$R ~ t1$t, col = scales::alpha("purple", 0.5))
}

for(i in 1:10){
  t1 <- ibm_het(N = N, beta = beta, sigma = sigma, i0 = i0, times = seq(0, t_f, dt), dt = dt)
  t1 <- lapply(t1, function(x){x[ind]})
  lines(t1$S ~ t1$t, col = scales::alpha("blue", 0.5))
  lines(t1$I ~ t1$t, col = scales::alpha("blue", 0.5))
  lines(t1$R ~ t1$t , col = scales::alpha("blue", 0.5))
}

for(i in 1:10){
  t1 <- ibm_het(N = N, beta = beta, sigma = sigma, i0 = i0, times = seq(0, t_f, dt), dt = dt, het = TRUE)
  t1 <- lapply(t1, function(x){x[ind]})
  lines(t1$S ~ t1$t, col = scales::alpha("orange", 0.5))
  lines(t1$I ~ t1$t, col = scales::alpha("orange", 0.5))
  lines(t1$R ~ t1$t , col = scales::alpha("orange", 0.5))
}

for(i in 1:10){
  t1 <- ibm_scheduled(sigma, beta, N, i0, t_f, 52, age_dist, prob_death)
  t1 <- lapply(t1, function(x){x[ind]})
  lines((ind / 52), t1[[1]], col = scales::alpha("deepskyblue", 1))
  lines((ind / 52), t1[[2]], col = scales::alpha("deepskyblue", 1))
  lines((ind / 52), t1[[3]] , col = scales::alpha("deepskyblue", 1))
}


det <- odin_closed_sir(N = N, beta = beta, sigma = sigma, i0 = i0, t_final = t_f, dt = dt)
lines(det$S ~ det$t, col = 'green', lty = 1, lwd = 2)
lines(det$I ~ det$t, col = 'green', lty = 1, lwd = 2)
lines(det$R ~ det$t, col = 'green', lty = 1, lwd = 2)
