devtools::load_all()

system.time(t1 <- demog_test(500000, 365 * 50, 1, age_dist, prob_death))

tcut <- rep(1:(200*5), each = 365/5)
ann_Death <- tapply(t1, tcut, sum)
plot(ann_Death)
plot(t1, t = "l")
