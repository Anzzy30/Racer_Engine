#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>
#include <QDate>

#ifdef QT_DEBUG
    #include <Logger/logger.h>
#endif

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

    #ifdef QT_DEBUG
        Logger::SetVerbose(3);
        Logger::Warning("Debug testing layer 0",0);
        Logger::Warning("Debug testing layer 1",1);
        Logger::Warning("Debug testing layer 2",2);
        Logger::Warning("Debug testing layer 3",3);
        Logger::Warning("Debug testing layer 4",4);
        Logger::Warning("Debug testing layer 5",5);
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
