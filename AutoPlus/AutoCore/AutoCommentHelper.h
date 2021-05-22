#ifndef AUTOCOMMENTHELPER_H
#define AUTOCOMMENTHELPER_H
#include <qdebug.h>
#include <QString>
#include <QStringList>
#include "FileHandler.h"
#include "FunctionInfo.h"

class AutoCommentHelper
{
public:
    AutoCommentHelper();
    ~AutoCommentHelper();

    void returnDebugLogs(int, int, int, int);
    QStringList formatString(QString fun);
    QString removeWhiteSpaces(QString curentLine);
    QString removeDataInsideParenthesis(QString curentLine);
    bool isCurrLineFunction(QString currentLine, QString nextLine);
    bool isCurrLineFunctionCheck1(QString currentLine, QString nextLine);
    bool isCurrLineFunctionCheck2(QString currentLine);
    bool isCurrLineFunctionCheck3(QString currentLine);

    QString toStdSyntax(QString functionSyntax);
    QString removeNewLineChar(QString functionSyntax);
    QString removeExtraWhiteSpaces(QString functionSyntax);
    QString removeMultiLineComments(QString functionSyntax);
    QString removeSingleLineComments(QString functionSyntax);

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

    QStringList checkList;
    void fillCheckList();
};

#endif // AUTOCOMMENTHELPER_H
