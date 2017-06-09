#include<string>
#include<iostream>
#include<fstream>
#include"pFind_PairResearch.h"
#include<vector>
#include <algorithm>
const int paranum=2;
using namespace std;
ostream& operator<<(ostream& os, spectra& s);
bool sortbyupper(spectra& n1, spectra& n2);//用于sort()函数的排序规则，这里为升序排列。sort()按照使此函数返回true的条件来排序目标数组
int argc = 2;
char* argv[2] = { "aaa","Hep_1.spectra" };
int main(){//int argc,char* argv[]) {
	if (argc != paranum) {
		cout << "参数数量异常，程序退出。";
		exit(EXIT_FAILURE);
	}
	ifstream in(argv[1]);
	if (!in.is_open()) {
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
	string waste;
	getline(in, waste);//去除标题行
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
		in.get(ch).get(ch);
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
		if (temp.targe != "target"||temp.q_value>=0.01)
			continue;
		if (temp.modi == "")
			list_no.push_back(temp);
		else if(int(temp.modi.find("->"))+1|| int(temp.modi.find("Carbamidomethyl")) + 1)//将modi项符合标准的项放入list_modi中
			list_modi.push_back(temp);
	}
	sort(list_modi.begin(), list_modi.end(), sortbyupper);
	sort(list_no.begin(), list_no.end(), sortbyupper);//对两vector升序排列，以便接下来的搜索
	vector<spectra>::iterator iter_modi = list_modi.begin(), iter_no = list_no.begin();
	int marker_modi = 0,marker_no=0;//标记正在对比的成员的序号，用于在erase后重新找到正在对比的位置
	while (iter_no != list_no.end()) {
		while (iter_modi != list_modi.end()) {
			if (iter_modi->seq.find(iter_no->seq) == string::npos && iter_no->seq.find(iter_modi->seq) == string::npos) {//若modi和no中的第一个元素的seq项互不为子串（相等是子串的一种特殊情况）
				iter_modi++;
				marker_modi++;
			}
			else if (iter_modi->seq.length() >= iter_no->seq.length()) {
				out << *iter_modi << endl;//迭代打印modi,在list_modi中找包含iter_no.seq的序列并erase之
				iter_modi = list_modi.erase(iter_modi);
				while (iter_modi!=list_modi.end()) {
					if (iter_modi->seq.find(iter_no->seq) != string::npos) {
						out << *iter_modi << endl;
						iter_modi = list_modi.erase(iter_modi);
					}
					else
						iter_modi++;
				}
				iter_modi = list_modi.begin()+marker_modi;//归位
				vector<spectra>::iterator temp1 = iter_no + 1;//迭代打印no，并在list_no中找包含它的序列，打印并erase之
				while (temp1!=list_no.end()) {
					if (temp1->seq.find(iter_no->seq) != string::npos) {
						out << *temp1 << endl;
						temp1 = list_no.erase(temp1);//到时检测此处运行情况，若显示迭代器无法引用，则加一句：iter_modi = list_no.begin()+marker_no;
						iter_no = list_no.begin() + marker_no;//归位
					}
					else
						temp1++;
				}
				out << *iter_no << endl;
				iter_no = list_no.erase(iter_no);//最后才打印原来的序列
			}
			////	
			else {//与上面的else if 正好相反
				out << *iter_no << endl;//迭代打印no,在list_no中找包含iter_modi.seq的序列并erase之
				iter_no = list_no.erase(iter_no);
				while (iter_no!=list_no.end()) {
					if (iter_no->seq.find(iter_modi->seq) != string::npos) {
						out << *iter_no << endl;
						iter_no = list_no.erase(iter_no);
					}
					else
						iter_no++;
				}
				iter_no = list_no.begin() + marker_no;//归位
				vector<spectra>::iterator temp2 = iter_modi + 1;//迭代打印modi，并在list_no中找包含它的序列，打印并erase之
				while (temp2!=list_modi.end()) {
					if (temp2->seq.find(iter_modi->seq) != string::npos) {
						out << *temp2 << endl;
						temp2 = list_modi.erase(temp2);//到时检测此处运行情况，若显示迭代器无法引用，则加一句：iter_modi = list_no.begin()+marker_modi;
						iter_modi = list_modi.begin() + marker_modi;//归位
					}
					else
						temp2;
				}
				out << *iter_modi << endl;
				iter_modi = list_modi.erase(iter_modi);//最后才打印原来的序列
			}
		}	
		iter_modi = list_modi.begin();
		iter_no++;
		marker_modi = 0;//归零
		marker_no++;
	}
	in.close();
	out.close();
	return 0;
}

ostream & operator<<(ostream & os, spectra & s)
{
	os << s.file_name << "	" << s.scan_no << "	" << s.exp_mh << "	" << s.charge << "	" << s.q_value << "	" << s.seq << "	"
		<< s.calc_mh << "	" << s.mass_shift << "	" << s.raw_score << "	" << s.final_score << "	" << s.modi << "	" << s.spec
		<< "	" << s.prot << "	" << s.posi << "	" << s.label << "	" << s.targe << "	" << s.mc_sites << "	" << s.afm_shift << "	"
		<< s.others;
	return os;
}

bool sortbyupper(spectra & n1, spectra & n2)
{
	return n1.seq<n2.seq;//从左往右（数组下标从大到小）越来越大，即升序排列。
}
