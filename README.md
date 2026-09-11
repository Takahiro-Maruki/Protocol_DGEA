# Protocol_DGEA
Protocol for the differential gene expression analysis in the environmental transcriptomics of nutrient response in freshwater eukaryotes

0. Compile the C++ programs and make the R script executable.\
g++ -o ext_reads_taxon ext_reads_taxon.cpp -lm\
g++ -o freq_perc freq_perc.cpp -lm\
chmod u+x KM_PF_run_DESeq_stats.R 

2. Extract sequence reads mapped to a class of interest (e.g., Eurotatoria) from a DIAMOND output table in the BLAST tabular format.  

