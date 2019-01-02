r <- rnorm(2000, mean=4, sd=10)
write.csv(r, "norm.csv", row.names=FALSE)

r <- runif(2000, 4, 10)
write.csv(r, "unif.csv", row.names=FALSE)
<<<<<<< HEAD


y <- c(1.5, 2.4, 3.2, 4.8,  5.0, 7.0,  8.43)
x <- c(3.5, 5.3, 7.7, 6.2, 11.0, 9.5, 10.27)

model <- lm(y~x)
summary(model)


=======
>>>>>>> 0746138df6fe69b5832ec97b20dc6dadac256a7f
