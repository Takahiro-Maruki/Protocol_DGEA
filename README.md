# Protocol_DGEA
Protocol for the differential gene expression analysis in the environmental transcriptomics of nutrient response in freshwater eukaryotes

0. Compile the C++ programs and make the R script executable.<br>
g++ -o ext_reads_taxon ext_reads_taxon.cpp -lm<br>
g++ -o freq_perc freq_perc.cpp -lm<br>
chmod u+x KM_PF_run_DESeq_stats.R<br> 

2. Extract sequence reads mapped to a class of interest (e.g., Eurotatoria) from a DIAMOND output table in the BLAST tabular format.<br>  
