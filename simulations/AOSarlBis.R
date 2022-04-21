# For each method, we estimate the average run length as a function of the
# threshold based on data, with no change, of length two million observations. 
# We average the results across 100 different replicates.
# For each method we choose the threshold that gives an average run 
# length of 1 × 106 observations. 

library(Dlm)
pows <- 7:15
times <- rep(NA, length(pows))
for(i in seq_along(pows)){
    p <- pows[i]
    t0 <- Sys.time()
    system.time(scoresAOS(matrix(cumsum(c(0, rnorm(2 ^ p))), nrow = 1)))
    t1 <- Sys.time()
    times[i] <- difftime(t1, t0, units="secs")
}
print(times)
plot(times, type = 'l')

if(F) {

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
S_noise <- lapply(1:REP, function (i) matrix(cumsum(c(0, rnorm(N))), nrow = 1), mc.cores = CORES_1)
cat('S_noise done. '); print(Sys.time() - t0); 

t0 <- Sys.time()
AOS_run <- lapply(X = S_noise, FUN = scoresAOS)


cat('AOS_run done. '); print(Sys.time() - t0)

thre_seq <- seq(2, 7, by = .01)
avg_run_len <- rep(NA, length(thre_seq))

t0 <- Sys.time()
avg_run_len <-
    lapply(seq_along(thre_seq),
        function(i) {
            lapply(AOS_run, run_len_calculator,
                     thres = thre_seq[i],
                     mc.cores = CORES_2) %>%
                                unlist %>%
                                mean
        },
        mc.cores = CORES_2
    ) %>% unlist


cat('avg_run_len done. '); print(Sys.time() - t0); cat('\n')

threAOS <- fn_thre_cand(avg_run_len, thre_seq, targ_runLen)

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# results / plots ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
cat('threAOS:', threAOS, '\n')
cat('CORES_1:', CORES_1, '\n')
cat('N:', N, '\n')


mat <- cbind(thre_seq, avg_run_len)
colnames(mat) <- c('threshold', 'avg_run_len')

plot(
    x = mat,
    type = 'l',
    main = paste('N:', N, '| Target run length:', targ_runLen, '| REP:', REP)
)
abline(v = thre)
text(thre, 1, paste0('AOS threshold: ', thre))
}
