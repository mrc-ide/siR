
library(dplyr)
library(ggplot2)

N = 1000000
days = 36500

t1 <- demog_test(N, days, 10, age_dist_ana, prob_death)

bin <- rep(1:365, each = 1000)
out <- data.frame(deaths = t1, bin = bin) %>%
  group_by(bin) %>%
  summarise(deaths = sum(deaths))

ggplot(out, aes(x = bin, y = deaths)) +
  geom_line() +
  theme_bw()

ggplot(out, aes(deaths)) +
  geom_histogram(bins = 50, col = "darkblue", fill = "lightblue") +
  theme_bw()
