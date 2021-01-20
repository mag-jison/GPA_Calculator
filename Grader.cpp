#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#include "Grader.h"

using namespace std;

void GradeCalc::readFile() {
	fstream myfile;
	char answer = ' ';
	int num_unknown = 0;
	double score = 0.0, weight = 0.0, tweight = 0.0, grade = 0.0, t = 0.0;

	int user_input;
	cout << "************Grade Calculator************" << endl;
	cout << "----------------------------------------" << endl;
	cout << "\n(1) Class 1" << endl;
	cout << "(2) Class 2" << endl;
	cout << "(3) Class 3" << endl;
	cout << "(4) Class 4" << endl;
	cout << "\nSelect a class: ";
	cout << "\033[35m";
	cin >> user_input;
	cout << "\033[0m";
	switch (user_input) {
	case 1:
		myfile.open("class1_grades.txt");
		system("CLS");
		break;
	case 2:
		myfile.open("class2_grades.txt");
		system("CLS");
		break;
	case 3:
		myfile.open("class3_grades.txt");
		system("CLS");
		break;
	case 4:
		myfile.open("class4_grades.txt");
		system("CLS");
		break;
	default:
		cout << "ERROR 402: Please enter a VALID integer" << endl;
	}

	if (myfile.is_open()) {
			bool _empty = true;
			if (user_input != 8) {
				vector<double> _grad(5, 0);
				int k = 0;
				while (myfile >> weight >> score) {
					_empty = false;
					cout << "------------------" << endl;
					grade += (weight / 100) * score;
					t = grade - t;
					cout << weight << "% " << "| " << score << "% " << "| " << t << "% " << "| \n";
					tweight += weight;

					if (score > 89)
						_grad[0] += 1;
					else if (79 < score < 89)
						_grad[1] += 1;
					else if (69 < score < 79)
						_grad[2] += 1;
					else if (59 < score < 69)
						_grad[3] += 1;
					else
						_grad[4] += 1;
				}
				if (!_empty){
					predictor(num_unknown, grade, tweight);
					cout << endl << endl;
					exportGraph(_grad);
				} else
					cout << "ERROR 45: EMPTY FILE!" << endl;
			} else {
				vector<double> gp = { 4, 3.7, 3.3, 3, 2.7, 2.3, 2, 1.7, 1.3, 1, 0.7, 0.0 }, dist_grad(5, 0);
				string letter = "", course = "";
				double total_units = 0, total_gpa = 0;

				while (myfile >> units >> letter >> course && letter != "//") {
					total_units += units;
					cout << course;
					for (int i = 0; i <= (9 - course.length()); ++i)
						cout << " ";

					cout << " |   " << letter;

					for (int i = 0; i <= (2 - letter.length()); ++i)
						cout << " ";

					cout << " | ";

					if (letter == "A+" || letter == "A") {
						gpa = gp[0] * units;
						dist_grad[0] += 1;
					}
					else if (letter == "A-") {
						gpa = gp[1] * units;
						dist_grad[0] += 1;
					}
					else if (letter == "B+") {
						gpa = gp[2] * units;
						dist_grad[1] += 1;
					}
					else if (letter == "B") {
						gpa = gp[3] * units;
						dist_grad[1] += 1;
					}
					else if (letter == "B-") {
						gpa = gp[4] * units;
						dist_grad[1] += 1;
					}
					else if (letter == "C+") {
						gpa = gp[5] * units;
						dist_grad[2] += 1;
					}
					else if (letter == "C") {
						gpa = gp[6] * units;
						dist_grad[2] += 1;
					}
					else if (letter == "C-") {
						gpa = gp[7] * units;
						dist_grad[2] += 1;
					}
					else if (letter == "D+") {
						gpa = gp[8] * units;
						dist_grad[3] += 1;
					}
					else if (letter == "D") {
						gpa = gp[9] * units;
						dist_grad[3] += 1;
					}
					else if (letter == "D-") {
						gpa = gp[10] * units;
						dist_grad[3] += 1;
					}
					else {
						gpa = 0;
						dist_grad[4] += 1;
					}

					cout << gpa << " pts " << endl;
					cout << "-------------------------" << endl;
					total_gpa += gpa;
				}
				cout << endl << endl;
				exportGraph(dist_grad);
				cout << "\nYour GPA is: " << "\033[32m" << setprecision(3) << total_gpa / total_units << "\033[0m" << endl;
			}
		}
		else
			cout << "ERROR 405: NO FILES FOUND";

	cout << "...\n...\n...\nagain? (Y/N): ";
	cin >> answer;
	} while (answer == 'Y' || answer == 'y');
}


void GradeCalc::exportGraph(vector<double> dis) {
	int max = 0;
	for (double i : dis) {
		if (i > max)
			max = i;
	}
	for (int j = max; j != 0; --j) {
		if (j < 10)
			cout << " ";
		cout << j << " " << ".";
		for (int l = 0; l < dis.size(); ++l) {
			cout << " ";
			if (j == dis.at(l)) {
				cout << "\033[95m" << "|" << "\033[0m" << "  ";
				dis.at(l)--;
			}
		}
		cout << endl;
	}
	cout << "   . . . . . . . . . .\n     A   B   C   D   F" << endl << endl;
}

void GradeCalc::predictor(int num_unknown, double grade, double tweight) {
	string color;
	double w_ass = 0.0, s_ass = 0.0, g_ass = 0.0;
	double probA = 0.0, probB = 0.0, probC = 0.0, probD = 0.0, probF = 0.0, leftover = 100 - tweight;
	int i = 100;
	cout << endl;
	while (i != 0) {
		g_ass = 0.0;
		g_ass += (leftover / 100) * i;

		if ((grade + g_ass) >= 90) {
			color = "\033[32m";
			probA++;
		}
		else if ((grade + g_ass) >= 80) {
			color = "\033[96m";
			probB++;
		}
		else if ((grade + g_ass) >= 70) {
			color = "\033[93m";
			probC++;
		}
		else if ((grade + g_ass) >= 60) {
			color = "\033[35m";
			probD++;
		}
		else {
			color = "\033[91m";
			probF++;
		}
		cout << "Your FINAL GRADE with a " << i << "% on the Final Exam is: " << color << setprecision(3) << (grade + g_ass) << "%" << "\033[0m" << endl;
		i -= 1;
	}
	cout << "\nThe probability of getting an A is: " << probA << "%" << endl;
	cout << "The probability of getting an B is: " << probB << "%" << endl;
	cout << "The probability of getting an C is: " << probC << "%" << endl;
	cout << "The probability of getting an D is: " << probD << "%" << endl;
	cout << "The probability of getting an F is: " << probF << "%" << endl;
}
