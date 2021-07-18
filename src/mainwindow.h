#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "documentmetrics.h"
#include "editor.h"
#include "finddialog.h"
#include "gotodialog.h"
#include "tabbededitor.h"
#include "language.h"
#include "metricreporter.h"
#include <highlighters/highlighter.h>
#include <QMainWindow>
#include <QCloseEvent>                  // closeEvent
#include <QLabel>                       // GUI labels
#include <QActionGroup>
#include <QStandardPaths>               // see default directory

#include <qssh/sftpdefs.h>
#include <qssh/sftpchannel.h>
#include <qssh/sshconnection.h>
#include <QDialog>
#include <QElapsedTimer>
#include <QHash>
#include <QList>
#include <QObject>
#include <QSharedPointer>

///Terminal
#include <qtermwidget5/qtermwidget.h>

using namespace ProgrammingLanguage;
namespace QSsh { class SftpFileSystemModel; }

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void launchFindDialog();
    void launchGotoDialog();
    void closeEvent(QCloseEvent *event) override;

private:
    void reconnectEditorDependentSignals();
    void disconnectEditorDependentSignals();
    QMessageBox::StandardButton askUserToSave();

    void appendShortcutsToToolbarTooltips();
    void setupLanguageOnStatusBar();
    void selectProgrammingLanguage(Language language);
    void triggerCorrespondingMenuLanguageOption(Language lang);
    void mapMenuLanguageOptionToLanguageType();
    void mapFileExtensionsToLanguages();
    void setLanguageFromExtension();

    void matchFormatOptionsToEditorDefaults();
    void updateFormatMenuOptions();
    void writeSettings();
    void readSettings();

    void toggleVisibilityOf(QWidget *widget);

    // The "core" or essential members
    Ui::MainWindow *ui;
    TabbedEditor *tabbedEditor;
    MetricReporter *metricReporter;
    Editor *editor = nullptr;
    Settings *settings = Settings::instance();

    // Used for storing application state upon termination
    const QString WINDOW_SIZE_KEY = "window_size";
    const QString WINDOW_POSITION_KEY = "window_position";
    const QString WINDOW_STATUS_BAR = "window_status_bar";
    const QString WINDOW_TOOL_BAR = "window_tool_bar";
    const QString DEFAULT_DIRECTORY_KEY = "default_directory";
    const QString DEFAULT_DIRECTORY = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    // Other widget members
    FindDialog *findDialog;
    GotoDialog *gotoDialog;
    QActionGroup *languageGroup;
    QLabel *languageLabel;
    QMap<QAction*, Language> menuActionToLanguageMap;
    QMap<QString, Language> extensionToLanguageMap;

    typedef QHash<QSsh::SftpJobId, QString> JobMap;
    typedef QSharedPointer<QFile> FilePtr;
    enum State {
        Inactive, Connecting, InitializingChannel, UploadingSmall, DownloadingSmall,
        RemovingSmall, UploadingBig, DownloadingBig, RemovingBig, CreatingDir,
        CheckingDirAttributes, CheckingDirContents, RemovingDir, ChannelClosing, Disconnecting
    };

    void removeFile(const FilePtr &filePtr, bool remoteToo);
    void removeFiles(bool remoteToo);
    QString cmpFileName(const QString &localFileName) const;
    QString remoteFilePath(const QString &localFileName) const;
    void earlyDisconnectFromHost();
    bool checkJobId(QSsh::SftpJobId job, QSsh::SftpJobId expectedJob, const char *activity);
    bool handleJobFinished(QSsh::SftpJobId job, JobMap &jobMap,
        const QString &error, const char *activity);
    bool handleJobFinished(QSsh::SftpJobId job, QSsh::SftpJobId expectedJob, const QString &error,
        const char *activity);
    bool handleBigJobFinished(QSsh::SftpJobId job, QSsh::SftpJobId expectedJob,
        const QString &error, const char *activity);
    bool compareFiles(QFile *orig, QFile *copy);

    //const Parameters m_parameters;
    State m_state;
    bool m_error;
    QString remotePath;
    QSsh::SshConnection *m_connection;
    QSsh::SftpChannel::Ptr m_channel;
    QList<FilePtr> m_localSmallFiles;
    JobMap m_smallFilesUploadJobs;
    JobMap m_smallFilesDownloadJobs;
    JobMap m_smallFilesRemovalJobs;
    FilePtr m_localBigFile;
    QSsh::SftpJobId m_bigFileUploadJob;
    QSsh::SftpJobId m_bigFileDownloadJob;
    QSsh::SftpJobId m_bigFileRemovalJob;
    QSsh::SftpJobId m_mkdirJob;
    QSsh::SftpJobId m_statDirJob;
    QSsh::SftpJobId m_lsDirJob;
    QSsh::SftpJobId m_rmDirJob;
    QElapsedTimer m_bigJobTimer;
    QString m_remoteDirPath;
    QSsh::SftpFileInfo m_dirInfo;
    QList<QSsh::SftpFileInfo> m_dirContents;


    QString openedFilePath ;
    void on_Edit_Button_clicked();
    void when_disconnected();

    /////Terminal
    QTermWidget *console;
public slots:
    void toggleUndo(bool undoAvailable);
    void toggleRedo(bool redoAvailable);
    void toggleCopyAndCut(bool copyCutAvailable);

    void updateTabAndWindowTitle();
    bool closeTab(Editor *tabToClose);
    inline bool closeTab(int index) { return closeTab(tabbedEditor->tabAt(index)); }
    inline void closeTabShortcut() { closeTab(tabbedEditor->currentTab()); }
    inline void informUser(QString title, QString message) { QMessageBox::information(findDialog, title, message); }

// All UI and/or keyboard shortcut interactions
private slots:
    void on_currentTabChanged(int index);
    void on_languageSelected(QAction* languageAction);
    void on_actionNew_triggered();
    bool on_actionSaveTriggered();
    void on_actionOpen_triggered();
    void on_actionExit_triggered();
    void on_actionUndo_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionFind_triggered();
    void on_actionGo_To_triggered();
    void on_actionSelect_All_triggered();
    void on_actionRedo_triggered();
    void on_actionPrint_triggered();
    void on_actionStatus_Bar_triggered();
    void on_actionTime_Date_triggered();
    void on_actionFont_triggered();
    void on_actionAuto_Indent_triggered();
    void on_actionWord_Wrap_triggered();
    void on_actionTool_Bar_triggered();
    void on_pushButton_clicked();
    void on_comboBox_currentIndexChanged(int index);


    ////DT
    void handleConnected();
    void handleError();
    void handleDisconnected();
    void handleChannelInitialized();
    void handleChannelInitializationFailure(const QString &reason);
    void handleSftpJobFinished(QSsh::SftpJobId job, const QSsh::SftpError errorType, const QString &error);
    void handleFileInfo(QSsh::SftpJobId job, const QList<QSsh::SftpFileInfo> &fileInfoList);
    void handleChannelClosed();
    void on_Connect_Button_clicked();
    void on_Load_Button_clicked();
    void on_Upload_Button_clicked();
    void on_Disconnect_Button_clicked();
    void on_comboBox_4_currentIndexChanged(int index);
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
