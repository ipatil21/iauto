#include "ParamInfo.h"
#include <qdebug.h>

ParamInfo::ParamInfo()
{

}

QList<ParamInfo::SParamInfo> ParamInfo::get_paramInfoList()
{
    int paramListCount = ParamInfoList.count();
    Q_UNUSED(paramListCount)
    //qDebug()<<"ParamInfoList count"<< paramListCount;
    return ParamInfoList;
}

void ParamInfo::clear_paramInfoList()
{
    ParamInfoList.clear();
}

void ParamInfo::set_paramInfo(QString functionSyntax)
{
    if( functionSyntax.contains('(') && functionSyntax.contains(')') )
    {
        QStringList paramList = getDataInsideParenthesis(functionSyntax);
        // qDebug()<<"******paramList count*******"<<paramList.count();
        for(int i = 0; i < paramList.count(); i++)
        {
            QString paramListElement = getElementFromParamList(paramList, i);
            paramListElement = handleSpecialCharCase(paramListElement);
            QStringList paramListSplitedWhiteSpaces = splitParamListByWhiteSpaces(paramListElement);
            int splittedListCount = paramListSplitedWhiteSpaces.count();

            QString paramReturnType = "";
            QString paramVaraible = "";

            for(int x = 0; x < splittedListCount - 1; x++ )
            {
                paramReturnType = paramReturnType + " " + paramListSplitedWhiteSpaces.at(x);
                paramReturnType = paramReturnType.trimmed();
            }
            paramVaraible = paramListSplitedWhiteSpaces.at(splittedListCount - 1);

            if(splittedListCount > 1)
            {
                QString keyword = paramListSplitedWhiteSpaces.at(splittedListCount - 1);
                if(keyword == "int" || keyword == "char")
                {
                    paramReturnType = paramReturnType + " " + paramVaraible;
                    paramVaraible = "";
                }
            }

            if(splittedListCount == 1)
            {
                paramReturnType = paramVaraible;
                paramVaraible = "";
            }

            //qDebug()<<"paramReturnType"<<paramReturnType;
            //qDebug()<<"paramVaraible"<<paramVaraible;

            SParamInfo SParamInfo_Obj;
            SParamInfo_Obj.m_ParamObjectName  = paramVaraible;
            SParamInfo_Obj.m_paramDataType    = paramReturnType;
            SParamInfo_Obj.m_isParamConst     = isParamConst(paramReturnType);
            SParamInfo_Obj.m_isParamStatic    = isParamStatic(paramReturnType);
            SParamInfo_Obj.m_isParamDefault   = isParamDefault(paramReturnType);
            SParamInfo_Obj.m_isParamPointer   = isParamPointer(paramReturnType);
            SParamInfo_Obj.m_isParamReference = isParamReference(paramReturnType);

            ParamInfoList.append(SParamInfo_Obj);
        }
    }
}

bool ParamInfo::isParamStatic(QString paramReturnType)
{
    bool retVal = paramReturnType.contains("static") ? true : false;
    return retVal;
}

bool ParamInfo::isParamConst(QString paramReturnType)
{
    bool retVal = paramReturnType.contains("const") ? true : false;
    return retVal;
}

bool ParamInfo::isParamReference(QString paramReturnType)
{
    bool retVal = paramReturnType.contains("&") ? true : false;
    return retVal;
}

bool ParamInfo::isParamPointer(QString paramReturnType)
{
    bool retVal = paramReturnType.contains("*") ? true : false;
    return retVal;
}

bool ParamInfo::isParamDefault(QString paramReturnType)
{
    bool retVal = false;//paramReturnType.contains("const") ? true : false;
    Q_UNUSED(paramReturnType);
    return retVal;
}

QStringList  ParamInfo::getDataInsideParenthesis(QString functionSyntax)
{
    int indexStart = functionSyntax.indexOf('(');
    int indexEnd = functionSyntax.indexOf(')');
    QString insideCircularBrackets = functionSyntax.section("", indexStart + 2 , indexEnd);
    QStringList paramList;
    if(!insideCircularBrackets.isEmpty())
    {
        paramList = insideCircularBrackets.split(',');
    }
    return paramList;
}

QString ParamInfo::spaceBeforeSpecialChar(QString paramListElement, int indexOfSpecialChar)
{
    paramListElement = paramListElement.insert(indexOfSpecialChar + 1, " " );
    QStringList splittedList = paramListElement.split(" ");
    int whiteSpacesCount = splittedList.count() - 2;
    paramListElement = paramListElement.remove(indexOfSpecialChar - whiteSpacesCount, whiteSpacesCount );
    return paramListElement;
}

QString ParamInfo::spaceAfterSpecialChar(QString paramListElement, int indexOfSpecialChar)
{
    QStringList splittedList = paramListElement.split(" ");
    int whiteSpacesCount = splittedList.count() - 2;
    paramListElement = paramListElement.remove(indexOfSpecialChar + 1, whiteSpacesCount );
    return paramListElement;
}

QString ParamInfo::spaceAfterBeforeSpecialChar(QString paramListElement, int indexOfSpecialChar)
{
    Q_UNUSED((indexOfSpecialChar))
    QStringList splittedList = paramListElement.split(" ");
    QString paramListElementF;

    for(int j = 0; j < splittedList.count(); j++)
    {
        if(splittedList.at(j) != " ")
        {
            paramListElementF = paramListElementF + splittedList.at(j);
        }
    }

    if(paramListElementF.contains('*'))
    {
        paramListElement = paramListElementF.insert(paramListElementF.indexOf('*') + 1," ");
    }
    else
    {
        paramListElement = paramListElementF.insert(paramListElementF.indexOf('&') + 1," ");
    }
    return paramListElement;
}

QString ParamInfo::handleSpecialCharCase(QString paramListElement)
{
    if(paramListElement.contains('&') || paramListElement.contains('*'))
    {
        int indexOfSpecialChar = paramListElement.contains('&') ? paramListElement.indexOf('&') : paramListElement.indexOf('*');
        QChar charBeforeSpecialChar = paramListElement.at(indexOfSpecialChar - 1);
        QChar charAfterSpecialChar = paramListElement.at(indexOfSpecialChar + 1);

        if(charAfterSpecialChar.isLetterOrNumber() && charBeforeSpecialChar.isSpace())
        {
            paramListElement = spaceBeforeSpecialChar(paramListElement, indexOfSpecialChar);
        }
        else if(charAfterSpecialChar.isSpace() && charBeforeSpecialChar.isLetterOrNumber())
        {
            paramListElement = spaceAfterSpecialChar(paramListElement, indexOfSpecialChar);
        }
        else if(charAfterSpecialChar.isSpace() && charBeforeSpecialChar.isSpace())
        {
            paramListElement = spaceAfterBeforeSpecialChar(paramListElement, indexOfSpecialChar);
        }
    }
    return paramListElement;
}

QString ParamInfo::getElementFromParamList(QStringList paramList, int index)
{
    QString paramListElement =  paramList.at(index);
    paramListElement = paramListElement.trimmed();
    return paramListElement;
}

QStringList ParamInfo::splitParamListByWhiteSpaces(QString paramListElement)
{
    QStringList paramListSplitedWhiteSpaces = paramListElement.split(" ");
    return paramListSplitedWhiteSpaces;
}
