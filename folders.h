#pragma once
#include <sys\stat.h>
#include <iostream>
#include <dirent.h>
#include <conio.h>
#include <fstream>
#include "filebutton.h"

using namespace std;


struct nod {
	string extension = "folder";
	int activ;
	string nume;
	string adresa;
	int nr_foldere = 0;
	nod* parinte;
	nod* foldere[1001];
	int x = 0;
	int y = 0;
} *folderCopiat;

struct arbore {
	nod* start;
}a[1001],arboreActiv;

struct fereastra {
    int x;
    int y;
	nod* backToParinte;
	nod* activFolder;
	nod* selectedFolder;
	string sortedExtension = "default";
	string sortedName = "default";
	//string activeExtension = "folder";
}F1, F2, F;

string numeFolder;

int fereastraActiva = 1; //1 - fereastra stanga | 2 - fereastra dreapta


string extension(string file_name)
{
	//store the position of last '.' in the file name
	int position = file_name.find_last_of(".");

	//store the characters after the '.' from the file_name string
	string result = file_name.substr(position + 1);
	//print the result
	return result;
}

string name(string file_name)
{
	//store the position of last '.' in the file name
	int position = file_name.find_last_of(".");
    char nume[100];
    nume[0]=NULL;
    strcpy(nume,file_name.c_str());
	nume[position]=NULL;
	if(file_name=="." || file_name=="..") return file_name;
	file_name=nume;
	return file_name ;
}


void getFolders(nod* parinte)
{
	struct dirent* d;
	struct stat dst;

	DIR* dr;

	string path = parinte->adresa;


	dr = opendir(path.c_str());

	if (dr != NULL)
	{

		for (d = readdir(dr); d != NULL; d = readdir(dr))
		{
			nod* newFolder;
			newFolder = new nod;
			string type = d->d_name;
			type = path + type;
			if (stat(type.c_str(), &dst) == 0)
			{
				if (dst.st_mode & S_IFDIR)
				{
					type = "is a FOLDER.";
					newFolder->extension = "folder";
				}
				else if (dst.st_mode & S_IFREG)
				{
					type = "is a FILE.";
					newFolder->extension = extension(d->d_name);
				}
			}
			//Cream un nod pentru folder/fisier nou
			newFolder->adresa = parinte->adresa;
			newFolder->adresa = newFolder->adresa + d->d_name + "/";
			newFolder->nume = name(d->d_name);
			newFolder->parinte= parinte;

			//Legam folderul/fisierul creat de folderul parinte
			parinte->foldere[parinte->nr_foldere] = newFolder;
			parinte->nr_foldere++;


			//cout<<d->d_name<<endl<<type<<endl;
		}
		//cout << path;
		closedir(dr);
	}
	else
	{
		cout << "ERROR" << endl;
	}
	//getch();
}
