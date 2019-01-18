
#' Open sIR
#'
#' Open SIR IBM, implemented internally in c++
#'
#' @param N Number of individuals
#' @param days Number of days
#' @param substep Steps per day
#' @param sigma Recovery rate
#' @param beta Infection rate
#' @param i0 Initial number of infected
#' @param aod Distribution of age of death
#' @param eq Equilibrium age distribution
#'
#' @return A processed data.frame of model output
open_sir <- function(N = 1000, days = 100, substep = 1,
                     sigma = 0.003, beta = 0.05,  i0 = 10,
                     aod = age_of_death,
                     eq = equilibrium_age){

  open_sir_rcpp(N, days, substep, aod, eq, beta,
                sigma, i0) %>%
    post(days, substep)
}

#' Model times
#'
#' @inheritParams open_sir
#'
#' @return Vector of times
get_time <- function(days, substep){
  time <- seq(0, days, 1 / substep)
  time[-length(time)]
}

#' Set time
#'
#' Adds model time and calendar (day, month, year) time to c++ model output
#'
#' @param out Raw model output
#' @inheritParams open_sir
#'
#' @return Model output with time columns added
set_time <- function(out, days, substep){
  month_length <- c(31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)
  time <- get_time(days, substep)

  out %>%
    dplyr::mutate(t = time,
           day = rep(rep(1:365, each = substep), length.out = n()),
           week = rep(rep(1:52, each = substep * 7), length.out = n()),
           month = rep(rep(1:12, substep * month_length), length.out = n()),
           year = rep(rep(1:1000, each = substep * 365), length.out = n()))
}


#' Format c++
#'
#' Formats c++ model output (column order and selection)
#'
#' @inheritParams set_time
#'
#' @return Formated output
format_cpp <- function(out){
  out %>%
    dplyr::select(t, day, week, month, year, S, I, R, deaths)
}

#' Post processing wrapper for c++ output
#'
#' @inheritParams open_sir
#' @inheritParams set_time
#'
#' @return Processed c++ output
post <- function(out, days, substep){
  time <- get_time(days, substep)

  out %>%
    dplyr::bind_rows() %>%
    set_time(days, substep) %>%
    format_cpp()
}
