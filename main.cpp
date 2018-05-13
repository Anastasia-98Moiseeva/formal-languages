/*
Реализациа алгоритма обработки регулярных выражений. Аргументами являются строка в алфавите {a, b, c, 1, ..., +, *},
а так же параметры: буква x и натуральное число k. В случае, если входная строка не является корректным регулярным
выражением в обратной польской записи, необходимо выдать сообщение об ошибке. Вывести есть ли в данном языке слова,
содержащие суффикс x^k.
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>

using namespace std;

class Search
{
public:

	string regular_expression;

	char x;

	double k;

	string SearchSuffix();

	bool IsCorrect();

	Search();

private:

	string language;
	string operations;

	int FindBorders(int i, vector<int>& border);

	double MaxSuffLength(vector<int>& border);

	double MaxPref(int i, vector<int>& border);

	double FindMaxLetter(int i, vector<int>& border);
};

Search::Search(){
	language = "abc1";
	operations = "+.*";
}

bool Search::IsCorrect(){
	stack<char> symbols;
	for (int i = 0; i < regular_expression.length(); i++){
		if (language.find(regular_expression[i]) != -1){
			symbols.push(regular_expression[i]);
		}
		else {
			if (operations.find(regular_expression[i]) == 0 || operations.find(regular_expression[i]) == 1){
				if (symbols.size() < 2){
					return false;
				}
				symbols.pop();
			}
			else {
				if (operations.find(regular_expression[i]) == 2){
					if (symbols.size() == 0){
						return false;
					}
				}
				else {
					return false;
				}
			}
		}
	}
	if (symbols.size() == 1){
		return true;
	}
	else {
		return false;
	}
}

double Search::FindMaxLetter(int i, vector<int>& border){
	if (operations.find(regular_expression[i]) == 0){
		return max(FindMaxLetter(i + 1, border), FindMaxLetter(border[i] + 1, border));
	}
	else {
		if (operations.find(regular_expression[i]) == 1){
			double max1 = FindMaxLetter(i + 1, border);
			double max2 = FindMaxLetter(border[i] + 1, border);
			if (max1 == -INFINITY || max2 == -INFINITY){
				return -INFINITY;
			}
			return max1 + max2;
		}
		else {
			if (operations.find(regular_expression[i]) == 2){
				if (FindMaxLetter(i + 1, border) > 0){
					return INFINITY;
				}
				else {
					return 0;
				}
			}
			else {
				if (regular_expression[i] == x){
					return 1;
				}
				else {
					if (regular_expression[i] == '1'){
						return 0;
					}
					else {
						return -INFINITY;
					}
				}
			}
		}
	}
}

double Search::MaxPref(int i, vector<int>& border){
	if (operations.find(regular_expression[i]) == 0){
		return max(MaxPref(i + 1, border), MaxPref(border[i] + 1, border));
	}
	else {
		if (operations.find(regular_expression[i]) == 1){
			double max_letter = FindMaxLetter(i + 1, border);
			if (max_letter == INFINITY){
				return INFINITY;
			}
			return max(MaxPref(i + 1, border), max_letter + MaxPref(border[i] + 1, border));
		}
		else {
			if (operations.find(regular_expression[i]) == 2){
				if (FindMaxLetter(i + 1, border) > 0){
					return INFINITY;
				}
				else {
					return MaxPref(i + 1, border);
				}
			}
			else {
				if (regular_expression[i] == x){
					return 1;
				}
				else {
					return 0;
				}
			}
		}
	}
}

double Search::MaxSuffLength(vector<int>& border){
	FindBorders(0, border);
	return MaxPref(0, border);
}

int Search::FindBorders(int i, vector<int>& border){
	if (operations.find(regular_expression[i]) == 0 || operations.find(regular_expression[i]) == 1){
		border[i] = FindBorders(i + 1, border);
		return FindBorders(border[i] + 1, border);
	}
	else {
		if (operations.find(regular_expression[i]) == 2){
			return FindBorders(i + 1, border);
		}
		else {
			if (language.find(regular_expression[i] != -1)){
				return i;
			}
			else {
				throw "Error: unidentified character.";
			}
		}
	}
}

string Search::SearchSuffix(){
	reverse(regular_expression.begin(), regular_expression.end());

	int l = regular_expression.length();

	vector<int> border(l);

	double max_length_suff = MaxSuffLength(border);

	if (max_length_suff >= k){
		return "YES";
	}
	else {
		return "NO";
	}
}

int main()
{
	Search S;

	cout << "Enter a regular expression:\n";
	cin >> S.regular_expression;
	while (S.IsCorrect() == false){
		cout << "Invalid regular expression. Please, enter correct expression:\n";
		cin >> S.regular_expression;
	}
	cout << "Enter a letter:\n";
	cin >> S.x;
	while (S.x != 'a' && S.x != 'b' && S.x != 'c' && S.x != '1'){
		cout << "Invalid letter. Please, enter correct letter:\n";
		cin >> S.x;
	}
	cout << "Enter a number:\n";
	cin >> S.k;
	while (S.k < 0){
		cout << "Invalid number. Please, enter correct number:\n";
		cin >> S.k;
	}
	string result = S.SearchSuffix();
	cout << result;

	return 0;
}
