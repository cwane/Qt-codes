#include "mainwindow.h"

#include <QApplication>

//int main( int argc, char *argv[] )
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
//}

#include <QtSql>
#include <QtWidgets>

int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );

    // Set up database
    QString dbName( "C:/database/database files/sqlite.db" );
//    QFile::remove( dbName ); // delete sqlite file if it exists from a previous run
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( dbName );
    db.open();

    // Generate an image (in this case a screenshot) and store it in a QByteArray
//    QScreen *screen = app.primaryScreen();
//    QPixmap inPixmap = screen->grabWindow( 0 );

    QPixmap *inPixmap   = new QPixmap("C:/Users/Dell/Pictures/edc.png");
//     QPixmap qImage2 = qImage2->scaled(this->width(),this->height(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //    QPixmap inPixmap;
    QByteArray inByteArray;
   QBuffer inBuffer( &inByteArray );
  inBuffer.open( QIODevice::WriteOnly );
  inPixmap->save( &inBuffer, "PNG" ); // write inPixmap into inByteArray in PNG format

    // Alternatively, load an image file directly into a QByteArray
//     QFile file("screenshot.png");
//     if (!file.open(QIODevice::ReadOnly))
//         return 0;
//     QByteArray inByteArray = file.readAll();

    // Insert image bytes into the database
    // Note: make sure to wrap the :placeholder in parenthesis
    QSqlQuery query= QSqlQuery( db );
//    query.exec( "CREATE TABLE IF NOT EXISTS imgTable ( filename TEXT, imagedata BLOB )" );

    query.prepare( "INSERT INTO imgTable (filename, imagedata) VALUES ('codee.png', :imageData)" );
    query.bindValue( ":imageData", inByteArray );
    if( !query.exec() )
        qDebug() << "Error inserting image into table:\n" << query.lastError();



    // Get image data back from database
    if( !query.exec( "SELECT  imagedata from imgTable" ))
        qDebug() << "Error getting image from table:\n" << query.lastError();
    query.first();
    QByteArray outByteArray = query.value( 0 ).toByteArray();
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray );
    db.close();

    // Display image
    QLabel myLabel;
    myLabel.setPixmap( outPixmap );
    myLabel.show();

    return app.exec();
}



