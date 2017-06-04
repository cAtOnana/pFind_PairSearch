#pragma once
#include<string>
using namespace std;
struct spectra
{
	string file_name;
	int scan_no;
	double exp_mh;
	int charge;
	int q_value;
	string sequence;
	double calc_mh;
	double mass_shift;
	double raw_score;
	string final_score;
	string Modification;
	int specificity;
	string proteins;
	string positions;
	string label;
	string targe="target";
	int mc_sites;
	double afm_shift;
	int others;
};