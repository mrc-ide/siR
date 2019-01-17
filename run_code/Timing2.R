# Timing comparison
devtools::load_all()

aod <- c(rep(0,89), 1)

r <- function(N){
  ibm_closed_sir(N = N, beta = 0.03, sigma = 0.005, i0 = 10, days = 3650, substep = 1)
}
rcpp <- function(N){
  open_sir(N = N , 3650, 1, aod, equilibrium_age, 0.03,
           0.005, 10)
}



mb1 <- microbenchmark::microbenchmark(r(5000), rcpp(5000),
                                      r(10000), rcpp(10000),
                                      r(50000), rcpp(50000),
                                      times = 20)
mb1
ggplot2::autoplot(mb1)

