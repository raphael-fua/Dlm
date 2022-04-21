# below, set to TRUE if modifications have been made to cpp package
cat('\14')
if(F){ rebuild() }

library(Dlm)
set.seed(1)
noise <- 1
X <- rep(0:1,c(100, 100)) + rnorm(200, 0, noise)
print(scoresAOS(cumsum(0, X)))

if(F) {
# You need to add a S_0 = 0 (empty sum)
S <- matrix(cumsum(c(0,X)), nrow=1)

# Binary Segmentation
print(OneStepSearch(S, shift=0, method="naive"))
print(OneStepSearch(S, shift=0, method="advanced"))
print(OneStepSearch(S, shift=0, method="combined"))
print(OneStepSearch(S, shift=0, method="full"))


for (i in 5:201) {
    SS <- matrix(S[1:i], nrow = 1)
    print(OneStepSearch(SS, shift=0, method="combined")$stat)
}
cat('------------------------------\n')

print(runtimeAOS(S, 6))
print(scoresAOS(S))


# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Test ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

main <- function() {
    set.seed(8)
    p <- 7
    noise <- rnorm(2^p)
    
    cat('==============================\n')
    cat('= Without cp \n')
    cat('==============================\n')
    print(scoresAOS(noise))
    plot(scoresAOS(d = noise, q = q))
    
    cat('\n==============================\n')
    cat('= With cp \n')
    cat('==============================\n')
    d <- noise + c(rep(0, 2^(p-1)), rep(10, 2^(p-1)))
    cat("runtime: ", runtimeGDLM(q = q, d = d, th = threshold), '\n')
    cat("scores: \n")
    print(scoresGDLM(d = d, q = q))
    print(summary(scoresGDLM(d = d, q = q)))
    plot(scoresGDLM(d = d, q = q))
    
    cat('\n==============================\n')
    cat('= runtimeGDLM_allocate  \n')
    cat('==============================\n')
    # cat("runtime: ", runtimeGDLM(q = q, d = noise, th = threshold), '\n')
    # cat("runtime allocate: ", runtimeGDLM_allocate(q = q, d = noise, th = threshold), '\n')
    # cat("runtime: ", runtimeGDLM(q = q, d = d, th = threshold), '\n')
    # cat("runtime allocate: ", runtimeGDLM_allocate(q = q, d = d, th = threshold), '\n')
    print(identical(runtimeGDLM(q = q, d = noise, th = threshold), runtimeGDLM_allocate(q = q, d = noise, th = threshold)))
    print(identical(runtimeGDLM(q = q, d = d, th = threshold), runtimeGDLM_allocate(q = q, d = d, th = threshold)))
    
    
    cat('\n==============================\n')
    cat('= runtimeGDLM_allocate  \n')
    cat('==============================\n')
    # cat("*scores: ", scoresGDLM(d = noise, q = q), '\n\n')
    # cat("*scores allocate: ", scoresGDLM_allocate(d = noise, q = q), '\n\n')
    # cat("*scores: ", scoresGDLM(d = d, q = q), '\n\n')
    # cat("*scores allocate: ", scoresGDLM_allocate(d = d, q = q), '\n')
    print(identical(scoresGDLM_allocate(d = noise, q = q), scoresGDLM_allocate(d = noise, q = q)))
    print(identical(scoresGDLM(d = d, q = q), scoresGDLM(d = d, q = q)))
    
    return(0)
}

main()
}
