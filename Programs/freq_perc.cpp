// Updated on 10/30/22

/*
        Program Find_Desc_GO_Genes.cpp to calculate the percentage
	of sequence reads associated with each protein or species
	annotation.

        Input: tab-delimited file containing two fields (1. number of
	associated reads; 2: annotation) without a heaer.

	Output: tab-delimited file consisting of three fields (1. Percentage
	of associated reads; 2: number of associated reads; 3: annotation)
	without a header.

*/


#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
	// Default values of the options
	const char* in_file = {"In_fp"};
	const char* out_file_name = {"Out_fp.txt"};
	int print_help = 0;

	int argz = 1; // argument counter

	// Read specified settings
	while( (argz<argc) && (argv[argz][0] == '-') ) {
		if (strcmp(argv[argz], "-h") == 0) {
			print_help = 1;
		} else if (strcmp(argv[argz], "-in") == 0) {
			in_file = argv[++argz];
		} else if (strcmp(argv[argz], "-out") == 0) {
                        out_file_name = argv[++argz];
		} else {
			fprintf(stderr, "unknown option %s\n", argv[argz]);
			print_help = 1;
			break;
		}
		argz++;
	}

	if (print_help) { // print error/usage message ?
		fprintf(stderr, "USAGE: %s {<options>}\n", argv[0]);
		fprintf(stderr, "	options:\n");
		fprintf(stderr, "	-h: print the usage message\n");
		fprintf(stderr, "	-in <s>: specify the input file\n");
		fprintf(stderr, "       -out <s>: specify the output file name\n");
		exit(1);
	}

	ifstream inputFile(in_file); // Try to open the input file
	if ( !inputFile.is_open() ) { // Exit on failure
		fprintf(stderr, "Cannot open %s for reading.\n", in_file);
		exit(1);
	}

	FILE *outstream;

	// Open the output file
	outstream = fopen(out_file_name, "w");
	if (outstream == NULL ) { // Exit on failure
		fprintf(stderr, "Cannot open %s for writing.\n", out_file_name);
		exit(1);
	}

	// Read the input data into vectors
	string line;    // string buffer
	string s_num;
	string t_annot;
	int t_num;
	int sum_num;
	vector <int> num;
	vector <string> annot;
	int num_annots;

	// Clear the vectors
	num.clear();
	annot.clear();

	sum_num = 0;
	while( getline(inputFile, line) ) {
		istringstream ss(line);
		getline(ss, s_num, '\t');
		getline(ss, t_annot, '\t');
		// printf("%s\n", t_annot.c_str());
		t_num = atoi(s_num.c_str());
		num.push_back(t_num);
		sum_num = sum_num + t_num;
		annot.push_back(t_annot);
	}
	num_annots = annot.size();
	printf("%d annotations\n", num_annots);

	// Close the input file
        inputFile.close();

	// Add the percentage to each annotation
	int ag;
	double percent;

	for (ag=0; ag<num_annots; ag++) {
		percent = ( (double)num.at(ag)/(double)sum_num ) * (double)100.0;
		fprintf(outstream, "%f\t%d\t%s\n", percent, num.at(ag), annot.at(ag).c_str());
		printf("%f\t%d\t%s\n", percent, num.at(ag), annot.at(ag).c_str());
	}

	// Clear the vectors
	num.clear();
	annot.clear();

	// Close the files
	inputFile.close();
	fclose(outstream);

	return 0;
}
