

#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;

int theNubmerOfRules;
string productionsRules[1000];
string getTerminal(string currentRule, int stratFrom) {
	string terminal;
	for (int i = stratFrom; i < currentRule.size(); i++)
	{
		if (isupper(currentRule[i])) {
			cout << "PLEASE FOLLOW THER RULeES.\n"; exit(0);
		}

		if (isspace(currentRule[i]))
			break;
	
			terminal += currentRule[i];
			
	}
	return terminal;
}

string getNonTerminal(string currentRule, int stratFrom) {
	string nonTerminal;
	for (int i = stratFrom; i < currentRule.size(); i++)
	{
		if (islower(currentRule[i])) {
			cout << "PLEASE FOLLOW THE RULES.\n"; exit(0);
		}
		if (isspace(currentRule[i]))
			break;
		nonTerminal += currentRule[i];
	}
	return nonTerminal;
}
string firstTerminal(string currentRule, string productionsRules[]) {
	string firstSet = "";
	char TerminalOrNonTerminal = currentRule[currentRule.find('>')+2];
	int  IndexOfTerminalOrNonTerminal = currentRule.find('>') + 2;
	
	if (!isupper(TerminalOrNonTerminal)) {
		//to guarantee epsilon in the correct pos.
		if (currentRule.back() != '$' && TerminalOrNonTerminal == '$') {
			cout << "YOU CAN'T PUT $ HERE"; exit(0);
		}

		firstSet = getTerminal(currentRule, IndexOfTerminalOrNonTerminal);
		return firstSet;
	}
	else {
	string nonTerminal = getNonTerminal(currentRule, IndexOfTerminalOrNonTerminal);
	
		for (int rule = 0; rule < theNubmerOfRules; rule++) {
			string anotherNonTerminal = productionsRules[rule].substr(0, productionsRules[rule].find('-')-1);
		
			if (nonTerminal == anotherNonTerminal) {
				currentRule = productionsRules[rule];
				firstSet += firstTerminal(currentRule, productionsRules) + " ";
			}
		}

		return firstSet;
	}
	return firstSet;
}

set<string> getFirstSet(string NonTerminal) {

	string currentRule;
	set<string> firstSet;
	
	bool hasEpsilon = true;

	for (int j = 0; j < theNubmerOfRules; j++) {
		string anotherNonTerminal = productionsRules[j].substr(0, productionsRules[j].find('-') - 1);
		if ( NonTerminal == anotherNonTerminal) {
			 currentRule = productionsRules[j];
			//No repetition
				if (firstTerminal(currentRule, productionsRules).find("$") != firstTerminal(currentRule, productionsRules).npos && currentRule.size() != 6) {
					char TerminalOrNonTerminal = currentRule[currentRule.find('>') + 2];
					int  IndexOfTerminalOrNonTerminal = currentRule.find('>') + 2;

					for (int i = IndexOfTerminalOrNonTerminal; i < currentRule.size(); i++) {
						if (!isspace(TerminalOrNonTerminal)) {
						//	cout << TerminalOrNonTerminal;
								if (!isupper(TerminalOrNonTerminal)) {
									if (firstSet.count(getTerminal(currentRule, i)) == 0)
										firstSet.insert(getTerminal(currentRule, i));
										hasEpsilon = false;
										i += getTerminal(currentRule, i).size();
										TerminalOrNonTerminal = currentRule[i];
								}
								else {
									//to save from override
									set<string> save = getFirstSet(getNonTerminal(currentRule, i));
									firstSet.insert(save.begin(), save.end());
									
									if (firstSet.count("$") != 0)
										firstSet.erase("$");
									else
										hasEpsilon = false;

									i += getNonTerminal(currentRule, i).size();
									TerminalOrNonTerminal = currentRule[i + 1];

								}
						}
						
					}
				}

				else {
					hasEpsilon = false;
					firstSet.insert(firstTerminal(currentRule, productionsRules));
				}
			 
		}
	}

	if (hasEpsilon)
		firstSet.insert("$");
	
	return firstSet;

}
int main()
{
	cin >> theNubmerOfRules;
	cin.ignore();
	//get productions rules
	for (int i = 0; i < theNubmerOfRules; i++)
		getline(cin,productionsRules[i]);

	multiset<string>visited;
	for (int rule = 0; rule < theNubmerOfRules; rule++) {
		string currentRule = productionsRules[rule];
		string nonTerminal = getNonTerminal(currentRule,0);
		visited.insert(nonTerminal);
		set<string> firstSet;

		//to know if the rule has been visited or no
		if (visited.count(nonTerminal) == 1) {
			firstSet = getFirstSet(nonTerminal);
			cout << "  first set(" << nonTerminal << ") = ";
			for (auto it : firstSet) {

				cout << it << " ";
			}
			cout << endl;
		}
	}
}
