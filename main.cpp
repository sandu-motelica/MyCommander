#include <SFML/Graphics.hpp>
#include "Button.h"
#include "filebutton.h"
#include "filearbore.h"
#include "textbutton.h"
#include "textbox.h"
#include "folders.h"
#include <windows.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <sys\stat.h>
#include <iostream>
#include <dirent.h>
#include <conio.h>
#include <cstdlib>

using namespace std;
using namespace sf;

Font font;

void clearFolder(nod *folder) {
    folder->nr_foldere = 0;
}

void afisareArbore(nod *start, int k, RenderWindow &window) {
    int x = 0;
    int y = 1;
    for(int i = 0;i < start->nr_foldere;i++) {
            //for(int j = 0; j <= k;j++)cout << " ";
            //cout << start->foldere[i]->nume << "    Extensie: " << start->foldere[i]->extension <<   endl;
            fileButtonArbore btn4(start->foldere[i]->nume, { 160,20 }, 14, Color::White, Color::Black, 1, 32*(i+2), start->foldere[i]->extension);
            if (i * 20 < 518) {
                if(start->foldere[i]->parinte!=NULL){
                btn4.setPosition({ 1, 32 }, x, y, i);
                btn4.setFont(font);
                btn4.drawTo(window, x, y);
                start->foldere[i]->x = x;
                start->foldere[i]->y = y;
                }
                else {
                btn4.setPosition({ 1, 32 }, x, y, i);
                btn4.setFont(font);
                btn4.drawTo(window, x, 150);
                start->foldere[i]->x = x;
                start->foldere[i]->y = y*start->foldere[i-1]->nr_foldere*20;
                        }
                }
                //for(int j = 0;j <k;j++) cout << "---";
                //cout << start->foldere[i]->nume << endl;
            if(start->foldere[i]->nr_foldere>0) afisareArbore(start->foldere[i], k+4, window);

            }

    }

void parcurgereRecursiva(nod *start, int xP, int yP, RenderWindow &window) {
    int k = 0;
    for(int i = 0;i < start->nr_foldere;i++) {
      if(xP >= start->foldere[i]->x && xP <= start->foldere[i]->x+160 && yP >= start->foldere[i]->y && yP <= start->foldere[i]->y+20){
        clearFolder(start->foldere[i]);
        getFolders(start->foldere[i]);
        afisareArbore(arboreActiv.start,k, window);

        cout << start->foldere[i]->nume<< endl;
        return;
    }
    else {
        parcurgereRecursiva(start->foldere[i],xP, yP, window);
    }
    }
}


void afisareFereastra( RenderWindow &window, fereastra F) {
    int  x= 0, y = 0;
    //cout << F.activFolder->nr_foldere << endl;
        for(int i = 0;i < F.activFolder->nr_foldere;i++) {
            fileButton btn4(F.activFolder->foldere[i]->nume, { 430,20 }, 14, Color::White, Color::Black, F.x, F.y/4.5*(i+1), F.activFolder->foldere[i]->extension);
            if (i * 20 < 480) {

                btn4.setPosition({ F.x,F.y }, x, y, i);
                btn4.setFont(font);
                btn4.drawTo(window, x, y);
            }
            //cout << F.activFolder->foldere[i]->nume << F.x << " " << F.y/4*(i+1) << endl;
            //cout << start->foldere[i]->nume;
        }
}

void initApp(char disks[1001]) {
        for(int i = 0; i < 2;i++) {
            a[i].start = new nod;
            a[i].start->nume = disks[i];
            a[i].start->adresa = disks[i];
            a[i].start->adresa += ":/";
            a[i].start->nr_foldere = 0;
            //cout << a[i].start->nume << endl;
            getFolders(a[i].start);
            //cout << endl;
        }
        /*arboreActiv.start = new nod;
        arboreActiv.start->nume = "arbore";
        arboreActiv.start->foldere[0] = new nod;
         arboreActiv.start->foldere[1] = new nod;
        arboreActiv.start->nr_foldere = 2;
        arboreActiv.start->foldere[0]->nume = "C:/";
         arboreActiv.start->foldere[1]->nume = "D:/";
         */
        //k++;
        //arboreActiv.start->foldere[k] = a[1].start;
}

void creareFolder(RenderWindow &window, Textbox &textbox) {
        cout <<"textul: "<< textbox.getText() << endl;
    string adresa = F.activFolder->adresa + textbox.getText();
    if(mkdir(adresa.c_str()) == -1)
        cout << "Nu se poate crea folderul la adresa respectiva" << adresa<<endl;
    else{
        cout << "Fisierul a fost creat"<<endl;
       clearFolder(F.activFolder);
        getFolders(F.activFolder);
        afisareFereastra(window, F);
    }
}

void selectFolder(int xP, int yP, RenderWindow &window, int activZona, int &selectX, int &selectY){
      cout << "Activzona: " << activZona<<endl;
	    if(activZona == 1 || activZona == 2) {
	    	    int x = 0, y = 0;
	    yP-=70;
        //cout << xP << " " << yP << endl;
        for(int i = 0;i < F.activFolder->nr_foldere;i++) {

            fileButton btn4(F.activFolder->foldere[i]->nume, { 430,20 }, 14, Color::White, Color::Black, F.x, F.y/(4.5)*(i+1),F.activFolder->foldere[i]->extension);
            if (i * 20 < 480) {
                btn4.setPosition({ F.x,F.y }, x, y, i);
                btn4.setFont(font);
                btn4.drawTo(window, x, y);
            }

            if(xP >= F.x && xP <= F.x+430 && yP >= F.y/(4.5)*(i+1) && yP <= F.y/(4.5)*(i+1)+20) {
                    //F.activFolder->foldere[i]->nume << F.x<< endl;
                    //cout << F.activFolder->nume << "x";

                    if(F.activFolder->foldere[i]->nume == ".") {
                        //F.activFolder = F.activFolder->parinte;
                        //F.backToParinte = F.activFolder->parinte;
                        cout << "nu poti selecta acest folder"<<endl;

                        //F.activFolder = F.activFolder->foldere[i]->parinte;
                        //cout << "parinte " << F.activFolder->parinte->nume;
                    }
                    else {
                        F.selectedFolder = F.activFolder->foldere[i];
                        selectX=645;
                        selectY=90+20*i;

                    }
                   if(fereastraActiva == 1) {
                     F1= F;
                    afisareFereastra(window, F1);
                   }
                   else {
                      F2= F;
                    afisareFereastra(window, F2);
                   }

                    cout << "folderul selectat" << F.selectedFolder->nume<< endl;
                   return;
            }
            //cout << F.activFolder->foldere[i]->nume << F.x << " " << F.y*(i+1) << endl;
            //cout << start->foldere[i]->nume;
        }
	    }
	    else {
           // parcurgereRecursiva(arboreActiv.start, xP, yP, window);
	    }
}

	void getClickFolder(int xP, int yP, RenderWindow &window, int activZona) {
	    cout << "Activzona: " << activZona<<endl;
	    if(activZona == 1 || activZona == 2) {

	    	    int x = 0, y = 0;
	    yP-=70;
        //cout << xP << " " << yP << endl;
        for(int i = 0;i < F.activFolder->nr_foldere;i++) {

            fileButton btn4(F.activFolder->foldere[i]->nume, { 430,20 }, 14, Color::White, Color::Black, F.x, F.y/(4.5)*(i+1),F.activFolder->foldere[i]->extension);
            if (i * 20 < 480) {
                btn4.setPosition({ F.x,F.y }, x, y, i);
                btn4.setFont(font);
                btn4.drawTo(window, x, y);
            }
            if(xP >= F.x && xP <= F.x+430 && yP >= F.y/(4.5)*(i+1) && yP <= F.y/(4.5)*(i+1)+20) {
                    //F.activFolder->foldere[i]->nume << F.x<< endl;
                    //cout << F.activFolder->nume << "x";

                    if(F.activFolder->foldere[i]->nume == ".") {
                        F.activFolder = F.activFolder->parinte;
                        F.backToParinte = F.activFolder->parinte;

                        //F.activFolder = F.activFolder->foldere[i]->parinte;
                        //cout << "parinte " << F.activFolder->parinte->nume;
                    }
                    else {
                        if(F.activFolder->foldere[i]->extension=="folder")
                        {F.activFolder = F.activFolder->foldere[i];
                        F.backToParinte = F.activFolder->parinte;}
                        else {
                         char path[1001],aux[1001];
                            path[0]='"';
                            path[1]=NULL;
                            aux[0]=NULL;
                            strcat(path,F.activFolder->foldere[i]->adresa.c_str());
                            //cout << "xxx  " << F.activFolder->foldere[i]->adresa << endl;
                            for(int i=0;i<strlen(path);i++)
                            if(path[i]=='/') { strcpy(aux,path+i+1);
                            path[i]=NULL;
                            strcat(path,"\\");
                            strcat(path,aux);
                            }
                            int i=strlen(path);
                            path[i-1]='"';
                            path[i]=NULL;

                            cout << path << endl;

                    system(path);
                }

                    }
                    clearFolder(F.activFolder);
                    getFolders(F.activFolder);

                   if(fereastraActiva == 1) {
                     F1= F;
                    afisareFereastra(window, F1);
                   }
                   else {
                      F2= F;
                    afisareFereastra(window, F2);
                   }

                    cout << F.activFolder->nume<< endl;
                   return;
            }
            //cout << F.activFolder->foldere[i]->nume << F.x << " " << F.y*(i+1) << endl;
            //cout << start->foldere[i]->nume;
        }
	    }
	    else {
            parcurgereRecursiva(arboreActiv.start, xP, yP, window);
	    }
	}

int mouseFereastra(RenderWindow& window, RectangleShape &fereastra1, RectangleShape &fereastra2, string mouseButton, int &selectX, int &selectY) {
    F1.selectedFolder = NULL;
    F2.selectedFolder = NULL;
		float mouseX = Mouse::getPosition(window).x;
		float mouseY = Mouse::getPosition(window).y;

        float btnPosX1 = fereastra1.getPosition().x;
		float btnPosY1 = fereastra1.getPosition().y;

		float btnxPosWidth1 = fereastra1.getPosition().x + fereastra1.getLocalBounds().width;
		float btnxPosHeight1 = fereastra1.getPosition().y + fereastra1.getLocalBounds().height;

		float btnPosX2 = fereastra2.getPosition().x;
		float btnPosY2 = fereastra2.getPosition().y;

		float btnxPosWidth2 = fereastra2.getPosition().x + fereastra2.getLocalBounds().width;
		float btnxPosHeight2 = fereastra2.getPosition().y + fereastra2.getLocalBounds().height;
        //0 - arbore, 1-fereastra1, 2 - fereastra2

		if (mouseX<btnxPosWidth1 && mouseX>btnPosX1 && mouseY<btnxPosHeight1 && mouseY>btnPosY1) {
                cout<<"am selectat 1"<<endl;
                if(mouseButton == "LEFT")
                    getClickFolder(mouseX, mouseY, window, 1);
                else if(mouseButton == "RIGHT")
                    {
                selectFolder(mouseX, mouseY,window,1, selectX,selectY);
                /*RectangleShape file(Vector2f(430,20));
                file.setPosition({btnPosX1,btnPosY1});
                file.setFillColor(Color(0,0,0,0));
                file.setOutlineThickness(1);
                file.setOutlineColor(Color::Blue);
                window.draw(file);*/
                }
			return 1;
		}
		if (mouseX<btnxPosWidth2 && mouseX>btnPosX2 && mouseY<btnxPosHeight2 && mouseY>btnPosY2) {
		    cout<<"am selectat 2"<<endl;
		    if(mouseButton == "LEFT")
                    getClickFolder(mouseX, mouseY, window, 2);
                else if(mouseButton == "RIGHT")
                selectFolder(mouseX, mouseY,window,2,selectX, selectY);

			return 2;
		}

		if(mouseButton == "LEFT")
                    getClickFolder(mouseX, mouseY, window, 0);
                else if(mouseButton == "RIGHT")
                    {
                }
		return false;
	}


void activareFereastra(RenderWindow &window, RectangleShape &win2, RectangleShape &win3, string mouseButton, int &selectX,int &selectY) {
        //float mouseX = Mouse::getPosition(window).x;
		//float mouseY = Mouse::getPosition(window).y;
		//cout << "MOUSE CLICK : " << mouseX << " " << mouseY;

		/*mouseX>= 160 && mouseX<= 600 && mouseY >=7800 && mouseY<=56000*/
		fereastraActiva = mouseFereastra(window, win2, win3, mouseButton,selectX, selectY);
		//cout <<"mousefereastra" << mouseFereastra(window, win2, win3) << endl;
    if(fereastraActiva==1) {
        F = F1;
        fereastraActiva = 1;
        cout << "Fereastra activa : " << fereastraActiva<<endl;
    }
    else if(fereastraActiva==2) {
        F = F2;
        fereastraActiva = 2;
        cout << "Fereastra activa : "  << fereastraActiva<<endl;
    }
}


void remove_dir(char *path,fereastra F, RenderWindow &window)
{
        struct dirent *entry = NULL;
        DIR *dir = NULL;
        dir = opendir(path);
        while(entry = readdir(dir))
        {cout << path <<endl;
                DIR *sub_dir = NULL;
                FILE *file = NULL;
                char abs_path[100] = {0};
                if(*(entry->d_name) != '.')
                {
                        sprintf(abs_path, "%s/%s", path, entry->d_name);
                        if(sub_dir = opendir(abs_path))
                        {
                                closedir(sub_dir);
                                remove_dir(abs_path,F,window);
                        }
                        else
                        {
                                if(file = fopen(abs_path, "r"))
                                {
                                        fclose(file);
                                        remove(abs_path);
                                        rmdir(abs_path);
                                }
                        }
                }
        }

        if(path[strlen(path)-1] == '/') path[strlen(path)-1] = NULL;
         remove(path);
        rmdir(path);

        clearFolder(F.activFolder);
        getFolders(F.activFolder);
        afisareFereastra(window, F);
}

void stergereFolder(string adresa, fereastra F, RenderWindow &window) {
string deleteFnc = "rmdir /s /q D:/ffos";
cout << deleteFnc << endl;
   system ( deleteFnc.c_str());
    /*if(rmdir(adresa.c_str()) == -1)
        cout << "Nu se poate sterge folderul la adresa respectiva sau nu exista" << adresa<<endl;

    else{
        cout << "Fisierul a fost sters"<<endl;*/

        clearFolder(F.activFolder);
        getFolders(F.activFolder);
        afisareFereastra(window, F);
    //}
}


void redenumireFolder(fereastra F, RenderWindow &window, string numeNou) {

    char adresa_old[1001];
    adresa_old[0]==NULL;
    strcpy(adresa_old,F.selectedFolder->adresa.c_str());
    char adresa_new[1001];
    adresa_new[0]==NULL;
    strcpy(adresa_new,F.selectedFolder->adresa.c_str());
    int poz = -1;
    for(int i = strlen(adresa_new)-2;i>=0;i--) {
        if(adresa_new[i]=='/') {poz = i;break;}
    }
    if(poz!=-1) {adresa_new[poz+1] = NULL;

    //char old_name[] = "D:/AAA";
    char numeNouChar[1001];
    numeNouChar[0] = NULL;
    strcpy(numeNouChar, numeNou.c_str());
    strcat(adresa_new, numeNouChar);
    int value;

    value = rename(adresa_old, adresa_new);
    if(!value) {cout << "MERGE"<<endl;
    clearFolder(F.activFolder);
        getFolders(F.activFolder);
        afisareFereastra(window, F);
}
    }
else cout <<"NU SE POATE REDENUMI FOLDERUL/FISIERUL"<<endl;}


void changeDisk(string disk, int fereastraA, RenderWindow &window) {
//1-stanga 2-dreapta
    if(fereastraA == 1) {fereastraActiva = 1;
            a[0].start = new nod;
            a[0].start->nume = disk;
            a[0].start->adresa = disk;
            a[0].start->adresa += ":/";
            a[0].start->nr_foldere = 0;
            clearFolder(F1.activFolder);
            F1.activFolder = a[0].start;
            getFolders(a[0].start);
            afisareFereastra(window, F1);
            arboreActiv = a[0];

    }
    if(fereastraA == 2) {
            fereastraActiva = 2;
          a[1].start = new nod;
            a[1].start->nume = disk;
            a[1].start->adresa = disk;
            a[1].start->adresa += ":/";
            a[1].start->nr_foldere = 0;
            clearFolder(F2.activFolder);
            F2.activFolder = a[1].start;
            getFolders(a[1].start);
            afisareFereastra(window, F2);
    }
}

void copiereFolder(fereastra F) {
    //string adresa = F.selectedFolder->adresa;
    //string nume = F.selectedFolder->nume;
    folderCopiat = F.selectedFolder;
    if(folderCopiat) cout << folderCopiat->adresa<< endl;
}

void lipireFolder(fereastra F, RenderWindow &window) {
    string nume = folderCopiat->nume;
    string adresaLipire = F.activFolder->adresa;
    if(folderCopiat->extension == "folder") {
            adresaLipire = adresaLipire + nume + "/";
     if( mkdir(adresaLipire.c_str()) == -1 )
        cout << "Nu se poate crea folderul la adresa respectiva" << adresaLipire<<endl;
        else{
        cout << "Fisierul a fost creat"<<endl;
        }
    }
    char path[1001],aux[1001];
    path[0]=NULL;
    aux[0]=NULL;
    strcpy(path,folderCopiat->adresa.c_str());
    if(folderCopiat->extension!="folder" && path[strlen(path)-1]=='/') path[strlen(path)-1] = NULL;
    strcat(path," ");
    strcat(path,adresaLipire.c_str());
    for(int i=0;i<strlen(path);i++)
    if(path[i]=='/') {
    strcpy(aux,path+i+1);
    path[i]=NULL;
    strcat(path,"\\");
    strcat(path,aux);
    }
    strcpy(aux,path);
    strcpy(path, "Xcopy /E /I " );
    strcat(path,aux);
    cout << path << endl;
    system(path);

    clearFolder(F.activFolder);
    getFolders(F.activFolder);
    afisareFereastra(window, F);
}

char disks[101] = {'C', 'D'};

void numarff(fereastra F, int &foldere, int &fisiere){
    foldere=0;fisiere=0;
    for(int i = 0;i < F.activFolder->nr_foldere;i++)
       // cout<<F.activFolder->foldere[i]->extension<<endl;
        if(F.activFolder->foldere[i]->extension=="folder") foldere++;
    else fisiere++;
    if(F.activFolder->foldere[0]->nume==".") foldere=foldere-2;
}

string numarFisFol(fereastra F, int foldere, int fisiere){
    stringstream ss,ss1;
    numarff( F, foldere, fisiere);
    ss << foldere;
    ss1 << fisiere;
    string str = ss.str()+" foldere "+ss1.str()+" fisiere ";
return str;
}

void sortByExtension(fereastra F, RenderWindow &window) {
    cout << "fereastraactiva: " <<fereastraActiva;
    if(F.sortedExtension== "default" || F.sortedExtension== "down") {
            cout << "sortat " << F.sortedExtension<< endl;
            if(fereastraActiva == 1) F1.sortedExtension = "up";
            if(fereastraActiva == 2) F2.sortedExtension = "up";
            F.sortedExtension = "up";
            for(int i = 0; i < F.activFolder->nr_foldere-1;i++) {
                for(int j = i+1;j < F.activFolder->nr_foldere;j++) {
                    if(F.activFolder->foldere[i]->extension.compare(F.activFolder->foldere[j]->extension) > 0 && F.activFolder->foldere[i]->extension != "folder")
                        swap(F.activFolder->foldere[i],F.activFolder->foldere[j]);
                }
            }
    }
    else {
        cout << "sortat 2 " << F.sortedExtension<< endl;
        F.sortedExtension= "down";

    if(fereastraActiva == 1) F1.sortedExtension = "down";
    if(fereastraActiva == 2) F2.sortedExtension = "down";
    for(int i = 0; i < F.activFolder->nr_foldere-1;i++) {
                for(int j = i+1;j < F.activFolder->nr_foldere;j++) {
                    if(F.activFolder->foldere[i]->extension.compare(F.activFolder->foldere[j]->extension) < 0 && F.activFolder->foldere[i]->extension != "folder")
                        swap(F.activFolder->foldere[i],F.activFolder->foldere[j]);
                }
            }
    }
    afisareFereastra(window, F);
}
void sortByName(fereastra F, RenderWindow &window) {

    if(F.sortedName== "default" || F.sortedName == "down") {
            cout << "sortat 1 " << F.sortedName<< endl;
            if(fereastraActiva == 1) F1.sortedName = "up";
            if(fereastraActiva == 2) F2.sortedName = "up";
            F.sortedName = "up";
            for(int i = 0; i < F.activFolder->nr_foldere-1;i++) {
                for(int j = i+1;j < F.activFolder->nr_foldere;j++) {
                    if(F.activFolder->foldere[i]->nume.compare(F.activFolder->foldere[j]->nume) > 0 && F.activFolder->foldere[i]->extension != "folder")
                        swap(F.activFolder->foldere[i],F.activFolder->foldere[j]);
                }
            }
    }else {
        cout << "sortat 2 " << F.sortedName<< endl;
        F.sortedName = "down";

    if(fereastraActiva == 1) F1.sortedName = "down";
    if(fereastraActiva == 2) F2.sortedName = "down";
    for(int i = 0; i < F.activFolder->nr_foldere-1;i++) {
                for(int j = i+1;j < F.activFolder->nr_foldere;j++) {
                    if(F.activFolder->foldere[i]->nume.compare(F.activFolder->foldere[j]->nume) < 0 && F.activFolder->foldere[i]->extension != "folder")
                        swap(F.activFolder->foldere[i],F.activFolder->foldere[j]);
                }
            }
    }
    afisareFereastra(window, F);
}


int main()
{
    initApp(disks);
    F1.x = 168;F1.y = 90;
    F2.x = 645;F2.y = 90;
    arboreActiv = a[0];
    F1.activFolder = a[0].start;
    F2.activFolder = a[1].start;
    F = F1;

    int x = 0, y = 0, k=0,foldere1=0,foldere2=0,fisiere1=0,fisiere2=0,selectX,selectY;

    RenderWindow window(VideoMode(1080,635), "My Commander",Style::Close);
    window.setPosition({135,25});

    Image icon;
    icon.loadFromFile("images/mc.png");
    window.setIcon(64, 64, icon.getPixelsPtr());

    font.loadFromFile("Segoe UI.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(Color::White);
    text.setString("Fisiere PC:");

    RectangleShape header(Vector2f(1080, 30.5));
    header.setFillColor(Color::White);
    header.setPosition(0, 0);
    header.setOutlineThickness(1);
    header.setOutlineColor(Color(130, 135, 144));

    RectangleShape win1(Vector2f(160,558));
    win1.setFillColor(Color::White);
    win1.setPosition(1, 32);
    win1.setOutlineThickness(1);
    win1.setOutlineColor(Color(130, 135, 144));

    RectangleShape win2(Vector2f(430,500));
    win2.setFillColor(Color::White);
    win2.setPosition(168, 90);
    win2.setOutlineThickness(1);
    win2.setOutlineColor(Color(130, 135, 144));

    RectangleShape win3(Vector2f(430, 500));
    win3.setFillColor(Color::White);
    win3.setPosition(645, 90);
    win3.setOutlineThickness(1);
    win3.setOutlineColor(Color(130, 135, 144));

    RectangleShape fon(Vector2f(160,538));
    fon.setFillColor(Color(240,240,240));
    fon.setPosition(162, 32);

    Texture refreshtexture;
    refreshtexture.loadFromFile("images/refresh.png");
    Sprite refresh(refreshtexture);
    refresh.setOrigin({ 11,11 });
    refresh.setPosition(1065, 15);
    Button refreshbutton("", { 30,30 }, 20, Color::White, Color::Black);
    refreshbutton.setPosition({ 1050,0 });

    Texture addtexture;
    addtexture.loadFromFile("images/add2.png");
    Sprite add(addtexture);
    add.setPosition( 607, 281 );

    Button addbutton("", { 29,28 }, 20, Color(0,0,0,0), Color::Black);
    addbutton.setPosition({ 606, 280 });

    Texture renametexture;
    renametexture.loadFromFile("images/rename1.png");
    Sprite rename(renametexture);
    rename.setPosition( 607, 326 );

    Button renamebutton("", { 29,28 }, 20, Color(0,0,0,0), Color::Black);
    renamebutton.setPosition({ 606, 325 });

    textButton Vizualizare("F3 Vizualizare", { 35,614 }, 14, Color(0, 0, 0, 0), Color::Black, { 154, 25 });
    Vizualizare.setPosition({ 0, 610 });
    Vizualizare.setFont(font);

    textButton Lipire("F4 Lipire", { 203,614 }, 14, Color(0, 0, 0, 0), Color::Black, { 154, 25 });
    Lipire.setPosition({ 154, 610 });
    Lipire.setFont(font);

    textButton Copiere("F5 Copiere", { 348,614 }, 14, Color(0, 0, 0, 0), Color::Black, { 154, 25 });
    Copiere.setPosition({ 308, 610 });
    Copiere.setFont(font);

    textButton Redenumire("F6 Redenumire", { 494,614 }, 14, Color(0, 0, 0, 0), Color::Black, { 154, 25 });
    Redenumire.setPosition({ 462, 610 });
    Redenumire.setFont(font);

    textButton NewFolder("F7 Folder nou", { 651,614 }, 14, Color(0,0,0,0), Color::Black, {154, 25});
    NewFolder.setPosition({ 616, 610 });
    NewFolder.setFont(font);

    textButton Stergere("F8 Stergere", { 809,614 }, 14, Color(0, 0, 0, 0), Color::Black, { 154, 25 });
    Stergere.setPosition({ 770, 610 });
    Stergere.setFont(font);

    textButton Iesire("F9 Iesire", { 974,614 }, 14, Color(0, 0, 0, 0), Color::Black,  { 158, 25 });
    Iesire.setPosition({ 924, 610 });
    Iesire.setFont(font);

    textButton NumeFisier1("Nume", { 194,69 }, 14, Color::White, Color::Black,  { 290, 20 });
    NumeFisier1.setPosition({ 168, 68 });
    NumeFisier1.setFont(font);
    NumeFisier1.setOutlineThickness(1);
    NumeFisier1.setOutlineColor(Color(130, 135, 144));

    textButton ExtensieFisier1("Extensie", { 485,69 }, 14, Color::White, Color::Black,  { 140, 20 });
    ExtensieFisier1.setPosition({ 458, 68 });
    ExtensieFisier1.setFont(font);
    ExtensieFisier1.setOutlineThickness(1);
    ExtensieFisier1.setOutlineColor(Color(130, 135, 144));

    textButton NumeFisier2("Nume", { 671,69 }, 14, Color::White, Color::Black,  { 290, 20 });
    NumeFisier2.setPosition({ 645, 68 });
    NumeFisier2.setFont(font);
    NumeFisier2.setOutlineThickness(1);
    NumeFisier2.setOutlineColor(Color(130, 135, 144));

    textButton ExtensieFisier2("Extensie", { 962,69 }, 14, Color::White, Color::Black,  { 140, 20 });
    ExtensieFisier2.setPosition({ 935, 68 });
    ExtensieFisier2.setFont(font);
    ExtensieFisier2.setOutlineThickness(1);
    ExtensieFisier2.setOutlineColor(Color(130, 135, 144));

    textButton DiscC1("C", { 183,47 }, 14, Color::White, Color::Black,  { 40, 20 });
    DiscC1.setPosition({ 168, 45 });
    DiscC1.setFont(font);
    DiscC1.setOutlineThickness(1);
    DiscC1.setOutlineColor(Color(1, 72, 195));

    textButton DiscD1("D", { 228,47 }, 14, Color::White, Color::Black,  { 40, 20 });
    DiscD1.setPosition({ 213, 45 });
    DiscD1.setFont(font);
    DiscD1.setOutlineThickness(1);
    DiscD1.setOutlineColor(Color(130, 135, 144));

    textButton DiscC2("C", { 660,47 }, 14, Color::White, Color::Black,  { 40, 20 });
    DiscC2.setPosition({ 645, 45 });
    DiscC2.setFont(font);
    DiscC2.setOutlineThickness(1);
    DiscC2.setOutlineColor(Color(130, 135, 144));

    textButton DiscD2("D", { 705,47 }, 14, Color::White, Color::Black,  { 40, 20 });
    DiscD2.setPosition({ 690, 45 });
    DiscD2.setFont(font);
    DiscD2.setOutlineThickness(1);
    DiscD2.setOutlineColor(Color(1, 72, 195));


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {

            case  Event::Closed:
                window.close();
            case Event::MouseMoved: {
                if (refreshbutton.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left))
                    refreshbutton.setBackColor(Color(163, 206, 242));
                else if (refreshbutton.isMouseOver(window))
                    refreshbutton.setBackColor(Color(204, 232, 255));
                else refreshbutton.setBackColor(Color::White);

                if (addbutton.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left))
                    addbutton.setBackColor(Color(163, 206, 242));
                else if (addbutton.isMouseOver(window)) addbutton.setBackColor(Color(204, 232, 255));
                else addbutton.setBackColor(Color(0,0,0,0));
                if (renamebutton.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left))
                    renamebutton.setBackColor(Color(163, 206, 242));
                else if (renamebutton.isMouseOver(window)) renamebutton.setBackColor(Color(204, 232, 255));
                else renamebutton.setBackColor(Color(0,0,0,0));
            }
            }
         }

        window.clear(Color(240, 240, 240));
        window.draw(win1);
        afisareArbore(arboreActiv.start, k,window);
        window.draw(fon);
        window.draw(win2);
        window.draw(header);
        refreshbutton.drawTo(window);
        addbutton.drawTo(window);
        renamebutton.drawTo(window);
        window.draw(win3);
        window.draw(refresh);
        window.draw(add);
        window.draw(rename);
        afisareFereastra(window, F1);
        afisareFereastra(window, F2);
        string contor1=numarFisFol(F1,foldere1,fisiere1);
        string contor2=numarFisFol(F2,foldere2,fisiere2);

        textButton Contor1(contor1, { 174,572 }, 13, Color(240,240,240), Color::Black, { 430, 19 });
        Contor1.setPosition({ 168, 571 });
        Contor1.setFont(font);
        Contor1.setOutlineThickness(1);


        textButton Contor2(contor2, { 650,572 }, 13, Color(240,240,240), Color::Black, { 430, 19 });
        Contor2.setPosition({ 645, 571 });
        Contor2.setFont(font);
        Contor2.setOutlineThickness(1);

        if ( Iesire.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left) || (event.type==Event::KeyReleased && event.key.code==Keyboard::F9))
                {
                Iesire.setBackColor(Color(163, 206, 242));
                window.close();
                }
        else if(Iesire.isMouseOver(window))
            Iesire.setBackColor(Color(204, 232, 255));
            else  Iesire.setBackColor(Color(240, 240, 240));

        if ( DiscC1.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left)){
               DiscC1.setOutlineColor(Color(1, 72, 195));
                changeDisk("C",1,window);
                DiscD1.setOutlineColor(Color(130, 135, 144));
                }
        if ( DiscD1.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left))
                {
                DiscD1.setOutlineColor(Color(1, 72, 195));
                changeDisk("D",1,window);
                DiscC1.setOutlineColor(Color(130, 135, 144));
                }
        if ( DiscC2.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left))
                {
                DiscC2.setOutlineColor(Color(1, 72, 195));
                changeDisk("C",2,window);
                DiscD2.setOutlineColor(Color(130, 135, 144));
                }
        if ( DiscD2.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left))
                {
                DiscD2.setOutlineColor(Color(1, 72, 195));
                changeDisk("D",2,window);
                DiscC2.setOutlineColor(Color(130, 135, 144));
                }

        if ( addbutton.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left) || ( event.type==Event::KeyReleased && event.key.code==Keyboard::F7)
                || (NewFolder.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left))){

             RenderWindow createFolder(VideoMode(380,90), "My Commander");
             createFolder.setIcon(64, 64, icon.getPixelsPtr());
             Text namefolder;
                namefolder.setFont(font);
                namefolder.setCharacterSize(14);
                namefolder.setFillColor(Color::Black);
                namefolder.setString("Creare folder nou:");
                namefolder.setPosition({10,10});

             RectangleShape caseta(Vector2f(360,20));
                caseta.setPosition({10,35});
                caseta.setFillColor(Color::White);
                caseta.setOutlineThickness(1);
                caseta.setOutlineColor(Color(130, 135, 144));

             Textbox textbox2(14, Color::Black,true);
                textbox2.setFont(font);
                textbox2.setPosition({11,35});
                textbox2.setLimit(true,20);

            textButton OKButton("OK", { 250,64 }, 13, Color::White, Color::Black, {40, 20});
                OKButton.setPosition({ 240, 62 });
                OKButton.setFont(font);
                OKButton.setOutlineThickness(1);
                OKButton.setOutlineColor(Color(130, 135, 144));

            textButton RenuntaButton("Renunta", { 304,63 }, 14, Color::White, Color::Black, {80, 20});
                RenuntaButton.setPosition({ 290, 62 });
                RenuntaButton.setFont(font);
                RenuntaButton.setOutlineThickness(1);
                RenuntaButton.setOutlineColor(Color(130, 135, 144));


              while (createFolder.isOpen()){
                Event event1;

                while (createFolder.pollEvent(event1))
                {
                switch (event1.type) {
                case  Event::Closed:
                createFolder.close();
                case Event::TextEntered:
                textbox2.typedOn(event1);
                }
                 if ( OKButton.isMouseOver(createFolder) && Mouse::isButtonPressed(Mouse::Button::Left) || (event1.type==Event::KeyReleased && event1.key.code==Keyboard::Return))
                {
                    creareFolder(window, textbox2);
                    createFolder.close();
                }
                 else  if(OKButton.isMouseOver(createFolder)){
                     OKButton.setOutlineColor(Color(163, 206, 242));}
                else OKButton.setOutlineColor(Color(130, 135, 144));

                if(RenuntaButton.isMouseOver(createFolder) && Mouse::isButtonPressed(Mouse::Button::Left) || event1.type==Event::KeyReleased && event1.key.code==Keyboard::Escape)
                    createFolder.close();
                else  if(RenuntaButton.isMouseOver(createFolder)){
                     RenuntaButton.setOutlineColor(Color(163, 206, 242));}
                else RenuntaButton.setOutlineColor(Color(130, 135, 144));


                createFolder.clear(Color(240, 240, 240));
                createFolder.draw(namefolder);
                createFolder.draw(caseta);
                textbox2.drawTo(createFolder);
                OKButton.drawTo(createFolder);
                RenuntaButton.drawTo(createFolder);
                createFolder.display();
                }
              }

        }
        else if(NewFolder.isMouseOver(window))
                NewFolder.setBackColor(Color(204, 232, 255));
            else  NewFolder.setBackColor(Color(240, 240, 240));


        if ( ((renamebutton.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left)) || (Redenumire.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left)) ||
            (event.type==Event::KeyReleased && event.key.code==Keyboard::F6)) && (F1.selectedFolder != NULL || F2.selectedFolder != NULL))
        {
             RenderWindow RedenumireFolder(VideoMode(380,90), "My Commander");
             RedenumireFolder.setIcon(64, 64, icon.getPixelsPtr());
             Text namefolder;
                namefolder.setFont(font);
                namefolder.setCharacterSize(14);
                namefolder.setFillColor(Color::Black);
                namefolder.setString("Redenumire folder:");
                namefolder.setPosition({10,10});

             RectangleShape caseta(Vector2f(360,20));
                caseta.setPosition({10,35});
                caseta.setFillColor(Color::White);
                caseta.setOutlineThickness(1);
                caseta.setOutlineColor(Color(130, 135, 144));

             Textbox textbox2(14, Color::Black,true);
                textbox2.setFont(font);
                textbox2.setPosition({11,35});
                textbox2.setLimit(true,20);

            textButton OKButton("OK", { 250,64 }, 13, Color::White, Color::Black, {40, 20});
                OKButton.setPosition({ 240, 62 });
                OKButton.setFont(font);
                OKButton.setOutlineThickness(1);
                OKButton.setOutlineColor(Color(130, 135, 144));

            textButton RenuntaButton("Renunta", { 304,63 }, 14, Color::White, Color::Black, {80, 20});
                RenuntaButton.setPosition({ 290, 62 });
                RenuntaButton.setFont(font);
                RenuntaButton.setOutlineThickness(1);
                RenuntaButton.setOutlineColor(Color(130, 135, 144));

              while (RedenumireFolder.isOpen()){
                Event event1;

                while (RedenumireFolder.pollEvent(event1))
                {
                switch (event1.type) {
                case  Event::Closed:
                RedenumireFolder.close();
                case Event::TextEntered:
                textbox2.typedOn(event1);
                }
        if ( OKButton.isMouseOver(RedenumireFolder) && Mouse::isButtonPressed(Mouse::Button::Left) || (event1.type==Event::KeyReleased && event1.key.code==Keyboard::Return))
                {
            if(fereastraActiva == 1) {
            if(F1.selectedFolder == NULL) cout << "Nu ati selectat folderul"<<endl;else
                redenumireFolder(F1, window, textbox2.getText());
                }
        else if(fereastraActiva==2){
            if(F2.selectedFolder == NULL) cout << "Nu ati selectat folderul"<<endl;else
                redenumireFolder(F2, window,textbox2.getText());
            }

                RedenumireFolder.close();
                }
                 else  if(OKButton.isMouseOver(RedenumireFolder)){
                     OKButton.setOutlineColor(Color(163, 206, 242));}
                else OKButton.setOutlineColor(Color(130, 135, 144));

                if(RenuntaButton.isMouseOver(RedenumireFolder) && Mouse::isButtonPressed(Mouse::Button::Left) || event1.type==Event::KeyReleased && event1.key.code==Keyboard::Escape)
                    RedenumireFolder.close();
                else  if(RenuntaButton.isMouseOver(RedenumireFolder)){
                     RenuntaButton.setOutlineColor(Color(163, 206, 242));}
                else RenuntaButton.setOutlineColor(Color(130, 135, 144));

                RedenumireFolder.clear(Color(240, 240, 240));
                RedenumireFolder.draw(namefolder);
                RedenumireFolder.draw(caseta);
                textbox2.drawTo(RedenumireFolder);
                OKButton.drawTo(RedenumireFolder);
                RenuntaButton.drawTo(RedenumireFolder);
                RedenumireFolder.display();
                }
              }
        }
        else if(Redenumire.isMouseOver(window))
            Redenumire.setBackColor(Color(204, 232, 255));
        else Redenumire.setBackColor(Color(240, 240, 240));

              bool lock_click;
  if (event.type == sf::Event::MouseButtonPressed)
  {
      if (event.mouseButton.button == sf::Mouse::Left && lock_click != true)
      {
          lock_click = true;
      }
  }

  if (event.type == sf::Event::MouseButtonReleased)
  {
      if (event.mouseButton.button == sf::Mouse::Left&&lock_click==true)
      {
          lock_click = false;
          activareFereastra(window,win2,win3, "LEFT",selectX, selectY);

      }
  }
         /*if ( event.type==Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            activareFereastra(window,win2,win3);

        }*/

    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right ){
        activareFereastra(window,win2,win3, "RIGHT",selectX,selectY);
        RectangleShape select(Vector2f(430,20));
        select.setFillColor(Color(0,0,0,0));
        select.setPosition(selectX, selectY);
        select.setOutlineThickness(1);
        select.setOutlineColor(Color(1, 72, 195));
        window.draw(select);}
    if(fereastraActiva==1){
            win2.setOutlineColor(Color(1, 72, 195));
            Contor1.setOutlineColor(Color(1, 72, 195));
            win3.setOutlineColor(Color(130, 135, 144));
            Contor2.setOutlineColor(Color(130, 135, 144));
        }
    else {
            win2.setOutlineColor(Color(130, 135, 144));
            Contor1.setOutlineColor(Color(130, 135, 144));
            win3.setOutlineColor(Color(1, 72, 195));
            Contor2.setOutlineColor(Color(1, 72, 195));
    }

    if ( Stergere.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left) ||
        (event.type==Event::KeyReleased && event.key.code==Keyboard::F8) && (F1.selectedFolder != NULL || F2.selectedFolder != NULL) ){
        Stergere.setBackColor(Color(163, 206, 242));
        if(fereastraActiva == 1) {
            if(F1.selectedFolder == NULL) cout << "Nu ati selectat folderul/fiserul - ";else{
                    char adresaX[1001];
                    strcpy(adresaX, F1.selectedFolder->adresa.c_str());
                remove_dir(adresaX,F1, window);}
        }
        else if(fereastraActiva==2){
            if(F2.selectedFolder == NULL) cout << "Nu ati selectat folderul ";else{
                char adresaX[1001];
                    strcpy(adresaX, F2.selectedFolder->adresa.c_str());
                remove_dir(adresaX,F2, window);}
        }
    }
    else if(Stergere.isMouseOver(window))
            Stergere.setBackColor(Color(204, 232, 255));
        else if(event.type!=Event::KeyReleased && event.key.code!=Keyboard::F8) Stergere.setBackColor(Color(240, 240, 240));

    if ( Copiere.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left) || (event.type==Event::KeyReleased && event.key.code==Keyboard::F5)){
        Copiere.setBackColor(Color(163, 206, 242));
        if(fereastraActiva == 1) {
            if(F1.selectedFolder == NULL) cout << "Nu ati selectat folderul";else{
                copiereFolder(F1);}
        }
        else if(fereastraActiva==2){
            if(F2.selectedFolder == NULL) cout << "Nu ati selectat folderul";else{
                copiereFolder(F2);}
        }
        }
    else if(Copiere.isMouseOver(window))
            Copiere.setBackColor(Color(204, 232, 255));
        else Copiere.setBackColor(Color(240, 240, 240));

    if ( Lipire.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left) || (event.type==Event::KeyReleased && event.key.code==Keyboard::F4)){
        Lipire.setBackColor(Color(163, 206, 242));
        if(fereastraActiva == 1) {
            if(folderCopiat == NULL) cout << "Nu ati copiat folderul";else{
                lipireFolder(F1, window);}
        }
        else if(fereastraActiva==2){
            if(folderCopiat == NULL) cout << "Nu ati copiat folderul";else{
                lipireFolder(F2, window);}
        }
        }
    else if(Lipire.isMouseOver(window))
            Lipire.setBackColor(Color(204, 232, 255));
        else Lipire.setBackColor(Color(240, 240, 240));

    if ( Vizualizare.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left) || (event.type==Event::KeyReleased && event.key.code==Keyboard::F3)){
        Vizualizare.setBackColor(Color(163, 206, 242));
        if(F.selectedFolder!=NULL)
            if(F.selectedFolder->extension!="folder")
            {
                         char path[1001],aux[1001];
                            path[0]='"';
                            path[1]=NULL;
                            aux[0]=NULL;
                            strcat(path,F.selectedFolder->adresa.c_str());
                            //cout << "xxxxxx   " << F.activFolder->foldere[i]->adresa << endl;
                            for(int i=0;i<strlen(path);i++)
                            if(path[i]=='/') { strcpy(aux,path+i+1);
                            path[i]=NULL;
                            strcat(path,"\\");
                            strcat(path,aux);
                            }
                            int i=strlen(path);
                            path[i-1]='"';
                            path[i]=NULL;

                            cout << path << endl;

                    system(path);
                }
        }
         else if(Vizualizare.isMouseOver(window))
            Vizualizare.setBackColor(Color(204, 232, 255));
        else Vizualizare.setBackColor(Color(240, 240, 240));

        if ( ExtensieFisier2.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left)){
        fereastraActiva=2;
        sortByExtension(F2,window);
        }
        if ( ExtensieFisier1.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left)){
        fereastraActiva=1;
        sortByExtension(F1,window);
        }
        if ( NumeFisier2.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left)){
        fereastraActiva=2;
        sortByName(F2,window);
        }
        if ( NumeFisier1.isMouseOver(window) && Mouse::isButtonPressed(Mouse::Button::Left)){
        fereastraActiva=1;
        sortByName(F1,window);
        }
        Contor1.drawTo(window);
        Contor2.drawTo(window);
        DiscC1.drawTo(window);
        DiscD1.drawTo(window);
        DiscC2.drawTo(window);
        DiscD2.drawTo(window);
        NumeFisier1.drawTo(window);
        ExtensieFisier1.drawTo(window);
        NumeFisier2.drawTo(window);
        ExtensieFisier2.drawTo(window);
        Vizualizare.drawTo(window);
        Lipire.drawTo(window);
        Copiere.drawTo(window);
        Redenumire.drawTo(window);
        NewFolder.drawTo(window);
        Stergere.drawTo(window);
        Iesire.drawTo(window);
        window.display();
    }
    return 0;
}
