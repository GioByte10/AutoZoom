#include <windows.h>
#include <bits/stdc++.h>
#include <sstream>
//#include <stdlib.h>
using namespace std;

bool spanish = false;
LPCSTR fileFound;

void SetLanguage(){

  ifstream getData;
  getData.open("data.txt");

  if(getData.fail()){
    MessageBox(NULL, fileFound, "AutoZoom Error", MB_ICONHAND);
    exit(1);
  }

  string line;

  while(getData){
    getline(getData, line);

    if(line.find("spanish") != string::npos){
      getData.close();
      spanish = true;
      break;

    }else if(line.find("english") != string::npos){
      getData.close();
      spanish = false;
      break;

    }
  }

  if(spanish)
    fileFound = "El archivo data.txt no ha sido encontrado. Intente correr AutoZoom.exe de nuevo";

  else
    fileFound = "The file data.txt has not been found. Try running AutoZoom.exe again";
}


int main(){

  ShowWindow(GetConsoleWindow(), SW_HIDE);

  HKEY hkey;
  RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
  RegDeleteValue(hkey, "AutoZoom");
  RegCloseKey(hkey);

  system("taskkill /f /im AutoZoom.exe");

  SetLanguage();

  ifstream getData;
  getData.open("data.txt");

  if(getData.fail()){
    MessageBox(NULL, fileFound, "AutoZoom Error", MB_ICONHAND);
    exit(1);
  }

  int nLines;
  string line;

  for(nLines = 0; getline(getData, line); nLines++);

  if(nLines > 0){

    string lines[nLines];

    getData.clear();
    getData.seekg(0);

    for(int j = 0; j < nLines ; j++)
      getline(getData, lines[j]);

    getData.close();

    ofstream rewrite;
    rewrite.open("data.txt", ios::out | ios::trunc);
    rewrite.close();

    rewrite.open("data.txt");

    rewrite << "*" << endl;

    for(int i = 1; i < nLines; i++){
      rewrite << lines[i];

    if(i + 1 != nLines)
        rewrite << endl;
    }
    rewrite.close();

    LPCSTR m;
    LPCSTR t;

    if(spanish){

      m = "AutoZoom.exe se ha desactivado correctamente\nRecuerda volver a correr AutoZoom.exe para reactivarlo despues";
      t = "Desactivacion";

    }else{

      m = "AutoZoom.exe has been deactivated correctly\n Make sure to run AutoZoom.exe again to reactivate it later";
      t = "Deactivation";

    }

    MessageBox(NULL, m, t, MB_ICONASTERISK);

  }
  return 0;
}
