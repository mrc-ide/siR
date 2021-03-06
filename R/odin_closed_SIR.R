#' Closed SIR (ODIN)
#'
#' @param sigma Recovery rate (1 / mean duration of infection)
#' @param beta  Transmission parameter
#' @param N Population size
#' @param i0 Number of infected people at time = 0
#' @param days Number of days
#' @param substep Number of substeps per day
#'
#' @return Odin closed SIR model output
#' @export
odin_closed_sir <- function(N = 1000, days = 100, substep = 1,
                            sigma = 2, beta = 6,  i0 = 1){

  dt <- 1 / substep
  beta <- beta / substep
  sigma <- sigma / substep

  closed_sir <- odin::odin({
    ## Derivatives
    deriv(S) <- -beta * S * (I / N)
    deriv(I) <- (beta * S * (I / N)) - (sigma * I)
    deriv(R) <- sigma * I

    ## Initial conditions
    initial(S) <- init_S
    initial(I) <- init_I
    initial(R) <- init_R
    init_S <- user()
    init_I <- user()
    init_R <- 0.0

    # Params
    sigma <- user()
    beta <- user()
    N <- user()

  })
  # Generate model
  m1 <- closed_sir(sigma = sigma, beta = beta, N = N,
                   init_S = N - i0, init_I = i0)
  # Run model
  as.data.frame(m1$run(seq(0, days, dt)))
}
