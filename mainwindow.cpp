#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(1);

    QStringList listFileName = QFileDialog::getOpenFileNames(0,tr("Import Data"),"D:\\PSM\\user_data");
    if(listFileName.size() < 0)
        return;
    ui->tableWidget->setRowCount(listFileName.size());
    for(int listfilei=0;listfilei<listFileName.size();++listfilei)
    {
        QFile file(listFileName.at(listfilei));
        int nSize = file.size() / sizeof(double);
        double * pdData = new double[nSize+1];
        memset(pdData, 0, nSize+1);
        pdData[0] = nSize+1;

        if (file.open(QFile::ReadOnly))
        {
            file.read(reinterpret_cast<char *>(pdData+1), nSize*sizeof(double));
            file.close();
        }
        if(ui->tableWidget->columnCount() < pdData[0])
            ui->tableWidget->setColumnCount(pdData[0]);
        ui->tableWidget->setItem(listfilei,0,new QTableWidgetItem(listFileName.at(listfilei)));

        for(int i=1;i<pdData[0];++i)
        {
            ui->tableWidget->setItem(listfilei,i,new QTableWidgetItem(QString("%1").arg(pdData[i],15,'d',1)));
        }
    }


}
