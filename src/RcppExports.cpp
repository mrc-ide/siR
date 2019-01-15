// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// demog_test
Rcpp::List demog_test(int N, int days, int substep, std::vector<double> age_of_death, std::vector<double> equilibrium_age);
RcppExport SEXP _siR_demog_test(SEXP NSEXP, SEXP daysSEXP, SEXP substepSEXP, SEXP age_of_deathSEXP, SEXP equilibrium_ageSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type N(NSEXP);
    Rcpp::traits::input_parameter< int >::type days(daysSEXP);
    Rcpp::traits::input_parameter< int >::type substep(substepSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type age_of_death(age_of_deathSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type equilibrium_age(equilibrium_ageSEXP);
    rcpp_result_gen = Rcpp::wrap(demog_test(N, days, substep, age_of_death, equilibrium_age));
    return rcpp_result_gen;
END_RCPP
}
// draw_equilibrium_age
int draw_equilibrium_age(std::vector<int>& age_years, std::vector<double>& equilibrium_age);
RcppExport SEXP _siR_draw_equilibrium_age(SEXP age_yearsSEXP, SEXP equilibrium_ageSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<int>& >::type age_years(age_yearsSEXP);
    Rcpp::traits::input_parameter< std::vector<double>& >::type equilibrium_age(equilibrium_ageSEXP);
    rcpp_result_gen = Rcpp::wrap(draw_equilibrium_age(age_years, equilibrium_age));
    return rcpp_result_gen;
END_RCPP
}
// draw_equilibrium_death_age
int draw_equilibrium_death_age(int age, std::vector<int>& age_years, std::vector<double> age_of_death, int max_age);
RcppExport SEXP _siR_draw_equilibrium_death_age(SEXP ageSEXP, SEXP age_yearsSEXP, SEXP age_of_deathSEXP, SEXP max_ageSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type age(ageSEXP);
    Rcpp::traits::input_parameter< std::vector<int>& >::type age_years(age_yearsSEXP);
    Rcpp::traits::input_parameter< std::vector<double> >::type age_of_death(age_of_deathSEXP);
    Rcpp::traits::input_parameter< int >::type max_age(max_ageSEXP);
    rcpp_result_gen = Rcpp::wrap(draw_equilibrium_death_age(age, age_years, age_of_death, max_age));
    return rcpp_result_gen;
END_RCPP
}
// sample_int
int sample_int(int from, int to);
RcppExport SEXP _siR_sample_int(SEXP fromSEXP, SEXP toSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type from(fromSEXP);
    Rcpp::traits::input_parameter< int >::type to(toSEXP);
    rcpp_result_gen = Rcpp::wrap(sample_int(from, to));
    return rcpp_result_gen;
END_RCPP
}
// sample_double
double sample_double(double from, double to);
RcppExport SEXP _siR_sample_double(SEXP fromSEXP, SEXP toSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type from(fromSEXP);
    Rcpp::traits::input_parameter< double >::type to(toSEXP);
    rcpp_result_gen = Rcpp::wrap(sample_double(from, to));
    return rcpp_result_gen;
END_RCPP
}
// weighted_sample_int
int weighted_sample_int(std::vector<int>& x, std::vector<double>& weights);
RcppExport SEXP _siR_weighted_sample_int(SEXP xSEXP, SEXP weightsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<int>& >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::vector<double>& >::type weights(weightsSEXP);
    rcpp_result_gen = Rcpp::wrap(weighted_sample_int(x, weights));
    return rcpp_result_gen;
END_RCPP
}
// weighted_sample_double
double weighted_sample_double(std::vector<double>& x, std::vector<double>& weights);
RcppExport SEXP _siR_weighted_sample_double(SEXP xSEXP, SEXP weightsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double>& >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::vector<double>& >::type weights(weightsSEXP);
    rcpp_result_gen = Rcpp::wrap(weighted_sample_double(x, weights));
    return rcpp_result_gen;
END_RCPP
}
// weighted_sample_min_int
int weighted_sample_min_int(std::vector<int>& x, std::vector<double>& weights, int lower);
RcppExport SEXP _siR_weighted_sample_min_int(SEXP xSEXP, SEXP weightsSEXP, SEXP lowerSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<int>& >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::vector<double>& >::type weights(weightsSEXP);
    Rcpp::traits::input_parameter< int >::type lower(lowerSEXP);
    rcpp_result_gen = Rcpp::wrap(weighted_sample_min_int(x, weights, lower));
    return rcpp_result_gen;
END_RCPP
}
// weighted_sample_min_double
double weighted_sample_min_double(std::vector<double>& x, std::vector<double>& weights, int lower);
RcppExport SEXP _siR_weighted_sample_min_double(SEXP xSEXP, SEXP weightsSEXP, SEXP lowerSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< std::vector<double>& >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::vector<double>& >::type weights(weightsSEXP);
    Rcpp::traits::input_parameter< int >::type lower(lowerSEXP);
    rcpp_result_gen = Rcpp::wrap(weighted_sample_min_double(x, weights, lower));
    return rcpp_result_gen;
END_RCPP
}
// years_to_steps
int years_to_steps(const int years, const int substep);
RcppExport SEXP _siR_years_to_steps(SEXP yearsSEXP, SEXP substepSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const int >::type years(yearsSEXP);
    Rcpp::traits::input_parameter< const int >::type substep(substepSEXP);
    rcpp_result_gen = Rcpp::wrap(years_to_steps(years, substep));
    return rcpp_result_gen;
END_RCPP
}
// days_to_steps
int days_to_steps(const int days, const int substep);
RcppExport SEXP _siR_days_to_steps(SEXP daysSEXP, SEXP substepSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const int >::type days(daysSEXP);
    Rcpp::traits::input_parameter< const int >::type substep(substepSEXP);
    rcpp_result_gen = Rcpp::wrap(days_to_steps(days, substep));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_siR_demog_test", (DL_FUNC) &_siR_demog_test, 5},
    {"_siR_draw_equilibrium_age", (DL_FUNC) &_siR_draw_equilibrium_age, 2},
    {"_siR_draw_equilibrium_death_age", (DL_FUNC) &_siR_draw_equilibrium_death_age, 4},
    {"_siR_sample_int", (DL_FUNC) &_siR_sample_int, 2},
    {"_siR_sample_double", (DL_FUNC) &_siR_sample_double, 2},
    {"_siR_weighted_sample_int", (DL_FUNC) &_siR_weighted_sample_int, 2},
    {"_siR_weighted_sample_double", (DL_FUNC) &_siR_weighted_sample_double, 2},
    {"_siR_weighted_sample_min_int", (DL_FUNC) &_siR_weighted_sample_min_int, 3},
    {"_siR_weighted_sample_min_double", (DL_FUNC) &_siR_weighted_sample_min_double, 3},
    {"_siR_years_to_steps", (DL_FUNC) &_siR_years_to_steps, 2},
    {"_siR_days_to_steps", (DL_FUNC) &_siR_days_to_steps, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_siR(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
