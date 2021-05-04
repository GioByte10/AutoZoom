# AutoZoom
***Español*** [***abajo***](#español)

If you would like to share any feedback or report a problem, please fill this [english form](https://forms.gle/L7LCvQ3MgRciuaqk8)

Si quisieras compartir retroalimentación o reportar algún problema, por favor llena esta [forma](https://forms.gle/n6eLG34afu7hrVXZ6) en español

## English
AutoZoom is a C++ written program that automatically joins your Zoom meetings by running the Zoom Links. This is the link for the [English Version](https://github.com/GioByte10/AutoZoom/releases/tag/English)

In order to do this, the main program, [**_AutoZoom.exe_**](https://github.com/GioByte10/AutoZoom/blob/main/AutoZoom.cpp) adds itself to the Current User's StartUp and acceses the [**_data.txt_**](https://github.com/GioByte10/AutoZoom/blob/main/data.txt) file which contains all information necessary for it to run, this includes:

| Parameter     | Description   |
| ------------- |:--------------|
| Zoom Link     | Must contain **https://** and **zoom** in it                                            |
| Time          | In the 24 hour format; Must contain 4 digits; 2 → hour & 2 → minute.<br>e.g.  →  07:25  |
| Days          | Days in which the meeting will be joined; Separated by coma<br>e.g.  →  monday, tuesday |

AutoZoom then continuously checks if the current time and day are equal to that of any Zoom Link, and if so, it executes the respective Link.

The user can also be notified **X** minutes before the meeting with a dialog box if requested in the **data.txt** file.

Of the files included:
* **AutoZoom.exe** is the main code
* **Deactive.exe** kills the AutoZoom process and removes it from StartUp
* There is a text file included with installation instructions
* **data.txt** contains the user's meetings' information
* **MessageBox.vbs** is used to notify the user previous to the Zoom meeting (if chosen by the user), while allowing the process to keep running
* All three **.dll** libraries are required for the program to function.

Zoom Links are executed using the following command:
```c++
ShellExecute(nullptr, "open", linksS.c_str(), nullptr, nullptr, 0);
```
[ShellExecute Documentation](https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shellexecutea)

where:<br>
&nbsp;&nbsp;&nbsp;&nbsp;linksS is a variable of **string** type holding a single link.<br>
&nbsp;&nbsp;&nbsp;&nbsp;_c_str()_ is added, as a **LPCSTR** variable is needed.<br>

Note that links will be open in the user's default browser

The program also features 10 different error [MessageBox()](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox), which without closing, the process cannot continue.

Each MessageBox() contains a code and description of the error.



***DO NOT MODIFY ANY OF THE LINES MARKED WITH AN*** "*" ***IN THE DATA.TXT***<br>
***DO NOT DELETE ANY OF THE FILES INCLUDED IN THE AUTOZOOM FOLDER***

<br>

---

<br>

## Español
AutoZoom es un programa escrito en C++ que automáticamente entra a tus reuniones de Zoom ejecutando los Links de Zoom. Este es el link para la [Versión en Español](https://github.com/GioByte10/AutoZoom/releases/tag/Spanish)

Para hacer esto, el programa principal [**_AutoZoom.exe_**](https://github.com/GioByte10/AutoZoom/blob/main/AutoZoom.cpp) se añade a si mismo al StartUp del Usuario Actual y accesa al archivo [**_data.txt_**](https://github.com/GioByte10/AutoZoom/blob/main/data.txt), el cual contiene toda la información necesaria para correr el programa, esto incluye:

| Parámetro     | Descripción   |
| ------------- |:--------------|
| Zoom Link     | Debe contener **https://** y **zoom** en el                                                |
| Hora          | En el formato de 24 horas; Debe contener 4 dígitos; 2 → hora & 2 → minuto.<br>ej.  →  07:25|
| Día	          | Días en los cuales se unirá a la reunión; Separados por coma<br>ej.  →  lunes, martes      |

AutoZoom entonces checa continuamente si la hora y día actual son iguales a los de cualquier Link de Zoom, y en dado caso, ejecuta el respectivo link.

El usuario también puede ser notificado **X** minutos antes de la reunion con una ventana de diálogo si es solicitado en el archivo **data.txt**.

De los archivos incluidos:
* **AutoZoom.exe** es el programa principal.
* **Deactive.exe** destruye el proceso de AutoZoom y lo remueve del StartUp
* Hay un archivo que incluye las instrucciones de instalación
* **data.txt** contiene la información de las reuniones del usuario
* **MessageBox.vbs** es usado para notificar al usuario previo a la reunión (si así lo solicita el usuario), y permite que el proceso siga corriendo
* Todas las tres librarías **.dll** son requeridas para el funcionamiento del programa

Los Links de Zoom son ejecutados utilizando el siguiente comando:
```c++
ShellExecute(nullptr, "open", linksS.c_str(), nullptr, nullptr, 0);
```
[ShellExecute Documentation](https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shellexecutea)

donde:<br>
&nbsp;&nbsp;&nbsp;&nbsp;linksS es una variable del tipo **string** conteniendo un solo Link.<br>
&nbsp;&nbsp;&nbsp;&nbsp;_c_str()_ es incluido, ya que una variable de tipo **LPCSTR** es requerida.<br>

Nótese que los Links serán ejecutados en el navegador por defecto del usuario.

El programa también incluye 10 diferentes [MessageBox()](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox) de error, los cuales, si no son cerrados, el proceso no puede continuar.

Cada MessageBox() contiene un código y descripción del error.



***NO MODIFIQUE NINGUNA LINEA MARCADA CON UN*** "*" ***EN EL ARCHIVO DATA.TXT***<br>
***NO BORRE NINGUN ARCHIVO INCLUIDO EN EL FOLDER DE AUTOZOOM***
