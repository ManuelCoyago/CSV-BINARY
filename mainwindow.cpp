#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//csv a binario
void MainWindow::on_pushButton_released()
{

    // Mostrar el diálogo para seleccionar un archivo CSV
    QString csvFilePath = QFileDialog::getOpenFileName(this, "Seleccionar archivo CSV", QString(), "Archivos CSV (*.csv)");

    // Verificar si se seleccionó un archivo
    if (!csvFilePath.isEmpty()) {
        // Abrir el archivo CSV para lectura
        QFile csvFile(csvFilePath);
        if (csvFile.open(QIODevice::ReadOnly)) {
            // Leer los datos del archivo CSV
            QTextStream csvStream(&csvFile);
            QStringList csvData;
            while (!csvStream.atEnd()) {
                QString line = csvStream.readLine();
                csvData.append(line);
            }
            csvFile.close();

            // Convertir los datos a binario
            QByteArray binaryData;
            for (const QString& line : csvData) {
                binaryData.append(line.toUtf8());
                binaryData.append('\n');
            }

            // Guardar el archivo binario
            QString binFilePath = QFileDialog::getSaveFileName(this, "Guardar archivo binario", QString(), "Archivos binarios (*.bin)");
            if (!binFilePath.isEmpty()) {
                QFile binFile(binFilePath);
                if (binFile.open(QIODevice::WriteOnly)) {
                    binFile.write(binaryData);
                    binFile.close();
                    qDebug() << "Archivo binario guardado correctamente.";
                } else {
                    qDebug() << "Error al guardar el archivo binario.";
                }
            }
        } else {
            qDebug() << "Error al abrir el archivo CSV.";
        }
    }
}
//binario a csv
void MainWindow::on_pushButton_2_released()
{
    // Mostrar el diálogo para seleccionar un archivo binario
    QString binFilePath = QFileDialog::getOpenFileName(this, "Seleccionar archivo binario", QString(), "Archivos binarios (*.bin)");

    // Verificar si se seleccionó un archivo
    if (!binFilePath.isEmpty()) {
        // Abrir el archivo binario para lectura
        QFile binFile(binFilePath);
        if (binFile.open(QIODevice::ReadOnly)) {
            // Leer los datos del archivo binario
            QByteArray binaryData = binFile.readAll();
            binFile.close();

            // Convertir los datos binarios a CSV
            QStringList csvData;
            QString currentLine;
            for (char ch : binaryData) {
                if (ch == '\n') {
                    csvData.append(currentLine);
                    currentLine.clear();
                } else {
                    currentLine.append(ch);
                }
            }
            if (!currentLine.isEmpty()) {
                csvData.append(currentLine);
            }

            // Guardar el archivo CSV
            QString csvFilePath = QFileDialog::getSaveFileName(this, "Guardar archivo CSV", QString(), "Archivos CSV (*.csv)");
            if (!csvFilePath.isEmpty()) {
                QFile csvFile(csvFilePath);
                if (csvFile.open(QIODevice::WriteOnly)) {
                    QTextStream csvStream(&csvFile);
                    for (const QString& line : csvData) {
                        csvStream << line << '\n';
                    }
                    csvFile.close();
                    qDebug() << "Archivo CSV guardado correctamente.";
                } else {
                    qDebug() << "Error al guardar el archivo CSV.";
                }
            }
        } else {
            qDebug() << "Error al abrir el archivo binario.";
        }
    }
}

