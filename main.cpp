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
        Logger::Info("Verbose Threshold set to 3",0);
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
