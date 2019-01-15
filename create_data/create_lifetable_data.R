# *•.¸¸¸.•*¨¨*•.¸¸¸.•* Create lifetable data *•.¸¸¸.•*¨¨*•.¸¸¸.•* #

# Creates demography data for use in model (from an example of Mali WHO lifetable data)

# Load the data
life_table<- read.csv("create_data/Mali_life_table_example.csv")$P_death
# Smooth to all yearly age groups
smooth_life_table <- prob_death_who_to_annual(life_table)
# Estimate probability fo death in each age group
age_of_death <- equilibrium_age_death(smooth_life_table)
# Estimate equilbrium age distribution
equilibrium_age <- equilibrium_age_distribution(smooth_life_table)
# View outputs
par(mfrow = c(1, 2))
plot(age_of_death, ylab = "Probability", main = "Age of death", pch = 19)
plot(equilibrium_age, ylab = "Probability", main = "Age distribution", pch = 19)
#Save data for use in package
devtools::use_data(age_of_death)
devtools::use_data(equilibrium_age)
