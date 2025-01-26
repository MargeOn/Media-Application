#ifndef TRANSLATION_H
#define TRANSLATION_H
#include <QObject>
#include <QTranslator>
#include <QGuiApplication>
#include <QDebug>

class Translation : public QObject
{
    Q_OBJECT
    // Biến emptyString dùng để QML nhận biết và hiển thị ngôn ngữ mới khi có sự thay đổi ngôn ngữ
    Q_PROPERTY(QString emptyString READ getEmptyString NOTIFY languageChanged)
    // Dùng trong cách 2: Bố trí các lá cờ thẳng hàng
    // Nếu không dùng ComboBox để thay đổi ngôn ngữ, ta dùng biến currentLanguage để xét visible của border. Nó sẽ thể hiện ngôn ngữ nào được chọn trong 4 lá cờ bằng cách hiển thị border của lá cờ đó: visible: translator.currentLanguage === "currentLanguage"
    Q_PROPERTY(QString currentLanguage READ currentLanguage NOTIFY languageChanged)
public:
    Translation( QGuiApplication *app, QObject *parent = nullptr);
    enum LANGUAGE{
        UnitedStates,
        Vietnamese,
        Korean,
        Japanese
    };
    QString getEmptyString();
    // Dùng trong cách 2: Hàm QString currentLanguage() sẽ trả về ngôn ngữ được chọn hiện tại ở C++, biến currentLanguage trên QML
    // sẽ lấy giá trị trả về của hàm đó và kiểm tra trên QML.
    QString currentLanguage();
    void setCurrentLanguage(int indexLanguage);
    Q_INVOKABLE void selectLanguage(int indexLanguage);
signals:
    void languageChanged();

private:
    QTranslator *translator;
    QGuiApplication *m_app;
    QString m_currentLanguage;
};

#endif // TRANSLATION_H
