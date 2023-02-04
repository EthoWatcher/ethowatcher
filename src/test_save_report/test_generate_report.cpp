#include "test_generate_report.h"
#include "ui_test_generate_report.h"
#include <QDebug>
test_generate_report::test_generate_report(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::test_generate_report)
{
    ui->setupUi(this);
}

test_generate_report::~test_generate_report()
{
    delete ui;
}

static void gera_relatorio_python(QString path)
{
    //    https://forum.qt.io/topic/115682/how-to-get-the-path-of-a-c-file-which-is-added-as-the-resource-file/12

    //C:\Users\User\AppData\Local\Temp o arquivo temporario fica aqui
    //gerando relatorio
    qDebug() << path;
    QString filename = path; // + ".txt";
//    QFile file(filename);
//    if (file.open(QIODevice::ReadWrite)) {
////        QTextStream stream(&file);
////        stream << text;
//        file.write(text.toUtf8());
//    }

    //fazendo outras coisas
    std::string path_inside_qrc = "://writer.exe";
//    std::string path_inside_qrc = "C:\\doutorado\\software\\Terminando o Ethowatcher\\ethowatcher\\src\\report_writer\\dist\\writer.exe";
    std::unique_ptr<QTemporaryFile> temporary_file;

    temporary_file.reset(
        QTemporaryFile::createNativeFile(QString::fromStdString(path_inside_qrc))
     );
    std::string file_name = temporary_file->fileName().toUtf8().constData();

//    QObject *parent;
    qDebug() << "temporary" << QString::fromStdString(file_name);
    QString program = temporary_file->fileName();
    QStringList arguments;
    QString newname = program + ".exe";

    qDebug() << newname;
//    QByteArray double_quotes = '"';
    QFile::copy(program, newname);
    QString arg = "\"\"\"" + path+"\"\"\"";//"\""+path+"\"";
    qDebug().noquote() << "new" << arg;

//    arg.replace("/", "\\\\");

    arguments << arg; //<< text;




//     QString Cmd = "cmd";
//    QProcess::startDetached(program, arguments );
    QObject *parent = nullptr;

    QProcess *myProcess = new QProcess(parent);
    myProcess->start( newname, arguments);
//    myProcess->waitForFinished(-1);


    if(myProcess->waitForStarted(5000))
    {
        QByteArray out_data = myProcess->readAllStandardOutput();
        QString out_string(out_data);
        qDebug() << out_string.toStdString().c_str();
    }
    else
    {
        qDebug() << "myProcess did not start in time";
    }
     myProcess->waitForFinished();


//    temporary_file.reset();


//    if (QFile::exists(newname))
//    {
//        QFile::remove(newname);

//    }

}


//static void gravar_csv_ls_cell(QString csv_path, QList< QList<Cell> > t_saida){
//    qDebug() << "csv_ls_cell path_ to write" << csv_path;

////        QFile outGravador_csv;
////        outGravador_csv.setFileName(csv_path);
//        QFile file(csv_path);
//        if (file.open(QIODevice::ReadWrite)) {
//            QTextStream stream(&file);
//            for (auto list_celulas : t_saida) {
//                for (auto celula : list_celulas) {
//                    if (celula.r_number){
//                        stream << celula.number << ";" << celula.content.toDouble() << ";" << celula.r_number << "\n";
//                    }else{
//                        stream << celula.number << ";" << celula.content << ";" << celula.r_number << "\n";
//                    }

////                    stream << "something" << "";
//                }
//            }

//        gera_relatorio_python(csv_path);
//        };



////        outGravador_csv.
////          QXlsx::Document xlsx;

////          for (auto list_celulas : t_saida) {
////            for (auto celula : list_celulas) {
////              if (celula.r_number) {
////                xlsx.write(celula.number, celula.content.toDouble());
////              } else {
////                xlsx.write(celula.number, celula.content);
////              }
////            }
////          }
////          xlsx.saveAs(csv_path);
//};


void test_generate_report::on_pushButton_clicked()
{
    auto nomeGravarProcesImagem = QFileDialog::getOpenFileName(
                this,
                tr("Open File")
               );
    gera_relatorio_python(nomeGravarProcesImagem);
}

