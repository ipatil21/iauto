#ifndef AUTOCOMMENT_H
#define AUTOCOMMENT_H

#include "FileHandler.h"
#include "AutoCommentHelper.h"
#include "FunctionInfo.h"
#include "ParamInfo.h"
#include "QDir"
#include <QFile>
#include <qdebug.h>

class AutoComment
{

public:
    AutoComment();
    ~AutoComment();

    void doFileOperations();
    void applyCommentsOnFile();
    void set_filePath(QString filePath);
    QString applyCommentsOnText(QString demoText);
    void setFunctionMetrics(QString curentLine);
    void applyCommentsOnFolder(QString folderPath)
    {Q_UNUSED(folderPath)}

private:

    int m_insertIndex;
    QByteArray m_allFileData;

    QFile* m_pFile;
    QFile* m_pHeaderInfo;
    QString m_filePath;
    ParamInfo* m_pParamInfo;
    FunctionInfo* m_pFuncInfo;
    AutoCommentHelper* m_pHelper;

    void applyHeader();
    void addBriefInfo();
    void addParamInfo();
    QString get_filePath();
    void readAllFileData();
    void functionDebugLogs();
    void addReturnTypeInfo();

    QString addParamInfoText();
    QString addBriefInfoText();
    QString addReturnTypeInfoText();
    bool stopParsing(QString &currentLine, int &stackCount);
    void currLineIdentifiedAsFunction(QString currentLine);
    void currLineIsAFunctionForText(QString &frCurentLine, QStringList &frDemoTextList,
                                    int &frDemoTextListItr);
    void textParsing(int &frDemoTextListItr, int &demoTextLineCount,
                     QString &curentLine, QStringList &frDemoTextList);

};

#endif // AUTOCOMMENT_H
