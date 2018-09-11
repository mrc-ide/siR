
library(dplyr)
library(ggplot2)

N = 1000000
days = 10 * 700

t1 <- demog_test(N, days, 10, age_dist, prob_death)

weeks <- rep(1:1000, each = 70)
out <- data.frame(deaths = t1, week = weeks) %>%
  group_by(week) %>%
  summarise(deaths = sum(deaths))

ggplot(out, aes(x = week, y = deaths)) +
  geom_line() +
  theme_bw()

ggplot(out, aes(deaths)) +
  geom_histogram(bins = 50, col = "darkblue", fill = "lightblue") +
  theme_bw()
