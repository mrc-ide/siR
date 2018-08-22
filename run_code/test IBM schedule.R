devtools::load_all()

# Sort out rates and substeps
t2 <- ibm_scheduled(0.5, 1, 10000, 20, 50, 52, age_dist, prob_death)

plot(t2[[1]],  t = "l", ylim = c(0, 10000))
lines(t2[[2]], t= "l", col = "red")
lines(t2[[3]], t= "l", col = "blue")
