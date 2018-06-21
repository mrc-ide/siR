# Comparing closed SIR models

t_f <- 20
beta <- 2
sigma <- 1
N <- 1000
i0 <- 10

plot(NA, xlim = c(1, t_f), ylim = c(0, N), xlab = "Time", ylab = "N")

for(i in 1:10){
  t1 <- ibm_closed_SIR(N = N, beta = beta, sigma = sigma, i0 = i0, t_final = t_f, dt = 0.01)
  lines(t1$S ~ t1$t, col = scales::alpha("black", 0.2))
  lines(t1$I ~ t1$t, col = scales::alpha("red", 0.2))
  lines(t1$R ~ t1$t, col = scales::alpha("blue", 0.2))
}

det <- odin_closed_sir(N = N, beta = beta, sigma = sigma, i0 = i0, t_final = t_f, dt = 0.01)
lines(det$S ~ det$t, col = 'green', lty = 1, lwd = 2)
lines(det$I ~ det$t, col = 'green', lty = 1, lwd = 2)
lines(det$R ~ det$t, col = 'green', lty = 1, lwd = 2)
