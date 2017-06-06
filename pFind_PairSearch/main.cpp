#include<string>
#include<iostream>
#include<fstream>
#include"pFind_PairResearch.h"
#include<vector>
const int paranum=2;
using namespace std;
int main(int argc,char* argv[]) {
	if (argc != paranum) {
		cout << "参数数量异常，程序退出。";
		exit(EXIT_FAILURE);
	}
	ifstream in(argv[1]);
	if (in.is_open()) {
		cout << "文件" << argv[1] << "打开失败，程序退出。";
		exit(EXIT_FAILURE);
	}
	vector<spectra>list_modi, list_no;
	spectra temp;
	char ch;
	int count_modi = 0,count_no=0;
	while (in >> temp.file_name) {
		in >> temp.scan_no;
		in >> temp.exp_mh;
		in >> temp.charge;
		in >> temp.q_value;
		in >> temp.sequence;
		in >> temp.calc_mh;
		in >> temp.mass_shift;
		in >> temp.raw_score;
		in >> temp.final_score;
		in.get(ch);
		if (ch == '\t')
			temp.modi = "";
		else
		{
			in >> temp.modi;
			temp.modi = ch + temp.modi;
		}
		in >> temp.spec;
		in >> temp.prot;
		in >> temp.posi;
		in >> temp.label;
		in >> temp.targe;
		in >> temp.mc_sites;
		in >> temp.afm_shift;
		in >> temp.others;
		if (temp.modi == "")
			list_no.push_back(temp);
		else if(int(temp.modi.find("->"))+1|| int(temp.modi.find("->")) + 1)
			list_modi.push_back(temp);
	}
}