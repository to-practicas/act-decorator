#include "MainWindow.h"

#include <QCheckBox>
#include <QFile>
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStatusBar>
#include <QTextEdit>
#include <QTextStream>
#include <QVBoxLayout>
#include <QWidget>

#include "../core/ReportComposer.h"

// Ventana principal: formulario de datos, selección de decoradores,
// vista previa en tiempo real y guardado del reporte en un archivo .txt.
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      titleEdit_(new QLineEdit(this)),
      bodyEdit_(new QPlainTextEdit(this)),
      authorEdit_(new QLineEdit(this)),
      signerEdit_(new QLineEdit(this)),
      dateCheck_(new QCheckBox(tr("Fecha"), this)),
      authorCheck_(new QCheckBox(tr("Autor"), this)),
      signatureCheck_(new QCheckBox(tr("Firma"), this)),
      chainLabel_(new QLabel(this)),
      preview_(new QTextEdit(this)) {
    // Configuración general de la ventana.
    setWindowTitle(tr("Reportes con Decorator - Grupo 5"));
    resize(720, 620);

    // Textos de ayuda para orientar al usuario al introducir los datos.
    titleEdit_->setPlaceholderText(tr("Título del reporte"));
    bodyEdit_->setPlaceholderText(tr("Contenido del reporte"));
    authorEdit_->setPlaceholderText(tr("Nombre del autor"));
    signerEdit_->setPlaceholderText(tr("Nombre del firmante"));

    // Los tres decoradores se activan por defecto.
    dateCheck_->setChecked(true);
    authorCheck_->setChecked(true);
    signatureCheck_->setChecked(true);

    // Formulario con los datos básicos del reporte.
    auto* centralWidget = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(centralWidget);

    auto* formLayout = new QFormLayout();
    formLayout->addRow(tr("Título:"), titleEdit_);
    formLayout->addRow(tr("Contenido:"), bodyEdit_);
    formLayout->addRow(tr("Autor:"), authorEdit_);
    formLayout->addRow(tr("Firmante:"), signerEdit_);
    mainLayout->addLayout(formLayout);

    // Casillas que controlan qué decoradores se aplican al reporte.
    auto* decoratorsBox = new QGroupBox(tr("Decoradores"), centralWidget);
    auto* decoratorsLayout = new QHBoxLayout(decoratorsBox);
    decoratorsLayout->addWidget(dateCheck_);
    decoratorsLayout->addWidget(authorCheck_);
    decoratorsLayout->addWidget(signatureCheck_);
    decoratorsLayout->addStretch();
    mainLayout->addWidget(decoratorsBox);

    // Etiqueta que muestra la cadena de decoradores actualmente aplicada.
    chainLabel_->setWordWrap(true);
    mainLayout->addWidget(chainLabel_);

    // Vista previa de solo lectura del reporte generado.
    preview_->setReadOnly(true);
    mainLayout->addWidget(preview_, 1);

    // Botones de acción: guardar el reporte o limpiar el formulario.
    auto* saveButton = new QPushButton(tr("Guardar como .txt"), centralWidget);
    auto* clearButton = new QPushButton(tr("Limpiar"), centralWidget);

    auto* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(clearButton);
    mainLayout->addLayout(buttonsLayout);

    setCentralWidget(centralWidget);

    // Cada cambio en un campo o casilla reconstruye la vista previa.
    connect(titleEdit_, &QLineEdit::textChanged, this, &MainWindow::refreshPreview);
    connect(bodyEdit_, &QPlainTextEdit::textChanged, this, &MainWindow::refreshPreview);
    connect(authorEdit_, &QLineEdit::textChanged, this, &MainWindow::refreshPreview);
    connect(signerEdit_, &QLineEdit::textChanged, this, &MainWindow::refreshPreview);
    connect(dateCheck_, &QCheckBox::toggled, this, &MainWindow::refreshPreview);
    connect(authorCheck_, &QCheckBox::toggled, this, &MainWindow::refreshPreview);
    connect(signatureCheck_, &QCheckBox::toggled, this, &MainWindow::refreshPreview);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSave);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClear);

    // Se muestra una primera vista previa al abrir la ventana.
    statusBar()->showMessage(tr("Listo"));
    refreshPreview();
}

void MainWindow::refreshPreview() {
    // 1. Se recogen los datos introducidos por el usuario.
    ReportOptions options;
    options.title = titleEdit_->text().toStdString();
    options.body = bodyEdit_->toPlainText().toStdString();
    options.author = authorEdit_->text().toStdString();
    options.signer = signerEdit_->text().toStdString();
    options.withDate = dateCheck_->isChecked();
    options.withAuthor = authorCheck_->isChecked();
    options.withSignature = signatureCheck_->isChecked();

    // 2. El compositor arma la cadena: reporte básico + decoradores elegidos.
    const auto report = composeReport(options);

    // 3. Se muestran la cadena aplicada y el reporte resultante.
    chainLabel_->setText(tr("Cadena de decoradores: %1")
                             .arg(QString::fromStdString(report->description())));
    preview_->setPlainText(QString::fromStdString(report->generate()));
}

void MainWindow::onSave() {
    // Se solicita al usuario la ruta y el nombre del archivo .txt.
    const QString fileName = QFileDialog::getSaveFileName(
        this, tr("Guardar reporte"), QStringLiteral("reporte.txt"),
        tr("Archivos de texto (*.txt);;Todos los archivos (*)"));
    // Si el usuario cancela el diálogo, no se hace nada.
    if (fileName.isEmpty()) {
        return;
    }

    // Se abre el archivo para escritura y se avisa si no es posible.
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(
            this, tr("Error al guardar"),
            tr("No se pudo abrir el archivo para escritura:\n%1").arg(fileName));
        return;
    }

    QTextStream output(&file);
    // Se escribe exactamente el contenido que se muestra en la vista previa.
    output << preview_->toPlainText();
    output.flush();

    if (file.error() != QFileDevice::NoError) {
        QMessageBox::critical(
            this, tr("Error al guardar"),
            tr("No se pudo escribir el archivo:\n%1").arg(fileName));
        return;
    }

    file.close();
    // Confirmación del guardado en la barra de estado.
    statusBar()->showMessage(tr("Reporte guardado en %1").arg(fileName), 5000);
}

void MainWindow::onClear() {
    // Se vacían los cuatro campos; las conexiones refrescan la vista previa.
    titleEdit_->clear();
    bodyEdit_->clear();
    authorEdit_->clear();
    signerEdit_->clear();
}
