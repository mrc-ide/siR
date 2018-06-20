#' Closed SIR (ODIN)
#'
#' @param sigma Recovery rate (1 / mean duration of infection)
#' @param beta Transmission parameter (contact rate * probability of infection upon contact)
#' @param init Vector of initial values (S, I, R)
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
odin_closed_sir <- function(sigma = 2, beta = 4, init = c(1000, 1, 0), t = seq(0, 10, length.out = 2000)){
  closed_sir <- odin::odin({
    ## Derivatives
    deriv(S) <- -beta * S * (I / N)
    deriv(I) <- (beta * S * (I / N)) - (sigma * I)
    deriv(R) <- sigma * I

    ## Initial conditions
    initial(S) <- init_S
    initial(I) <- init_I
    initial(R) <- init_R
    init_S <- user(1000.0)
    init_I <- user(1.0)
    init_R <- user(0.0)

    # Params
    sigma <- user(2.0)
    beta <- user(4.0)

    N <- S + I + R
  })
  # Generate model
  m1 <- closed_sir(sigma = sigma, beta = beta,
                   init_S = init[1], init_I = init[2], init_R = init[3])
  # Run model
  as.data.frame(m1$run(t))
}
