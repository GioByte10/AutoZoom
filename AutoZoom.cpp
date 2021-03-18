#include <windows.h>
#include <iostream>
#include <fstream>
using namespace std;

TCHAR* GetFilePath(){

  static TCHAR filePath[MAX_PATH];
  GetModuleFileName(NULL, filePath, MAX_PATH);

  return filePath;

}


void AddToStartUp(){

  TCHAR filePath[MAX_PATH];
  GetModuleFileName(NULL, filePath, MAX_PATH);

  HKEY newKey;

  RegOpenKey(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &newKey);
  RegSetValueEx(newKey, "AutoZoom", 0, REG_SZ, (LPBYTE)filePath, sizeof(filePath));
  RegCloseKey(newKey);

}

string GetTxtPath(){

  ifstream inputData;
  string txtPath;

  inputData.open("data.txt");

  if(inputData.fail())
    exit(1);

  getline(inputData, txtPath);

  inputData.close();

  return txtPath;

}


void UpdateTxt(){

  ifstream getData;
  getData.open("data.txt");

  string line;

  int i;

  for(i = 0; getline(getData, line); i++);

  if(i > 0){

      string lines[i];

      getData.clear();
      getData.seekg(0);

      for(int j = 0; j < i ; j++)
        getline(getData, lines[j]);

      getData.close();

      ofstream writeData;
      writeData.open("data.txt");

      lines[0] = GetFilePath();

      for(int j = 0; j < i - 1; j++)
        writeData << lines[j] << endl;

      writeData << lines[i - 1];

      writeData.close();

  }else{

    ofstream writeData;
    writeData.open("data.txt");

    writeData << GetFilePath();

    writeData.close();

  }
}


int main(){

  string txtPath = GetTxtPath();
  TCHAR* filePath = GetFilePath();

  if(filePath == txtPath)
    cout << "Like1";

  else if(txtPath.length() == 0){

    AddToStartUp();
    UpdateTxt();
    cout << "Like2";

  }else{

    AddToStartUp();
    UpdateTxt();

  }

  return 0;

}
