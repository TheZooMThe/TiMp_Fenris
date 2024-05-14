#ifndef FUNCTIONSFORCLIENT_H
#define FUNCTIONSFORCLIENT_H

#include "mainwindow.h"
#include "authregform.h"

#include <QObject>

class FunctionsForClient: public QObject
{
    Q_OBJECT
public:
    static void is_auth();
    static void on_reg();
    FunctionsForClient();

signals:
    //void on_auth_ok();
private:
    static MainWindow *mainForm;
    static AuthRegForm * authregForm;
};

#endif // FUNCTIONSFORCLIENT_H
