
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct	Protein
{
	int    iid;					// item id
	string gid;					// gi number
	string rid;					// reference number
	string name;				// name of the protein
	vector<char> sequence;		// protein's amino acid sequence
};

int load_database(ifstream* fin, vector<Protein>* database);
int menu_select_db();
int menu_main();
int menu_protein();
int search_database(vector<Protein>* database, vector<int>* match_list, int option);
void print_matches(vector<Protein>* database, vector<int>* match_list);
void report_protein_stats(vector<Protein>* database, int itemnum);

int main()
{
	int option = 0;
	int suboption = 0;
	int match_option = 0;
	int temp_i = 0;
	int n_matches = 0;
	int mi = 0;
	
	vector<Protein>	database;
	vector<int>	match_list;
	
	ifstream fin;
	ofstream fout;
	fout.open("selected_proteins.txt",ios_base::out);

	// opening greeting
	cout << endl;
	cout << "Welcome to the Protein Database" << endl;
	cout << endl;
	
	// select database to open
	option = menu_select_db();						// 1. select abridged version
	if (option == 1)
	{
		fin.open("protein_a.fa",ios_base::in);
		load_database(&fin, &database);
	}
	else if (option == 2)							// 2. select complete version
	{
		fin.open("protein_c.fa",ios_base::in);
		load_database(&fin, &database);
	}
	else											// 3. quit the program
	{
		option = 6; // quit the program
		cout << "Exiting the database" << endl;
		cout << endl;
	}
	
	// repeat until quit command is called
	// when understanding my code, look at the overall structure (and flow) of the
	// loops and if-statements.
	while (option != 6)
	{
		// request user for options
		option = menu_main();
		if (option == 1)							// 1. database overview
		{
			cout << "The proteins in the database are from GenBank(R)" << endl;
			cout << "Total number of proteins in the database: " << database.size() << endl;
			cout << "Amino acids are represented by the following characters:" << endl;
			cout << "A  alanine               P  proline" << endl;
			cout << "B  aspartate/asparagine  Q  glutamine" << endl;
			cout << "C  cystine               R  arginine" << endl;
			cout << "D  aspartate             S  serine" << endl;
			cout << "E  glutamate             T  threonine" << endl;
			cout << "F  phenylalanine         U  selenocysteine" << endl; 
			cout << "G  glycine               V  valine" << endl;
			cout << "H  histidine             W  tryptophan" << endl;  
			cout << "I  isoleucine            Y  tyrosine" << endl;
			cout << "K  lysine                Z  glutamate/glutamine" << endl;
			cout << "L  leucine               X  any" << endl;
			cout << "M  methionine            *  translation stop" << endl;
			cout << "N  asparagine            -  gap of indeterminate length" << endl;
			cout << endl;
		}
		else if ((option >= 2) && (option <= 5))	// search options selected
		{											// I decided to handle options 2-5
													// here, because they are all search
													// options that lead to a match
													// or no match. In other words,
													// they share code
													
			if (option == 2)						// 2. search by item ID
				n_matches = search_database(&database,  &match_list, 1);
			else if (option == 3)					// 3. search by gi ID
				n_matches = search_database(&database,  &match_list, 2);
			else if (option == 4)					// 4. search by ref ID
				n_matches = search_database(&database,  &match_list, 3);
			else if (option == 5)					// 5. search by keyword
			{
				n_matches = search_database(&database,  &match_list, 4);
				print_matches(&database, &match_list);
				if (n_matches >= 1)					// if there's more than one match
				{									// then ask use to select one
					cout << "Select one of the matches" << endl;
					match_option = 0;
					while ((match_option < 1) || (match_option > match_list.size()))
					{
						cout << ">>";
						cin >> match_option;
					}
					cout << endl;
					
					temp_i = match_list[match_option];
					match_list.clear();
					match_list.push_back(temp_i-1);
					//cout << match_list[0];
					n_matches = match_list.size();
				}
			}
			
			if (n_matches >= 1)						// when a match is found and selected,
			{										// then proceed to the next menu
				
				while (suboption != 5)				// keep asking the user until the
				{									// he/she exits the sub-menu
					// request user for option
					suboption = menu_protein();
					if (suboption == 1)				// 1. description of the protein
					{
						mi = match_list[0];
						cout << "Description of the protein:" << endl;
						cout << "item id: " << database[mi].iid << endl;
						cout << "gi id:   " << database[mi].gid << endl;
						cout << "ref id:  " << database[mi].rid << endl;
						cout << "name:    " << database[mi].name << endl;
						cout << endl;
					}
					else if (suboption == 2)		// 2. protein sequence
					{
						mi = match_list[0];
						cout << "Protein sequence: " << endl;
						for (int i = 0; i < database[mi].sequence.size(); i++)
						{
							cout << database[mi].sequence[i];
						}
						cout << endl;
						cout << endl;
					}
					else if (suboption == 3)		// 3. protein statistics
					{
						mi = match_list[0];
						report_protein_stats(&database, mi);
					}
					else if (suboption == 4)		// 4. print out to file
					{
						mi = match_list[0];
						fout << "item id: " << database[mi].iid;
						fout << ", gi id: " << database[mi].gid;
						fout << ", ref id: " << database[mi].rid << endl;
						fout << "name: " << database[mi].name << endl;
						for (int i = 0; i < database[mi].sequence.size(); i++)
						{
							fout << database[mi].sequence[i];
						}
						fout << endl;
						
						cout << "The protein was written to file." << endl;			
						cout << endl;
					}
				}
				suboption = 0;
			}
			else
			{
				cout << "No match was found" << endl;			
				cout << endl;
			}
		}
		else if (option == 6)						// 6. quit database
		{
			cout << "Exiting the database" << endl;
			cout << endl;
		}
	}	
	fin.close();

	return 0;
}

// menu to select which database to use
int menu_select_db()
{
	int selection = 0;
	cout << "Select an option from the menu below" << endl;
	cout << "1) Load the abridged protein data" << endl;
	cout << "2) Load the complete protein data" << endl;
	cout << "3) Quit database" << endl;
	while ((selection < 1) || (selection > 3))
	{
		cout << ">>";
		cin >> selection;
	}
	cout << endl;

	return selection;
}

// menu to search through the database
int menu_main()
{
	int selection = 0;
	cout << "Select an option from the menu below" << endl;
	cout << "1) Overview of the database" << endl;
	cout << "2) Search by protein #" << endl;
	cout << "3) Search by gi #" << endl;
	cout << "4) Search by ref #" << endl;
	cout << "5) Search by keyword" << endl;
	cout << "6) Quit database" << endl;
	while ((selection < 1) || (selection > 6))
	{
		cout << ">>";
		cin >> selection;
	}
	cout << endl;
	
	return selection;
}

// menu to reveal more about the protein
int menu_protein()
{
	int selection = 0;
	cout << "Select and option from the menu below" << endl;
	cout << "1) Description of the protein" << endl;
	cout << "2) Protein sequence" << endl;
	cout << "3) Protein statistics" << endl;
	cout << "4) Record protein to file" << endl;
	cout << "5) Return to main menu" << endl;
	
	while ((selection < 1) || (selection > 5))
	{
		cout << ">>";
		cin >> selection;
	}
	cout << endl;
	
	return selection;
}

// loads data from a file that has proteins in FASTA format
int load_database(ifstream* fin, vector<Protein>* database)
{
	string trash;
	string line;
	string temp_str;
	char c;

	int num_proteins = 0;
	Protein temp_p;

	cout << "Loading database..." << endl;
	

	fin->get(c);
	while (getline(*fin, line))
	{
		num_proteins++;
		temp_p.iid = num_proteins;
		
		stringstream sin(line);
		getline(sin,trash,'|');
		getline(sin,temp_p.gid,'|');
		getline(sin,trash,'|');
		getline(sin,temp_p.rid,'|');
		getline(sin,temp_p.name,'|');
		temp_p.sequence.clear();

		getline(*fin,line,'>');
		for (int i = 0; i < line.size(); i++)
		{
			if (isalpha(line[i]))
			{
				temp_p.sequence.push_back(line[i]); 
			}
		}

		database->push_back(temp_p);
	}
	cout << "Database loaded." << endl;
	cout << endl;
	return 0;
}

// searches through the database for a protein with different search options
int search_database(vector<Protein>* database, vector<int>* match_list, int option)
{
	int int_query = 0;
	string str_query;
	
	match_list->clear();
	
	if (option == 1)		// search iid
	{
		cout << "Enter an item id" << endl;
		while (int_query < 1)
		{
			cout << ">>";
			cin >> int_query;
		}
			
	}
	else if (option == 2)	// search gid
	{
		cout << "Enter a gi id" << endl;
		cout << ">>";
		cin >> str_query;
	}
	else if (option == 3)	// search rid
	{
		cout << "Enter a ref id" << endl;
		cout << ">>";
		cin >> str_query;
	}
	else if (option == 4)	// search keyword
	{
		cout << "Enter a keyword" << endl;
		cout << ">>";
		cin >> str_query;
	}
	
	int n_matches = 0;
	for (int i = 0; i < database->size(); i++)
	{
		if (option == 1)		// search item number
		{
			if ((*database)[i].iid == int_query)
			{
				n_matches++;
				match_list->push_back(i);
			}
		}
		else if (option == 2)	// search gi id
		{
			if ((*database)[i].gid == str_query)
			{
				n_matches++;
				match_list->push_back(i);
			}
		}
		else if (option == 3)	// search rid
		{
			if ((*database)[i].rid == str_query)
			{
				n_matches++;
				match_list->push_back(i);
			}
		}
		else if (option == 4)	// search for keyword in name
		{
			if ((*database)[i].name.find(str_query) != string::npos)
			{
				n_matches++;
				match_list->push_back(i);
			}
		}
	}
	cout << endl;
	
	return match_list->size();
}

// given a list if item IDs in match_list, print out all the database proteins
void print_matches(vector<Protein>* database, vector<int>* match_list)
{
	int j = 0;
	cout << "Number of matches founds: " << match_list->size() << endl;
	
	// loop through the match list and display the results from database
	for (int i = 0; i < match_list->size(); i++)
	{
		j = (*match_list)[i];
		cout << i+1 << ") item id: " << (*database)[j].iid;
		cout << ", gi id: " << (*database)[j].gid << ", ref id: " << (*database)[j].rid << endl;
		cout << "   " << (*database)[j].name << endl;
	}
	cout << endl;
}

// perform some basic processing of the protein sequence
void report_protein_stats(vector<Protein>* database, int mi)
{
	int aa[26];	// amino acids
	char curr_aa = '1';
	int count_aa = 0;
	
	for (int i = 0; i < 26; i++)	// initialise the AA count
	{
		aa[i] = 0;
	}

	cout << "Report on the protein statistics:" << endl;
	cout << endl;
	
	// loop through the sequence of amino acids and count
	for (int i = 0; i < (*database)[mi].sequence.size(); i++)
	{
		count_aa++;
		curr_aa = (*database)[mi].sequence[i];
		if (curr_aa == 'A')
			aa[0]++;
		else if (curr_aa == 'B')
			aa[1]++;
		else if (curr_aa == 'C')
			aa[2]++;
		else if (curr_aa == 'D')
			aa[3]++;
		else if (curr_aa == 'E')
			aa[4]++;
		else if (curr_aa == 'F')
			aa[5]++;
		else if (curr_aa == 'G')
			aa[6]++;
		else if (curr_aa == 'H')
			aa[7]++;
		else if (curr_aa == 'I')
			aa[8]++;
		else if (curr_aa == 'K')
			aa[9]++;
		else if (curr_aa == 'L')
			aa[10]++;
		else if (curr_aa == 'M')
			aa[11]++;
		else if (curr_aa == 'N')
			aa[12]++;
		else if (curr_aa == 'P')
			aa[13]++;
		else if (curr_aa == 'Q')
			aa[14]++;
		else if (curr_aa == 'R')
			aa[15]++;
		else if (curr_aa == 'S')
			aa[16]++;
		else if (curr_aa == 'T')
			aa[17]++;
		else if (curr_aa == 'U')
			aa[18]++;
		else if (curr_aa == 'V')
			aa[19]++;
		else if (curr_aa == 'W')
			aa[20]++;
		else if (curr_aa == 'Y')
			aa[21]++;
		else if (curr_aa == 'Z')
			aa[22]++;
		else if (curr_aa == 'X')
			aa[23]++;
		else if (curr_aa == '*')
			aa[24]++;
		else if (curr_aa == '-')
			aa[25]++;
	}
	
	cout << "Total number of amino acids: " << count_aa << endl;
	cout << "A  " << aa[0]  <<  "\tP " << aa[13] << endl;
	cout << "B  " << aa[1]  <<  "\tQ " << aa[14] << endl;
	cout << "C  " << aa[2]  <<  "\tR " << aa[15] << endl;
	cout << "D  " << aa[3]  <<  "\tS " << aa[16] << endl;
	cout << "E  " << aa[4]  <<  "\tT " << aa[17] << endl;
	cout << "F  " << aa[5]  <<  "\tU " << aa[18] << endl;
	cout << "G  " << aa[6]  <<  "\tV " << aa[19] << endl;
	cout << "H  " << aa[7]  <<  "\tW " << aa[20] << endl;
	cout << "I  " << aa[8]  <<  "\tY " << aa[21] << endl;
	cout << "K  " << aa[9]  <<  "\tZ " << aa[22] << endl;
	cout << "L  " << aa[10] <<  "\tX " << aa[23] << endl;
	cout << "M  " << aa[11] <<  "\t* " << aa[24] << endl;
	cout << "N  " << aa[12] <<  "\t- " << aa[25] << endl;
	cout << endl;
	
}
