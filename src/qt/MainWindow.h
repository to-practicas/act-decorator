#pragma once
#include <QMainWindow>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPlainTextEdit;
class QTextEdit;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void refreshPreview();
    void onSave();
    void onClear();

private:
    QLineEdit* titleEdit_;
    QPlainTextEdit* bodyEdit_;
    QLineEdit* authorEdit_;
    QLineEdit* signerEdit_;
    QCheckBox* dateCheck_;
    QCheckBox* authorCheck_;
    QCheckBox* signatureCheck_;
    QLabel* chainLabel_;
    QTextEdit* preview_;
};
