
devtools::load_all()

N <- 1000
t <- 365 * 5
step <- 1
beta <- 0.03
sigma <- 0.005
i0 <- 20

par(mfrow = c(1, 3))
## Example closed (All deaths at 90) ###########################################
aod <- c(rep(0,89), 1)
plot(NA, ylim = c(0, N), xlim = c(0, t * step), ylab = "N", xlab = "Time")

for(i in 1:20){
  t1 <- open_sir(N, t, step, sigma, beta, i0, aod, equilibrium_age)
  lines(t1$S ~ t1$t)
  lines(t1$I ~ t1$t, col = "red")
  lines(t1$R ~ t1$t, col = "purple")
}

det <- odin_closed_sir(N = N, beta = beta, sigma = sigma,
                       i0 = i0, days = t, substep = step)
lines(det$S ~ det$t, col = 'green', lty = 1, lwd = 2)
lines(det$I ~ det$t, col = 'green', lty = 1, lwd = 2)
lines(det$R ~ det$t, col = 'green', lty = 1, lwd = 2)

t2 <- ibm_closed_sir(N = N, beta = beta, sigma = sigma,
                        i0 = i0, days = t, substep = step)
lines(t2$S ~ t2$t)
################################################################################

## Example R closed ###########################################
plot(NA, ylim = c(0, N), xlim = c(0, t * step), ylab = "N", xlab = "Time")

for(i in 1:20){
  t1 <- ibm_closed_sir(N = N, beta = beta, sigma = sigma,
                       i0 = i0, days = t, substep = step)
  lines(t1$S)
  lines(t1$I, col = "red")
  lines(t1$R, col = "purple")
}

det <- odin_closed_sir(N = N, beta = beta, sigma = sigma,
                       i0 = i0, days = t, substep = step)
lines(det$S ~ det$t, col = 'green', lty = 1, lwd = 2)
lines(det$I ~ det$t, col = 'green', lty = 1, lwd = 2)
lines(det$R ~ det$t, col = 'green', lty = 1, lwd = 2)
################################################################################

# Example open #################################################################
# Secondary epidemics
N <- 5000
beta2 <- 0.007
sigma2 <- 0.0013
t <- 365 * 100
step <- 1
plot(NA, ylim = c(0, N), xlim = c(0, t * step), ylab = "N", xlab = "Time")

for(i in 1:10){
  t1 <- open_sir(N, t, step, sigma2, beta2, i0, age_of_death, equilibrium_age)
  lines(t1$S ~ t1$t)
  lines(t1$I ~ t1$t, col = "red")
  lines(t1$R ~ t1$t, col = "purple")
}
