# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Instructions before running ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# 1) Before sourcing this file execute: setwd("simulations")

source('helper_functions.r')
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Core functions ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
MAXcusum <- function(idx, sums) {
    if(length(idx) <= 1) {
        return(0)
    }
    
    s <- head(idx, -1)
    sl <- head(sums, -1)
    
    t <- tail(idx, 1)
    st <- tail(sums, 1)
    
    return(max(sqrt(t / (s * (t - s))) * abs(s / t * st - sl)))
}

runtimeGDLM <- function(q, d, th) {
    S <- cumsum(d)
    m <- matrix(NA, nrow = 2^q, ncol = 1)
    k <- 1 # counter
    tmp <- NA
    
    t <- 1 # t = time corresponds to new data
    while(t <= length(d)) {
        tmp[1] <- m[1, 1]
        m[2, 1] <- m[1, 1]
        m[1, 1] <- t
        
        zeroIDX <- which(k == 0)
        if(length(zeroIDX) == 0) {
            k <- c(k, 0)
            zeroIDX <- which(k == 0)
            m <- cbind(m, matrix(NA, nrow = 2^q, ncol = 1))
            tmp <- c(tmp, NA)
        }
        
        for(i in 2:zeroIDX[1]){
            tmp[i] <- m[1, i]
            m[, i] <- c(tmp[i -1], head(m[, i], -1))
            k[i] <- (k[i]+1)%%2
        }
        idx <- unique(sort(na.omit(c(m))))
        if(MAXcusum(idx, S[idx]) > th) {
            return(t)
        }
        t <- t + 1
    }
    return(t)
}

runtimeGDLM_allocate <- function(q, d, th) {
    S <- cumsum(d)
    C <- ceiling(log(length(d), 2)) + 3
    m <- matrix(NA, nrow = 2^q, ncol = C)
    k <- rep(0, C)
    k[1] <- 1 
    tmp <- rep(NA, C)
    
    t <- 1 # t = time corresponds to new data
    while(t <= length(d)) {
        tmp[1] <- m[1, 1]
        m[2, 1] <- m[1, 1]
        m[1, 1] <- t
        
        for(i in 2:which(k == 0)[1]){
            tmp[i] <- m[1, i]
            m[, i] <- c(tmp[i -1], head(m[, i], -1))
            k[i] <- (k[i]+1)%%2
        }
        idx <- unique(sort(na.omit(c(m))))
        if(MAXcusum(idx, S[idx]) > th) {
            return(t)
        }
        t <- t + 1
    }
    return(t)
}

scoresGDLM_allocate <- function(d, q) {
    S <- cumsum(d)
    maxs <- rep(NA, length(d))
    

    C <- ceiling(log(length(d), 2)) + 3
    m <- matrix(NA, nrow = 2^q, ncol = C)
    k <- rep(0, C)
    k[1] <- 1 
    tmp <- rep(NA, C)
    
    t <- 1 # t = time corresponds to new data
    while(t <= length(d)) {
        tmp[1] <- m[1, 1]
        m[2, 1] <- m[1, 1]
        m[1, 1] <- t
        
        for(i in 2:which(k == 0)[1]){
            tmp[i] <- m[1, i]
            m[, i] <- c(tmp[i -1], head(m[, i], -1))
            k[i] <- (k[i]+1)%%2
        }
        idx <- unique(sort(na.omit(c(m))))
        maxs[t] <- MAXcusum(idx, S[idx]) 
        t <- t + 1
    }
    return(maxs)
}

scoresGDLM <- function(d, q) {
    S <- cumsum(d)
    maxs <- rep(NA, length(d))
    
    m <- matrix(NA, nrow = 2^q, ncol = 1)
    k <- 1 # counter
    tmp <- NA
    
    t <- 1 # t = time corresponds to new data
    while(t <= length(d)) {
        tmp[1] <- m[1, 1]
        m[2, 1] <- m[1, 1]
        m[1, 1] <- t
        
        zeroIDX <- which(k == 0)
        if(length(zeroIDX) == 0) {
            k <- c(k, 0)
            zeroIDX <- which(k == 0)
            m <- cbind(m, matrix(NA, nrow = 2^q, ncol = 1))
            tmp <- c(tmp, NA)
        }
        
        for(i in 2:zeroIDX[1]){
            tmp[i] <- m[1, i]
            m[, i] <- c(tmp[i -1], head(m[, i], -1))
            k[i] <- (k[i]+1)%%2
        }
        idx <- unique(sort(na.omit(c(m))))
        maxs[t] <- MAXcusum(idx, S[idx]) 
        t <- t + 1
        
    }
    return(maxs)
}

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Test ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

main <- function() {
    set.seed(8)
    threshold <- 5
    q <- 4
    p <- 8
    
    set.seed(8)
    noise <- rnorm(2^p)
    
    cat('==============================\n')
    cat('= Without cp \n')
    cat('==============================\n')
    cat("runtime: ", runtimeGDLM(q = q, d = noise, th = threshold), '\n')
    cat("scores: \n")
    print(scoresGDLM(d = noise, q = q))
    print(summary(scoresGDLM(d = noise, q = q)))
    plot(scoresGDLM(d = noise, q = q))
    
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
    cat("runtime: ", runtimeGDLM(q = q, d = noise, th = threshold), '\n')
    cat("runtime allocate: ", runtimeGDLM_allocate(q = q, d = noise, th = threshold), '\n')
    cat("runtime: ", runtimeGDLM(q = q, d = d, th = threshold), '\n')
    cat("runtime allocate: ", runtimeGDLM_allocate(q = q, d = d, th = threshold), '\n')
    
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

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Calibration ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Set up ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
N <- 2e5 
SEED <- 45
RNGkind("L'Ecuyer-CMRG")
set.seed(SEED)
CORES_1 <- 4
CORES_2 <- sqrt(CORES_1)

if(! isWhole(CORES_2)) {
    stop('sqrt(CORES_1) must be an integer')
}

REP <- 25 * CORES_1
targ_runLen <- N/2

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Auxiliary functions ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
run_len_calculator <- function (score, thres) {
    cp <- which(score >= thres)[1]
    ifelse(is.na(cp), length(score), cp)
}

fn_thre_cand <- function(avg_run_len, thre_seq, target) {
    thre_seq[which(avg_run_len > target)[1]]
}

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Simulation ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
t0 <- Sys.time()
l_noise <- mclapply(1:REP, function (i) rnorm(N), mc.cores = CORES_1)
cat('l_noise done. '); print(Sys.time() - t0);

t0 <- Sys.time()
GDLM_run <- mclapply(X = l_noise,
                    FUN = scoresGDLM, q = 4, # cpp fun
                    mc.cores = CORES_1
)
cat('GDLM_run done. '); print(Sys.time() - t0)

thre_seq <- seq(1, 10, by = .01)
avg_run_len <- rep(NA, length(thre_seq))

t0 <- Sys.time()

avg_run_len <-
    mclapply(seq_along(thre_seq),
             function(i) {
                 mclapply(GDLM_run, run_len_calculator,
                          thres = thre_seq[i],
                          mc.cores = CORES_2) %>%
                     unlist %>%
                     mean
             },
             mc.cores = CORES_2
    ) %>% unlist

cat('avg_run_len done. '); print(Sys.time() - t0); cat('\n')

threGDLM <- fn_thre_cand(avg_run_len, thre_seq, targ_runLen)


# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# results / plots ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cat('threGDLM :', threGDLM, '\n')

mat <- cbind(thre_seq, avg_run_len)
colnames(mat) <- c('threshold', 'avg_run_len')


plot(
    x = mat,
    type = 'l',
    main = paste('N:', N, '| Target run length:', targ_runLen, '| REP:', REP)
)
abline(v = threGDLM)
text(threGDLM, 1, paste0('GDLM threshold: ',threGDLM))

# # %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# # Saving results / plots ####
# # %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# save(list = c('N','targ_runLen', 'avg_run_len', 'thre'),
#      file = "results/avg_run_len.RData"
# )
# 
# # plotting ####
# mat <- cbind(thre_seq, avg_run_len)
# colnames(mat) <- c('threshold', 'avg_run_len')
# 
# 
# png('results/threshold.png')
# plot(
#     x = mat,
#     type = 'l',
#     main = paste('N:', N, '| Target run length:', targ_runLen, '| REP:', REP)
# )
# abline(v = thre)
# text(thre, 1, thre)
# invisible(dev.off())




