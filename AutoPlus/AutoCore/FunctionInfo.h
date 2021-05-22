#ifndef FUNCTIONINFO_H
#define FUNCTIONINFO_H
#include <QString>
#include <qdebug.h>

class FunctionInfo
{
public:
    FunctionInfo();

    // getters
    bool get_isFunctionInline();
    bool get_isFunctionConst();
    bool get_isFunctionPureVirtual();
    bool get_isClassNamePresent();
    bool get_isReturnConst();
    bool get_isReturnPointer();
    QString get_className();
    QString get_functionName();
    QString get_functionReturnType();

    // setters
    void set_isFunctionInline(QString functionSyntax);
    void set_isFunctionConst(QString functionSyntax);
    void set_isFunctionPureVirtual(QString functionSyntax);
    void set_isClassNamePresent(QString functionSyntax);
    void set_isReturnConst(QString functionSyntax);
    void set_isReturnPointer(QString functionSyntax);
    void set_className_and_returnType(QString functionSyntax);
    void set_FunctionName(QString functionSyntax);

private:
    bool m_isFunctionInline;
    bool m_isFunctionConst;
    bool m_isFunctionVirtual;
    bool m_isFunctionPureVirtual;
    bool m_isClassNamePresent;
    bool m_isReturnConst;
    bool m_isReturnReference;
    bool m_isReturnPointer;

    QString m_functionName;
    QString m_returnDataType;
    QString m_className;

};

#endif // FUNCTIONINFO_H
