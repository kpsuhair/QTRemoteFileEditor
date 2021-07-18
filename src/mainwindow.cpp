#include "mainwindow.h"
#include "utilityfunctions.h"
#include "ui_mainwindow.h"
#include "settings.h"                   // storing app state
#include <QtDebug>
#include <QtPrintSupport/QPrinter>      // printing
#include <QtPrintSupport/QPrintDialog>  // printing
#include <QFileDialog>                  // file open/save dialogs
#include <QFile>                        // file descriptors, IO
#include <QTextStream>                  // file IO
#include <QStandardPaths>               // default open directory
#include <QDateTime>                    // current time
#include <QApplication>                 // quit
#include <QShortcut>
#include <QProgressDialog>

#include <qssh/sftpfilesystemmodel.h>
#include <qssh/sshconnection.h>

#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QModelIndexList>
#include <QItemSelectionModel>
#include <QString>
#include <iostream>

using namespace QSsh;


/* Sets up the main application window and all of its children/widgets.
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color: blue;");
    //this->setStyleSheet("QLabel { background-color : red; color : blue; }");


//    this->setAutoFillBackground(true);
//    QPixmap pixmap=QPixmap("./images/ai_1.jpeg").scaled(this->size());
//    QPalette palette(this->palette());
//    palette.setBrush(this->backgroundRole(),QBrush(pixmap.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
//    this->setPalette(palette);


    //QPalette pal = palette();
    //    pal.setColor(QPalette::Window, Qt::black);
     //   this->setPalette(pal);

    readSettings();

    // Used to ensure that only one language can ever be checked at a time
    languageGroup = new QActionGroup(this);
    languageGroup->setExclusive(true);
    languageGroup->addAction(ui->actionC_Lang);
    languageGroup->addAction(ui->actionCPP_Lang);
    languageGroup->addAction(ui->actionJava_Lang);
    languageGroup->addAction(ui->actionPython_Lang);
    connect(languageGroup, SIGNAL(triggered(QAction*)), this, SLOT(on_languageSelected(QAction*)));
    // Language label frame
    setupLanguageOnStatusBar();

    // Set up the find dialog
    findDialog = new FindDialog();
    findDialog->setParent(this, Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);

    // Set up the goto dialog
    gotoDialog = new GotoDialog();
    gotoDialog->setParent(this, Qt::Tool | Qt::MSWindowsFixedSizeDialogHint);

    // Set up the tabbed editor
    tabbedEditor = ui->tabWidget;
    tabbedEditor->setTabsClosable(true);

    // Add metric reporter and simulate a tab switch
    metricReporter = new MetricReporter();
    ui->statusBar->addPermanentWidget(metricReporter);
    on_currentTabChanged(0);


    // Stacked widget
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->lineEdit->setText("192.168.9.5");
    ui->lineEdit_2->setText("atc8110");
    ui->lineEdit_3->setText("123456");
    ui->Disconnect_Button->setEnabled(false);
    ui->Load_Button->setEnabled(false);
    ui->Upload_Button->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    //connect(tabbedEditor, SIGNAL(currentChanged(int)), this, SLOT(on_currentTabChanged(int)));

    // Connect tabbedEditor's signals to their handlers
    connect(tabbedEditor, SIGNAL(currentChanged(int)), this, SLOT(on_currentTabChanged(int)));
    connect(tabbedEditor, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    // Connect action signals to their handlers
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(on_actionSaveTriggered()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(on_actionSaveTriggered()));
    connect(ui->actionReplace, SIGNAL(triggered()), this, SLOT(on_actionFind_triggered()));

    // Have to add this shortcut manually because we can't define it via the GUI editor
    QShortcut *tabCloseShortcut = new QShortcut(QKeySequence("Ctrl+W"), this);
    QObject::connect(tabCloseShortcut, SIGNAL(activated()), this, SLOT(closeTabShortcut()));

    // For word wrap and auto indent
    matchFormatOptionsToEditorDefaults();

    mapMenuLanguageOptionToLanguageType();
    mapFileExtensionsToLanguages();
    appendShortcutsToToolbarTooltips();

    //////Terminal
     ui->tabWidget_2->setUsesScrollButtons(true);
     console = new QTermWidget();

     QFont font = QApplication::font();
     font.setFamily("Monospace");
     font.setPointSize(12);

     console->setTerminalFont(font);
     console->setScrollBarPosition(QTermWidget::ScrollBarRight);
     console->setColorScheme("WhiteOnBlack");

     ui->tabWidget_2->insertTab(ui->tabWidget_2->currentIndex(), console, QString(QDir::currentPath()));
}


/* Ensures that the checkable formatting menu options, like auto indent
 * and word wrap, match the previously saved defaults for the Editor class.
 * See constructor for usage.
 */
void MainWindow::matchFormatOptionsToEditorDefaults()
{
    QAction *autoIndent = ui->actionAuto_Indent;
    editor->autoIndentEnabled ? autoIndent->setChecked(true) : autoIndent->setChecked(false);

    QAction *wordWrap = ui->actionWord_Wrap;
    editor->lineWrapMode ? wordWrap->setChecked(true) : wordWrap->setChecked(false);
}


/* Updates the Format menu options (e.g., Word wrap, Auto indent) to match
 * the settings of the currently selected editor. See onCurrentTabChanged for usage.
 */
void MainWindow::updateFormatMenuOptions()
{
    ui->actionWord_Wrap->setChecked(editor->textIsWrapped());
    ui->actionAuto_Indent->setChecked(editor->textIsAutoIndented());
}


/* Initializes the language label and adds it to a frame
 * that gets set as a widget on the far left of the status bar.
 */
void MainWindow::setupLanguageOnStatusBar()
{
    languageLabel = new QLabel("Language: not selected");
    QFrame *langFrame = new QFrame();
    QHBoxLayout *langLayout = new QHBoxLayout();
    langLayout->addWidget(languageLabel);
    langFrame->setLayout(langLayout);
    ui->statusBar->addWidget(langFrame);
}


/* Maps each menu language option (from the Format dropdown) to its corresponding
 * Language type, for convenience.
 */
void MainWindow::mapMenuLanguageOptionToLanguageType()
{
    menuActionToLanguageMap[ui->actionC_Lang] = Language::C;
    menuActionToLanguageMap[ui->actionCPP_Lang] = Language::CPP;
    menuActionToLanguageMap[ui->actionJava_Lang] = Language::Java;
    menuActionToLanguageMap[ui->actionPython_Lang] = Language::Python;
}


/* Maps known file extensions to the languages the editor supports.
 */
void MainWindow::mapFileExtensionsToLanguages()
{
    extensionToLanguageMap.insert("cpp", Language::CPP);
    extensionToLanguageMap.insert("h", Language::CPP);
    extensionToLanguageMap.insert("c", Language::C);
    extensionToLanguageMap.insert("java", Language::Java);
    extensionToLanguageMap.insert("py", Language::Python);
}


void MainWindow::appendShortcutsToToolbarTooltips()
{
    for (QAction* action : ui->mainToolBar->actions())
    {
        QString tooltip = action->toolTip() + " (" + action->shortcut().toString() + ")";
        action->setToolTip(tooltip);
    }
}

/* Performs all necessary memory cleanup operations on dynamically allocated objects.
 */
MainWindow::~MainWindow()
{
    delete languageLabel;
    delete languageGroup;
    delete ui;
}


/* Called when the user selects a language from the main menu. Sets the current language to
 * that language internally for the currently tabbed Editor.
 */
void MainWindow::on_languageSelected(QAction* languageAction)
{
    Language language = menuActionToLanguageMap[languageAction];
    selectProgrammingLanguage(language);
}


/* Given a Language enum, this function checks the corresponding radio option from the Format > Language
 * menu. Used by on_currentTabChanged to reflect the current tab's selected language.
 */
void MainWindow::triggerCorrespondingMenuLanguageOption(Language lang)
{
    switch (lang)
    {
        case (Language::C):
            if (!ui->actionC_Lang->isChecked())
            {
                ui->actionC_Lang->trigger();
            }
            break;

        case (Language::CPP):
            if (!ui->actionCPP_Lang->isChecked())
            {
                ui->actionCPP_Lang->trigger();
            }
            break;

        case (Language::Java):
            if (!ui->actionJava_Lang->isChecked())
            {
                ui->actionJava_Lang->trigger();
            }
            break;

        case (Language::Python):
            if (!ui->actionPython_Lang->isChecked())
            {
                ui->actionPython_Lang->trigger();
            }
            break;

        default: return;
    }
}


/* Uses the extension of a file to determine what language, if any, it should be
 * mapped to. If the extension does not match one of the supported languages, or if
 * the file does not have an extension, then the language is set to Language::None.
 */
void MainWindow::setLanguageFromExtension()
{
    QString fileName = editor->getFileName();
    int indexOfDot = fileName.indexOf('.');

    if (indexOfDot == -1)
    {
        selectProgrammingLanguage(Language::None);
        return;
    }

    QString fileExtension = fileName.mid(indexOfDot + 1);

    bool extensionSupported = extensionToLanguageMap.find(fileExtension) != extensionToLanguageMap.end();

    if (!extensionSupported)
    {
        selectProgrammingLanguage(Language::None);
        return;
    }

    selectProgrammingLanguage(extensionToLanguageMap[fileExtension]);
}


/* Wrapper for all common logic that needs to run whenever a given language
 * is selected for use on a particular tab. Triggers the corresponding menu option.
 */
void MainWindow::selectProgrammingLanguage(Language language)
{
    if (language == editor->getProgrammingLanguage())
    {
        return;
    }

    editor->setProgrammingLanguage(language);
    languageLabel->setText(toString(language));
    triggerCorrespondingMenuLanguageOption(language);
}


/* Disconnects all signals that depend on the cached editor/tab. Used mainly
 * when the current editor is changed (when a new tab is opened, for example).
 */
void MainWindow::disconnectEditorDependentSignals()
{
    disconnect(findDialog, SIGNAL(startFinding(QString, bool, bool)), editor, SLOT(find(QString, bool, bool)));
    disconnect(findDialog, SIGNAL(startReplacing(QString, QString, bool, bool)), editor, SLOT(replace(QString, QString, bool, bool)));
    disconnect(findDialog, SIGNAL(startReplacingAll(QString, QString, bool, bool)), editor, SLOT(replaceAll(QString, QString, bool, bool)));
    disconnect(gotoDialog, SIGNAL(gotoLine(int)), editor, SLOT(goTo(int)));
    disconnect(editor, SIGNAL(findResultReady(QString)), findDialog, SLOT(onFindResultReady(QString)));
    disconnect(editor, SIGNAL(gotoResultReady(QString)), gotoDialog, SLOT(onGotoResultReady(QString)));

    disconnect(editor, SIGNAL(wordCountChanged(int)), metricReporter, SLOT(updateWordCount(int)));
    disconnect(editor, SIGNAL(charCountChanged(int)), metricReporter, SLOT(updateCharCount(int)));
    disconnect(editor, SIGNAL(lineCountChanged(int, int)), metricReporter, SLOT(updateLineCount(int, int)));
    disconnect(editor, SIGNAL(columnCountChanged(int)), metricReporter, SLOT(updateColumnCount(int)));
    disconnect(editor, SIGNAL(fileContentsChanged()), this, SLOT(updateTabAndWindowTitle()));

    disconnect(editor, SIGNAL(undoAvailable(bool)), this, SLOT(toggleUndo(bool)));
    disconnect(editor, SIGNAL(redoAvailable(bool)), this, SLOT(toggleRedo(bool)));
    disconnect(editor, SIGNAL(copyAvailable(bool)), this, SLOT(toggleCopyAndCut(bool)));
}


/* Connects all signals and slots that depend on the cached editor/tab. Used mainly
 * when the current editor is changed (when a new tab is opened, for example).
 */
void MainWindow::reconnectEditorDependentSignals()
{
    connect(findDialog, SIGNAL(startFinding(QString, bool, bool)), editor, SLOT(find(QString, bool, bool)));
    connect(findDialog, SIGNAL(startReplacing(QString, QString, bool, bool)), editor, SLOT(replace(QString, QString, bool, bool)));
    connect(findDialog, SIGNAL(startReplacingAll(QString, QString, bool, bool)), editor, SLOT(replaceAll(QString, QString, bool, bool)));
    connect(gotoDialog, SIGNAL(gotoLine(int)), editor, SLOT(goTo(int)));
    connect(editor, SIGNAL(findResultReady(QString)), findDialog, SLOT(onFindResultReady(QString)));
    connect(editor, SIGNAL(gotoResultReady(QString)), gotoDialog, SLOT(onGotoResultReady(QString)));

    connect(editor, SIGNAL(wordCountChanged(int)), metricReporter, SLOT(updateWordCount(int)));
    connect(editor, SIGNAL(charCountChanged(int)), metricReporter, SLOT(updateCharCount(int)));
    connect(editor, SIGNAL(lineCountChanged(int, int)), metricReporter, SLOT(updateLineCount(int, int)));
    connect(editor, SIGNAL(columnCountChanged(int)), metricReporter, SLOT(updateColumnCount(int)));
    connect(editor, SIGNAL(fileContentsChanged()), this, SLOT(updateTabAndWindowTitle()));

    connect(editor, SIGNAL(undoAvailable(bool)), this, SLOT(toggleUndo(bool)));
    connect(editor, SIGNAL(redoAvailable(bool)), this, SLOT(toggleRedo(bool)));
    connect(editor, SIGNAL(copyAvailable(bool)), this, SLOT(toggleCopyAndCut(bool)));
}


/* Called each time the current tab changes in the tabbed editor. Sets the main window's current editor,
 * reconnects any relevant signals, and updates the window.
 */
void MainWindow::on_currentTabChanged(int index)
{
    // Happens when the tabbed editor's last tab is closed
    if (index == -1)
    {
        return;
    }

    // Note: editor will only be nullptr on the first launch, so this will get skipped in that edge case
    if (editor != nullptr)
    {
        disconnectEditorDependentSignals();
    }

    editor = tabbedEditor->currentTab();
    reconnectEditorDependentSignals();
    editor->setFocus(Qt::FocusReason::TabFocusReason);

    Language tabLanguage = editor->getProgrammingLanguage();

    // If this tab had a programming language set, trigger the corresponding option
    if (tabLanguage != Language::None)
    {
        triggerCorrespondingMenuLanguageOption(tabLanguage);
    }
    else
    {        
        // If a menu language is checked but the current tab has no language set, uncheck the menu option
        if (languageGroup->checkedAction())
        {
            languageGroup->checkedAction()->setChecked(false);
        }
    }

    // Update language reflected on status bar
    languageLabel->setText(toString(tabLanguage));

    // Update main window actions to reflect the current tab's available actions
    toggleRedo(editor->redoAvailable());
    toggleUndo(editor->undoAvailable());
    toggleCopyAndCut(editor->textCursor().hasSelection());

    updateFormatMenuOptions();


    // We need to update this information manually for tab changes
    DocumentMetrics metrics = editor->getDocumentMetrics();
    updateTabAndWindowTitle();
    metricReporter->updateWordCount(metrics.wordCount);
    metricReporter->updateCharCount(metrics.charCount);
    metricReporter->updateLineCount(metrics.currentLine, metrics.totalLines);
    metricReporter->updateColumnCount(metrics.currentColumn);
}


/* Launches the Find dialog box if it isn't already visible and sets its focus.
 */
void MainWindow::launchFindDialog()
{
    if (findDialog->isHidden())
    {
        findDialog->show();
        findDialog->activateWindow();
        findDialog->raise();
        findDialog->setFocus();
    }
}


/* Launches the Go To dialog box if it isn't already visible and sets its focus.
 */
void MainWindow::launchGotoDialog()
{
    if (gotoDialog->isHidden())
    {
        gotoDialog->show();
        gotoDialog->activateWindow();
        gotoDialog->raise();
        gotoDialog->setFocus();
    }
}


/* Updates the tab name and the main application window title to reflect the
 * currently open document.
 */
void MainWindow::updateTabAndWindowTitle()
{
    QString tabTitle = editor->getFileName();
    QString windowTitle = tabTitle;

    if (editor->isUnsaved())
    {
        tabTitle += " *";
        windowTitle += " [Unsaved]";
    }

    tabbedEditor->setTabText(tabbedEditor->currentIndex(), tabTitle);
    setWindowTitle( "QTRemoteFileEditor ");
}


/* Launches a dialog box asking the user if they would like to save the current file.
 * If the user selects "No" or closes the dialog window, the file will not be saved.
 * Otherwise, if they select "Yes," the file will be saved.
 */
QMessageBox::StandardButton MainWindow::askUserToSave()
{
    QString fileName = editor->getFileName();

    return Utility::promptYesOrNo(this, "Unsaved changes", tr("Do you want to save the changes to ") + fileName + tr("?"));
}


/* Called when the user selects the New option from the menu or toolbar (or uses Ctrl+N).
 * Adds a new tab to the editor.
 */
void MainWindow::on_actionNew_triggered()
{
    tabbedEditor->add(new Editor());
}


/* Called when the user selects the Save or Save As option from the menu or toolbar
 * (or uses Ctrl+S). On success, saves the contents of the text editor to the disk using
 * the file name provided by the user. If the current document was never saved, or if the
 * user chose Save As, the program prompts the user to specify a name and directory for the file.
 * Returns true if the file was saved and false otherwise.
 */
bool MainWindow::on_actionSaveTriggered()
{
    bool saveAs = sender() == ui->actionSave_As;
    QString currentFilePath = editor->getCurrentFilePath();

    // If user hit Save As or user hit Save but current document was never saved to disk
    if (saveAs || currentFilePath.isEmpty())
    {
        // Title to be used for saving dialog
        QString saveDialogWindowTitle = saveAs ? tr("Save As") : tr("Save");

        // Try to get a valid file path
        QString filePath = QFileDialog::getSaveFileName(this, saveDialogWindowTitle);

        // Don't do anything if the user changes their mind and hits Cancel
        if (filePath.isNull())
        {
            return false;
        }
        editor->setCurrentFilePath(filePath);
    }

    // Attempt to create a file descriptor with the given path
    QFile file(editor->getCurrentFilePath());
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return false;
    }

    ui->statusBar->showMessage("Document saved", 2000);

    // Save the contents of the editor to the disk and close the file descriptor
    QTextStream out(&file);
    QString editorContents = editor->toPlainText();
    out << editorContents;
    file.close();

    editor->setModifiedState(false);
    updateTabAndWindowTitle();
    setLanguageFromExtension();

    return true;
}


/* Called when the user selects the Open option from the menu or toolbar
 * (or uses Ctrl+O). If the current document has unsaved changes, it first
 * asks the user if they want to save. In any case, it launches a dialog box
 * that allows the user to select the file they want to open. Sets the editor's
 * current file path to that of the opened file on success and updates the app state.
 */
void MainWindow::on_actionOpen_triggered()
{
    // Used to switch to a new tab if there's already an open doc
    bool openInCurrentTab = editor->isUntitled() && !editor->isUnsaved();

    QString openedFilePath;
    QString lastUsedDirectory = settings->value(DEFAULT_DIRECTORY_KEY).toString();

    if (lastUsedDirectory.isEmpty())
    {
        openedFilePath = QFileDialog::getOpenFileName(this, tr("Open"), DEFAULT_DIRECTORY);
    }
    else
    {
        openedFilePath = QFileDialog::getOpenFileName(this, tr("Open"), lastUsedDirectory);
    }

    // Don't do anything if the user hit Cancel
    if (openedFilePath.isNull())
    {
        return;
    }

    // Update the recently used directory
    QDir currentDirectory;
    settings->setValue(DEFAULT_DIRECTORY_KEY, currentDirectory.absoluteFilePath(openedFilePath));

    // Attempt to create a file descriptor for the file at the given path
    QFile file(openedFilePath);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Read the file contents into the editor and close the file descriptor
    QTextStream in(&file);
    QString documentContents = in.readAll();

    if (!openInCurrentTab)
    {
        tabbedEditor->add(new Editor());
    }
    editor->setCurrentFilePath(openedFilePath);
    editor->setPlainText(documentContents);
    file.close();

    editor->setModifiedState(false);
    updateTabAndWindowTitle();
    setLanguageFromExtension();
}


/* Called when the user selects the Print option from the menu or toolbar (or uses Ctrl+P).
 * Allows the user to print the contents of the current document.
 */
void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName(tr("Document printer"));
    QPrintDialog printDialog(&printer, this);

    if (printDialog.exec() != QPrintDialog::Rejected)
    {
        editor->print(&printer);
        ui->statusBar->showMessage("Printing", 2000);
    }
}


/* Called when the user tries to close a tab in the editor (or uses Ctrl+W). Allows the user
 * to save the contents of the tab if unsaved. Closes the tab, unless the file is unsaved
 * and the user declines saving. Returns true if the tab was closed and false otherwise.
 */
bool MainWindow::closeTab(Editor *tabToClose)
{
    Editor *currentTab = editor;
    bool closingCurrentTab = (tabToClose == currentTab);

    // Allow the user to see what tab they're closing if it's not the current one
    if (!closingCurrentTab)
    {
        tabbedEditor->setCurrentWidget(tabToClose);
    }

    // Don't close a tab immediately if it has unsaved contents
    if (tabToClose->isUnsaved())
    {
        QMessageBox::StandardButton selection = askUserToSave();

        if (selection == QMessageBox::StandardButton::Yes)
        {
            bool fileSaved = on_actionSaveTriggered();

            if (!fileSaved)
            {
                return false;
            }
        }

        else if (selection == QMessageBox::Cancel)
        {
            return false;
        }
    }

    int indexOfTabToClose = tabbedEditor->indexOf(tabToClose);
    tabbedEditor->removeTab(indexOfTabToClose);

    // If we closed the last tab, make a new one
    if (tabbedEditor->count() == 0)
    {
        on_actionNew_triggered();
    }

    // And finally, go back to original tab if the user was closing a different one
    if (!closingCurrentTab)
    {
        tabbedEditor->setCurrentWidget(currentTab);
    }

    return true;
}


/* Called when the user selects the Exit option from the menu. Allows the user
 * to save any unsaved files before quitting.
 */
void MainWindow::on_actionExit_triggered()
{
    QVector<Editor*> unsavedTabs = tabbedEditor->unsavedTabs();

    for (Editor *tab : unsavedTabs)
    {
        bool userClosedTab = closeTab(tab);

        if (!userClosedTab)
        {
            return;
        }
    }

    writeSettings();
    QApplication::quit();
}


/* Saves the main application state/settings so they may be
 * restored the next time the application is started. See
 * readSettings and the constructor for more info.
 */
void MainWindow::writeSettings()
{
    settings->setValue(WINDOW_SIZE_KEY, size());
    settings->setValue(WINDOW_POSITION_KEY, pos());
    settings->setValue(WINDOW_STATUS_BAR, ui->statusBar->isVisible());
    settings->setValue(WINDOW_TOOL_BAR, ui->mainToolBar->isVisible());
}


/* Reads the stored app settings and restores them.
 */
void MainWindow::readSettings()
{
    settings->apply(settings->value(WINDOW_SIZE_KEY, QSize(400, 400)),
                    [=](QVariant setting){ this->resize(setting.toSize()); });

    settings->apply(settings->value(WINDOW_POSITION_KEY, QPoint(200, 200)),
                    [=](QVariant setting){ this->move(setting.toPoint()); });

    settings->apply(settings->value(WINDOW_STATUS_BAR),
                    [=](QVariant setting) {
                        this->ui->statusBar->setVisible(qvariant_cast<bool>(setting));
                        this->ui->actionStatus_Bar->setChecked(qvariant_cast<bool>(setting));
                    });

    settings->apply(settings->value(WINDOW_TOOL_BAR),
                    [=](QVariant setting) {
                        this->ui->mainToolBar->setVisible(qvariant_cast<bool>(setting));
                        this->ui->actionTool_Bar->setChecked(qvariant_cast<bool>(setting));
                    });
}


/* Called when the Undo operation is toggled by the editor.
 */
void MainWindow::toggleUndo(bool undoAvailable)
{
    ui->actionUndo->setEnabled(undoAvailable);
}


/* Called when the Redo operation is toggled by the editor.
 */
void MainWindow::toggleRedo(bool redoAvailable)
{
    ui->actionRedo->setEnabled(redoAvailable);
}


/* Called when the user performs the Undo operation.
 */
void MainWindow::on_actionUndo_triggered()
{
    if (ui->actionUndo->isEnabled())
    {
        editor->undo();
    }
}


/* Called when the user performs the Redo operation.
 */
void MainWindow::on_actionRedo_triggered()
{
    if (ui->actionRedo->isEnabled())
    {
        editor->redo();
    }
}


/* Called when the Copy and Cut operations are toggled by the editor.
 */
void MainWindow::toggleCopyAndCut(bool copyCutAvailable)
{
    ui->actionCopy->setEnabled(copyCutAvailable);
    ui->actionCut->setEnabled(copyCutAvailable);
}


/* Called when the user performs the Cut operation.
 */
void MainWindow::on_actionCut_triggered()
{
    if (ui->actionCut->isEnabled())
    {
        editor->cut();
    }
}


/* Called when the user performs the Copy operation.
 */
void MainWindow::on_actionCopy_triggered()
{
    if (ui->actionCopy->isEnabled())
    {
        editor->copy();
    }
}


/* Called when the user performs the Paste operation.
 */
void MainWindow::on_actionPaste_triggered()
{
    editor->paste();
}


/* Called when the user explicitly selects the Find option from the menu
 * (or uses Ctrl+F). Launches a dialog that prompts the user to enter a search query.
 */
void MainWindow::on_actionFind_triggered()
{
    launchFindDialog();
}


/* Called when the user explicitly selects the Go To option from the menu (or uses Ctrl+G).
 * Launches a Go To dialog that prompts the user to enter a line number they wish to jump to.
 */
void MainWindow::on_actionGo_To_triggered()
{
    launchGotoDialog();
}


/* Called when the user explicitly selects the Select All option from the menu (or uses Ctrl+A).
 */
void MainWindow::on_actionSelect_All_triggered()
{
    editor->selectAll();
}


/* Called when the user explicitly selects the Time/Date option from the menu (or uses F5).
 */
void MainWindow::on_actionTime_Date_triggered()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    editor->insertPlainText(currentTime.toString());
}


/* Called when the user selects the Font option from the menu. Launches a font selection dialog.
 */
void MainWindow::on_actionFont_triggered()
{
    tabbedEditor->promptFontSelection();
}


/* Called when the user selects the Auto Indent option from the Format menu.
 */
void MainWindow::on_actionAuto_Indent_triggered()
{
    bool shouldAutoIndent = ui->actionAuto_Indent->isChecked();
    bool autoIndentToggled = tabbedEditor->applyAutoIndentation(shouldAutoIndent);

    // If the user canceled the operation, reverse the checking
    if (!autoIndentToggled)
    {
        ui->actionAuto_Indent->setChecked(!shouldAutoIndent);
    }
}


/* Called when the user selects the Word Wrap option from the Format menu.
 */
void MainWindow::on_actionWord_Wrap_triggered()
{
    tabbedEditor->applyWordWrapping(ui->actionWord_Wrap->isChecked());
}


/* Toggles the visibility of the given widget. It is assumed that this
 * widget is part of the main window. Otherwise, the effect may not be seen.
 */
void MainWindow::toggleVisibilityOf(QWidget *widget)
{
    bool opposite = !widget->isVisible();
    widget->setVisible(opposite);
}


/* Toggles the visibility of the status bar.
 */
void MainWindow::on_actionStatus_Bar_triggered()
{
    toggleVisibilityOf(ui->statusBar);
}


/* Toggles the visibility of the main tool bar
*/
void MainWindow::on_actionTool_Bar_triggered()
{
    toggleVisibilityOf(ui->mainToolBar);
}


/* Overrides the QWidget closeEvent virtual method. Called when the user tries
 * to close the main application window conventually via the red X. Allows the
 * user to save any unsaved files before quitting.
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    on_actionExit_triggered();
}

void MainWindow::on_pushButton_clicked()
{
    // Used to switch to a new tab if there's already an open doc
    bool openInCurrentTab = editor->isUntitled() && !editor->isUnsaved();

    QString openedFilePath;
    QString lastUsedDirectory = settings->value(DEFAULT_DIRECTORY_KEY).toString();


    openedFilePath = (ui->lineEdit_3->text());

     if (openedFilePath.isEmpty()){
         QMessageBox::warning(this, "Warning", "Local open file path is empty ");
         return;
     }
     /*
    if (lastUsedDirectory.isEmpty())
    {
        openedFilePath = QFileDialog::getOpenFileName(this, tr("Open"), DEFAULT_DIRECTORY);
    }
    else
    {
        openedFilePath = QFileDialog::getOpenFileName(this, tr("Open"), lastUsedDirectory);
    }
*/
    // Don't do anything if the user hit Cancel
    if (openedFilePath.isNull())
    {
        return;
    }

    // Update the recently used directory
    QDir currentDirectory;
    settings->setValue(DEFAULT_DIRECTORY_KEY, currentDirectory.absoluteFilePath(openedFilePath));

    // Attempt to create a file descriptor for the file at the given path
    QFile file(openedFilePath);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    // Read the file contents into the editor and close the file descriptor
    QTextStream in(&file);
    QString documentContents = in.readAll();

    if (!openInCurrentTab)
    {
        tabbedEditor->add(new Editor());
    }
    editor->setCurrentFilePath(openedFilePath);
    editor->setPlainText(documentContents);
    file.close();

    editor->setModifiedState(false);
    updateTabAndWindowTitle();
    setLanguageFromExtension();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    QString blank="";
    QString Configure="Configure";
    QString Download="Download";
    QString Upload="Upload";

     int check_blank = QString::compare(blank, ui->comboBox_4->currentText(), Qt::CaseInsensitive);
     int check_Configure = QString::compare(Configure, ui->comboBox_4->currentText(), Qt::CaseInsensitive);
     int check_Download = QString::compare(Download, ui->comboBox_4->currentText(), Qt::CaseInsensitive);
     int check_Upload = QString::compare(Upload, ui->comboBox_4->currentText(), Qt::CaseInsensitive);

    if(index ==0 ){
        if(check_blank ==0){
            ui->stackedWidget->setCurrentIndex(0);
            ui->stackedWidget_2->setCurrentIndex(0);
        }else if (check_Configure ==0 ) {
            ui->stackedWidget->setCurrentIndex(1);
            ui->stackedWidget_2->setCurrentIndex(0);
        }else if (check_Download==0) {
            ui->stackedWidget->setCurrentIndex(0);
            ui->stackedWidget_2->setCurrentIndex(0);
        }else if (check_Upload==0) {
            ui->stackedWidget->setCurrentIndex(0);
            ui->stackedWidget_2->setCurrentIndex(0);
        }

    }else if (index ==1 ){
        if(check_blank ==0){
            ui->stackedWidget->setCurrentIndex(0);
            ui->stackedWidget_2->setCurrentIndex(0);
        }else if (check_Configure ==0 ) {
            ui->stackedWidget->setCurrentIndex(2);
            ui->stackedWidget_2->setCurrentIndex(1);
        }else if (check_Download==0) {
            ui->stackedWidget->setCurrentIndex(2);
            ui->stackedWidget_2->setCurrentIndex(2);
        }else if (check_Upload==0) {
            ui->stackedWidget->setCurrentIndex(2);
            ui->stackedWidget_2->setCurrentIndex(3);
        }
    }else {

    }
}

void MainWindow::on_Connect_Button_clicked()
{
    //ui->Connect_Button->setEnabled(false);
    SshConnectionParameters sshParams;
    sshParams.setHost(ui->lineEdit->text());
    sshParams.setUserName(ui->lineEdit_2->text());
    sshParams.authenticationType
            = SshConnectionParameters::AuthenticationTypeTryAllPasswordBasedMethods;
    sshParams.setPassword(ui->lineEdit_3->text());
    //sshParams.setPort(m_ui->portSpinBox->value());
    sshParams.setPort(22);
    sshParams.timeout = 10;
    m_connection = new SshConnection(sshParams);
    connect(m_connection, &SshConnection::connected, this, &MainWindow::handleConnected);
    connect(m_connection, &SshConnection::error, this, &MainWindow::handleError);
    connect(m_connection, &SshConnection::disconnected, this, &MainWindow::handleDisconnected);
    std::cout << "Connecting to host '"
        << qPrintable(sshParams.host()) << "'..." << std::endl;
    m_state = Connecting;
    m_connection->connectToHost();
}

void MainWindow::handleConnected()
{
    if (m_state != Connecting) {
        std::cerr << "Unexpected state " << m_state << " in function "
            << Q_FUNC_INFO << "." << std::endl;
        earlyDisconnectFromHost();
    } else {
        std::cout << "Connected. Initializing SFTP channel..." << std::endl;
        m_channel = m_connection->createSftpChannel();
        connect(m_channel.data(), &SftpChannel::initialized, this,
           &MainWindow::handleChannelInitialized);
        connect(m_channel.data(), &SftpChannel::channelError, this,
            &MainWindow::handleChannelInitializationFailure);
        connect(m_channel.data(), &SftpChannel::finished,
            this, &MainWindow::handleSftpJobFinished);
        connect(m_channel.data(),
            &SftpChannel::fileInfoAvailable,
            this, &MainWindow::handleFileInfo);
        connect(m_channel.data(), &SftpChannel::closed, this,
            &MainWindow::handleChannelClosed);
        m_state = InitializingChannel;
        m_channel->initialize();
    }
}

void MainWindow::handleDisconnected()
{
    if (m_state != Disconnecting) {
        std::cerr << "Unexpected state " << m_state << " in function "
            << Q_FUNC_INFO << std::endl;
        m_error = true;
    } else {
        std::cout << "Connection closed." << std::endl;
    }

    std::cout << std::endl;
    QMessageBox::critical(this, "Error", " SSH Connection Disconnected  ");
    //QCoreApplication::exit(m_error ? EXIT_FAILURE : EXIT_SUCCESS);
    when_disconnected();
}

void MainWindow::handleError()
{
    std::cerr << "Encountered SSH error: "
        << qPrintable(m_connection->errorString()) << "." << std::endl;
    m_error = true;
    m_state = Disconnecting;
    //QCoreApplication::exit(EXIT_FAILURE);
    QMessageBox::critical(this, "Error", " Error on Creating ssh connection, Please check Hostname, username, password  ");
}

void MainWindow::handleChannelInitialized()
{
    if (m_state != InitializingChannel) {
        std::cerr << "Unexpected state " << m_state << "in function "
            << Q_FUNC_INFO << "." << std::endl;
        earlyDisconnectFromHost();
        return;
    }
    ui->Connect_Button->setStyleSheet("QPushButton { background-color: green; }\n");
    ui->Disconnect_Button->setEnabled(true);
    ui->Connect_Button->setEnabled(false);
    ui->Load_Button->setEnabled(true);
    ui->Upload_Button->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
  /*
    std::cout << "Creating " << m_parameters.smallFileCount
        << " files of 1 KB each ..." << std::endl;
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    qsrand(QDateTime::currentDateTime().toTime_t());
#endif
    for (int i = 0; i < m_parameters.smallFileCount; ++i) {
        const QString fileName
            = QLatin1String("sftptestfile") + QString::number(i + 1);
        const FilePtr file(new QFile(QDir::tempPath() + QLatin1Char('/')
            + fileName));
        bool success = true;
        if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate))
            success = false;
        if (success) {
            int content[1024/sizeof(int)];
            for (size_t j = 0; j < sizeof content / sizeof content[0]; ++j)
#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0))
                content[j] = QRandomGenerator::system()->generate();
#else
                content[j] = qrand();
#endif
            file->write(reinterpret_cast<char *>(content), sizeof content);
            file->close();
        }
        success = success && file->error() == QFile::NoError;
        if (!success) {
            std::cerr << "Error creating local file "
                << qPrintable(file->fileName()) << "." << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        m_localSmallFiles << file;
    }



    std::cout << "Files created. Now uploading..." << std::endl;
    foreach (const FilePtr &file, m_localSmallFiles) {
        const QString localFilePath = file->fileName();
        const QString remoteFp
            = remoteFilePath(QFileInfo(localFilePath).fileName());
        const SftpJobId uploadJob = m_channel->uploadFile(file->fileName(),
            remoteFp, SftpOverwriteExisting);
        if (uploadJob == SftpInvalidJob) {
            std::cerr << "Error uploading local file "
                << qPrintable(localFilePath) << " to remote file "
                << qPrintable(remoteFp) << "." << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        m_smallFilesUploadJobs.insert(uploadJob, remoteFp);
    }
    m_state = UploadingSmall;
    */
}

void MainWindow::handleChannelInitializationFailure(const QString &reason)
{
    std::cerr << "Could not initialize SFTP channel: " << qPrintable(reason)
        << "." << std::endl;
    earlyDisconnectFromHost();
}

void MainWindow::handleChannelClosed()
{
    if (m_state != ChannelClosing) {
        std::cerr << "Unexpected state " << m_state << " in function "
            << Q_FUNC_INFO << "." << std::endl;
    } else {
        std::cout << "SFTP channel closed. Now disconnecting..." << std::endl;
    }
    m_state = Disconnecting;
    m_connection->disconnectFromHost();
}

void MainWindow::handleSftpJobFinished(SftpJobId job, const SftpError errorType, const QString &error)
{
    Q_UNUSED(errorType);
    /*
    switch (m_state) {
    case UploadingSmall:
        if (!handleJobFinished(job, m_smallFilesUploadJobs, error, "uploading"))
            return;
        if (m_smallFilesUploadJobs.isEmpty()) {
            std::cout << "Uploading finished, now downloading for comparison..."
                << std::endl;
            foreach (const FilePtr &file, m_localSmallFiles) {
                const QString localFilePath = file->fileName();
                const QString remoteFp
                    = remoteFilePath(QFileInfo(localFilePath).fileName());
                const QString downloadFilePath = cmpFileName(localFilePath);
                const SftpJobId downloadJob = m_channel->downloadFile(remoteFp,
                    downloadFilePath, SftpOverwriteExisting);
                if (downloadJob == SftpInvalidJob) {
                    std::cerr << "Error downloading remote file "
                        << qPrintable(remoteFp) << " to local file "
                        << qPrintable(downloadFilePath) << "." << std::endl;
                    earlyDisconnectFromHost();
                    return;
                }
                m_smallFilesDownloadJobs.insert(downloadJob, remoteFp);
            }
            m_state = DownloadingSmall;
        }
        break;
    case DownloadingSmall:
        if (!handleJobFinished(job, m_smallFilesDownloadJobs, error, "downloading"))
            return;
        if (m_smallFilesDownloadJobs.isEmpty()) {
            std::cout << "Downloading finished, now comparing..." << std::endl;
            foreach (const FilePtr &ptr, m_localSmallFiles) {
                if (!ptr->open(QIODevice::ReadOnly)) {
                    std::cerr << "Error opening local file "
                        << qPrintable(ptr->fileName()) << "." << std::endl;
                    earlyDisconnectFromHost();
                    return;
                }
                const QString downloadedFilePath = cmpFileName(ptr->fileName());
                QFile downloadedFile(downloadedFilePath);
                if (!downloadedFile.open(QIODevice::ReadOnly)) {
                    std::cerr << "Error opening downloaded file "
                        << qPrintable(downloadedFilePath) << "." << std::endl;
                    earlyDisconnectFromHost();
                    return;
                }
                if (!compareFiles(ptr.data(), &downloadedFile))
                    return;
            }

            std::cout << "Comparisons successful, now removing files..."
                << std::endl;
            QList<QString> remoteFilePaths;
            foreach (const FilePtr &ptr, m_localSmallFiles) {
                const QString downloadedFilePath = cmpFileName(ptr->fileName());
                remoteFilePaths
                    << remoteFilePath(QFileInfo(ptr->fileName()).fileName());
                if (!ptr->remove()) {
                    std::cerr << "Error: Failed to remove local file '"
                        << qPrintable(ptr->fileName()) << "'." << std::endl;
                    earlyDisconnectFromHost();
                }
                if (!QFile::remove(downloadedFilePath)) {
                    std::cerr << "Error: Failed to remove downloaded file '"
                        << qPrintable(downloadedFilePath) << "'." << std::endl;
                    earlyDisconnectFromHost();
                }
            }
            m_localSmallFiles.clear();
            foreach (const QString &remoteFp, remoteFilePaths) {
                m_smallFilesRemovalJobs.insert(m_channel->removeFile(remoteFp),
                    remoteFp);
            }
            m_state = RemovingSmall;
        }
        break;
    case RemovingSmall:
        if (!handleJobFinished(job, m_smallFilesRemovalJobs, error, "removing"))
            return;
        if (m_smallFilesRemovalJobs.isEmpty()) {
            std::cout << "Small files successfully removed. "
                << "Now creating big file..." << std::endl;
            const QLatin1String bigFileName("sftpbigfile");
            m_localBigFile = FilePtr(new QFile(QDir::tempPath()
                + QLatin1Char('/') + bigFileName));
            bool success = m_localBigFile->open(QIODevice::WriteOnly);
            const int blockSize = 8192;
            const quint64 blockCount
                = static_cast<quint64>(m_parameters.bigFileSize)*1024*1024/blockSize;
            for (quint64 block = 0; block < blockCount; ++block) {
                int content[blockSize/sizeof(int)];
                for (size_t j = 0; j < sizeof content / sizeof content[0]; ++j) {
#if (QT_VERSION >= QT_VERSION_CHECK(5, 10, 0))
                    content[j] = QRandomGenerator::system()->generate();
#else
                    content[j] = qrand();
#endif
                }
                m_localBigFile->write(reinterpret_cast<char *>(content),
                    sizeof content);
            }
            m_localBigFile->close();
            success = success && m_localBigFile->error() == QFile::NoError;
            if (!success) {
                std::cerr << "Error trying to create big file '"
                    << qPrintable(m_localBigFile->fileName()) << "'."
                    << std::endl;
                earlyDisconnectFromHost();
                return;
            }

            std::cout << "Big file created. Now uploading ..." << std::endl;
            m_bigJobTimer.start();
            m_bigFileUploadJob
                = m_channel->uploadFile(m_localBigFile->fileName(),
                      remoteFilePath(bigFileName), SftpOverwriteExisting);
            if (m_bigFileUploadJob == SftpInvalidJob) {
                std::cerr << "Error uploading file '" << bigFileName.latin1()
                    << "'." << std::endl;
                earlyDisconnectFromHost();
                return;
            }
            m_state = UploadingBig;
        }
        break;
    case UploadingBig: {
        if (!handleBigJobFinished(job, m_bigFileUploadJob, error, "uploading"))
            return;
        const qint64 msecs = m_bigJobTimer.elapsed();
        std::cout << "Successfully uploaded big file. Took " << (msecs/1000)
            << " seconds for " << m_parameters.bigFileSize << " MB."
            << std::endl;
        const QString localFilePath = m_localBigFile->fileName();
        const QString downloadedFilePath = cmpFileName(localFilePath);
        const QString remoteFp
            = remoteFilePath(QFileInfo(localFilePath).fileName());
        std::cout << "Now downloading big file for comparison..." << std::endl;
        m_bigJobTimer.start();
        m_bigFileDownloadJob = m_channel->downloadFile(remoteFp,
            downloadedFilePath, SftpOverwriteExisting);
        if (m_bigFileDownloadJob == SftpInvalidJob) {
            std::cerr << "Error downloading remote file '"
                << qPrintable(remoteFp) << "' to local file '"
                << qPrintable(downloadedFilePath) << "'." << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        m_state = DownloadingBig;
        break;
    }
    case DownloadingBig: {
        if (!handleBigJobFinished(job, m_bigFileDownloadJob, error, "downloading"))
            return;
        const qint64 msecs = m_bigJobTimer.elapsed();
        std::cout << "Successfully downloaded big file. Took " << (msecs/1000)
            << " seconds for " << m_parameters.bigFileSize << " MB."
            << std::endl;
        std::cout << "Now comparing big files..." << std::endl;
        QFile downloadedFile(cmpFileName(m_localBigFile->fileName()));
        if (!downloadedFile.open(QIODevice::ReadOnly)) {
            std::cerr << "Error opening downloaded file '"
                << qPrintable(downloadedFile.fileName()) << "': "
                << qPrintable(downloadedFile.errorString()) << "." << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        if (!m_localBigFile->open(QIODevice::ReadOnly)) {
            std::cerr << "Error opening big file '"
                << qPrintable(m_localBigFile->fileName()) << "': "
                << qPrintable(m_localBigFile->errorString()) << "."
                << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        if (!compareFiles(m_localBigFile.data(), &downloadedFile))
            return;
        std::cout << "Comparison successful. Now removing big files..."
            << std::endl;
        if (!m_localBigFile->remove()) {
            std::cerr << "Error: Could not remove file '"
                << qPrintable(m_localBigFile->fileName()) << "'." << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        if (!downloadedFile.remove()) {
            std::cerr << "Error: Could not remove file '"
                << qPrintable(downloadedFile.fileName()) << "'." << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        const QString remoteFp
            = remoteFilePath(QFileInfo(m_localBigFile->fileName()).fileName());
        m_bigFileRemovalJob = m_channel->removeFile(remoteFp);
        m_state = RemovingBig;
        break;
    }
    case RemovingBig:
        if (!handleBigJobFinished(job, m_bigFileRemovalJob, error, "removing"))
            return;
        std::cout << "Big files successfully removed. "
            << "Now creating remote directory..." << std::endl;
        m_remoteDirPath = m_parameters.remotePath + QLatin1String("sftptest-") + QDateTime::currentDateTime().toString();
        m_mkdirJob = m_channel->createDirectory(m_remoteDirPath);
        m_state = CreatingDir;
        break;
    case CreatingDir:
        if (!handleJobFinished(job, m_mkdirJob, error, "creating remote directory"))
            return;
        std::cout << "Directory successfully created. Now checking directory attributes..."
            << std::endl;
        m_statDirJob = m_channel->statFile(m_remoteDirPath);
        m_state = CheckingDirAttributes;
        break;
    case CheckingDirAttributes: {
        if (!handleJobFinished(job, m_statDirJob, error, "checking directory attributes"))
            return;
        if (m_dirInfo.type != FileTypeDirectory) {
            std::cerr << "Error: Newly created directory has file type " << m_dirInfo.type
                << ", expected was " << FileTypeDirectory << "." << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        const QString fileName = QFileInfo(m_remoteDirPath).fileName();
        if (m_dirInfo.name != fileName) {
            std::cerr << "Error: Remote directory reports file name '"
                << qPrintable(m_dirInfo.name) << "', expected '" << qPrintable(fileName) << "'."
                << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        std::cout << "Directory attributes ok. Now checking directory contents..." << std::endl;
        m_lsDirJob = m_channel->listDirectory(m_remoteDirPath);
        m_state = CheckingDirContents;
        break;
    }
    case CheckingDirContents:
        if (!handleJobFinished(job, m_lsDirJob, error, "checking directory contents"))
            return;
        if (m_dirContents.count() != 2) {
            std::cerr << "Error: Remote directory has " << m_dirContents.count()
                << " entries, expected 2." << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        foreach (const SftpFileInfo &fi, m_dirContents) {
            if (fi.type != FileTypeDirectory) {
                std::cerr << "Error: Remote directory has entry of type " << fi.type
                    << ", expected " << FileTypeDirectory << "." << std::endl;
                earlyDisconnectFromHost();
                return;
            }
            if (fi.name != QLatin1String(".") && fi.name != QLatin1String("..")) {
                std::cerr << "Error: Remote directory has entry '" << qPrintable(fi.name)
                    << "', expected '.' or '..'." << std::endl;
                earlyDisconnectFromHost();
                return;
            }
        }
        if (m_dirContents.first().name == m_dirContents.last().name) {
            std::cerr << "Error: Remote directory has two entries of the same name." << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        std::cout << "Directory contents ok. Now removing directory..." << std::endl;
        m_rmDirJob = m_channel->removeDirectory(m_remoteDirPath);
        m_state = RemovingDir;
        break;
    case RemovingDir:
        if (!handleJobFinished(job, m_rmDirJob, error, "removing directory"))
            return;
        std::cout << "Directory successfully removed. Now closing the SFTP channel..." << std::endl;
        m_state = ChannelClosing;
        m_channel->closeChannel();
        break;
    case Disconnecting:
        break;
    default:
        if (!m_error) {
            std::cerr << "Unexpected state " << m_state << " in function "
                << Q_FUNC_INFO << "." << std::endl;
            earlyDisconnectFromHost();
        }
    }
    */
}

void MainWindow::handleFileInfo(SftpJobId job, const QList<SftpFileInfo> &fileInfoList)
{
    switch (m_state) {
    case CheckingDirAttributes: {
        static int count = 0;
        if (!checkJobId(job, m_statDirJob, "checking directory attributes"))
            return;
        if (++count > 1) {
            std::cerr << "Error: More than one reply for directory attributes check." << std::endl;
            earlyDisconnectFromHost();
            return;
        }
        m_dirInfo = fileInfoList.first();
        break;
    }
    case CheckingDirContents:
        if (!checkJobId(job, m_lsDirJob, "checking directory contents"))
            return;
        m_dirContents << fileInfoList;
        break;
    default:
        std::cerr << "Error: Unexpected file info in state " << m_state << "." << std::endl;
        //earlyDisconnectFromHost();
    }
}

void MainWindow::removeFile(const FilePtr &file, bool remoteToo)
{
    if (!file)
        return;
    const QString localFilePath = file->fileName();
    file->remove();
    QFile::remove(cmpFileName(localFilePath));
    if (remoteToo && m_channel
            && m_channel->state() == SftpChannel::Initialized)
        m_channel->removeFile(remoteFilePath(QFileInfo(localFilePath).fileName()));
}

QString MainWindow::cmpFileName(const QString &fileName) const
{
    return fileName + QLatin1String(".cmp");
}

QString MainWindow::remoteFilePath(const QString &localFileName) const
{
    return remotePath + localFileName + QLatin1String(".upload");
}

void MainWindow::earlyDisconnectFromHost()
{
    m_error = true;
    removeFiles(true);
    if (m_channel) {
        disconnect(m_channel.data(), nullptr, this, nullptr);
    }
    m_state = Disconnecting;
    m_connection->disconnectFromHost();
    when_disconnected();
}

bool MainWindow::checkJobId(SftpJobId job, SftpJobId expectedJob, const char *activity)
{
    if (job != expectedJob) {
        std::cerr << "Error " << activity << ": Expected job id " << expectedJob
           << ", got job id " << job << '.' << std::endl;
        earlyDisconnectFromHost();
        return false;
    }
    return true;
}

void MainWindow::removeFiles(bool remoteToo)
{
    foreach (const FilePtr &file, m_localSmallFiles)
        removeFile(file, remoteToo);
    removeFile(m_localBigFile, remoteToo);
}

bool MainWindow::handleJobFinished(SftpJobId job, JobMap &jobMap,
    const QString &error, const char *activity)
{
    JobMap::Iterator it = jobMap.find(job);
    if (it == jobMap.end()) {
        std::cerr << "Error: Unknown job " << job << "finished."
            << std::endl;
        earlyDisconnectFromHost();
        return false;
    }
    if (!error.isEmpty()) {
        std::cerr << "Error " << activity << " file " << qPrintable(it.value())
            << ": " << qPrintable(error) << "." << std::endl;
        earlyDisconnectFromHost();
        return false;
    }
    jobMap.erase(it);
    return true;
}

bool MainWindow::handleJobFinished(SftpJobId job, SftpJobId expectedJob, const QString &error,
    const char *activity)
{
    if (!checkJobId(job, expectedJob, activity))
        return false;
    if (!error.isEmpty()) {
        std::cerr << "Error " << activity << ": " << qPrintable(error) << "." << std::endl;
        earlyDisconnectFromHost();
        return false;
    }
    return true;
}

bool MainWindow::handleBigJobFinished(SftpJobId job, SftpJobId expectedJob,
    const QString &error, const char *activity)
{
    if (job != expectedJob) {
        std::cerr << "Error " << activity << " file '"
           << qPrintable(m_localBigFile->fileName())
           << "': Expected job id " << expectedJob
           << ", got job id " << job << '.' << std::endl;
        earlyDisconnectFromHost();
        return false;
    }
    if (!error.isEmpty()) {
        std::cerr << "Error " << activity << " file '"
            << qPrintable(m_localBigFile->fileName()) << "': "
            << qPrintable(error) << std::endl;
        earlyDisconnectFromHost();
        return false;
    }
    return true;
}

bool MainWindow::compareFiles(QFile *orig, QFile *copy)
{
    bool success = orig->size() == copy->size();
    qint64 bytesLeft = orig->size();
    orig->seek(0);
    while (success && bytesLeft > 0) {
        const qint64 bytesToRead = qMin(bytesLeft, Q_INT64_C(1024*1024));
        const QByteArray origBlock = orig->read(bytesToRead);
        const QByteArray copyBlock = copy->read(bytesToRead);
        if (origBlock.size() != bytesToRead || origBlock != copyBlock)
            success = false;
        bytesLeft -= bytesToRead;
    }
    orig->close();
    success = success && orig->error() == QFile::NoError
        && copy->error() == QFile::NoError;
    if (!success) {
        std::cerr << "Error: Original file '" << qPrintable(orig->fileName())
            << "'' differs from downloaded file '"
            << qPrintable(copy->fileName()) << "'." << std::endl;
        earlyDisconnectFromHost();
    }
    return success;
}



void MainWindow::on_Load_Button_clicked()
{
     QString remoteFp ;
     QString temp_filename;
     QString lastUsedDirectory = settings->value(DEFAULT_DIRECTORY_KEY).toString();

     remoteFp = ui->lineEdit_7->text();
     temp_filename ="tempfile.txt";

     if (remoteFp.isEmpty()){
         QMessageBox::warning(this, "Warning", "remote File to Edit path is Empty " );
         return;
     }

          QDir dir;
          if(!dir.exists("temp")){
              dir.mkdir("temp");
          }
          dir="temp";
          QString temp_path = dir.filePath(temp_filename);

          //qDebug() << "temp_path :: "<< temp_path   ;
          //QFile temp_file;
          //temp_file.setFileName(temp_path);

          //qDebug() << "QDir::currentPath() :: "<< QDir::currentPath()  ;

          QString total = QString(QDir::currentPath());

          //qDebug() << "total  :: "<< total  ;
          QString space{"/"};
          QString downloadFilePath ;
          downloadFilePath = total + space+ temp_path;

          const SftpJobId downloadJob = m_channel->downloadFile(remoteFp,
              downloadFilePath, SftpOverwriteExisting);
          if (downloadJob == SftpInvalidJob) {
              std::cerr << "Error downloading remote file "
                  << qPrintable(remoteFp) << " to local file "
                  << qPrintable(downloadFilePath) << "." << std::endl;
              std::cout << "Load button fail "<< std::endl;
              earlyDisconnectFromHost();
              return;
          }

    openedFilePath= downloadFilePath;
      /*
     if (lastUsedDirectory.isEmpty())
     {
         openedFilePath = QFileDialog::getOpenFileName(this, tr("Open"), DEFAULT_DIRECTORY);
     }
     else
     {
         openedFilePath = QFileDialog::getOpenFileName(this, tr("Open"), lastUsedDirectory);
     }
 */
     // Don't do anything if the user hit Cancel
     //if (openedFilePath.isNull())
     //{
     //    return;
     //}

     // Update the recently used directory
     QDir currentDirectory;
     settings->setValue(DEFAULT_DIRECTORY_KEY, currentDirectory.absoluteFilePath(openedFilePath));

     QMessageBox::information(this, "Info", "Remote File : "+ remoteFp +  "  Downloaded Succusfully to " +openedFilePath );
    on_Edit_Button_clicked();
}

void MainWindow::on_Upload_Button_clicked()
{
    QString UploadFilePath = editor->getCurrentFilePath();
    QString UploadFileName= editor->getFileName();

    qDebug() << "editor File path :: "<< UploadFilePath   ;
    qDebug() << "editor Filename :: "<< UploadFileName  ;

    if (UploadFilePath.isEmpty()){
        QMessageBox::warning(this, "Warning", "Upload File path in Local machine is Empty " );
        return;
    }

    QString remoteFp= ui->lineEdit_7->text();

    if (remoteFp.isEmpty()){
        QMessageBox::warning(this, "Warning", "Remote Upload File path is Empty " );
        return;
    }

    const QString localFilePath = UploadFilePath;
    const SftpJobId uploadJob = m_channel->uploadFile(UploadFilePath,
        remoteFp, SftpOverwriteExisting);
    if (uploadJob == SftpInvalidJob) {
        std::cerr << "Error uploading local file "
            << qPrintable(localFilePath) << " to remote file "
            << qPrintable(remoteFp) << "." << std::endl;
        earlyDisconnectFromHost();
        return;
    }
    QMessageBox::information(this, "Info", "Upload ::  File  "+ remoteFp + "  Uploaded succusfully" );

}

void MainWindow::on_Edit_Button_clicked()
{
    // Used to switch to a new tab if there's already an open doc
    bool openInCurrentTab = editor->isUntitled() && !editor->isUnsaved();

    // Attempt to create a file descriptor for the file at the given path
    QFile file(openedFilePath);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());

        return;
    }

    // Read the file contents into the editor and close the file descriptor
    QTextStream in(&file);
    QString documentContents = in.readAll();

    if (!openInCurrentTab)
    {
        tabbedEditor->add(new Editor());
    }
    editor->setCurrentFilePath(openedFilePath);
    editor->setPlainText(documentContents);
    file.close();

    editor->setModifiedState(false);
    updateTabAndWindowTitle();
    setLanguageFromExtension();
}

void MainWindow::on_Disconnect_Button_clicked()
{
    m_state = Disconnecting;
    QMessageBox::critical(this, "Error", " SSH Connection Disconnected  ");
    ui->Connect_Button->setStyleSheet("QPushButton { background-color: red; }\n");
    m_connection->disconnectFromHost();
    ui->Disconnect_Button->setEnabled(false);
    ui->Connect_Button->setEnabled(true);
    ui->Load_Button->setEnabled(false);
    ui->Upload_Button->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

void MainWindow::when_disconnected(){
    ui->Connect_Button->setStyleSheet("QPushButton { background-color: red; }\n");
    ui->Disconnect_Button->setEnabled(false);
    ui->Connect_Button->setEnabled(true);
    ui->Load_Button->setEnabled(false);
    ui->Upload_Button->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}
void MainWindow::on_comboBox_4_currentIndexChanged(int index)
{
    QString Local="Local";
    QString Remote="Remote";

     int check_Local = QString::compare(Local, ui->comboBox->currentText(), Qt::CaseInsensitive);
     int check_Remote = QString::compare(Remote, ui->comboBox->currentText(), Qt::CaseInsensitive);

    if(index ==0 ){
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget_2->setCurrentIndex(0);
    }else if (index ==1 ){
        if(check_Local ==0){
            ui->stackedWidget->setCurrentIndex(1);
            ui->stackedWidget_2->setCurrentIndex(0);
        }else if (check_Remote ==0) {
            ui->stackedWidget->setCurrentIndex(2);
            ui->stackedWidget_2->setCurrentIndex(1);
        }else {

        }
    }else if (index ==2 ){
        if(check_Local ==0){
            ui->stackedWidget->setCurrentIndex(0);
            ui->stackedWidget_2->setCurrentIndex(0);
        }else if (check_Remote ==0) {
            ui->stackedWidget->setCurrentIndex(2);
            ui->stackedWidget_2->setCurrentIndex(2);
        }else {

        }
    }else if (index ==3 ){
        if(check_Local ==0){
            ui->stackedWidget->setCurrentIndex(0);
            ui->stackedWidget_2->setCurrentIndex(0);
        }else if (check_Remote ==0) {
            ui->stackedWidget->setCurrentIndex(2);
            ui->stackedWidget_2->setCurrentIndex(3);
        }else {

        }
    }
}

void MainWindow::on_pushButton_2_clicked()  //DOWNLOAD
{
    QString remote_download_file_path=ui->lineEdit_4->text();

    if (remote_download_file_path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", " Remote file path to Download is Empty ");

        return;
    }

    //qDebug() << "remote_download_file_path :: "<< remote_download_file_path   ;

    QString file_save_name;
    QString file_save_path;
    QString file_save_dir;
    QString slash{"/"};

    file_save_name=ui->lineEdit_6->text();

    if (file_save_name.isEmpty())
    {
        QMessageBox::warning(this, "Warning", " Target File name to Save is Empty ");

        return;
    }

   //qDebug() << "file_save_name :: "<< file_save_name   ;

    file_save_dir = QFileDialog::getExistingDirectory(this, tr("Select Location to Save Remote File "), DEFAULT_DIRECTORY);

    // Don't do anything if the user hit Cancel
    if (file_save_dir.isNull())
    {
        QMessageBox::warning(this, "Warning", " Remote file Save path is Empty ");
        return;
    }

    //qDebug() << "file_save_dir :: "<< file_save_dir   ;

    file_save_path = file_save_dir + slash + file_save_name;

    //qDebug() << "file_save_path :: "<< file_save_path   ;

    const SftpJobId chech_file_job = m_channel->statFile(remote_download_file_path);
    if (chech_file_job == SftpInvalidJob) {
        qDebug() << "remote file path not exist  :: "   ;
        std::cerr << "Error downloading remote file "
            << qPrintable(remote_download_file_path) << " to Local Path "
            << qPrintable(file_save_path) << "." << std::endl;
        earlyDisconnectFromHost();
        return;
    }

    const SftpJobId downloadJob = m_channel->downloadFile(remote_download_file_path,
        file_save_path, SftpOverwriteExisting);
    if (downloadJob == SftpInvalidJob) {
        std::cerr << "Error downloading remote file "
            << qPrintable(remote_download_file_path) << " to Local Path "
            << qPrintable(file_save_path) << "." << std::endl;
        earlyDisconnectFromHost();
        return;
    }
    QMessageBox::information(this, "Info", "Download ::  File  "+ remote_download_file_path + "  Downloaded succusfully" );
}

void MainWindow::on_pushButton_3_clicked()  ///UPLOAD
{
    QString remote_upload_path=ui->lineEdit_5->text();

    if (remote_upload_path.isEmpty())
    {
        QMessageBox::warning(this, "Warning", " Remote Upload Path is Empty ");

        return;
    }

    QString local_file_path;

    local_file_path = QFileDialog::getOpenFileName(this, tr("Select File to Upload"), DEFAULT_DIRECTORY);

    // Don't do anything if the user hit Cancel
    if (local_file_path.isNull())
    {
        QMessageBox::warning(this, "Warning", " File not Selected to upload ");
        return;
    }

    qDebug() << "remote_upload_path :: "<< remote_upload_path   ;
    qDebug() << "local_file_path :: "<< local_file_path   ;


    const SftpJobId uploadJob = m_channel->uploadFile(local_file_path,
        remote_upload_path, SftpOverwriteExisting);
    if (uploadJob == SftpInvalidJob) {
        std::cerr << "Error uploading local file "
            << qPrintable(local_file_path) << " to remote file "
            << qPrintable(remote_upload_path) << "." << std::endl;
        earlyDisconnectFromHost();
        return;
    }
    QMessageBox::information(this, "Info", "Upload ::  File  "+ remote_upload_path + "  Uploaded succusfully" );
}
