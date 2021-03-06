% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/open_sir_wrapper.R
\name{set_time}
\alias{set_time}
\title{Set time}
\usage{
set_time(out, days, substep)
}
\arguments{
\item{out}{Raw model output}

\item{days}{Number of days}

\item{substep}{Steps per day}
}
\value{
Model output with time columns added
}
\description{
Adds model time and calendar (day, month, year) time to c++ model output
}
