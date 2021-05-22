#include "AutoCommentHelper.h"

AutoCommentHelper::AutoCommentHelper()
{
    qDebug()<<Q_FUNC_INFO;
}

AutoCommentHelper::~AutoCommentHelper()
{
    qDebug()<<Q_FUNC_INFO;
}

QString AutoCommentHelper::removeDataInsideParenthesis(QString curentLine)
{
    qDebug()<<Q_FUNC_INFO;
//    curentLine = curentLine.remove(curentLine.indexOf('('),
//                                   curentLine.indexOf(')') - curentLine.indexOf('(') + 1);

    curentLine = curentLine.remove(curentLine.indexOf('('), curentLine.count()-1 );
    return curentLine;
}

QString AutoCommentHelper::removeSemiColon(QString curentLine)
{
    qDebug()<<Q_FUNC_INFO;
    curentLine = curentLine.replace(';',"");
    return curentLine;
}

QString AutoCommentHelper::removeWhiteSpaces(QString curentLine)
{
    qDebug()<<Q_FUNC_INFO;
    curentLine = curentLine.remove(curentLine.indexOf(curentLine.at(0)),
                                   curentLine.indexOf(' ') + 1);
    return curentLine;
}


bool AutoCommentHelper::checkCurrentLineisFunctionOrNot(QString currentLine, QString nextLine)
{
    qDebug()<<Q_FUNC_INFO;
    bool returnValue = false;
    if( (currentLine.contains(')') && currentLine.contains('{')) ||
        (currentLine.contains(')') && nextLine.contains('{'))    ||
        (currentLine.contains(')') && currentLine.contains(';')) )
    {
        returnValue = true;
    }

    return returnValue;
}

QStringList AutoCommentHelper::formatString(QString fun)
{
    qDebug()<<Q_FUNC_INFO;
    fun = fun.trimmed();

    QStringList splitFun = fun.remove(";").split(" ");
    QStringList formattedStringList;

    foreach (QString string , splitFun)
    {
        if(!string.isEmpty())
        {
            formattedStringList.append(string);
        }
    }
    return formattedStringList;
}

void AutoCommentHelper::getCommentInfo( QString functionSyntax, QString &returnType, QString &functionName, QList<QPair<QString,QString> > &paramList )
{
    // Storing class name
    QString className;

    if(functionSyntax.contains("::"))
    {
        int endIndex = functionSyntax.indexOf(':');
        QStringList list = functionSyntax.split(" ");

        QStringListIterator listItr = list.begin();
        listItr.
               int startIndex;
    }

//    qDebug()<<"functionSyntax :"<<functionSyntax;

//    while(functionSyntax.contains("/*") && functionSyntax.contains("*/"))
//    {
//       int delS = functionSyntax.indexOf("/*");
//       int delE = functionSyntax.indexOf("*/");
//       functionSyntax = functionSyntax.remove(delS,delE - delS);
//       qDebug()<<"functionSyntax :"<<functionSyntax;
//    }

    //functionSyntax = " ABC /* Indraneel */ QStringList /* Patil */ formatString(QString fun, QString index);;";
//    functionSyntax = "QStringList formatString(QString fun, QString index);/* asdfasdf";
    qDebug()<<"functionSyntax :"<<functionSyntax;

    //Removing Multiline comments if any .
    int startIndex = functionSyntax.indexOf("/*");
    while( startIndex > -1  )
    {
        int endIndex = functionSyntax.indexOf("*/");
        if( endIndex > -1 )
        {
            functionSyntax = functionSyntax.remove(startIndex,endIndex - startIndex + 2);
        }
        else
        {
            functionSyntax = functionSyntax.remove(functionSyntax.indexOf("/*"), functionSyntax.length()-functionSyntax.indexOf("/*"));
        }
        startIndex = functionSyntax.indexOf("/*");
    }

    //Removing SingleLine comments if any .
    if(functionSyntax.contains("//"))
    {
        int startIndex = functionSyntax.indexOf("//");
        int length = functionSyntax.length() - startIndex;
        functionSyntax.remove(startIndex, length);
    }

    //Removing Semicolon
    functionSyntax = functionSyntax.replace(";","");

    qDebug()<<"functionSyntax :"<<functionSyntax;

    QStringList returnTypeList = functionSyntax.split(" ").removeOne();
    returnType = returnTypeList.at(0);

    functionName = functionSyntax.remove(functionSyntax.indexOf(functionSyntax.at(0)),
                                       functionSyntax.indexOf(':') - functionSyntax.indexOf(functionSyntax.at(0)) + 1);

    qDebug()<<"returnType :"<<returnType<<":";
    qDebug()<<"className :"<<className.isEmpty()?"className.isEmpty()":className<<":";
    qDebug()<<"functionName :"<<functionName<<":";
    qDebug()<<"paramList :"<<paramList<<":";
}
