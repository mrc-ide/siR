#ifndef sample_h
#define sample_h

int sample_int(int from, int to);
double sample_double(double from, double to);
int weighted_sample_int(std::vector<int> &x, std::vector<double> &weights);
double weighted_sample_double(std::vector<double> &x, std::vector<double> &weights);
int weighted_sample_min_int(std::vector<int> &x, std::vector<double> &weights, int lower);
double weighted_sample_min_double(std::vector<double> &x, std::vector<double> &weights, int lower);
#endif
