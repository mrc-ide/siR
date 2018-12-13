

N <- 50000
t <- 40000

ca <- current_age(N, equilbrium_age)
da <- sapply(ca, conditional_lifespan, age_of_death)


t1 <- demog_test(N, t, 1, age_of_death, ca, da)
plot(tapply(t1, rep(1:400, each = 100), sum), t = "l", ylim = c(150, 350))


for(i in 1:10){
  ca <- current_age(N, equilbrium_age)
  da <- sapply(ca, conditional_lifespan, age_of_death)
  t1 <- demog_test(N, t, 1, age_of_death, ca, da)
  lines(tapply(t1, rep(1:400, each = 100), sum), t = "l", ylim = c(150, 350), col = rainbow(10)[i])
}

cppFunction('int current_age(std::vector<double> &equilibrium_age) {
  int sum = x + y + z;
  return sum;
}')
