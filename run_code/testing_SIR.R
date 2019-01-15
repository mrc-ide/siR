
N <- 5000
t <- 365 * 10
t1 <- dplyr::bind_rows(open_sir(N, t, 1, age_of_death, equilibrium_age, 0.03, 0.005, 20))
#t1


plot(t1$S, t = "l", ylim =c (0, N))
lines(t1$I, col = "red")
lines(t1$R, col = "green")

plot(t1$deaths, t = "l")

