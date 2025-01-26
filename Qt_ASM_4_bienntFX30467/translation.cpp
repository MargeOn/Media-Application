#include "translation.h"

Translation::Translation( QGuiApplication *app, QObject *parent)
    : QObject(parent), translator(new QTranslator(this)),
      m_app(app)
{

}

QString Translation::getEmptyString()
{
    return "";
}


QString Translation::currentLanguage()
{
    return m_currentLanguage;
}

void Translation::setCurrentLanguage(int indexLanguage)
{
    if(indexLanguage == Translation::UnitedStates){
        if(translator->load(":/translate_us.qm")){
            qDebug() << "us";
        }
        else{
            qDebug() << "Cannot open file us.qm";
        }
        m_app->installTranslator(translator);
        m_currentLanguage = "us";
    }
    else if(indexLanguage == Translation::Vietnamese){
        if(translator->load(":/translate_vn.qm")){
            qDebug() << "vn";
        }
        else{
            qDebug() << "Cannot open file vn.qm";
        }
        m_app->installTranslator(translator);
        m_currentLanguage = "vn";
    }
    else if(indexLanguage == Translation::Korean){
        if(translator->load(":/translate_kr.qm")){
            qDebug() << "kr";
        }
        else{
            qDebug() << "Cannot open file kr.qm";
        }
        m_app->installTranslator(translator);
        m_currentLanguage = "kr";
    }
    else if(indexLanguage == Translation::Japanese){
        if(translator->load(":/translate_jp.qm")){
            qDebug() << "jp";
        }
        else{
            qDebug() << "Cannot open file jp.qm";
        }
        m_app->installTranslator(translator);
        m_currentLanguage = "jp";
    }
}

void Translation::selectLanguage(int indexLanguage)
{
    setCurrentLanguage(indexLanguage);
    emit languageChanged();
}
