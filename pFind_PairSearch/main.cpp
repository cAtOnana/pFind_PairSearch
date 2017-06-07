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
	string outfilename = argv[1];
	outfilename += "txt";
	ofstream out(outfilename);
	if (!out.is_open()) {
		cout << "无法建立输出文件，程序退出。";
		exit(EXIT_FAILURE);
	}

	///
	vector<spectra>list_modi, list_no;
	spectra temp;
	char ch;
	int count_modi = 0,count_no=0;
	while (in >> temp.file_name) {
		in >> temp.scan_no;
		in >> temp.exp_mh;
		in >> temp.charge;
		in >> temp.q_value;
		in >> temp.seq;
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
		else if(int(temp.modi.find("->"))+1|| int(temp.modi.find("->")) + 1)//将modi项符合标准的项放入list_modi中
			list_modi.push_back(temp);
	}
	vector<spectra>::iterator iter_modi = list_modi.begin(), iter_no = list_no.begin();
	while (iter_no != list_no.end()) {
		while (iter_modi != list_modi.end()) {
			if (iter_modi->seq.find(iter_no->seq) == string::npos || iter_no->seq.find(iter_modi->seq) == string::npos) {//若modi和no中的第一个元素的seq项互不为子串（相等是子串的一种特殊情况）
					iter_modi++;
			}
			else if(iter_modi->seq.length()>iter_no->seq.length())
				//迭代打印modi,在list_modi中找相同序列并erase之
				//迭代打印no，并在list_no中找包含它的序列，打印并erase之

		}	
	}
}