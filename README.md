# AutoZoom

## English
AutoZoom is a C++ written program that automatically joins your Zoom meetings by running the Zoom Links. This is the link for the [English Version](https://github.com/GioByte10/AutoZoom/releases/tag/English)

In order to do this, the main program, **_AutoZoom.exe_** acceses the **_data.txt_** file which contains all information necessary for it to run, this includes:

Zoom Links are executing using the following command:
```c++
ShellExecute(nullptr, "open", linksS.c_str(), nullptr, nullptr, 0);
```
where:

  linksS is a variable of **string** type holding a single link.
  
  _c_str()_ is added, as a **LPCSTR** variable is needed.


thus, links will be open in the user's default browser
