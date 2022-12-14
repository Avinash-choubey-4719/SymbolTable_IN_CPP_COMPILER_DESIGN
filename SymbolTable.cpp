#include <iostream>
using namespace std;

const int MAX = 100;

class Node {

	string identifier, scope, type;
	int lineNo;
	Node* next;

public:
	Node()
	{
		next = NULL;
	}

	Node(string key, string value, string type, int lineNo)
	{
		this->identifier = key;
		this->scope = value;
		this->type = type;
		this->lineNo = lineNo;
		next = NULL;
	}

	void print()
	{
		cout << "Identifier's Name:" << identifier
			<< "\nType:" << type
			<< "\nScope: " << scope
			<< "\nLine Number: " << lineNo << endl;
	}
	friend class SymbolTable;
};

class SymbolTable {
	Node* head[MAX];

public:
	SymbolTable()
	{
		for (int i = 0; i < MAX; i++)
			head[i] = NULL;
	}

	int hashf(string id); 
	bool insert(string id, string scope,
				string Type, int lineno);

	string find(string id);

	bool deleteRecord(string id);

	bool modify(string id, string scope,
				string Type, int lineno);
};


bool SymbolTable::modify(string id, string s,
						string t, int l)
{
	int index = hashf(id);
	Node* start = head[index];

	if (start == NULL)
		return "-1";

	while (start != NULL) {
		if (start->identifier == id) {
			start->scope = s;
			start->type = t;
			start->lineNo = l;
			return true;
		}
		start = start->next;
	}

	return false; 
}


bool SymbolTable::deleteRecord(string id)
{
	int index = hashf(id);
	Node* tmp = head[index];
	Node* par = head[index];

	
	if (tmp == NULL) {
		return false;
	}
    
	if (tmp->identifier == id && tmp->next == NULL) {
		tmp->next = NULL;
		delete tmp;
		return true;
	}

	while (tmp->identifier != id && tmp->next != NULL) {
		par = tmp;
		tmp = tmp->next;
	}
	if (tmp->identifier == id && tmp->next != NULL) {
		par->next = tmp->next;
		tmp->next = NULL;
		delete tmp;
		return true;
	}

	
	else {
		par->next = NULL;
		tmp->next = NULL;
		delete tmp;
		return true;
	}
	return false;
}


string SymbolTable::find(string id)
{
	int index = hashf(id);
	Node* start = head[index];

	if (start == NULL)
		return "-1";

	while (start != NULL) {

		if (start->identifier == id) {
			start->print();
			return start->scope;
		}

		start = start->next;
	}

	return "-1"; 
}


bool SymbolTable::insert(string id, string scope,
						string Type, int lineno)
{
	int index = hashf(id);
	Node* p = new Node(id, scope, Type, lineno);

	if (head[index] == NULL) {
		head[index] = p;
		cout << "\n"
			<< id << " inserted";

		return true;
	}

	else {
		Node* start = head[index];
		while (start->next != NULL)
			start = start->next;

		start->next = p;
		cout << "\n"
			<< id << " inserted";

		return true;
	}

	return false;
}

int SymbolTable::hashf(string id)
{
	int asciiSum = 0;

	for (int i = 0; i < id.length(); i++) {
		asciiSum = asciiSum + id[i];
	}

	return (asciiSum % 100);
}


int main()
{
	SymbolTable st;
	string check;
	cout << "**** SYMBOL_TABLE ****\n";

	
	if (st.insert("if", "local", "keyword", 4))
		cout << " -successfully";
	else
		cout << "\nFailed to insert.\n";


	if (st.insert("number", "global", "variable", 2))
		cout << " -successfully\n\n";
	else
		cout << "\nFailed to insert\n";

	
	check = st.find("if");
	if (check != "-1")
		cout << "Identifier Is present\n";
	else
		cout << "\nIdentifier Not Present\n";

	
	if (st.deleteRecord("if"))
		cout << "if Identifier is deleted\n";
	else
		cout << "\nFailed to delete\n";

	
	if (st.modify("number", "global", "variable", 3))
		cout << "\nNumber Identifier updated\n";

	
	check = st.find("number");
	if (check != "-1")
		cout << "Identifier Is present\n";
	else
		cout << "\nIdentifier Not Present";

	return 0;
}