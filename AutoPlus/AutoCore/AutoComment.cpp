#include "AutoComment.h"

/*
 * Auto Comment class constructor.
 */
AutoComment::AutoComment():
    m_insertIndex(-1),
    m_allFileData(""),
    m_pFile(NULL),
    m_pHeaderInfo(NULL),
    m_pParamInfo (NULL),
    m_pFuncInfo(NULL),
    m_pHelper(NULL)
{
    m_pHeaderInfo = new QFile();
    m_pParamInfo  = new ParamInfo();
    m_pFuncInfo   = new FunctionInfo();
    m_pHelper     = new AutoCommentHelper();
    m_pHeaderInfo->setFileName("~/headerInfo.txt");
}

/*
 * Auto Comment class destructor.
 */
AutoComment::~AutoComment()
{
    if(NULL != m_pHelper)
        delete m_pHelper;

    if(NULL != m_pHeaderInfo)
        delete m_pHeaderInfo;

    if(NULL != m_pFuncInfo)
        delete m_pFuncInfo;
}

/*
 * This function set_filePath is called by mainscreen.cpp file.
 * When tool gets launched you can select multiple files for applying comments
 * So for each file this function is called sequential
 */
void AutoComment::set_filePath(QString filePath)
{
    m_filePath = filePath;
    readAllFileData();
}

/*
 * This function readAllFileData is called,
 * once file path is set from set_filePath function.
 * Once file path is decided, this function extracts all data from the specified file
 */
void AutoComment::readAllFileData()
{
    m_pFile = new QFile(m_filePath);
    m_pFile->setFileName(m_filePath);
    m_pFile->open(QFile::ReadWrite);
    m_allFileData = m_pFile->readAll();
}

/*
 * While applying comments, this function get_filePath is used
 * When applycomments function is called, it asks get_filePath function.
 * And get_filePath() function provides desired file path with file name.
 */
QString AutoComment::get_filePath()
{
    return m_filePath;
}

/*
 * This function is used only for file processing.
 * File processing means when from GUI user sends selects FILE to apply comments.
 * This function is used when current read line is identified as function.
 * This function provides standard brief info as comments.
 */
void AutoComment::addBriefInfo()
{
    QString briefInfo;
    QString separator = "::";
    QString classname = m_pFuncInfo->get_className();
    QString funcName = m_pFuncInfo->get_functionName();
    bool isClassNamePresent = m_pFuncInfo->get_isClassNamePresent();

    if(true == isClassNamePresent)
    {
        briefInfo = "\n/** \n * @brief " + classname + separator + funcName;
    }
    else
    {
        briefInfo = "\n/** \n * @brief " + funcName;
    }

    m_allFileData.insert(m_insertIndex,briefInfo);
    qDebug()<<"BRIEF INFO IS "<<briefInfo;
}

/*
 * This function is used only for text processing.
 * Text processing means when from GUI user sends STRING/DEMO_TEXT to check o/p of tool.
 * This function is used when current read line is identified as function.
 * This function provides standard brief info as comments.
 */
QString AutoComment::addBriefInfoText()
{
    QString briefInfo;
    QString separator = "::";
    QString classname = m_pFuncInfo->get_className();
    QString funcName = m_pFuncInfo->get_functionName();
    bool isClassNamePresent = m_pFuncInfo->get_isClassNamePresent();

    if(true == isClassNamePresent)
    {
        briefInfo = "/** \n * @brief " + classname + separator + funcName;
    }
    else
    {
        briefInfo = "/** \n * @brief " + funcName;
    }
    // qDebug()<<"BRIEF INFO IS "<<briefInfo;

    return briefInfo;
}

/*
 * This function is used only for file processing.
 * File processing means when from GUI user sends selects FILE to apply comments.
 * This function is used when current read line is identified as function.
 * This function provides standard return type info as comments.
 */
void AutoComment::addReturnTypeInfo()
{
    QString returnTypeInfo = m_pFuncInfo->get_functionReturnType();
    returnTypeInfo = "\n * @return " + returnTypeInfo + "\n */" ;
    // qDebug()<<"RETURN INFO IS "<<returnTypeInfo;
    m_allFileData.insert(m_insertIndex,returnTypeInfo);
}

/*
 * This function is used only for text processing.
 * Text processing means when from GUI user sends STRING/DEMO_TEXT to check o/p of tool.
 * This function is used when current read line is identified as function.
 * This function provides standard return type info as comments.
 */
QString AutoComment::addReturnTypeInfoText()
{
    QString returnTypeInfo = m_pFuncInfo->get_functionReturnType();
    returnTypeInfo = "\n * @return " + returnTypeInfo + "\n */" ;
    // qDebug()<<"RETURN INFO IS "<<returnTypeInfo;
    return returnTypeInfo;
}

/*
 * This function is used only for file processing.
 * File processing means when from GUI user sends selects FILE to apply comments.
 * This function is used when current read line is identified as function.
 * This function provides standard param info as comments.
 */
void AutoComment::addParamInfo()
{
    QList<ParamInfo::SParamInfo> paramList = m_pParamInfo->get_paramInfoList();
    QListIterator<ParamInfo::SParamInfo> paramListItr(paramList);

    if(!paramList.isEmpty())
    {
        while(paramListItr.hasNext())
        {
            ParamInfo::SParamInfo sParam = paramListItr.next();
            QString paramInfo = "\n * @param " + sParam.m_paramDataType + " " +  sParam.m_ParamObjectName;
            qDebug()<<"PARAM INFO IS "<<paramInfo;
            m_allFileData.insert(m_insertIndex,paramInfo);
        }
    }
}

/*
 * This function is used only for text processing.
 * Text processing means when from GUI user sends STRING/DEMO_TEXT to check o/p of tool.
 * This function is used when current read line is identified as function.
 * This function provides standard param info as comments.
 */
QString AutoComment::addParamInfoText()
{
    QList<ParamInfo::SParamInfo> paramList = m_pParamInfo->get_paramInfoList();
    QListIterator<ParamInfo::SParamInfo> paramListItr(paramList);
    QString paramInfo = "";

    if(!paramList.isEmpty())
    {
        while(paramListItr.hasNext())
        {
            ParamInfo::SParamInfo sParam = paramListItr.next();
            paramInfo = paramInfo + "\n * @param " + sParam.m_paramDataType + " " +  sParam.m_ParamObjectName;
            // qDebug()<<"PARAM INFO IS "<<paramInfo;
        }
    }

    // qDebug()<<"PARAM INFO IS "<<paramInfo;
    return paramInfo;
}

/*
 * This function is currently not in use.
 * This function is reserved for future dev.
 * Its auto dev. responsibility to update comments of this function when it comes in use.
 */
void AutoComment::applyHeader()
{
    /*
    QByteArray headerInfoArray = m_pHeaderInfo->readAll();
    QByteArray allFileData = m_pFile->readEveryLine();

    if(!allFileData.contains(headerInfoArray))
    {
        m_pFile->shrink(0);
        m_pFile->writeData(allFileData);
        m_pFile->flush();
        m_pFile->close();
        m_pFile->open(QFile::ReadWrite);
    }
    */
}

QString AutoComment::applyCommentsOnText(QString demoText)
{
    /*
     * We cannot assure that input recieved in this function as a string
     * can be single line input.
     * Inorder to separate multiple lines we use below logic.
     * Split by \n delimeter.
     */
    QStringList demoTextList = demoText.split("\n");

    /* Define iterator, to iterate through above splitted list */
    int demoTextListItr = 0;

    /*
     * Defining new list.
     * This list will not contain extra blank spaces.
     * We termed it as formatted list. i.e frDemoTextList
     */
    QStringList frDemoTextList;

    /* Define iterator for above formatted list. i.e frDemoTextList */
    int frDemoTextListItr = 0;

    /* Define variables used accross this function */
    int demoTextLineCount = 0;

    /* Logic to remove extra blank spaces, cleaning buffer in other words */
    /* Actually this logic is not neccessary, there is one bug if this function is bypassed */
    /* The root cause of this bug is unknown */
    while(demoTextListItr < demoTextList.count())
    {
        if(demoTextList.at(demoTextListItr) != "xxxxx")
        {
            frDemoTextList.append(demoTextList.at(demoTextListItr));
        }
        demoTextListItr++;
    }

    /* Collecting count of elements present in formatted list*/
    demoTextLineCount = frDemoTextList.count();
    qDebug()<<"demoTextLineCount"<<demoTextLineCount;

    int stackCount = 0;
    while(frDemoTextListItr < demoTextLineCount)
    {
        if(demoTextLineCount <= 0)
            break;

        QString curentLine = frDemoTextList.at(frDemoTextListItr);

        qDebug()<<"*** Current Line is ***"<<curentLine<<endl;

        if( false == stopParsing(curentLine, stackCount) )
        {
            qDebug()<<"***Parsing started***";
            textParsing(frDemoTextListItr, demoTextLineCount,
                        curentLine, frDemoTextList);
        }
        else
        {
            qDebug()<<"***Parsing stopped***";
        }

        frDemoTextListItr++;
    }

    // qDebug()<<"This is return demo text \n"<<demoText;
    demoText = "";
    frDemoTextListItr = 0;
    while(frDemoTextListItr < frDemoTextList.count())
    {
        /*if(demoText == "")
        {
             demoText = frDemoTextList.at(frDemoTextListItr);
        }
        else
        {
            demoText =  demoText + "\n" + frDemoTextList.at(frDemoTextListItr);
        }*/

        demoText =  demoText + "\n" + frDemoTextList.at(frDemoTextListItr);
        frDemoTextListItr++;
    }

    //TO Do -> this logic is not correct.

    // demoText = demoText.section();
    return demoText.right(demoText.count() - 1);
}

/*
 * This function is exlusively used to add logs.
 * It is called when metrics of current line identified as function
 * need to be printed.
 */
void AutoComment::functionDebugLogs()
{
    qDebug()<<"className :"<<m_pFuncInfo->get_className();
    qDebug()<<"functionName :"<<m_pFuncInfo->get_functionName();
    qDebug()<<"isReturnConst :"<<m_pFuncInfo->get_isReturnConst();
    qDebug()<<"isReturnPointer :"<<m_pFuncInfo->get_isReturnPointer();
    qDebug()<<"isFunctionInline :"<<m_pFuncInfo->get_isFunctionInline();
    qDebug()<<"isFunctionInline :"<<m_pFuncInfo->get_isFunctionConst();
    qDebug()<<"isClassNamePresent :"<<m_pFuncInfo->get_isClassNamePresent();
    qDebug()<<"isFunctionPureVirtual :"<<m_pFuncInfo->get_isFunctionPureVirtual();
}

void AutoComment::applyCommentsOnFile()
{
    QString filePath = get_filePath();
    QFile* pfile = new QFile(filePath);
    pfile->setFileName(filePath);

    if(pfile->open(QFile::ReadWrite))
    {
        QString curentLine = pfile->readLine();
        // qInfo()<<"reading file : "<<filePath;

        while (!pfile->atEnd())
        {
            qDebug()<<"current line : "<<curentLine;
            QString nextLine = pfile->readLine();

            curentLine = m_pHelper->toStdSyntax(curentLine);
            nextLine = m_pHelper->toStdSyntax(nextLine);

            bool isCurrLineFunc = m_pHelper->isCurrLineFunction(curentLine,nextLine);

            if(true == isCurrLineFunc)
            {
                // qInfo()<<"current line is identified as function";
                currLineIdentifiedAsFunction(curentLine);
            }
            else
            {
                // qInfo()<<"current line is not identified as function";
            }
            curentLine = nextLine;
            m_pParamInfo->clear_paramInfoList();
        }
        doFileOperations();
    }
}

/*
 * This function is used to save the content in to the file,
 * after adding all types of comments.
 */
void AutoComment::doFileOperations()
{
    m_pFile->resize(0);
    m_pFile->write(m_allFileData);
    m_pFile->flush();
    m_pFile->close();
    m_pHeaderInfo->close();
}

/*
 * This function is used to set function metrics when current line identified as function.
 * class name
 * return type
 * function name..
 * etc...for more info read below function defination
 */
void AutoComment::setFunctionMetrics(QString curentLine)
{
    m_pFuncInfo->set_className_and_returnType(curentLine);
    m_pFuncInfo->set_FunctionName(curentLine);

    QString functionReturnType = m_pFuncInfo->get_functionReturnType();
    m_pFuncInfo->set_isReturnPointer(functionReturnType);

    m_pFuncInfo->set_isFunctionConst(functionReturnType);
    m_pFuncInfo->set_isClassNamePresent(curentLine);
    m_pFuncInfo->set_isFunctionInline(curentLine);
    m_pFuncInfo->set_isFunctionPureVirtual(curentLine);
    m_pFuncInfo->set_isReturnConst(curentLine);
    m_pParamInfo->set_paramInfo(curentLine);
}

/*
 * This function can be used when current line identified as function.
 * It sets function metrics. i.e class name, return type, param info .....etc.
 */
void AutoComment::currLineIdentifiedAsFunction(QString curentLine)
{
    QStringList splitFun = m_pHelper->formatString(curentLine);

    if(splitFun.count() >= 2)
    {
        //qInfo()<<"split count is greater than 2";

        setFunctionMetrics(curentLine);
        functionDebugLogs();

        m_insertIndex = m_allFileData.indexOf(curentLine) - 1;
        addReturnTypeInfo();
        addParamInfo();
        addBriefInfo();
    }
    else
    {
        //qInfo()<<"split count is less than 2";
    }
}

void  AutoComment::currLineIsAFunctionForText(QString &frCurentLine, QStringList &frDemoTextList,
                                              int &frDemoTextListItr)
{
    setFunctionMetrics(frCurentLine);
    // functionDebugLogs();
    QString returnTypeInfo = addReturnTypeInfoText();
    QString paramInfo = addParamInfoText();
    QString briefInfo = addBriefInfoText();
    QString frDemoText = briefInfo + paramInfo + returnTypeInfo;
    frDemoTextList.insert(frDemoTextListItr++, frDemoText);
    m_pParamInfo->clear_paramInfoList();
}


bool AutoComment::stopParsing(QString &curentLine, int &stackCount)
{
    /* Ignoring parsing logic, ignore parsing @ first opening curly brace */
    /* Stop ignoring parsing corresponding closing curly brace */
    stackCount = curentLine.contains('{') ? stackCount + 1 : stackCount;
    stackCount = curentLine.contains('}') ? stackCount - 1 : stackCount;
    bool ignoreParsing = stackCount > 0 ? true : false;

    qDebug()<<"***Ignore parsing***"<<ignoreParsing;
    return ignoreParsing;
}


void AutoComment::textParsing(int &frDemoTextListItr, int &demoTextLineCount,
                              QString &curentLine, QStringList &frDemoTextList)
{
    QString nextLine  = "";
    if( frDemoTextListItr < demoTextLineCount - 1)
    {
        nextLine = frDemoTextList.at(frDemoTextListItr + 1);
    }

    QString frCurentLine = m_pHelper->toStdSyntax(curentLine);
    QString frNextLine = m_pHelper->toStdSyntax(nextLine);

    bool isCurrLineFunc = m_pHelper->isCurrLineFunction(frCurentLine,frNextLine);
    qDebug()<<"is current line function :"<<isCurrLineFunc;

    if(true == isCurrLineFunc)
    {
        currLineIsAFunctionForText(frCurentLine, frDemoTextList, frDemoTextListItr);
    }
}
