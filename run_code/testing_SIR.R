
N <- 50000
t <- 20 * 365
t1 <- dplyr::bind_rows(open_sir(N, t, 1, age_of_death, equilibrium_age, 0.2, 0.01, 5))
#t1


plot(t1$S, t = "l", ylim =c (0, N))
lines(t1$I, col = "red")
lines(t1$R, col = "green")

plot(t1$deaths, t = "l")

