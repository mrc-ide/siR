#' Closed SIR (ODIN)
#'
#' @param sigma Recovery rate (1 / mean duration of infection)
#' @param beta Transmission parameter (contact rate * probability of infection upon contact)
#' @param N Population size
#' @param infected Number of infected people at time = 0
#' @param t Vector of times
#'
#' @return Odin closed SIR model output
#' @export
#'
#' @examples
#' m1 <- odin_closed_sir()
#' plot(m1$S ~ m1$t,  t = "l", ylim = c(0, 1001))
#' lines(m1$I ~ m1$t, col = "red")
#' lines(m1$R ~ m1$t,  col = "blue")
odin_closed_sir <- function(sigma = 2, beta = 6, N = 1000, infected = 1,
                            t = seq(0, 10, length.out = 2000)){
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
                   init_S = N - infected, init_I = infected)
  # Run model
  as.data.frame(m1$run(t))
}
