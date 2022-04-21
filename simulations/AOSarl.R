source('helper_functions.r')

message_parallel <- function(...){
    system(sprintf('echo "\n%s\n"', paste0(..., collapse="")))
}

N <- 2e6 # hopefully only thing that needs to be touched

# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# Set up ####
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
SEED <- 45
RNGkind("L'Ecuyer-CMRG")
set.seed(SEED)
CORES_1 <- 4
CORES_2 <- sqrt(CORES_1)

if(! isWhole(CORES_2)) {
	stop('sqrt(CORES_1) must be an integer')
}

REP <- 25*CORES_1
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
S_noise <- mclapply(1:REP, function (i) matrix(cumsum(c(0, rnorm(N))), nrow = 1), mc.cores = CORES_1)
cat('S_noise done. '); print(Sys.time() - t0);

t0 <- Sys.time()
AOS_run <- mclapply(X = S_noise,
                    FUN = 
                        function(x) {
                            res <- scoresAOS(x)
                            message_parallel('.')
                            return(res)
                        }, #cpp function
                    mc.cores = CORES_1
)
cat('AOS_run done. '); print(Sys.time() - t0)

thre_seq <- seq(2, 7, by = .01)
avg_run_len <- rep(NA, length(thre_seq))

t0 <- Sys.time()
avg_run_len <-
    mclapply(seq_along(thre_seq),
        function(i) {
            mclapply(AOS_run, run_len_calculator,
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
abline(v = threAOS)
text(threAOS, 1, paste0('AOS threshold: ', threAOS))

# 
# 
# ##################################
# source('helper_functions.r')
# 
# N <- 2e2 # hopefully only thing that needs to be touched
# targ_runLen <- N/2
# 
# REP <- 100
# 
# 
# # %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# # Auxiliary functions ####
# # %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# run_len_calculator <- function (score, thres) {
#     cp <- which(score >= thres)[1]
#     ifelse(is.na(cp), length(score), cp)
# }
# 
# fn_thre_cand <- function(avg_run_len, thre_seq, target) {
#     thre_seq[which(avg_run_len > target)[1]]
# }
# 
# # %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# # Simulation ####
# # %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# 
# t0 <- Sys.time()
# S_noise <- lapply(1:REP, function (i) matrix(cumsum(c(0, rnorm(N))), nrow = 1))
# cat('S_noise done. '); print(Sys.time() - t0); 
# 
# t0 <- Sys.time()
# AOS_run <- 
#     lapply(
#         X = S_noise, 
#         FUN = function(x){
#             res <- scoresAOS(x)
#             cat('.')
#             return(res)
#         }
#     )
# cat('\n')
# cat('AOS_run done. '); print(Sys.time() - t0)
# 
# thre_seq <- seq(2, 3, by = .01)
# avg_run_len <- rep(NA, length(thre_seq))
# 
# t0 <- Sys.time()
# avg_run_len <-
#     lapply(seq_along(thre_seq), 
#            function(i) {
#                lapply(AOS_run, run_len_calculator,thres = thre_seq[i]) %>% unlist %>% mean
#            }) %>% unlist
# 
# cat('avg_run_len done. '); print(Sys.time() - t0); cat('\n')
# 
# threAOS <- fn_thre_cand(avg_run_len, thre_seq, targ_runLen)
# 
# # %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# # results / plots ####
# # %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# cat('threAOS:', threAOS, '\n')
# cat('N:', N, '\n')
# 
# 
# mat <- cbind(thre_seq, avg_run_len)
# colnames(mat) <- c('threshold', 'avg_run_len')
# 
# plot(
#     x = mat,
#     type = 'l',
#     main = paste('N:', N, '| Target run length:', targ_runLen, '| REP:', REP)
# )
# abline(v = threAOS)
# text(threAOS, 1, paste0('AOS threshold: ', threAOS))
# 
# 



