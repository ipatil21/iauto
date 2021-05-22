#ifndef PARAMINFO_H
#define PARAMINFO_Ha
#include <QString>
#include <QStringList>

class ParamInfo
{
public:
    ParamInfo();

    struct SParamInfo
    {
        bool m_isParamStatic;
        bool m_isParamConst;
        bool m_isParamReference;
        bool m_isParamPointer;
        bool m_isParamDefault;
        QString m_paramDataType;
        QString m_ParamObjectName;
        QString m_paramDefaultValue;
    };


    void set_paramInfo(QString functionSyntax);

    QString spaceBeforeSpecialChar(QString paramListElement, int indexOfSpecialChar);

    QString spaceAfterSpecialChar(QString paramListElement, int indexOfSpecialChar);

    QString spaceAfterBeforeSpecialChar(QString paramListElement, int indexOfSpecialChar);

    QString handleSpecialCharCase(QString paramListElement);

    QString getElementFromParamList(QStringList paramList, int index);

    QStringList getDataInsideParenthesis(QString functionSyntax);

    QStringList splitParamListByWhiteSpaces(QString paramListElement);
    QList<ParamInfo::SParamInfo> get_paramInfoList();
    bool isParamStatic(QString paramReturnType);
    bool isParamConst(QString paramReturnType);
    bool isParamReference(QString paramReturnType);
    bool isParamPointer(QString paramReturnType);
    bool isParamDefault(QString paramReturnType);
    void clear_paramInfoList();

private:

    QList<SParamInfo> ParamInfoList;
};

#endif // PARAMINFO_H
