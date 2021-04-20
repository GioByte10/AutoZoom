#include <windows.h>
#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <list>
#include <ctime>
using namespace std;

LPCSTR fileFound, aError, zoomLinks, headers, notification1, notification2, notificationT;
bool spanish = false;
bool error = false;

list <string> zoomLinks_list;
list <int> hour_list;
list <int> minute_list;
list <string> days_list;
int minutesBefore = 5;


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


bool GetLastWritten(int *lastWritten){

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

  //printf("Last Written on %02d/%02d/%d  %02d:%02d\n", stLocal.wMonth, stLocal.wDay, stLocal.wYear, stLocal.wHour, stLocal.wMinute);

  bool changed = false;

  if(lastWritten[5] != stLocal.wSecond)
    changed = true;

  else if(lastWritten[4] != stLocal.wMinute)
    changed = true;

  else if(lastWritten[3] != stLocal.wHour)
    changed = true;

  else if(lastWritten[2] != stLocal.wDay)
    changed = true;

  else if(lastWritten[1] != stLocal.wMonth)
    changed = true;

  else if(lastWritten[0] != stLocal.wYear)
    changed = true;

  lastWritten[0] = stLocal.wYear;
  lastWritten[1] = stLocal.wMonth;
  lastWritten[2] = stLocal.wDay;
  lastWritten[3] = stLocal.wHour;
  lastWritten[4] = stLocal.wMinute;
  lastWritten[5] = stLocal.wSecond;

  CloseHandle(file);

  return changed;

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


string GetDays(string daysL, string word){

  for(int i = 0; i < word.length(); i++)
    word[i] = tolower(word[i]);

  if(word.find("lunes") != string::npos || word.find("monday") != string::npos)
    daysL += "monday ";

  else if(word.find("martes") != string::npos || word.find("tuesday") != string::npos)
    daysL += "tuesday ";

  else if(word.find("miercoles") != string::npos || word.find("wednesday") != string::npos)
    daysL += "wednesday ";

  else if(word.find("jueves") != string::npos || word.find("thursday") != string::npos)
    daysL += "thursday ";

  else if(word.find("viernes") != string::npos || word.find("friday") != string::npos)
    daysL += "friday ";

  else if(word.find("sabado") != string::npos || word.find("saturday") != string::npos)
    daysL += "saturday ";

  else if(word.find("domingo") != string::npos || word.find("sunday") != string::npos)
    daysL += "sunday ";

  return daysL;

}


void ResetTxt(int* lastWritten){

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

     }else{
      error = true;

      while(!GetLastWritten(lastWritten)){
        //cout <<"waiting" << endl;
        Sleep(3000);
      }
   }
}


bool GetInfo(int* lastWritten){

  bool message = false;

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

    for(int i = 0; i < nLines; i++)
        if(lines[i].find("notificado") != string::npos || lines[i].find("notified") != string::npos){

                for(int j = 0; j < lines[i].length(); j++)
                    lines[i][j] = tolower(lines[i][j]);

            if(lines[i].substr(lines[i].length() - 3, 3).find("si") != string::npos || lines[i].substr(lines[i].length() - 3, 3).find("yes") != string::npos){
              message = true;
              break;
            }
        }

    line = "";

    for(int i = 0; i < nLines; i++)
        if(lines[i].find("caso de que si") != string::npos || lines[i].find("case yes") != string::npos){
              for(int j = 1; j <= lines[i].length(); j++){
                if(lines[i][lines[i].length() - j] == ' ')
                    break;
                line += lines[i][lines[i].length() - j];
              }
            }

    reverse(line.begin(), line.end());
    minutesBefore = stoi(line);

    int firstL = -1;

    for(int i = 0; i < nLines; i++)
        if(lines[i].find("hora") != string::npos || lines[i].find("time") != string::npos){
            firstL = i + 1;
            break;
        }

    if(firstL != -1 && CheckTxt()){

      int nLinks = 0;

      for(int i = 0; i < nLines - firstL; i++)
        if(lines[firstL + i].find("zoom") != string::npos)
            nLinks ++;

    if(nLinks > 0){

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
      string daysL = "";

      for(int i = 0; i < nLinks; i++){

        if(allThree[i]){
          istringstream ss(linesWlinks[i]);

          while(ss >> word){

            if(j == 0){

              zoomLinks_list.push_back(word);

            }else if(j == 1){
              GetHours(times, word);
              hour_list.push_back(times[0]);
              minute_list.push_back(times[1]);

            }else{
              daysL = GetDays(daysL, word);
            }
            j++;
          }

            days_list.push_back(daysL.substr(0, daysL.length() - 1));
            daysL = "";

            j = 0;

        }
      }

      }else{
        MessageBox(NULL, zoomLinks, "AutoZoom Error", MB_ICONEXCLAMATION);
        error = true;

        while(!GetLastWritten(lastWritten)){
          //cout <<"waiting" << endl;
          Sleep(3000);
        }

      }

    }else{

      ResetTxt(lastWritten);

    }
  }
  return message;
}


void ShowLists(){

  for(auto l: zoomLinks_list)
    cout << l.c_str() << endl;

  cout << endl << "horas: " << endl;

  for(auto t: hour_list)
        cout << t <<  endl;

  cout << endl << "minutos: " << endl;

    for(auto t: minute_list)
        cout << t << endl;

  cout << endl << "dias: " << endl;

  for(auto d: days_list)
        cout << d << endl;
}


void SetLanguage(){

  ifstream getData;
  getData.open("data.txt");

  spanish = false;

  if(getData.fail()){
    MessageBox(NULL, "kkkkk", "AutoZoom Error", MB_ICONHAND);
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

  if(spanish){

    fileFound = "El archivo data.txt no ha sido encontrado. Intente correr AutoZoom.exe de nuevo";
    aError = "Ha ocurrido un error. Intente correr AutoZoom.exe de nuevo";
    zoomLinks = "Asegurese de que haya puesto los links de zoom";
    headers = "Al parecer los encabezados de las columnas han sido modificados. Desea eliminar y crear un nuevo archivo de texto?\nEsto borrara toda la informacion que haya puesto en el archivo!\n\nEn caso de que no, debera de arreglar el problema manualmente";
    notification1 = "La junta de Zoom comenzara en ";
    notification2 = " minutos";
    notificationT = "Notificacion";

  }else{

    fileFound = "The file data.txt has not been found. Try running AutoZoom.exe again";
    aError = "There has been an error. Try running AutoZoom.exe again";
    zoomLinks = "Make sure you have added the zoom links";
    headers = "It seems like the columns' headers have been modified. Do you wish to eliminate and create a new text file?\nThis will delete all the information that you had inputted in the file!\n\nIn case no, you will have to manually fix the problem";
    notification1 = "The Zoom metting will start in ";
    notification2 = " minutes";
    notificationT = "Notification";

  }
}


int GetTime(const string &t, time_t now, tm *ltm){

    now = time(nullptr);
    localtime(&now);

    if(t == "min")
        return ltm -> tm_min;

    else if(t == "hour")
        return ltm -> tm_hour;

    else if(t == "day")
        return ltm -> tm_mday;

    else if(t == "wday")
        return ltm -> tm_wday;

    else if(t == "month")
        return ltm -> tm_mon;

    else if(t == "year")
        return ltm -> tm_year;

    return -1;

}


string WDayToSDay(int day){

  string d = "";

  if(day == 1)
    d = "monday";

  else if(day == 2)
    d = "tuesday";

  else if(day == 3)
    d = "wednesday";

  else if(day == 4)
    d = "thursday";

  else if(day == 5)
    d = "friday";

  else if(day == 6)
    d = "saturday";

  else if(day == 0)
    d = "sunday";

    return d;

}


bool IsToday(int i, time_t now, tm *ltm){

    auto days_i = days_list.begin();
    advance(days_i, i);

    string daysS = *days_i;

        if(daysS.find(WDayToSDay(GetTime("wday", now, ltm))) != string::npos)
            return true;

    return false;
}


bool CheckIfMessage(int i, int hour, int minute, time_t now, tm *ltm){

  int epochF = 0;
  int epochN = 0;
  string m = "";

  if(IsToday(i, now, ltm)){
    epochF = hour * 60 + minute;
    epochN = GetTime("hour", now, ltm) * 60 + GetTime("min", now, ltm);

    m += notification1 + to_string(epochF - epochN) + notification2;

    if(epochF - epochN <= minutesBefore && epochF - epochN > 0){
      MessageBox(NULL, m.c_str(), notificationT, MB_ICONASTERISK);
      return true;
    }
  }
    return false;
}


void ResetLists(){

  zoomLinks_list.clear();
  hour_list.clear();
  minute_list.clear();
  days_list.clear();

}


int main(){

  ShowWindow(GetConsoleWindow(), SW_HIDE);

  while(true){

      ResetLists();
      SetLanguage();

      string txtPath = GetTxtPath();
      TCHAR* filePath = GetFilePath();

      bool message = false;
      bool once = false;

      int lastWritten[6];
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

      if(!CheckTxt())
        ResetTxt(lastWritten);

      message = GetInfo(lastWritten);

      time_t now = time(nullptr);
      tm *ltm = localtime(&now);

      string linksS, daysS;
      int hour, minute;

      while(true){

        if(error){
          error = false;
          break;
        }

        if(GetLastWritten(lastWritten))
          break;

        auto zoomLinks_i = zoomLinks_list.begin();
        auto hour_i = hour_list.begin();
        auto minute_i = minute_list.begin();

        for(int i = 0; i < zoomLinks_list.size(); i++){

            linksS = *zoomLinks_i;
            hour = *hour_i;
            minute = *minute_i;

            //cout << linksS << "  " << hour << "   " << minute << endl;

            if(message && !once)
                once = CheckIfMessage(i, hour, minute, now, ltm);

            if(hour == GetTime("hour", now, ltm) && minute == GetTime("min", now, ltm) && IsToday(i, now, ltm)){
                ShellExecute(nullptr, "open", linksS.c_str(), nullptr, nullptr, 0);
                once = false;
                Sleep(60000);
            }

            advance(zoomLinks_i, 1);
            advance(hour_i, 1);
            advance(minute_i, 1);

        }
        Sleep(1000);
      }
  }
  return 0;
}
