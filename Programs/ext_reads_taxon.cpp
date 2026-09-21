// Updated on 03/29/23

/*
	Program ext_reads_taxon.cpp to extract sequence reads mapped to
	a taxonomic group of interest from a diamond output table.

	Inputs:
	1. Diamond output table
	2. List of NCBI taxon IDs belonging to a taxonomic group of interest without a header

	Output:
	Diamond output table of sequence reads mapped to a taxonomic group of interest

*/

#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
	// Default values of the options
	const char* in_file = {"Table.txt"};
	const char* list_file = {"List.txt"};
	const char* out_file = {"ext_stitle.sh"};
	int print_help = 0;
	int q_id = 1;	// one if the qseqid is included in the diamond table, zero, otherwise

	int argz = 1;	// argument counter

	// Read the specified setting
	while( (argz<argc) && (argv[argz][0] == '-') ) {
		if (strcmp(argv[argz], "-h") == 0) {
			print_help = 1;
		} else if (strcmp(argv[argz], "-in") == 0) {
                        in_file = argv[++argz];
		} else if (strcmp(argv[argz], "-list") == 0) {
			list_file = argv[++argz];
		} else if (strcmp(argv[argz], "-out") == 0) {
                        out_file = argv[++argz];
		} else if (strcmp(argv[argz], "-q") == 0) {
			sscanf(argv[++argz], "%d", &q_id);
		} else {
			fprintf(stderr, "unknown option %s\n", argv[argz]);
			print_help = 1;
			break;
		}
		argz++;
	}
	if (print_help) {	// print error/usage message ?
		fprintf(stderr, "USAGE: %s {<options>}\n", argv[0]);
		fprintf(stderr, "	options: -h: print the usage message\n");
		fprintf(stderr, "       -in <s>: specify the input file name\n");
		fprintf(stderr, "       -list <s>: specify the list file name\n");
		fprintf(stderr, "       -out <s>: specify the name of the output file\n");
		fprintf(stderr, "       -q <d>: specify whether the qseqid is included in the diamond table\n");
		exit(1);
	}

	ifstream l_inputFile(list_file);               // Try to open the list file
        if ( !l_inputFile.is_open() ) {           // Exit on failure
                fprintf(stderr, "Cannot open %s for reading.\n", list_file);
                exit(1);
        }

	// Read NCBI taxon IDs into vectors
	string l_line;	// string buffer
	string t_taxonid;
	vector <string> taxonid;
	int ids;

	// Clear the vector
	taxonid.clear();

	while (getline(l_inputFile, l_line)) {
		istringstream l_ss(l_line);
		l_ss >> t_taxonid;
		taxonid.push_back(t_taxonid);
	}

	ids = taxonid.size();
	printf("%d IDs in %s\n", ids, list_file);

	FILE *outstream;

	// Open the output file
	outstream = fopen(out_file, "w");
	if (outstream == NULL ) { // Exit on failure
		fprintf(stderr, "Cannot open %s for writing.\n", out_file);
		exit(1);
	}

	ifstream inputFile(in_file);               // Try to open the input file
        if ( !inputFile.is_open() ) {           // Exit on failure
                fprintf(stderr, "Cannot open %s for reading.\n", in_file);
                exit(1);
        }

	// Read the input file
	string line; // String buffer
	string qseqid, sseqid, pident, length, staxids, sscinames, stitle, evalue, bitscore;
	int belong;	// one if the sequence read is mapped to the taxon of interest, zero, otherwise
	string staxid;

	while (getline(inputFile, line)) {
		istringstream ss(line);
		if (q_id == 1) {
			getline(ss, qseqid, '\t');
		}
		getline(ss, sseqid, '\t');
		getline(ss, pident, '\t');
                getline(ss, length, '\t');
		getline(ss, staxids, '\t');
                getline(ss, sscinames, '\t');
                getline(ss, stitle, '\t');
                getline(ss, evalue, '\t');
		getline(ss, bitscore, '\t');
		belong = 1;
		if ( staxids.find(';') < staxids.length() ) {	// more than one staxid
			stringstream s_ss(staxids);
			while( s_ss.good() ) {
				getline( s_ss, staxid, ';' );
				if ( find(taxonid.begin(), taxonid.end(), staxid) != taxonid.end() ) {
					belong = belong*1;
				} else {
					belong = belong*0;
				}
			}
		} else {
			if ( find(taxonid.begin(), taxonid.end(), staxids) != taxonid.end() ) {
				belong = belong*1;
			} else {
				belong = belong*0;
			}
		}
		if (belong == 1) {
			fprintf(outstream, "%s\n", line.c_str());
			// printf("%s\n", line.c_str());
		}
	}

	// Close the input and output files
	inputFile.close();
	l_inputFile.close();
	fclose(outstream);

	return(0);
}
