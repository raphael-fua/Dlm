# below, set to TRUE if modifications have been made to cpp package
cat('\14')
if(T){ rebuild() }

set.seed(1)
noise <- 1
X <- rep(0:1,c(100,100)) + rnorm(200, 0, noise)
plot(X)

# You need to add a S_0 = 0 (empty sum)
S <- matrix(cumsum(c(0,X)), nrow=1)

# Binary Segmentation
print(OneStepSearch(S, shift=0, method="naive"))
print(OneStepSearch(S, shift=0, method="advanced"))
print(OneStepSearch(S, shift=0, method="combined"))
print(OneStepSearch(S, shift=0, method="full"))
# $ind = candidate indices
# $stat is CUSUM statistic at ind (sqrt of log-likelihood ratio)
