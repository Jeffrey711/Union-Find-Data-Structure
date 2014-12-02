#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void mytolower(string & line) {
	int i = 0;
	for (i = 0; i < line.length(); i++) {
		if (line[i] >= 'A' && line[i] <= 'Z') {
			line[i] = line[i] - ('Z' - 'z');
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc == 3) {
		string stdfilename(argv[1]);
		ifstream stdfile(stdfilename.c_str());
		if (!stdfile.is_open()) {
			cout << "No standard input file" << endl;
			return -1;
		}
		
		string stufilename(argv[2]);
		ifstream stufile(stufilename.c_str());
		if (!stufile.is_open()) {
			cout << "No student input file" << endl;
			return -1;
		}

		int linenum = 0;
		string stdline, stuline;
		while (!stdfile.eof() && !stufile.eof()) {
			linenum++;

			getline(stdfile, stdline);
			getline(stufile, stuline);
			
			mytolower(stuline);
			mytolower(stdline);

			if (stdline.compare(stuline) != 0) {
				cout << "Wrong Answer at Line: " << linenum << endl;
				cout << "STD output: " << stdline << endl;
				cout << "Your output:" << stuline << endl;
				return -1;
			}
		}

		int i;
		if (stufile.eof()) {
			while (!stdfile.eof()) {
				getline(stdfile, stdline);
				mytolower(stdline);
			
				for (i = 0; i < stdline.length(); i++)
					if (stdline[i] != ' ') {
						cout << "Wrong Answer: " << endl;
						cout << "Your Output Missing: " << stdline << endl;
						return -1;
					}
			}
		}

		if (stdfile.eof()) {
			while (!stufile.eof()) {
				getline(stufile, stuline);
				mytolower(stuline);
				for (i = 0; i < stuline.length(); i++)
					if (stuline[i] != ' ') {
						cout << "Wrong Answer: " << endl;
						cout << "Your Output Missing: " << stuline << endl;
						return -1;
					}
			}
		}

		if (!(stdfile.eof() && stufile.eof())) {
			cout << "Wrong Answer, Didn't eof" << endl;
		}
			
		stdfile.close();
		stufile.close();
		cout << "Accepted" << endl;
		return 0;
	}
	return -1;
}