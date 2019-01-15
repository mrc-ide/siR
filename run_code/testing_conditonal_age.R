
devtools::load_all()

N <- 10000
r <- rep(NA, N)
p <- rep(NA, N)

for (i in 1:N){
  r[i] <- conditional_lifespan(2000, age_of_death, max_age = 89)
  p[i] <- draw_equilibrium_death_age(2000, 0:89, age_of_death, 89)

}

summary(r)
summary(p)

plot(density(r))
lines(density(p), col = "red")

# Edge cases
set.seed(100)
conditional_lifespan(0, age_of_death, max_age = 89)


draw_equilibrium_death_age(0, 0:89, age_of_death, 89)
conditional_lifespan(90*365, age_of_death, max_age = 89)
draw_equilibrium_death_age(90*365, 0:89, age_of_death, 89)


mb1 <- microbenchmark::microbenchmark(conditional_lifespan(2000, age_of_death, max_age = 89),
                                      draw_equilibrium_death_age(2000, 0:89, age_of_death, 89),
                                      times = 20000)
mb1
ggplot2::autoplot(mb1)
