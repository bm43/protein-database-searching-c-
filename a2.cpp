#include <iostream>
#include <fstream>
using namespace std;
/*
class load {
	protected:
		string p_id;
		string gi;
		string ref;
		string keyword;
		string line;
	public:
		void loadfile(string filename){

			cout<<"Search by:\n1. Overview of the database\n2. protein id\n3. gi id\n4. ref id\n5. keyword\n6. Quit database\n";
			int b;
			cin>>b;
			switch(b){
				case 1:
					cout<<"\n";//huge chunk of text about database
					loadfile(filename);
					break;
				case 2:
					cout<<"enter item id: ";
					cin>>p_id;

					//
					break;
				case 3:
					cout<<"enter gi id: ";
					cin>>gi;
					//
					break;
				case 4:
					cout<<"enter ref id: ";
					cin>>ref;
					//
					break;
				case 5:
					cout<<"enter keyword: ";
					cin>>keyword;
					//
				case 6:
					cout<<"*Quit database*\n";
					myfile.close();
					break;
					return;
				default:
					cout<<"";
					loadfile(filename);
		}
		return;
	}
};


class child:public load{
public:


};

int main(int agrc, char **argv){
		int a;
		load obj;
		cout<<"Select option:\n1) Load the abridged protein data\n"<<"2) Load the complete protein data\n"<<"3) Quit database\n";
		cin>>a;
		switch(a){
			case 1:
				obj.loadfile("protein_a.fa");
				break;

			case 2:
				obj.loadfile("protein_c.fa");
				break;

			case 3:
				cout<<"*Quits Database*\n";
				break;

			default:
				break;
		}
return 0;
}
*/
/*
int main( int argc, char **argv ){
	cout<<argc<<endl<<argv<<endl;
		if( argc < 1 ){
        cerr << "Usage: "<<argv[0]<<" [infile]" << endl;
				cout<<argv[0];
        return -1;
    }

    ifstream input(argv[1]);
    if(!input.good()){
        cerr << "Error opening '"<<argv[1]<<"'. Bailing out." << endl;
        return -1;
    }

    string line, name, content;
    while( getline( input, line ).good() ){
        if( line.empty() || line[0] == '>' ){ // Identifier marker
            if( !name.empty() ){ // Print out what we read from the last entry
                cout << name << " : " << content << endl;
                name.clear();
            }
            if( !line.empty() ){
                name = line.substr(1);
            }
            content.clear();
        } else if( !name.empty() ){
            if( line.find(' ') != string::npos ){ // Invalid sequence--no spaces allowed
                name.clear();
                content.clear();
            } else {
                content += line;
            }
        }
    }
    if( !name.empty() ){ // Print out what we read from the last entry
        cout << name << " : " << content << endl;
    }

    return 0;
}
*/

int main(int argc, char **argv)
{
	cout << "You have entered " << argc
		<< " arguments:" << "\n";

	for (int i = 0; i < argc; ++i)
		cout << argv[i] << "\n";

	return 0;
}
