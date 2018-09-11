# Timing comparison
devtools::load_all()

R <- function(N){
  ibm_closed_sir(N = N, beta = 2, sigma = 1, i0 = 10, t_final = 20, dt = 0.1)
}
Rcpp_basic <- function(N){
  ibm_closed_sir_rcpp(N = N, beta = 2, sigma = 1, i0 = 10, t_final = 20, dt = 0.1)
}
Rcpp_het <- function(N){
  ibm_het(N = N, beta = 2, sigma = 1, i0 = 10, times = seq(0, 20, 0.1), dt = 0.1, het = FALSE,
          age_distribution = age_dist, life_distribution =  prob_death)
}
Rcpp_sch <- function(N){
  ibm_scheduled(sigma = 1, beta = 2, N, i0 = 10, days = 20, 10, age_dist, prob_death)
}


mb1 <- microbenchmark::microbenchmark(R(5000), Rcpp_basic(5000), Rcpp_het(5000), Rcpp_sch(5000),
                                      R(10000), Rcpp_basic(10000), Rcpp_het(10000), Rcpp_sch(10000),
                                      R(50000), Rcpp_basic(50000), Rcpp_het(50000), Rcpp_sch(50000),
                                      times = 20)
mb1
ggplot2::autoplot(mb1)

