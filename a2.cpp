#include <iostream>
#include <fstream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
/*
struct proteinProperties{

}data;
*/
class load {

	protected://what the user inputs
	string p_id;
	string gi;
	string ref;
	string keyword;
	string line[200];
	int ui;
	public:
		void secondcase(string filename){
			
			cout<<"secondcase\n";
			cout<<"Select one:\n1. Description of the protein\n2. Protein sequence\n3. Protein statistics\n4. Record protein to file\n5. Return to main menu\n";
			cin>>ui;
			switch(ui)
			{
				case 6:
					firstcase(filename);
					break;
				default:
				cout<<"?\n";
			}
		}
		void firstcase(string filename){
			cout<<"firstcase\n";
			int b;char c;int n;
			cout<<"1. Overview of the database\nOr search by:\n2. protein id\n3. gi id\n4. ref id\n5. keyword\n6. Quit database\n";
			cin>>ui;

			switch(ui){

				case 1:
					cout<<"The proteins in the database are from GenBank(R)\nTotal number of proteins in the database:"<<n<<endl;
					cout<<"Amino acids are represented by the following characters:\nA alanine P proline\nB aspartate/asparagine Q glutamine\nC cystine R arginine\nD aspartate S serine\nE glutamate T threonine\nF phenylalanine U selenocysteine\nG glycine V valine\nH histidine W tryptophan\nI isoleucine Y tyrosine\nK lysine Z glutamate/glutamine\nL leucine X any\nM methionine * translation stop\nN asparagine - gap of indeterminate length\n";
					firstcase(filename);
					break;

				case 2:
					cout<<"enter protein id: ";
					cin>>p_id;//gets what the user wants to find
					ifstream file;
					file.open(filename);//opens file
					//search through file for the same string
					if(file.is_open()){
						int offset;
						offset = line.find(p_id,0);//reads through file lines one by one
						//some_string.find('a') will EITHER return the position of the first appearance
						// of 'a' in some_string if 'a' appears at least once in some_string,
						//OR it will return a value that is equal to std::string::npos
						//if 'a' does not appear at all in some_string.
						while(!file.eof()){//till the end of file
							getline(file,line);
							if(offset!=string::npos){
								//couts description of the protein
								cout<<"Protein details:\n";
								//+cout protein id, gi, ref, keyword
							}
						}
						file.close();
					}
					else{cout<<"couldn't open file\n";}
					//then returns to options
					firstcase(filename);
					break;

				case 3:
					cout<<"enter gi id: ";
					cin>>gi;
					ifstream file;
					file.open(filename);
					if(file.is_open()){
						int offset;
						offset = line.find(gi,0);
						while(!file.eof()){
							getline(file,line);
							if(offset!=string::npos){
								cout<<"Protein details:\n";
								//
							}
						}
						file.close();
					}
					firstcase(filename);
					break;

				case 4:
					cout<<"enter ref id: ";
					cin>>ref;
					ifstream file;
					file.open(filename);
					if(file.is_open()){
						int offset;
						offset = line.find(ref,0);
						while(!file.eof()){
							getline(file,line);
							if(offset!=string::npos){
								cout<<"Protein details:\n";
							
							}
						}
						file.close();
					}
					firstcase(filename);
					break;

				case 5:
					cout<<"enter keyword: ";
					cin>>keyword;
					ifstream file;
					file.open(filename);
					if(file.is_open()){
						int offset;
						offset = line.find(keyword,0);
						while(!file.eof()){
							getline(file,line);
							if(offset!=string::npos){
								cout<<"Protein details:\n";
							}
						}
						file.close();
					}
					firstcase(filename);
					break;

				case 6:
					cout<<"*Quits database*\n";
					break;

				default:
					break;
					firstcase(filename);
		}
	}
};

int main(){
		int a;
		load obj;
		cout<<"Select option:\n1) Load the abridged protein data\n"<<"2) Load the complete protein data\n"<<"3) Quit database\n";
		cin>>a;
		switch(a){
			case 1:
				obj.firstcase("protein_a.fa");
				break;

			case 2:
				obj.firstcase("protein_c.fa");
				break;

			case 3:
				cout<<"*Quits Database*\n";
				break;

			default:
				break;
		}
return 0;
}
