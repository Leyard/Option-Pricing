r <- rnorm(2000, mean=4, sd=10)
write.csv(r, "norm.csv", row.names=FALSE)

r <- runif(2000, 4, 10)
write.csv(r, "unif.csv", row.names=FALSE)
