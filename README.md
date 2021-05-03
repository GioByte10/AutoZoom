# AutoZoom

## English
AutoZoom is a C++ written program that automatically joins your Zoom meetings by running the Zoom Links. This is the link for the [English Version](https://github.com/GioByte10/AutoZoom/releases/tag/English)

In order to do this, the main program, **_AutoZoom.exe_** acceses the **_data.txt_** file which contains all information necessary for it to run, this includes:

| Parameter     | Description   |
| ------------- |:--------------|
| Zoom Link     | Must contain **https://** and **zoom** in it                                            |
| Time          | In the 24 hour format; Must contain 4 digits; 2 → hour & 2 → minute.<br>e.g.  →  07:25  |
| Days          | Days in which the meeting will be joined; Separated by coma.<br>e.g.  →  monday, tuesday|

Of the files included:
* **AutoZoom.exe** is the main code
* **Deactive.exe** kills the AutoZoom process and removes it from StartUp
* There is a text file included with installation instructions
* data.txt contains the user's meetings' information
* **MessageBox.vbs** is used to notify the user previous to the Zoom meeting, while allowing the process to keep running
* All three **.dll** libraries are required for the program's function.

Zoom Links are executing using the following command:
```c++
ShellExecute(nullptr, "open", linksS.c_str(), nullptr, nullptr, 0);
```
where:<br>
&nbsp;&nbsp;&nbsp;&nbsp;linksS is a variable of **string** type holding a single link.<br>
&nbsp;&nbsp;&nbsp;&nbsp;_c_str()_ is added, as a **LPCSTR** variable is needed.<br>


* thus, links will be open in the user's default browser
