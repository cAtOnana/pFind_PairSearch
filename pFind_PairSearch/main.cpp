#include<string>
#include<iostream>
#include<fstream>
#include"pFind_PairResearch.h"
#include<vector>
#include <algorithm>
const int paranum=2;
using namespace std;
ostream& operator<<(ostream& os, spectra& s);
bool sortbyupper(spectra& n1, spectra& n2);//����sort()�����������������Ϊ�������С�sort()����ʹ�˺�������true������������Ŀ������
int argc = 2;
char* argv[2] = { "aaa","all_openresearch_sample.spectra" };
int main(){//int argc,char* argv[]) {
	if (argc != paranum) {
		cout << "���������쳣�������˳���";
		exit(EXIT_FAILURE);
	}
	ifstream in(argv[1]);
	if (!in.is_open()) {
		cout << "�ļ�" << argv[1] << "��ʧ�ܣ������˳���";
		exit(EXIT_FAILURE);
	}
	string outfilename = argv[1];
	outfilename += "txt";
	ofstream out(outfilename);
	if (!out.is_open()) {
		cout << "�޷���������ļ��������˳���";
		exit(EXIT_FAILURE);
	}

	///
	vector<spectra>list_modi, list_no;
	spectra temp;
	string waste;
	getline(in, waste);//ȥ��������
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
		if(temp.modi.find("->")!=string::npos && temp.modi.find("Dha")==string::npos && temp.modi.find("Xle")==string::npos && temp.modi.find("pyro")==string::npos)//����ͻ��������list_modi��
			list_modi.push_back(temp);
		else//�����������������ͻ��ĺ���������ͻ����������list_no��
			list_no.push_back(temp);
	}
	sort(list_modi.begin(), list_modi.end(), sortbyupper);
	sort(list_no.begin(), list_no.end(), sortbyupper);//����vector�������У��Ա������������
	vector<spectra>::iterator iter_modi = list_modi.begin(), iter_no = list_no.begin();
	int marker_modi = 0,marker_no=0;//������ڶԱȵĳ�Ա����ţ�������erase�������ҵ����ڶԱȵ�λ��
	while (iter_no != list_no.end()) {
		while (iter_modi != list_modi.end()) {
			if (iter_modi->seq.find(iter_no->seq) == string::npos && iter_no->seq.find(iter_modi->seq) == string::npos) {//��modi��no�еĵ�һ��Ԫ�ص�seq���Ϊ�Ӵ���������Ӵ���һ�����������
				iter_modi++;
				marker_modi++;
			}
			else if (iter_modi->seq.length() >= iter_no->seq.length()) {
				out << *iter_modi << endl;//������ӡmodi,��list_modi���Ұ���iter_no.seq�����в�erase֮
				iter_modi = list_modi.erase(iter_modi);
				while (iter_modi!=list_modi.end()) {
					if (iter_modi->seq.find(iter_no->seq) != string::npos) {
						out << *iter_modi << endl;
						iter_modi = list_modi.erase(iter_modi);
					}
					else
						iter_modi++;
				}
				iter_modi = list_modi.begin()+marker_modi;//��λ
				vector<spectra>::iterator temp1 = iter_no + 1;//������ӡno������list_no���Ұ����������У���ӡ��erase֮
				while (temp1!=list_no.end()) {
					if (temp1->seq.find(iter_no->seq) != string::npos) {
						out << *temp1 << endl;
						temp1 = list_no.erase(temp1);//��ʱ���˴��������������ʾ�������޷����ã����һ�䣺iter_modi = list_no.begin()+marker_no;
						iter_no = list_no.begin() + marker_no;//��λ
					}
					else
						temp1++;
				}
				out << *iter_no << endl;
				iter_no = list_no.erase(iter_no);//���Ŵ�ӡԭ��������
			}
			////	
			else {//�������else if �����෴
				out << *iter_no << endl;//������ӡno,��list_no���Ұ���iter_modi.seq�����в�erase֮
				iter_no = list_no.erase(iter_no);
				while (iter_no!=list_no.end()) {
					if (iter_no->seq.find(iter_modi->seq) != string::npos) {
						out << *iter_no << endl;
						iter_no = list_no.erase(iter_no);
					}
					else
						iter_no++;
				}
				iter_no = list_no.begin() + marker_no;//��λ
				vector<spectra>::iterator temp2 = iter_modi + 1;//������ӡmodi������list_no���Ұ����������У���ӡ��erase֮
				while (temp2!=list_modi.end()) {
					if (temp2->seq.find(iter_modi->seq) != string::npos) {
						out << *temp2 << endl;
						temp2 = list_modi.erase(temp2);//��ʱ���˴��������������ʾ�������޷����ã����һ�䣺iter_modi = list_no.begin()+marker_modi;
						iter_modi = list_modi.begin() + marker_modi;//��λ
					}
					else
						temp2++;
				}
				out << *iter_modi << endl;
				iter_modi = list_modi.erase(iter_modi);//���Ŵ�ӡԭ��������
			}
		}	
		iter_modi = list_modi.begin();
		iter_no++;
		marker_modi = 0;//����
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
	return n1.seq<n2.seq;//�������ң������±��С����Խ��Խ�󣬼��������С�
}
