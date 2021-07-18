# QTRemoteFileEditor
QT GUI Application to Edit, Download and Uplaod Remote file using ssh &amp; sftp 

## Development

This project was developed in Qt5 using [Qt Creator](https://www.qt.io/download-qt-installer?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5).

All code is written in C++ using the [Qt framework and its libraries](http://doc.qt.io/).

## Compiling QSsh

Prerequisites:
   * [Qt](https://www.qt.io/)
   * ....

Steps:
```bash
git clone https://github.com/kpsuhair/QTRemoteFileEditor.git
cd QTRemoteFileEditor
mkdir build
cd build
qmake ../QTRemoteFileEditor.pro

```


## Credits
The GUI part of this code is taken from Scribe , Credit goes to [Feather Icons](https://github.com/AleksandrHovhannisyan/Scribe-Text-Editor). 

Terminal Part of the code using by Qssh, Credit goes to [Feather Icons](https://github.com/sandsmark/QSsh). 

The code for highlighting the current line and numbering the margins on the left was borrowed from the official [Qt Code Editor Example](http://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html) tutorial. All other code is original.
