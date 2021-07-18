/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[65];
    char stringdata0[1251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "toggleUndo"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "undoAvailable"
QT_MOC_LITERAL(4, 37, 10), // "toggleRedo"
QT_MOC_LITERAL(5, 48, 13), // "redoAvailable"
QT_MOC_LITERAL(6, 62, 16), // "toggleCopyAndCut"
QT_MOC_LITERAL(7, 79, 16), // "copyCutAvailable"
QT_MOC_LITERAL(8, 96, 23), // "updateTabAndWindowTitle"
QT_MOC_LITERAL(9, 120, 8), // "closeTab"
QT_MOC_LITERAL(10, 129, 7), // "Editor*"
QT_MOC_LITERAL(11, 137, 10), // "tabToClose"
QT_MOC_LITERAL(12, 148, 5), // "index"
QT_MOC_LITERAL(13, 154, 16), // "closeTabShortcut"
QT_MOC_LITERAL(14, 171, 10), // "informUser"
QT_MOC_LITERAL(15, 182, 5), // "title"
QT_MOC_LITERAL(16, 188, 7), // "message"
QT_MOC_LITERAL(17, 196, 20), // "on_currentTabChanged"
QT_MOC_LITERAL(18, 217, 19), // "on_languageSelected"
QT_MOC_LITERAL(19, 237, 8), // "QAction*"
QT_MOC_LITERAL(20, 246, 14), // "languageAction"
QT_MOC_LITERAL(21, 261, 22), // "on_actionNew_triggered"
QT_MOC_LITERAL(22, 284, 22), // "on_actionSaveTriggered"
QT_MOC_LITERAL(23, 307, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(24, 331, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(25, 355, 23), // "on_actionUndo_triggered"
QT_MOC_LITERAL(26, 379, 22), // "on_actionCut_triggered"
QT_MOC_LITERAL(27, 402, 23), // "on_actionCopy_triggered"
QT_MOC_LITERAL(28, 426, 24), // "on_actionPaste_triggered"
QT_MOC_LITERAL(29, 451, 23), // "on_actionFind_triggered"
QT_MOC_LITERAL(30, 475, 24), // "on_actionGo_To_triggered"
QT_MOC_LITERAL(31, 500, 29), // "on_actionSelect_All_triggered"
QT_MOC_LITERAL(32, 530, 23), // "on_actionRedo_triggered"
QT_MOC_LITERAL(33, 554, 24), // "on_actionPrint_triggered"
QT_MOC_LITERAL(34, 579, 29), // "on_actionStatus_Bar_triggered"
QT_MOC_LITERAL(35, 609, 28), // "on_actionTime_Date_triggered"
QT_MOC_LITERAL(36, 638, 23), // "on_actionFont_triggered"
QT_MOC_LITERAL(37, 662, 30), // "on_actionAuto_Indent_triggered"
QT_MOC_LITERAL(38, 693, 28), // "on_actionWord_Wrap_triggered"
QT_MOC_LITERAL(39, 722, 27), // "on_actionTool_Bar_triggered"
QT_MOC_LITERAL(40, 750, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(41, 772, 31), // "on_comboBox_currentIndexChanged"
QT_MOC_LITERAL(42, 804, 15), // "handleConnected"
QT_MOC_LITERAL(43, 820, 11), // "handleError"
QT_MOC_LITERAL(44, 832, 18), // "handleDisconnected"
QT_MOC_LITERAL(45, 851, 24), // "handleChannelInitialized"
QT_MOC_LITERAL(46, 876, 34), // "handleChannelInitializationFa..."
QT_MOC_LITERAL(47, 911, 6), // "reason"
QT_MOC_LITERAL(48, 918, 21), // "handleSftpJobFinished"
QT_MOC_LITERAL(49, 940, 15), // "QSsh::SftpJobId"
QT_MOC_LITERAL(50, 956, 3), // "job"
QT_MOC_LITERAL(51, 960, 15), // "QSsh::SftpError"
QT_MOC_LITERAL(52, 976, 9), // "errorType"
QT_MOC_LITERAL(53, 986, 5), // "error"
QT_MOC_LITERAL(54, 992, 14), // "handleFileInfo"
QT_MOC_LITERAL(55, 1007, 25), // "QList<QSsh::SftpFileInfo>"
QT_MOC_LITERAL(56, 1033, 12), // "fileInfoList"
QT_MOC_LITERAL(57, 1046, 19), // "handleChannelClosed"
QT_MOC_LITERAL(58, 1066, 25), // "on_Connect_Button_clicked"
QT_MOC_LITERAL(59, 1092, 22), // "on_Load_Button_clicked"
QT_MOC_LITERAL(60, 1115, 24), // "on_Upload_Button_clicked"
QT_MOC_LITERAL(61, 1140, 28), // "on_Disconnect_Button_clicked"
QT_MOC_LITERAL(62, 1169, 33), // "on_comboBox_4_currentIndexCha..."
QT_MOC_LITERAL(63, 1203, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(64, 1227, 23) // "on_pushButton_3_clicked"

    },
    "MainWindow\0toggleUndo\0\0undoAvailable\0"
    "toggleRedo\0redoAvailable\0toggleCopyAndCut\0"
    "copyCutAvailable\0updateTabAndWindowTitle\0"
    "closeTab\0Editor*\0tabToClose\0index\0"
    "closeTabShortcut\0informUser\0title\0"
    "message\0on_currentTabChanged\0"
    "on_languageSelected\0QAction*\0"
    "languageAction\0on_actionNew_triggered\0"
    "on_actionSaveTriggered\0on_actionOpen_triggered\0"
    "on_actionExit_triggered\0on_actionUndo_triggered\0"
    "on_actionCut_triggered\0on_actionCopy_triggered\0"
    "on_actionPaste_triggered\0"
    "on_actionFind_triggered\0"
    "on_actionGo_To_triggered\0"
    "on_actionSelect_All_triggered\0"
    "on_actionRedo_triggered\0"
    "on_actionPrint_triggered\0"
    "on_actionStatus_Bar_triggered\0"
    "on_actionTime_Date_triggered\0"
    "on_actionFont_triggered\0"
    "on_actionAuto_Indent_triggered\0"
    "on_actionWord_Wrap_triggered\0"
    "on_actionTool_Bar_triggered\0"
    "on_pushButton_clicked\0"
    "on_comboBox_currentIndexChanged\0"
    "handleConnected\0handleError\0"
    "handleDisconnected\0handleChannelInitialized\0"
    "handleChannelInitializationFailure\0"
    "reason\0handleSftpJobFinished\0"
    "QSsh::SftpJobId\0job\0QSsh::SftpError\0"
    "errorType\0error\0handleFileInfo\0"
    "QList<QSsh::SftpFileInfo>\0fileInfoList\0"
    "handleChannelClosed\0on_Connect_Button_clicked\0"
    "on_Load_Button_clicked\0on_Upload_Button_clicked\0"
    "on_Disconnect_Button_clicked\0"
    "on_comboBox_4_currentIndexChanged\0"
    "on_pushButton_2_clicked\0on_pushButton_3_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      46,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  244,    2, 0x0a /* Public */,
       4,    1,  247,    2, 0x0a /* Public */,
       6,    1,  250,    2, 0x0a /* Public */,
       8,    0,  253,    2, 0x0a /* Public */,
       9,    1,  254,    2, 0x0a /* Public */,
       9,    1,  257,    2, 0x0a /* Public */,
      13,    0,  260,    2, 0x0a /* Public */,
      14,    2,  261,    2, 0x0a /* Public */,
      17,    1,  266,    2, 0x08 /* Private */,
      18,    1,  269,    2, 0x08 /* Private */,
      21,    0,  272,    2, 0x08 /* Private */,
      22,    0,  273,    2, 0x08 /* Private */,
      23,    0,  274,    2, 0x08 /* Private */,
      24,    0,  275,    2, 0x08 /* Private */,
      25,    0,  276,    2, 0x08 /* Private */,
      26,    0,  277,    2, 0x08 /* Private */,
      27,    0,  278,    2, 0x08 /* Private */,
      28,    0,  279,    2, 0x08 /* Private */,
      29,    0,  280,    2, 0x08 /* Private */,
      30,    0,  281,    2, 0x08 /* Private */,
      31,    0,  282,    2, 0x08 /* Private */,
      32,    0,  283,    2, 0x08 /* Private */,
      33,    0,  284,    2, 0x08 /* Private */,
      34,    0,  285,    2, 0x08 /* Private */,
      35,    0,  286,    2, 0x08 /* Private */,
      36,    0,  287,    2, 0x08 /* Private */,
      37,    0,  288,    2, 0x08 /* Private */,
      38,    0,  289,    2, 0x08 /* Private */,
      39,    0,  290,    2, 0x08 /* Private */,
      40,    0,  291,    2, 0x08 /* Private */,
      41,    1,  292,    2, 0x08 /* Private */,
      42,    0,  295,    2, 0x08 /* Private */,
      43,    0,  296,    2, 0x08 /* Private */,
      44,    0,  297,    2, 0x08 /* Private */,
      45,    0,  298,    2, 0x08 /* Private */,
      46,    1,  299,    2, 0x08 /* Private */,
      48,    3,  302,    2, 0x08 /* Private */,
      54,    2,  309,    2, 0x08 /* Private */,
      57,    0,  314,    2, 0x08 /* Private */,
      58,    0,  315,    2, 0x08 /* Private */,
      59,    0,  316,    2, 0x08 /* Private */,
      60,    0,  317,    2, 0x08 /* Private */,
      61,    0,  318,    2, 0x08 /* Private */,
      62,    1,  319,    2, 0x08 /* Private */,
      63,    0,  322,    2, 0x08 /* Private */,
      64,    0,  323,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void,
    QMetaType::Bool, 0x80000000 | 10,   11,
    QMetaType::Bool, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   15,   16,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   47,
    QMetaType::Void, 0x80000000 | 49, 0x80000000 | 51, QMetaType::QString,   50,   52,   53,
    QMetaType::Void, 0x80000000 | 49, 0x80000000 | 55,   50,   56,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toggleUndo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->toggleRedo((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->toggleCopyAndCut((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->updateTabAndWindowTitle(); break;
        case 4: { bool _r = _t->closeTab((*reinterpret_cast< Editor*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->closeTab((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->closeTabShortcut(); break;
        case 7: _t->informUser((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->on_currentTabChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_languageSelected((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 10: _t->on_actionNew_triggered(); break;
        case 11: { bool _r = _t->on_actionSaveTriggered();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->on_actionOpen_triggered(); break;
        case 13: _t->on_actionExit_triggered(); break;
        case 14: _t->on_actionUndo_triggered(); break;
        case 15: _t->on_actionCut_triggered(); break;
        case 16: _t->on_actionCopy_triggered(); break;
        case 17: _t->on_actionPaste_triggered(); break;
        case 18: _t->on_actionFind_triggered(); break;
        case 19: _t->on_actionGo_To_triggered(); break;
        case 20: _t->on_actionSelect_All_triggered(); break;
        case 21: _t->on_actionRedo_triggered(); break;
        case 22: _t->on_actionPrint_triggered(); break;
        case 23: _t->on_actionStatus_Bar_triggered(); break;
        case 24: _t->on_actionTime_Date_triggered(); break;
        case 25: _t->on_actionFont_triggered(); break;
        case 26: _t->on_actionAuto_Indent_triggered(); break;
        case 27: _t->on_actionWord_Wrap_triggered(); break;
        case 28: _t->on_actionTool_Bar_triggered(); break;
        case 29: _t->on_pushButton_clicked(); break;
        case 30: _t->on_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->handleConnected(); break;
        case 32: _t->handleError(); break;
        case 33: _t->handleDisconnected(); break;
        case 34: _t->handleChannelInitialized(); break;
        case 35: _t->handleChannelInitializationFailure((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 36: _t->handleSftpJobFinished((*reinterpret_cast< QSsh::SftpJobId(*)>(_a[1])),(*reinterpret_cast< const QSsh::SftpError(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 37: _t->handleFileInfo((*reinterpret_cast< QSsh::SftpJobId(*)>(_a[1])),(*reinterpret_cast< const QList<QSsh::SftpFileInfo>(*)>(_a[2]))); break;
        case 38: _t->handleChannelClosed(); break;
        case 39: _t->on_Connect_Button_clicked(); break;
        case 40: _t->on_Load_Button_clicked(); break;
        case 41: _t->on_Upload_Button_clicked(); break;
        case 42: _t->on_Disconnect_Button_clicked(); break;
        case 43: _t->on_comboBox_4_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 44: _t->on_pushButton_2_clicked(); break;
        case 45: _t->on_pushButton_3_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Editor* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 46)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 46;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 46)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 46;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
