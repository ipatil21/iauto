#include "AutoCommentHelper.h"
#include "AutoDefinations.h"

/*
 *  Auto Comment helper class constructor.
 */
AutoCommentHelper::AutoCommentHelper()
{
    fillCheckList();
}

/*
 *  Auto Comment helper class destructor.
 */
AutoCommentHelper::~AutoCommentHelper()
{

}

/*
 * This function is used to fill checklist.
 * Checklist is actually ignore checklist.
 * If any keyword from checklist is present in the current line,
 * then this current line is not identified as function.
 */
void AutoCommentHelper::fillCheckList()
{
    checkList.append("<<");
    checkList.append(">>");
    checkList.append("==");
    checkList.append("->");
    checkList.append(".");
    checkList.append("#");
    //checkList.append("if");
    //checkList.append("(");
    //checkList.append("while");
    //checkList.append("(");
    checkList.append("new ");
    checkList.append("if ");
    checkList.append("if (");
    checkList.append("while ");
    checkList.append("while (");
}

/*
 * This function is used to remove data inside parenthesis
 * ***Example
 *      i/p = int main(void)
 *      o/p = int main
 */
QString AutoCommentHelper::removeDataInsideParenthesis(QString curentLine)
{
    int startIndex = curentLine.indexOf('(');
    int length = curentLine.count()-1;
    curentLine = curentLine.remove(startIndex, length);
    return curentLine;
}

/*
 * This function is deprecated function.
 * This function is used to remove extra whitespaces
 */
QString AutoCommentHelper::removeWhiteSpaces(QString curentLine)
{
    int startIndex = curentLine.indexOf(curentLine.at(0));
    int length = curentLine.indexOf(' ') + 1;
    curentLine = curentLine.remove(startIndex, length);
    return curentLine;
}

/*
 * This is used to identify following cases, in such below cases line will be identified as function.
 * ***Example :->
 *      Case 1 : void func_name(int i, char x) {
 *      Case 2 : void func_name(int s, char z)
 *               {
 *      Case 3 : void func_name(int s, char z);
 */
bool AutoCommentHelper::isCurrLineFunctionCheck1(QString currentLine, QString nextLine)
{
    bool returnValueCheck1 = true;
    if( !( (currentLine.contains(')') && currentLine.contains('{')) ||
           (currentLine.contains(')') && nextLine.contains('{'))      ||
           (currentLine.contains(')') && currentLine.contains(';')) ) )
    {
        returnValueCheck1 = false;
        //qInfo()<<"contains brackets";
    }
    return returnValueCheck1;
}

/*
 * This function is used to identify whether current is func defination/declaration or not
 *  Case 1 : printf("Love Jihaad");
 *           => Curr line is not declaration/defination, please ignore parsing.
 *  Case 2 : void myPrint("Love Sex Dhoka");
 *           => Curr line is declaration, dont ignore parsing put comments.
 *  to identify above cases split API is used, split count should be greater tha 1 to satisfy above cases.
 *  split is done using delimiter " "
 */
bool AutoCommentHelper::isCurrLineFunctionCheck2(QString currentLine)
{
    bool returnValueCheck2 = true;
    if(currentLine.split(" ").count() <= 1)
    {
        returnValueCheck2 = false;
        //qInfo()<<"split count is greater than 1";
    }
    return returnValueCheck2;
}

/*
 * This function is used to check special cases mentioned in checklist .
 * In case of any occurence of special case, the current line is not identified as function.
 */
bool AutoCommentHelper::isCurrLineFunctionCheck3(QString currentLine)
{
    bool returnValueCheck3 = true;
    foreach (QString check, checkList)
    {
        if(currentLine.contains(check))
        {
            returnValueCheck3 = false;
            qDebug()<<"contains checkList char :"<<check;
            break;
        }
    }
    return  returnValueCheck3;
}

/*
 * This function is master function
 * Final bool result of this function will decide current line is function or not
 * It evaluates based on result of following functions
 * 1. bool AutoCommentHelper::isCurrLineFunctionCheck1(QString currentLine, QString nextLine)
 * 2. bool AutoCommentHelper::isCurrLineFunctionCheck2(QString currentLine)
 * 3. bool AutoCommentHelper::isCurrLineFunctionCheck3(QString currentLine)
 */
bool AutoCommentHelper::isCurrLineFunction(QString currentLine, QString nextLine)
{
    // qDebug()<<"Current Line :"<<currentLine;
    // qDebug()<<"Next Line :"<<nextLine;

    bool returnValue = true ;

    bool returnValueCheck1 = isCurrLineFunctionCheck1(currentLine, nextLine);
    bool returnValueCheck2 = isCurrLineFunctionCheck2(currentLine);
    bool returnValueCheck3 = isCurrLineFunctionCheck3(currentLine);

    if(returnValueCheck1 == false || returnValueCheck2 == false || returnValueCheck3 == false)
    {
        returnValue = false;
    }

    /*returnDebugLogs(returnValueCheck1, returnValueCheck2,
                    returnValueCheck3, returnValue);*/
    return returnValue;
}

// ADD COMMENTS HERE.
QStringList AutoCommentHelper::formatString(QString fun)
{
    fun = fun.trimmed();
    QStringList formattedStringList;

    if(fun.contains(';') && fun.contains(' '))
    {
        QStringList splitFun = fun.remove(";").split(" ");
        foreach (QString string , splitFun)
        {
            if(!string.isEmpty())
            {
                formattedStringList.append(string);
            }
        }
    }
    return formattedStringList;
}

// Removes multiLine comments
/// Example1:
/// Input  : void fun_name(int param1 /*param1 contains key*/, int param2 /*param2 contains value*/ )
/// Output : void fun_name(int param1, int param2)

/// Example2:
/// Input  : void fun_name(int param1, int param2) /*param1 contains key and
///          param2 contains value*/
/// Output : void fun_name(int param1, int param2)
QString AutoCommentHelper::removeMultiLineComments(QString functionSyntax)
{
    int startIndex = functionSyntax.indexOf("/*");
    while( startIndex > -1  )
    {
        int endIndex = functionSyntax.indexOf("*/");
        if( endIndex > -1 )
        {
            int length = endIndex - startIndex + 2;
            functionSyntax = functionSyntax.remove(startIndex,length);
        }
        else
        {
            int length = functionSyntax.length() - startIndex;
            functionSyntax = functionSyntax.remove(startIndex, length);
        }
        startIndex = functionSyntax.indexOf("/*");
    }
    return functionSyntax;
}

// Removes singleLine comments
/// Example:
/// Input  : void fun_name(int param1, int param2 )//param1 contains key and param2 contains value
/// Output : void fun_name(int param1, int param2 )
QString AutoCommentHelper::removeSingleLineComments(QString functionSyntax)
{
    if(functionSyntax.contains("//"))
    {
        int startIndex = functionSyntax.indexOf("//");
        int length = functionSyntax.length() - startIndex;
        functionSyntax.remove(startIndex, length);
    }
    return functionSyntax;
}

// Removes "/n" charachter if any.
QString AutoCommentHelper::removeNewLineChar(QString functionSyntax)
{
    functionSyntax = functionSyntax.replace("\n","");
    return functionSyntax;
}

/*
 *  This function removes uneccessary whitespaces if any.
 */
QString AutoCommentHelper::removeExtraWhiteSpaces(QString functionSyntax)
{
    functionSyntax.replace(" ::","::");
    functionSyntax.replace(":: ","::");
    functionSyntax.replace("( ","(");
    functionSyntax.replace(" )",")");
    functionSyntax.replace('*'," * ");
    functionSyntax.replace('&'," & ");

    while(functionSyntax.contains("  "))
    {
        functionSyntax.replace("  "," ");
    }
    return functionSyntax;
}

/*
 * This function formats given line to standard syntax,
 * for identifying line as a function.
 * Further the standard syntax is sent to check whether,
 * the current line is function or not.
 */
QString AutoCommentHelper::toStdSyntax(QString functionSyntax)
{
    functionSyntax = functionSyntax.trimmed();
    functionSyntax = removeExtraWhiteSpaces(functionSyntax);
    functionSyntax = removeNewLineChar(functionSyntax);
    functionSyntax = removeMultiLineComments(functionSyntax);
    functionSyntax = removeSingleLineComments(functionSyntax);
    // functionSyntax = functionSyntax.replace(";","");
    // qDebug()<<"STD::SYNTAX is "<<functionSyntax;
    return functionSyntax;
}

/*
 * This function is used to print return debug logs.
 * return debug logs means here they are the checks,
 * which are used to identify the current line is function or not.
 */
void AutoCommentHelper::returnDebugLogs(int returnValueCheck1, int returnValueCheck2,
                                        int returnValueCheck3, int returnValue)
{
    // qDebug()<<"returnValueCheck1"<<returnValueCheck1;
    // qDebug()<<"returnValueCheck2"<<returnValueCheck2;
    // qDebug()<<"returnValueCheck3"<<returnValueCheck3;

    Q_UNUSED(returnValueCheck1);
    Q_UNUSED(returnValueCheck2);
    Q_UNUSED(returnValueCheck3);

    qDebug()<<"final return value"<<returnValue;
}
