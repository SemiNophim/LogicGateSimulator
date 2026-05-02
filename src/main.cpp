#include <QApplication>

#include "MainWindow.h"
#include "LangInit.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    registerLanguages();
    
    MainWindow window;
    window.show();

    return app.exec();
}
