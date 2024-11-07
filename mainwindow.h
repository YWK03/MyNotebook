#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

    void on_actionLooking_triggered();

    void on_actionReplacement_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAnther_triggered();

    void on_TextEdit_textChanged();

    void on_actionCut_triggered();

    void on_actionRevocation_triggered();

    void on_actionCopy_triggered();

    void on_actionSticking_triggered();

    void on_actionRestoration_triggered();

    void on_TextEdit_copyAvailable(bool b);

    void on_TextEdit_redoAvailable(bool b);

    void on_TextEdit_undoAvailable(bool b);

    void on_actionColor_triggered();

    void on_actionEditorBackgroundColor_triggered();

    void on_actionBackgroundColor_triggered();

    void on_actionWrap_triggered();

    void on_actionFont_triggered();

private:
    Ui::MainWindow *ui;

    QLabel statusCursorLabel;
    QLabel statusLabel;

    QString filePath;

    bool textChanged;

    bool useEditConfirmed();
};
#endif // MAINWINDOW_H
