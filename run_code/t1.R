devtools::load_all()

t1 <- demog_test(100000, 365 * 100, 1, prob_survive, prob_death)
plot(t1, t = "l")

tcut <- rep(1:100, each = 3650)
ann_Death <- tapply(t1, tcut, sum)
plot(ann_Death)
