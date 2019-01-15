
N <- 20000
t <- 800000
t1 <- demog_test(N, t, 1, age_of_death, equilibrium_age)

plot(tapply(t1$deaths, rep(1:800, each = 100), sum), t = "l", ylim = c(0, 400))


for(i in 1:10){
  t1 <- demog_test(N, t, 1, age_of_death, equilibrium_age)
  lines(tapply(t1, rep(1:800, each = 100), sum), t = "l", ylim = c(150, 350), col = rainbow(10)[i])
}



