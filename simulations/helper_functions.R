library(Dlm)
library(tidyverse)
library(parallel)
library(ggpubr, quietly = TRUE)
library(magrittr, warn.conflicts = FALSE)

theme_idris <- function() {
    theme(
        panel.grid.major = element_blank(),
        panel.grid.minor = element_blank(),
        panel.background = element_blank(),
        axis.line = element_line(colour = "grey20"),
        panel.border =  element_rect(fill = NA,
                                     colour = "grey20")
    )
}

