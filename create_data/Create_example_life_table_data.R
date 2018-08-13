# Create Age distribution and Death distribution example data

mali_life_table <- read.csv("create_data/Mali_life_table_example.csv")

reps <- c(1, 4, rep(5, 17))
age <- 1:90

prob_survive <- rep(mali_life_table$Prob_survive, reps)
prob_death <- rep(mali_life_table$Prob_death, reps)

par(mfrow = c(1, 2))
barplot(prob_survive, names.arg = age)
barplot(prob_death, names.arg = age)

devtools::use_data(prob_survive, overwrite = TRUE)
devtools::use_data(prob_death, overwrite = TRUE)
