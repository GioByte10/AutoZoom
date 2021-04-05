#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <list>
using namespace std;

LPCSTR fileFound, aError, zoomLinks, headers;
bool spanish;

list <string> zoomLinks_list;
list <int> time_list;
list <bool*> days_list;


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

  if(inputData.fail()){
    MessageBox(NULL, fileFound, "AutoZoom Error", MB_ICONHAND);
    exit(1);
  }

  getline(inputData, txtPath);

  inputData.close();

  return txtPath;

}


void UpdateTxt(){

  ifstream getData;
  getData.open("data.txt");

  if(getData.fail()){
    MessageBox(NULL, fileFound, "AutoZoom Error", MB_ICONHAND);
    exit(1);
  }

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

void GetLastWritten(int *lastWritten){

  HANDLE file;
  FILETIME tWritten;
  SYSTEMTIME stUTC, stLocal;

  TCHAR* filePath = GetFilePath();
  string txtPath = "";

  for(int i = 0; i < lstrlen(filePath) - 12; i++){
    txtPath += filePath[i];

    if(filePath[i] == '\\')
        txtPath += '\\';

  }

  txtPath += "data.txt";

  file = CreateFile(txtPath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  if(file == INVALID_HANDLE_VALUE){
    MessageBox(NULL, aError, "AutoZoom Error", MB_ICONHAND);
    exit(1);
  }

  if(!GetFileTime(file, NULL, NULL, &tWritten)){
    MessageBox(NULL, aError, "AutoZoom Error", MB_ICONHAND);
    exit(1);
  }

  FileTimeToSystemTime(&tWritten, &stUTC);
  SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

  printf("Last Written on %02d/%02d/%d  %02d:%02d\n", stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute);

  lastWritten[0] = stLocal.wYear;
  lastWritten[1] = stLocal.wMonth;
  lastWritten[2] = stLocal.wDay;
  lastWritten[3] = stLocal.wHour;
  lastWritten[4] = stLocal.wMinute;

  CloseHandle(file);

}

bool CheckTxt(){

  ifstream getData;
  getData.open("data.txt");

  if(getData.fail()){
    MessageBox(NULL, fileFound, "AutoZoom Error", MB_ICONHAND);
    exit(1);
  }

  string line;

  while(getData){
    getline(getData, line);

    if((line.find("zoom") != string::npos || line.find("link") != string::npos) && (line.find("hora") != string::npos || line.find("time") != string::npos) && (line.find("dia") != string::npos || line.find("day") != string::npos)){
        getData.close();
        return true;
    }
  }

  getData.close();
  return false;

}

void GetHours(int *times, string word){

  string h = "";
  string m = "";

  int i = 0;

  for(i = 0; i < word.length(); i++)
    if(word[i] != ':')
      h += word[i];

    else
        break;

  m = word.substr(i + 1, word.length() - i - 1);

  int hour = stoi(h);
  int minute = stoi(m);

  times[0] = hour;
  times[1] = minute;

}


void GetDays(bool *daysL, string word){

  for(int i = 0; i < word.length(); i++)
    word[i] = tolower(word[i]);

  if(word == "lunes" || word == "monday")
    daysL[0] = true;

  else if(word == "martes" || word == "tuesday")
    daysL[0] = true;

  else if(word == "miercoles" || word == "wednesday")
    daysL[0] = true;

  else if(word == "jueves" || word == "thursday")
    daysL[0] = true;

  else if(word == "viernes" || word == "friday")
    daysL[0] = true;

  else if(word == "sabado" || word == "saturday")
    daysL[0] = true;

  else if(word == "domingo" || word == "sunday")
    daysL[0] = true;

}


void GetInfo(){

  ifstream getData;
  getData.open("data.txt");

  if(getData.fail()){
    MessageBox(NULL, fileFound, "AutoZoom Error", MB_ICONHAND);
    exit(1);
  }

  int nLines, firstL = -1;
  string line;

  for(nLines = 0; getline(getData, line); nLines++);

  if(nLines > 0){

    string lines[nLines];

    getData.clear();
    getData.seekg(0);

    for(int j = 0; j < nLines ; j++)
      getline(getData, lines[j]);

    getData.close();

    for(int i = 0; i < nLines; i++)
        if(lines[i].find("hora") != string::npos || lines[i].find("time") != string::npos){
            firstL = i + 1;
            break;
        }

    if(firstL != -1){

      int nLinks = 0;

      for(int i = 0; i < nLines - firstL; i++)
        if(lines[firstL + i].find("zoom") != string::npos)
            nLinks ++;

      string linesWlinks[nLinks];
      nLinks = 0;

      for(int i = 0; i < nLines - firstL; i++)
        if(lines[firstL + i].find("zoom") != string::npos){
            linesWlinks[nLinks] = lines[firstL + i];
            nLinks ++;
        }

      string word;

      bool allThree[nLinks];
      int j = 0;

      for(int i = 0; i < nLinks; i++){
        istringstream ss(linesWlinks[i]);

        while(ss >> word)
            j++;

        if(j >= 3)
            allThree[i] = true;
        else
            allThree[i] = false;

        j = 0;
      }

      j = 0;

      int times[2];
      bool daysL[7] = {false, false, false, false, false, false, false};
      string temp;

      for(int i = 0; i < nLinks; i++){

        if(allThree[i]){
          istringstream ss(linesWlinks[i]);

          while(ss >> word){

            if(j == 0){

              zoomLinks_list.push_back(word);
              cout << *zoomLinks_list.begin() << "  ";

            }else if(j == 1){
              GetHours(times, word);
              cout << times[0] << " " << times[1] << "  ";
              time_list.push_back(times[0]);

              for(auto t: time_list){
                    cout << t << " ";
              }

            }else{
              GetDays(daysL, word);
            }

            j++;

          }

            days_list.push_back(daysL);

            for(int i = 0; i < 7; i++)
              daysL[i] = false;

            j = 0;

            cout << endl;

        }

      }

    }

    else
      MessageBox(NULL, zoomLinks, "AutoZoom Error", MB_ICONEXCLAMATION);
  }

}


void ShowLists(){

  cout << "\n\n";

  for(auto l: zoomLinks_list)
    cout << l.c_str() << endl;

  for(auto t: time_list){
        cout << t << " ";

    cout << endl;
  }


  for(auto d: days_list){
    for(int i = 0; i < 7; i++)
        cout << d[i] << " ";

    cout << endl;
  }


}


void ResetTxt(){

  int msbID = MessageBox(NULL, headers, "AutoZoom Error", MB_ICONEXCLAMATION | MB_YESNO);

    if(msbID == IDYES){
        ofstream newFile;
        newFile.open("data.txt", ios::out | ios::trunc);
        newFile.close();

        newFile.open("data.txt");

        if(spanish){

          newFile << GetFilePath() << endl;
          newFile << "*spanish" << endl;
          newFile << "*" << endl;
          newFile << "*Reportar cualquier problema/bug/sugerencia/etc a gvanni.bernal10@gmail.com" << endl;
          newFile << "*" << endl;
          newFile << "*No modificar ninguna linea que contenga asterisco (*), ni la primera linea" << endl;
          newFile << "*Favor de maximizar la ventana para ver todas las columnas" << endl;
          newFile << "*Asegurarse de que el link de zoom contega https://" << endl;
          newFile << "*" << endl;
          newFile << "*" << endl;
          newFile << "Quisieras ser notificado antes de entrar a la sesion?: no" << endl;
          newFile << "En caso de que si, cuantos minutos antes?: 5" << endl;
          newFile << "*" << endl;
          newFile << "*zoom link			 									hora (formato 24 horas)			dia (e.g lunes, martes...)";

        }else{

          newFile << GetFilePath() << endl;
          newFile << "*english" << endl;
          newFile << "*" << endl;
          newFile << "*Please report any problem/bug/suggestion/etc to gvanni.bernal10@gmail.com" << endl;
          newFile << "*" << endl;
          newFile << "*Do not modify any line that has asterisk (*), nor the first line" << endl;
          newFile << "*Please maximize the window to see all columns" << endl;
          newFile << "*Make sure the link contains https://" << endl;
          newFile << "*" << endl;
          newFile << "*" << endl;
          newFile << "Would you like to be notified before joining the meeting?: no" << endl;
          newFile << "In case yes, how many minutes before?: 5" << endl;
          newFile << "*" << endl;
          newFile << "*zoom link			 									time (24 hour format)			day (e.g monday, tuesday...)";

        }

        newFile.close();
    }
    system("data.txt");

}

void SetLanguage(){

  ifstream getData;
  getData.open("data.txt");

  spanish = false;

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

    }else if(line.find("spanish") != string::npos){
      getData.close();
      spanish = false;
      break;

    }

  }

  if(spanish){

    fileFound = "El archivo data.txt no ha sido encontrado. Intente correr AutoZoom.exe de nuevo";
    aError = "Ha ocurrido un error. Intente correr AutoZoom.exe de nuevo";
    zoomLinks = "Asegurese de que haya puesto los links de zoom";
    headers = "Al parecer los encabezados de las columnas han sido modificados. Desea eliminar y crear un nuevo archivo de texto?\nEsto borrara toda la informacion que haya puesto en el archivo!\n\nEn caso de que no, debera de arreglar el problema manualmente";

  }else{

    fileFound = "The file data.txt has not been found. Try running AutoZoom.exe again";
    aError = "There has been an error. Try running AutoZoom.exe again";
    zoomLinks = "Make sure you have added the zoom links";
    headers = "It seems like the columns' headers have been modified. Do you wish to eliminate and create a new text file?\nThis will delete all the information that you had inputted in the file!\n\nIn case no, you will have to manually fix the problem";

  }
}


int main(){

  SetLanguage();

  string txtPath = GetTxtPath();
  TCHAR* filePath = GetFilePath();

  int lastWritten[5];
  GetLastWritten(lastWritten);

  if(filePath != txtPath){

    AddToStartUp();
    UpdateTxt();

    txtPath = GetTxtPath();

    if(filePath != txtPath){
        MessageBox(NULL, aError, "AutoZoom Error", MB_ICONHAND);
        exit(1);
    }
  }

  if(!CheckTxt()){

    ResetTxt();

  }

  GetInfo();

  ShowLists();
  ShowLists();
  ShowLists();

  return 0;
}
