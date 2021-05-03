# AutoZoom
Español abajo

## English
AutoZoom is a C++ written program that automatically joins your Zoom meetings by running the Zoom Links. This is the link for the [English Version](https://github.com/GioByte10/AutoZoom/releases/tag/English)

In order to do this, the main program, **_AutoZoom.exe_** adds itself to the Current User's StartUp and acceses the **_data.txt_** file which contains all information necessary for it to run, this includes:

| Parameter     | Description   |
| ------------- |:--------------|
| Zoom Link     | Must contain **https://** and **zoom** in it                                            |
| Time          | In the 24 hour format; Must contain 4 digits; 2 → hour & 2 → minute.<br>e.g.  →  07:25  |
| Days          | Days in which the meeting will be joined; Separated by coma.<br>e.g.  →  monday, tuesday|

The user can also be notified **X** minutes before with a dialog box if requested by the user in the **data.txt** file.

Of the files included:
* **AutoZoom.exe** is the main code
* **Deactive.exe** kills the AutoZoom process and removes it from StartUp
* There is a text file included with installation instructions
* **data.txt** contains the user's meetings' information
* **MessageBox.vbs** is used to notify the user previous to the Zoom meeting (if chosen by the user), while allowing the process to keep running
* All three **.dll** libraries are required for the program's function.

Zoom Links are executed using the following command:
```c++
ShellExecute(nullptr, "open", linksS.c_str(), nullptr, nullptr, 0);
```
where:<br>
&nbsp;&nbsp;&nbsp;&nbsp;linksS is a variable of **string** type holding a single link.<br>
&nbsp;&nbsp;&nbsp;&nbsp;_c_str()_ is added, as a **LPCSTR** variable is needed.<br>

Note that links will be open in the user's default browser

The program also features 10 different error [MessageBox()](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox), which without closing, the process cannot continue.<br>
Each MessageBox() contains a code and description of the error.



## Español
AutoZoom es un programa escrito en C++ que automaticamente entra a tus reuniones de Zoom al ejecutar los Links de Zoom. Este es el link para la [Version en Español](https://github.com/GioByte10/AutoZoom/releases/tag/English)

Para hacer esto, el programa principal **_AutoZoom.exe_** se añade a si mismo al StartUp del Usuario Actual y accesa al archivo **_data.txt_**, el cual contiene toda la informacion necesaria para correr el programa, esto incluye:

| Parametro     | Descricion    |
| ------------- |:--------------|
| Zoom Link     | Debe contener **https://** y **zoom** en el                                                   |
| Hora          | En el formato de 24 horas; Debe contener 4 digitos; 2 → hora & 2 → minuto.<br>ej.  →  07:25   |
| Dia           | Dias en los cuales se unira a la reunion; Separados por coma.<br>ej.  →  lunes, martes        |

El usario tambien puede ser notificado **X** minutos antes con una vetana de dialogo si es solicitado por el usario en el archivo **data.txt**.

De los archivos incluidos:
* **AutoZoom.exe** es el programa principal.
* **Deactive.exe** destruye el proceso de AutoZoom y lo remueve del StartUp
* Hay un archivo que incluye las instrucciones de instalacion
* **data.txt** contiene la informacion de las reuniones del usuario
* **MessageBox.vbs** es usado para notificar al usuario previo a la reunion (si asi lo solicita el usuario), permitiendo que el proceso siga corriendo
* Todos las tres librerias **.dll** son requeridas para el funcionamiento del programa

Los Links de Zoom son ejecutados usando el siguiente comando:
```c++
ShellExecute(nullptr, "open", linksS.c_str(), nullptr, nullptr, 0);
```
donde:<br>
&nbsp;&nbsp;&nbsp;&nbsp;linksS es una variable del tipo **string** conteniendo un solo Link.<br>
&nbsp;&nbsp;&nbsp;&nbsp;_c_str()_ es incluido, ya que una variable de tipo **LPCSTR** es requerida.<br>

Notese que los Links seran ejecutados en el navegador por defecto del usuario.

El programa tambien incluye 10 differentes [MessageBox()](https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox) de error, los cuales, si no son cerrados, el proceso no puede continuar.<br>
Cada MessageBox() contiene un codigo y descripcion del error.
