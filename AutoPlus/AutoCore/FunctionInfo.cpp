#include "FunctionInfo.h"

/*
 * Function Info class constructor
 */
FunctionInfo::FunctionInfo():
    m_isFunctionInline(false),
    m_isFunctionConst(false),
    m_isFunctionVirtual(false),
    m_isFunctionPureVirtual(false),
    m_isClassNamePresent(false),
    m_isReturnConst(false),
    m_isReturnReference(false),
    m_isReturnPointer(false),
    m_returnDataType(""),
    m_className(""),
    m_functionName("")
{
}

/*
 * This function is used as getter function.
 * It return class name.
 */
QString FunctionInfo::get_className()
{
    return m_className;
}

/*
 * This function is used as getter function.
 * It returns function name.
 */
QString FunctionInfo::get_functionName()
{
    return m_functionName;
}

/*
 * This function is used as getter function.
 * It returns function return type.
 */
QString FunctionInfo::get_functionReturnType()
{
    return m_returnDataType;
}

/*
 * This function is used as getter function.
 * It returns bool value, true indicating function is inline.
 */
bool FunctionInfo::get_isFunctionInline()
{
    return m_isFunctionInline;
}

/*
 * This function is used as getter function.
 * It returns function name.
 */
bool FunctionInfo::get_isFunctionConst()
{
    return m_isFunctionConst;
}

/*
 * This function is used as getter function.
 * It returns bool, true indicating function is pure virtual.
 */
bool FunctionInfo::get_isFunctionPureVirtual()
{
    return m_isFunctionPureVirtual;
}

/*
 * This function is used as getter function.
 * It returns bool, true indicating class name is present.
 */
bool FunctionInfo::get_isClassNamePresent()
{
    return m_isClassNamePresent;
}

/*
 * This function is used as getter function.
 * It returns bool, true indicating function return is constant.
 */
bool FunctionInfo::get_isReturnConst()
{
    return m_isReturnConst;
}

/*
 * This function is used as getter function.
 * It returns bool, true indicating function return type is pointer.
 */
bool FunctionInfo::get_isReturnPointer()
{
    return m_isReturnPointer;
}

/*
 * This function is used as setter function.
 * It sets bool value, true indicating function is inline.
 */
void FunctionInfo::set_isFunctionInline(QString functionSyntax)
{
    m_isFunctionInline = functionSyntax.contains("inline ") ? true : false;
}

/*
 * This function is used as setter function.
 * It sets bool value, true indicating function is const.
 * ********** ADD RETURN IS CONST OR .................
 */
void FunctionInfo::set_isFunctionConst(QString functionSyntax)
{
    if(functionSyntax.contains(')'))
    {
        QStringList checkConstString = functionSyntax.split(" ");
        QString xyz = "";

        for(int cL = 0; cL < checkConstString.count(); cL++)
        {
            if(checkConstString.at(cL) != " ")
            {
                xyz = xyz + checkConstString.at(cL);
            }
        }
        m_isFunctionConst = xyz.contains("const;") ? true : xyz.contains("const{") ? true : false ;
    }
}

/*
 * This function is used as setter function.
 * It sets string value, indicating function name.
 */
void FunctionInfo::set_FunctionName(QString functionSyntax)
{
    if(functionSyntax.contains('(') && functionSyntax.contains(')'))
    {
        QStringList splittedString = functionSyntax.split('(');

        // Ignore data after '(', so sonsidering only at(0)
        QString functionName = splittedString.at(0);

        /*
         * Again splitting by space i.e ' ', ignoring return type,
         * Considering only function name and class name if any.
         */
        QStringList removeSpaces = functionName.split(" ");

        int splitCount = removeSpaces.count();
        functionName  = removeSpaces.at(splitCount - 1);

        // If text contains classname an function name both.
        if(functionName.contains("::"))
        {
            m_functionName = functionName.split("::").at(1);
        }
    }
}

/*
 * This function is used as setter function.
 * It sets bool value, true indicating function is pure virtual.
 */
void FunctionInfo::set_isFunctionPureVirtual(QString functionSyntax)
{
   m_isFunctionPureVirtual = functionSyntax.contains(") = 0") ? true :
                             functionSyntax.contains(") =0")  ? true :
                             functionSyntax.contains(")= 0")  ? true :
                             functionSyntax.contains(")=0")   ? true : false ;
}

/*
 * This function is used as setter function.
 * It sets bool value, true indicating class name is present.
 */
void FunctionInfo::set_isClassNamePresent(QString functionSyntax)
{
   m_isClassNamePresent = functionSyntax.contains("::") ? true : false;
}

/*
 * This function is not in use, please add comments when it comes in use.
 * ***** Deprecated version.
 */
void FunctionInfo::set_isReturnConst(QString functionSyntax)
{
    // m_isReturnConst = m_returnDataType ? c("const") ? true : false;
    Q_UNUSED(functionSyntax);
}

/*
 * This function is not in use, please add comments when it comes in use.
 * ***** Deprecated version.
 */
void FunctionInfo::set_isReturnPointer(QString functionSyntax)
{
    // m_isReturnPointer = m_returnDataType ? contains("*") ? true : false;
    Q_UNUSED(functionSyntax);
}

/// QListIterator<ParamInfo::SParamInfo> paramListItr(paramList);
/// ADD COMMENTS HERE.
void FunctionInfo::set_className_and_returnType(QString functionSyntax)
{
    if(functionSyntax.contains("::"))
    {
        QStringList splittedString  = functionSyntax.split("::");
        QString className  = splittedString.at(0);
        QStringList removeSpaces = className.split(" ");
        int splitCount = removeSpaces.count();

        if(splitCount >= 2)
        {
            m_className = removeSpaces.at(splitCount - 1);
            m_returnDataType = removeSpaces.at(splitCount - 2);
        }
    }
}
