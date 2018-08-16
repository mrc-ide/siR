# Create Age distribution and Death distribution example data

mali_life_table <- read.csv("create_data/Mali_life_table_example.csv")

prob_death <- mali_life_table$P_alive
prob_death <- prob_death / sum(prob_death)

reps <- c(1, 4, rep(5, 17))
age_cat <- 0:89

prob_death <- rep(prob_death, reps)

# Equilibrium age distribution (estimation)
N <- 100000
age <- rep(0, N)
death <- sample(0:89, N, prob = prob_death, replace = TRUE)
for(i in 0:1000){
  index <- age == death
  age <- age + 1
  age[index] <- 0
  death[index] <- sample(0:89, sum(index), prob = prob_death, replace = T)
}
age_dist <- as.vector(table(age))
age_dist <- age_dist / sum(age_dist)

par(mfrow = c(1, 2))
barplot(age_dist, names.arg = age_cat)
barplot(prob_death, names.arg = age_cat)

devtools::use_data(prob_death, overwrite = TRUE)
devtools::use_data(age_dist, overwrite = TRUE)
