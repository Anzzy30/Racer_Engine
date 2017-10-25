#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>
#include <QDate>

#ifndef QT_NO_OPENGL
    #include <Window/openglwindow.h>
#endif

int main(int argc, char *argv[])
{
    qsrand(QDateTime::currentDateTime().toTime_t());
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Racer Engine");
    app.setApplicationVersion("0.1");

    #ifdef QT_NO_DEBUG
      // release mode code
    #else
        QDebug::setVerbosity(1);

        if (QDebug.verbosity() >= 0)
        {
            qDebug() << "[0] Main.cpp => main();";
        }

        if (QDebug.verbosity() >= 1)
        {
            qDebug() << "[1] Advanced debugging";
        }
        //qInfo() << "C++ Style Info Message";
        //qWarning() << "C++ Style Warning Message";
        //qCritical() << "C++ Style Critical Error Message";
        // Celui là coupe l'exécution
        //qFatal( "C Style Fatal Error Message" );
    #endif



    #ifndef QT_NO_OPENGL
        OpenGLWindow window;
        window.setWindowTitle("Main Window");
        window.show();
    #else

        QLabel note("Application needs OpenGL up to date to execute properly.");
        note.show();
    #endif

    return app.exec();
}
