#include "AutoComment.h"

AutoComment::AutoComment():m_pFile(NULL),m_pHelper(NULL)
{
    m_pFile = new FileHandler();
    m_pHelper = new AutoCommentHelper();

    m_pHeaderInfo = new QFile();
    m_pHeaderInfo->setFileName("~/headerInfo.txt");
    qDebug()<<Q_FUNC_INFO<<"m_pFile :"<<m_pFile<<"m_pHelper :"<<m_pHelper<<"m_pHeaderInfo :"<<m_pHeaderInfo;
}

AutoComment::~AutoComment()
{
    qDebug()<<Q_FUNC_INFO;

    if(NULL != m_pHelper)
        delete m_pHelper;

    if(NULL != m_pHeaderInfo)
        delete m_pHeaderInfo;

    if(NULL != m_pFile)
        delete m_pFile;
}

void AutoComment::addBriefInfo(QByteArray &allFileData, QStringList &functionName, QString &curentLine)
{
    qDebug()<<Q_FUNC_INFO;
    qDebug()<<"================================================================================START";

    QString formattedCurrentLine;

    formattedCurrentLine = m_pHelper->removeDataInsideParenthesis(curentLine);
    qDebug()<<"formattedCurrentLine : After removeDataInsideParenthesis"<<formattedCurrentLine;

    formattedCurrentLine = m_pHelper->removeSemiColon(formattedCurrentLine);
//    qDebug()<<"formattedCurrentLine : After removeSemiColon"<<formattedCurrentLine;

    formattedCurrentLine = m_pHelper->removeWhiteSpaces(formattedCurrentLine);
    qDebug()<<"formattedCurrentLine : After removeWhiteSpaces"<<formattedCurrentLine;

    formattedCurrentLine = "\n/** \n * @brief " + formattedCurrentLine;

    qDebug()<<"Current line is :"<<curentLine;
    qDebug()<<"Final Current line is :"<<formattedCurrentLine;
    qDebug()<<"all file Data :"<<allFileData;

    if(allFileData.indexOf(formattedCurrentLine) == -1)
    {
        qDebug()<<"Brief info not found initially";
        allFileData.insert(allFileData.indexOf(curentLine) - 1, formattedCurrentLine);
    }
    qDebug()<<"all file Data :"<<allFileData;
    qDebug()<<"================================================================================END";
}


void AutoComment::addReturnTypeInfo(QByteArray &allFileData, QStringList &functionName, QString &curentLine)
{
    qDebug()<<Q_FUNC_INFO;

    QString returnTypeInfo = "\n * @return " + functionName.at(0) + "\n */" ;
    qDebug()<<"returnTypeInfo"<<returnTypeInfo;

    if(allFileData.indexOf(returnTypeInfo) == -1)
    {
        qDebug()<<"index returnTypeInfo is minus 1 : start :"<<returnTypeInfo;
        allFileData.insert(allFileData.indexOf(curentLine) - 1,returnTypeInfo);
        qDebug()<<"index returnTypeInfo is minus 1 : end :"<<returnTypeInfo;
    }
    qDebug()<<"RETUEN @@@@@@@ returnTypeInfo"<<returnTypeInfo;
    qDebug()<<"all file Data :"<<allFileData;
}

void AutoComment::addParamInfo(QByteArray &allFileData, QStringList &functionName, QString &curentLine)
{
    qDebug()<<Q_FUNC_INFO;

    int indexStart = curentLine.indexOf('('), indexEnd = curentLine.indexOf(')');
    qDebug()<<"indexStart : \n"<<indexStart<<"indexEnd : \n"<<indexEnd;

    QString insideCircularBrackets = curentLine.section("", indexStart + 2 , indexEnd);
    qDebug()<<"insideCircularBrackets : "<<insideCircularBrackets;

    if(!insideCircularBrackets.isEmpty())
    {
        qDebug()<<"Data inside Circular Brackets is present";
        QStringList dataInsideCircularBrackets = insideCircularBrackets.split(',');

        for(int i = 0; i < dataInsideCircularBrackets.length();i++)
        {
            QString paramData = dataInsideCircularBrackets.at(i);
            paramData = paramData.trimmed();
            QStringList formattedParamDataList = paramData.split(" ");
            QString paramInfo = "\n * @param " + formattedParamDataList.at(1);

            if(allFileData.indexOf(paramInfo) == -1)
            {
                allFileData.insert(allFileData.indexOf(curentLine) - 1,paramInfo);
            }
        }
    }
    //qDebug()<<"all file Data :"<<allFileData;
}

void AutoComment::applyHeader()
{
    qDebug()<<Q_FUNC_INFO;

    QByteArray headerInfoArray = m_pHeaderInfo->readAll();
    QByteArray allFileData = m_pFile->readEveryLine();

    if(!allFileData.contains(headerInfoArray))
    {
        //allFileData = headerInfoArray + allFileData;


        m_pFile->shrink(0);
        m_pFile->writeData(allFileData);
        m_pFile->flush();
        m_pFile->close();
        m_pFile->open(QFile::ReadWrite);
    }
}

void AutoComment::applyComments()
{
    qDebug()<<Q_FUNC_INFO;

    QString returntype,functionName;

    QList<QPair<QString,QString> > paramList;

    //QString functionSyntax;
    QString functionSyntax = "QStringList AutoCommentHelper::formatString(QString fun, QString index)";
    m_pHelper->getCommentInfo( functionSyntax,returntype,functionName,paramList);

    functionSyntax = "QStringList AutoCommentHelper::formatString(QString fun, QString index)    // asdgsdgv";
    m_pHelper->getCommentInfo( functionSyntax,returntype,functionName,paramList);

    functionSyntax = "QStringList formatString(QString fun, QString index)";
    m_pHelper->getCommentInfo( functionSyntax,returntype,functionName,paramList);

    functionSyntax = "QStringList formatString(QString fun, QString index);";
    m_pHelper->getCommentInfo( functionSyntax,returntype,functionName,paramList);

    functionSyntax = "QStringList* formatString(QString fun, QString index);";
    m_pHelper->getCommentInfo( functionSyntax,returntype,functionName,paramList);

    functionSyntax = " /* asdfasdgfa */ QStringList formatString(QString fun, QString index);";
    m_pHelper->getCommentInfo( functionSyntax,returntype,functionName,paramList);

    functionSyntax = " /* asdfasdgfa // ABC */ QStringList formatString(QString fun, QString index);";
    m_pHelper->getCommentInfo( functionSyntax,returntype,functionName,paramList);

    functionSyntax = " /* asdfasdgfa // ABC */ static /* */ QStringList formatString(QString fun, QString index);// ABC";
    m_pHelper->getCommentInfo( functionSyntax,returntype,functionName,paramList);

    functionSyntax = " /* asdfasdgfa // ABC // */ static /* */ QStringList formatString(QString fun, QString index);// ABC  /*";
    m_pHelper->getCommentInfo( functionSyntax,returntype,functionName,paramList);

//    bool delet = m_pFile->m_qtFile->open(QFile::ReadWrite);
//    qDebug()<<delet;

//    if(delet)
//    {

//        //QTextStream in(m_pFile->m_qtFile);

//        QByteArray allFileData = m_pFile->readEveryLine();
//        qDebug()<<"allFileData :"<<allFileData;

//        m_pFile->m_qtFile->seek(0);
//        QString nextLine, curentLine(m_pFile->readSingleLine());
//        qDebug()<<"curentLine :"<<curentLine;

//        while (curentLine != NULL)
//        {
//            nextLine = m_pFile->readSingleLine();
//            qDebug()<<"nextLine :"<<nextLine;

//            QStringList splitFun = m_pHelper->formatString(curentLine);
//            if(splitFun.count() >= 2 && m_pHelper->checkCurrentLineisFunctionOrNot(curentLine,nextLine))
//            {
//                qDebug()<<"split count is greater than equal to 2, func identified on currentline";

//                QString returnType;
//                QString functionName;
//                QStringList paramList;


//                //addBriefInfo(allFileData, functionName, functionSyntax);

//                addBriefInfo(allFileData, splitFun, curentLine);
//                qDebug()<<"all file Data after addBriefInfo:"<<allFileData;

//                //addParamInfo(allFileData,splitFun,curentLine);
//                //qDebug()<<"all file Data after addParamInfo:"<<allFileData;

////                addReturnTypeInfo(allFileData, splitFun, curentLine);
////                qDebug()<<"all file Data after addReturnTypeInfo:"<<allFileData;

//                qDebug()<<"How to avoid this";
//            }
//            curentLine = nextLine;
//        }

//        m_pFile->shrink(0);
//        m_pFile->flush();
//        m_pFile->m_qtFile->write(allFileData);//writeData(allFileData);
//    }
    m_pFile->close();
    m_pHeaderInfo->close();
}
