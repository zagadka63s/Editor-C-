#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>// Для функции replace
#include <locale.h>
using namespace std;

// Функция для вывода меню выбора действий
void printMenu()
{
	cout << "\n==== Текстовый Редактор ====\n";
	cout << "1. Открыть файл\n";
	cout << "2. Просмотреть содержимое\n";
	cout << "3. Редактировать содержимое\n";
	cout << "4. Поиск и замена\n";
	cout << "5. Настройки\n";
	cout << "6. Сохранить изменения\n";
	cout << "7. Выйти\n";
	cout << "Выбиерите действия ( 1- 7)";
}


// Функция для открытия файла
void openFile(ifstream& file, string& filename)
{
	cout << "Введите имя файла для открытия: ";
	cin.ignore();
	getline(cin, filename);
	file.open(filename);
	if (!file.is_open())
	{
		cout << "Ошибка открытия файла '" << filename << "'. Хотите создать новый файл с этим именем? (Y/N): ";
		char choice;
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
		{
			createNewFile(filename);
		}
	}
}



// Функция для просмотра содержимого файла

void viewFile(ifstream& file)
{
	string line;
	cout << "\n==== Содержимое файла ====\n";
	while (getline(file,line))
	{
		cout << line << endl;

	}
}

// Функия для поиска и замены текста в содержимом файла

void findAndReplace(string& content)
{
	string findStr, replaceStr;
	cout << "Введите строку для поиска: ";
	cin.ignore();
	getline(cin, findStr);
	cout << "Введите строку для замены: ";
	getline(cin, replaceStr);

	size_t pos = content.find(findStr);
	while (pos != string::npos)
	{
		content.replace(pos, findStr.length(), replaceStr);
		pos = content.find(findStr, pos + replaceStr.length());
	}
	cout << "Замена завершена.\n";
}

void createNewFile(const string& filename)
{
	ofstream newFile(filename);
	if (newFile.is_open())
	{
		cout << "Новый файл '" << filename << "' создан.\n";
	}
	else
	{
		cout << "Ошибка создания нового файла '" << filename << "'.\n";
	}
}


// Функция для отображения меню настроек ( пока не реализована)
void settingsMenu()
{
	cout << "\n==== Настройки ====\n";
}


// Функция для сохранения изменений в файле
void saveFile(ofstream& file, const string& filename, const string& content)
{
	file.open(filename);
	if (!file.is_open())
	{
		cout << "Ошибка открытия файла: " << filename << endl;
	}
	else {
		file << content;
		cout << "Файл успешно сохранен.\n";
	}
}

// Функция для редактирования содержимого файла
void editFile(string& content) {
	cout << "Введите новое содержимое файла (введите 'exit' для завершения редактирования):\n";
	content = "";
	string line;
	while (true) {
		getline(cin, line);
		if (line == "exit") {
			break;
		}
		content += line + "\n";
	}
}


int main()
{
	setlocale(LC_ALL, "russian");
	ifstream inputFile;
	ofstream outputFile;
	string currentFilename;
	string fileContent;

	while (true)
	{
		printMenu();
		int choice;
		cin >> choice;

		switch (choice)
		{
		case 1 :
			openFile(inputFile, currentFilename); // Открыть файл
			break;
		case 2 :
			if (inputFile.is_open())
			{
				viewFile(inputFile); // Просмотр содержмиого файла
			}
			else
			{
				cout << "Файл не открыт.\n";
			}
			break;
		case 3 :
			if (inputFile.is_open())
			{
				editFile(fileContent); // Редактировать содерижое файла
			}
			else
			{
				cout << "Файл не открыт.\n";
			}
			break;
		case 4:
			if (inputFile.is_open())
			{
				findAndReplace(fileContent); // Поиск и замена текста
			}
			else
			{
				cout << "Файл не открыт.\n";
			}
			break;
		case 5:
			settingsMenu(); // Меню настроек ( пока не реализован)
			break;
		case 6:
			if (inputFile.is_open())
			{
				saveFile(outputFile, currentFilename, fileContent);
			}
			else
			{
				cout << "Файл не открыт.\n";
			}
			break;
		case 7:
			cout << "Выход из редактора.\n";
			return 0;
		default:
			cout << "Недопустимый выбор.\n";
			break;
		}
	}
}