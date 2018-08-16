devtools::load_all()

### Equilibrium age distribution
N <- 100000
age <- rep(0, 100000)
death <- sample(0:89, N, prob = prob_death, replace = TRUE)
for(i in 0:1000){
  if(i %% 100 == 0){
    print(i)
  }
  index <- age == death
  age <- age + 1
  age[index] <- 0
  death[index] <- sample(0:89, sum(index), prob = prob_death, replace = T)
}
a2 <- as.vector(table(age))
a2 <- a2 / sum(a2)

system.time(t1 <- demog_test(500000, 365 * 1000, 1, a2, prob_death))
# plot(t1, t = "l")

tcut <- rep(1:1000, each = 365)
ann_Death <- tapply(t1, tcut, sum)
plot(ann_Death )

# Detahs over the first year weird pattern
t2 <- t1[1:(100*365)]
plot(t2)
which(t2 > 1000)
