# Timing comparison
devtools::load_all()

R <- function(N){
  ibm_closed_sir(N = N, beta = 2, sigma = 1, i0 = 10, t_final = 20, dt = 0.01)
}
Rcpp1 <- function(N){
  ibm_closed_sir_rcpp(N = N, beta = 2, sigma = 1, i0 = 10, t_final = 20, dt = 0.01)
}
Rcpp2 <- function(N){
  ibm_closed_sir_rcpp2(N = N, beta = 2, sigma = 1, i0 = 10, t_final = 20, dt = 0.01)
}
Rcpp3 <- function(N){
  ibm_closed_sir_rcpp3(N = N, beta = 2, sigma = 1, i0 = 10, t_final = 20, dt = 0.01)
}

mb1 <- microbenchmark::microbenchmark(R(5000), Rcpp1(5000), Rcpp2(5000), Rcpp3(5000),
                                      R(10000), Rcpp1(10000), Rcpp2(10000), Rcpp3(10000),
                                      times = 3)
mb1
ggplot2::autoplot(mb1)

