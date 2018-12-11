# Create Age distribution and Death distribution example data

mali_life_table <- read.csv("create_data/Mali_life_table_example.csv")
t1 <- mali_life_table$Dying / mali_life_table$Alive


# Probability of Dying in each age group
prob_death_raw <- mali_life_table$Dying
prob_death_raw <- prob_death_raw / sum(prob_death_raw)
# Age distribution
age_dist_raw <- mali_life_table$Alive
age_dist_raw <- age_dist_raw / sum(age_dist_raw)
# Age bands (mid-point of the age band)
ages_raw <- mali_life_table$Start_year + (c(1, 4, rep(5, 17)) / 2)


# Smoothing splines
sm_death <- smooth.spline(x = ages_raw, y = prob_death_raw, spar = 0.2)
sm_dist <- smooth.spline(x = ages_raw, y = age_dist_raw, spar = 0.2)

# Smoothed
ages <- 0:89
prob_death <- predict(sm_death, ages)$y
age_dist <- predict(sm_dist, ages)$y

# View smoothed outputs
par(mfrow = c(1, 2))
plot(prob_death ~ ages, pch = 19)
points(prob_death_raw ~ ages_raw, col = "green", pch = 19)
plot(age_dist ~ ages, pch = 19)
points(age_dist_raw ~ ages_raw, col = "red", pch = 19)

# standardise
prob_death <- prob_death / sum(prob_death)
age_dist <- age_dist / sum(age_dist)

# Equilibrium age distribution (numerical estimation)
N <- 500000
ages <- 0:89
age <- rep(0, N)
death <- sample(ages, N, prob = prob_death, replace = TRUE)
for(i in 0:5000){
  index <- age == death
  age <- age + 1
  age[index] <- 0
  death[index] <- sample(ages, sum(index), prob = prob_death, replace = T)
}
age_dist_num <- as.vector(table(age))
age_dist_num <- age_dist_num / sum(age_dist_num)

# Equilibrium age distribution (analytical estimate)
age_dist_ana <- (1 - cumsum(prob_death))
age_dist_ana <- age_dist_ana / sum(age_dist_ana)

# Plot comparison
par(mfrow = c(1, 1))
plot(age_dist_num ~ ages, ylim = c(0, 0.018))
lines(age_dist ~ ages, col = "red", lwd = 2)
lines(ages, age_dist_ana, col = "green", lwd = 2)

# Add data for testing
devtools::use_data(prob_death, overwrite = TRUE)

## Currently age_dist and age_dist_ana are not at equilibrum when testing_demography.R is run,
  # BUT ... numerical solution is (or appears to be)
devtools::use_data(age_dist, overwrite = TRUE)
devtools::use_data(age_dist_num, overwrite = TRUE)
devtools::use_data(age_dist_ana, overwrite = TRUE)


plot(data.frame(age_dist, age_dist_ana, age_dist_num))
abline(0,1)
