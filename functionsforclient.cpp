#include "functionsforclient.h"



MainWindow * FunctionsForClient::mainForm;
AuthRegForm * FunctionsForClient::authregForm;

FunctionsForClient::FunctionsForClient() {
    authregForm = new AuthRegForm();
    authregForm->show();
    mainForm = new MainWindow();
}

void FunctionsForClient::is_auth()
{
    //return client::sendmsg("auth&"+log+"&"+pass);

        authregForm->close();
        mainForm->show();


    //authregForm->showerr();

}


void FunctionsForClient::on_reg()
{

}
