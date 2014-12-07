/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#include <iostream>
#include <QApplication>
#include "httpsender.h"

//This HTTP module follow an API described here : http://www.uplmg.com/documentation/documentation.html

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    HttpSender http;
    http.setHost("http://uplmg.com/insert/upload", 80);
    http.setFile(R"(C:\Users\imote\Documents\Checkbox.psd)"); //Insert here your local file path
    http.setUplimgVersion("0.14_networkmodule");
    //Not necessary to set paste settings
    //We send file as anonymous so no user settings

    QObject::connect(&http, &HttpSender::finished, [&http]()
    {
        std::cout << http.getResponse().toStdString() << std::endl; //Will show the access link
    });

    QObject::connect(&http, &HttpSender::uploadProgress, [](qint64 bytesSent, qint64 bytesTotal)
    {
        if(bytesTotal == 0) return; //If the bytesTotal is 0, there is a problem and it is no possible. So we avoid the showing of false informations.
        std::cout << bytesSent << " bytes sent, for a total of " << bytesTotal << " bytes. "
                  << (float)bytesSent/(float)bytesTotal*100.0 << "%"
                  << std::endl;
    });

    QObject::connect(&http, &HttpSender::statusChanged, [](const HttpSender::Status &status)
    {
        if(status == HttpSender::Status::FILE_ERROR)
            std::cout << "Can't open the file. Aborted." << std::endl;
    });

    QObject::connect(&http, &HttpSender::error, [](QNetworkReply::NetworkError e)
    {
        std::cout << "Error occured. Code : " << e << std::endl;
    });

    //Call run function to send the file
    http.run();

    return app.exec();
}
