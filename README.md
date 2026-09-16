# Protocol_DGEA
Protocol for the differential gene expression analysis in the environmental transcriptomics of nutrient response in freshwater eukaryotes

0. Compile the C++ programs, install taxonkit, and make the R script executable.<br>
g++ -o ext_reads_taxon ext_reads_taxon.cpp -lm<br>
g++ -o freq_perc freq_perc.cpp -lm<br>
Download and install taxonkit following the instructions at https://bioinf.shenwei.me/taxonkit/download/<br>
chmod u+x KM_PF_run_DESeq_stats.R<br> 

2. Extract sequence reads mapped to a class of interest (e.g., Eurotatoria) from a DIAMOND output table in the BLAST tabular format.<br>  
taxonkit list --ids 2816136 --indent "" > IDs_Eurotatoria.txt<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_F6.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_F6.ribodepleted.nr_6c.table<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_J1.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_J1.ribodepleted.nr_6c.table<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_J3.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_J3.ribodepleted.nr_6c.table<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_G5.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_G5.ribodepleted.nr_6c.table<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_G7.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_G7.ribodepleted.nr_6c.table<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_K5.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_K5.ribodepleted.nr_6c.table<br>

