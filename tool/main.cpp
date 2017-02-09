#include <QCoreApplication>

#include <QCommandLineParser>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setOrganizationName("deepin");
    app.setApplicationName("dtk-settings-tools");
    app.setApplicationVersion("0.1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Generate translation of dtksetting.");
    parser.addHelpOption();
    parser.addVersionOption();

    //    QCommandLineOption optImageFile(QStringList() << "f" << "file",
    //                                    DApplication::tr("ISO image file"),
    //                                    "image-file");
    //    QCommandLineOption optKey(QStringList() << "k" << "key",
    //                              DApplication::tr("Communication key"),
    //                              "key");
    //    QCommandLineOption optDaemon(QStringList() << "d" << "daemon",
    //                                 DApplication::tr("Run in background"));
    //    QCommandLineOption optNoInteractive(QStringList() << "n" << "nointeractive",
    //                                        DApplication::tr("Do not run gui"));

    //    parser.addOption(optDaemon);
    //    parser.addOption(optNoInteractive);
    //    parser.addOption(optImageFile);
    //    parser.addOption(optKey);
    //    parser.addPositionalArgument("device", DApplication::tr("USB Device"));
        parser.process(app);

    //    if (parser.isSet(optDaemon)) {
    //        qDebug() << parser.value(optDaemon)
    //                 << parser.value(optNoInteractive)
    //                 << parser.value(optImageFile)
    //                 << parser.value(optKey)
    //                 << parser.positionalArguments();
    //        BootMaker bm;
    //        qDebug() << "Deepin Boot Maker Backend Started";

    //        return app.exec();
    //    }

    return app.exec();
}
