

N <- 50000
t <- 40000

ca <- current_age(N, equilibrium_age)
da <- sapply(ca, conditional_lifespan, age_of_death)


t1 <- demog_test(N, t, 1, age_of_death, ca, da)
plot(tapply(t1, rep(1:400, each = 100), sum), t = "l", ylim = c(150, 350))


for(i in 1:10){
  ca <- current_age(N, equilibrium_age)
  da <- sapply(ca, conditional_lifespan, age_of_death)
  t1 <- demog_test(N, t, 1, age_of_death, ca, da)
  lines(tapply(t1, rep(1:400, each = 100), sum), t = "l", ylim = c(150, 350), col = rainbow(10)[i])
}

current_age_years <- sample(0:89, N, replace = TRUE, prob = equilibrium_age)
current_age_additional_days <- sample(0:364, N, replace = TRUE)
current_age_years * 365 + current_age_additional_days

N <- 1000000
ca <- current_age(N, equilibrium_age)
ca2 <- rep(NA, N)
for(i in 1:N){
  ca2[i] <- current_age2(equilibrium_age)
}
plot(density(ca))
lines(density(ca2), col = "red")


cppFunction('int s1(NumericVector a, int n) {
  Rcpp::sample(a, n);
}')
