/*Используя библиотеку STL, написать программу формирования
частотного словаря появления отдельных слов в некотором тексте.
Предусмотреть следующую функциональность :
• Чтение исходного текста из файла;
• Вывод информации обо всех словах;
• Вывод информации о наиболее часто встречающемся слове;
• Запись результата в файл.
При разработке программы использовать ассоциативный контейнер map*/

#include <iostream>
#include <fstream>
#include<sstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

typedef multimap<int, vector<char>> MyMap;
typedef MyMap::iterator Iter;

int WordCount(vector<char> word, MyMap m)
{
	int count = 0;

	for (Iter it = m.begin(); it != m.end(); it++)
		if (word == it->second) count = it->first;

	return count;
}

vector<char> MostOftenWord(MyMap m)
{
	int max = 0, temp = 0;

	for (Iter it = m.begin(); it != m.end(); it++)
	{
		temp = it->first;
		if (max < temp) max = temp;
	}
	vector<char>word;

	Iter res = m.find(max);

	word = res->second;

	return word;
}
MyMap WordsCountedMap(MyMap m)
{
	MyMap n;

	int wordCount = 0;

	for (Iter it = m.begin(); it != m.end(); it++)
	{
		for (Iter it2 = m.begin(); it2 != m.end(); it2++)
		{
			if (it->second == it2->second) wordCount++;
		}
		n.insert(MyMap::value_type(wordCount, it->second));

		wordCount = 0;
	}

	return n;
}

MyMap getMap(string line)
{
	// начальная инициализация map
	MyMap m;

	int y, numWord = 1;

	vector<char> word;

	//ostream_iterator<char> out(cout, " ");

	for (int i = 0; i <= line.length(); i++)
	{
		y = 0;

		while (
			(int(line[i]) >= 65) &&
			(int(line[i]) <= 90) ||
			(int(line[i]) >= 97) &&
			(int(line[i]) <= 122)
			)
		{
			word.push_back(line[i]);
			i++;
		}

		if (word.size() != 0)
		{
			m.insert(MyMap::value_type(numWord, word));

			word.erase(word.begin(), word.end());

			numWord++;
		}
	}
	return m;
}

char* getAString(vector<char> word)
{

	int logSize = 0, phySize = 1;

	char* res;

	res = (char*)malloc(sizeof(char));

	vector<char>::iterator it;

	for (it = word.begin(); it != word.end(); it++)
	{
		if (logSize == phySize)
		{
			phySize *= 2;
			res = (char*)realloc(res, sizeof(char) * phySize);
		}
		res[logSize++] = *it;
	}

	res = (char*)realloc(res, sizeof(char*) * (logSize + 1));

	res[logSize] = '\0';

	return res;
}

string inToString(int number)
{

	stringstream stream;

	stream << number;

	string outString;

	stream >> outString;

	return  outString;

}
string GetReport(int count, vector<char> word, MyMap m)
{
	string report,s1,s2,s3,s4,s5;

	s1 = "\nREPORT: The most often word in text is [";
	s2 = getAString(word);
	s3 = "] meets [";
	s4 = inToString(count);
	s5 = "] times.\n";


	report = s1 + s2 + s3 + s4 + s5;

	return report;
}

void SaveReport(string filename, string report)
{
	std::ofstream file;

	file.open(filename);

	file << report;

	file.close();

	cout << "\nFile [" << filename << "] saved\n";
}

string LoadTextFile(string filename)
{
	string line;

	ifstream myfile(filename);

	if (myfile.is_open())
	{
		getline(myfile, line);

		if (getline(myfile, line))
		{
			cout << "\nFile [" << filename << "] is opened\n";
			//cout << line << '\n';
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	return line;
}


void PrintReport(string rep)
{
	cout << endl << rep << endl;
}

int main()
{
	string line;

	string filename = "Text1.txt", reportfile = "reportfile.txt";

	int a = 0;

	while ((a != 1) && (a != 2))
	{
		system("cls");

		cout << "\nPlease choose (1)small or (2)big file load : ";

		cin >> a;
	}
	if (a == 2) filename = "Text.txt";


	line = LoadTextFile(filename);

	PrintReport(line);

	MyMap m = getMap(line);

	cout << "\nPlease wait . . .\n";

	MyMap n = WordsCountedMap(m);

	vector<char> word = MostOftenWord(n);

	int count = WordCount(word, m);

	string report = GetReport(count, word, m);

	SaveReport(reportfile, report);

	string rep = LoadTextFile(reportfile);

	PrintReport(rep);

	return 0;
}
