# Protocol_DGEA
Protocol for the differential gene expression analysis in the environmental transcriptomics of nutrient response in freshwater eukaryotes

0. Compile the C++ programs, install taxonkit, and make the R script executable.<br>
g++ -o ext_reads_taxon ext_reads_taxon.cpp -lm<br>
g++ -o freq_perc freq_perc.cpp -lm<br>
Download and install taxonkit following the instructions at https://bioinf.shenwei.me/taxonkit/download/<br>
chmod u+x KM_PF_run_DESeq_stats.R<br> 

1. Extract sequence reads mapped to a class of interest (e.g., Eurotatoria) from a DIAMOND output table in the BLAST tabular format.<br>  
taxonkit list --ids 2816136 --indent "" > IDs_Eurotatoria.txt<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_F6.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_F6.ribodepleted.nr_6c.table<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_J1.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_J1.ribodepleted.nr_6c.table<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_J3.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_J3.ribodepleted.nr_6c.table<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_G5.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_G5.ribodepleted.nr_6c.table<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_G7.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_G7.ribodepleted.nr_6c.table<br>
./ext_reads_taxon -in Trimmed_environmental_RNA_K5.ribodepleted.nr_6c.table -list IDs_Eurotatoria.txt -out Eurotatoria_Trimmed_environmental_RNA_K5.ribodepleted.nr_6c.table<br>

2. Make input files of the R script to run DESeq2 (KM_PF_run_DESeq_stats.R).<br>
cut -f 2 Eurotatoria_Trimmed_environmental_RNA_F6.ribodepleted.nr_6c.table | sort | uniq -c | sort -nr | sed "s/^[ \t]*//" | sed 's/ /\t/' > freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_F6.ribodepleted.nr_6c.table<br>
cut -f 2 Eurotatoria_Trimmed_environmental_RNA_J1.ribodepleted.nr_6c.table | sort | uniq -c | sort -nr | sed "s/^[ \t]*//" | sed 's/ /\t/' > freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_J1.ribodepleted.nr_6c.table<br>
cut -f 2 Eurotatoria_Trimmed_environmental_RNA_J3.ribodepleted.nr_6c.table | sort | uniq -c | sort -nr | sed "s/^[ \t]*//" | sed 's/ /\t/' > freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_J3.ribodepleted.nr_6c.table<br>
cut -f 2 Eurotatoria_Trimmed_environmental_RNA_G5.ribodepleted.nr_6c.table | sort | uniq -c | sort -nr | sed "s/^[ \t]//" | sed 's/ /\t/' > freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_G5.ribodepleted.nr_6c.table<br>
cut -f 2 Eurotatoria_Trimmed_environmental_RNA_G7.ribodepleted.nr_6c.table | sort | uniq -c | sort -nr | sed "s/^[ \t]//" | sed 's/ /\t/' > freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_G7.ribodepleted.nr_6c.table<br>
cut -f 2 Eurotatoria_Trimmed_environmental_RNA_K5.ribodepleted.nr_6c.table | sort | uniq -c | sort -nr | sed "s/^[ \t]*//" | sed 's/ /\t/' > freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_K5.ribodepleted.nr_6c.table<br>
./freq_perc -in freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_F6.ribodepleted.nr_6c.table -out sseqid_Eurotatoria_environmental_RNA_F6_function.tsv<br>
./freq_perc -in freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_J1.ribodepleted.nr_6c.table -out sseqid_Eurotatoria_environmental_RNA_J1_function.tsv<br>
./freq_perc -in freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_J3.ribodepleted.nr_6c.table -out sseqid_Eurotatoria_environmental_RNA_J3_function.tsv<br>
./freq_perc -in freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_G5.ribodepleted.nr_6c.table -out sseqid_Eurotatoria_environmental_RNA_G5_function.tsv<br>
./freq_perc -in freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_G7.ribodepleted.nr_6c.table -out sseqid_Eurotatoria_environmental_RNA_G7_function.tsv<br>
./freq_perc -in freq_sseqid_Eurotatoria_Trimmed_environmental_RNA_K5.ribodepleted.nr_6c.table -out sseqid_Eurotatoria_environmental_RNA_K5_function.tsv<br>
mv sseqid_Eurotatoria_environmental_RNA_F6_function.tsv control_eRNA-F6.tsv<br>
mv sseqid_Eurotatoria_environmental_RNA_J1_function.tsv control_eRNA-J1.tsv<br>
mv sseqid_Eurotatoria_environmental_RNA_J3_function.tsv control_eRNA-J3.tsv<br>
mv sseqid_Eurotatoria_environmental_RNA_G5_function.tsv experimental_eRNA-G5.tsv<br>
mv sseqid_Eurotatoria_environmental_RNA_G7_function.tsv experimental_eRNA-G7.tsv<br>
mv sseqid_Eurotatoria_environmental_RNA_K5_function.tsv experimental_eRNA-K5.tsv<br>

3. Run the R script to run DESeq2 (KM_PF_run_DESeq_stats.R).<br>
Rscript ./KM_PF_run_DESeq_stats.R -I ./ -O KM_PF_sseqid_Eurotatoria_function_eRNA_LowT_DESeq2_results.tab<br>

References<br>
If you use programs used in this protocol, please cite the following papers:<br>
Klingenberg H., and Meinicke P., 2017. How to normalize metatranscriptomic count data for differential expression analysis. PeerJ 5: e3859.<br>
Shen W., and Ren H., 2021. TaxonKit: A practical and efficient NCBI taxonomy toolkit. J Genet Genomics 48: 844-850.<br>
Westreich S.T., Treiber M.L., Mills D.A., Korf I., Lemay D.G., 2018. SAMSA2: a standalone metatranscriptome analysis pipeline. BMC Bioinformatics 19: 175.<br>
Maruki, T., He, X., Hechler, R. M., Gamero, W. M., Gros, M., Belley, V., Nault, C., Fussmann, 
G. F., Gonzalez, A., Fugère, V., and Cristescu, M. E., Environmental RNA captures eukaryotic community and gene expression responses to eutrophication in freshwater ecosystems.  In revision.<br>
