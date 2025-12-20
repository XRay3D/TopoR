#include "xmlserializer.h"

#include <QFile>

namespace Xml {

Serializer::Serializer(const QString& name)
    : fileName{name} {
    item->itemData[TreeItem::NameType] = "Name (Type)";
    item->itemData[TreeItem::Value] = "Value";
    item->itemData[TreeItem::IsAttr] = "IsAttr";
    item->itemData[TreeItem::FLine] = "Line #";

    load();
    return;

    QFile file{"in.fst"};
    qWarning() << file.fileName();
    if(!file.open(QIODevice::WriteOnly)) {
        qWarning() << file.errorString();
        return;
    }

    QString text = doc.toString(4);
    text.replace("<![CDATA[", "");
    text.replace("]]>", "");
    text.replace("&#xd;", "\x0D");
    text.replace("&#xa;", "\x0A");
    file.write(text.toUtf8());
}

bool Serializer::load() {
    outDoc = {};
    do {
        QFile file{fileName};
        if(!file.open(QIODevice::ReadOnly)) {
            qWarning() << file.errorString();
            break;
        }
        if(auto [errMessage, errLine, errColumn] = doc.setContent(&file)) {
            file.close();
            return true;
        } else {
            qWarning() << errMessage << errLine << errColumn;
            break;
        }
    } while(false);
    return false;
}

QString Serializer::toString() const {
    QDomNode xmlNode = outDoc.createProcessingInstruction("xml", R"(version='1.0' encoding='UTF-8')");
    outDoc.insertBefore(xmlNode, outDoc.firstChild());
    QString text = outDoc.toString(4);
    text.replace("<![CDATA[", "");
    text.replace("]]>", "");
    text.replace("&#xd;", "\x0D");
    text.replace("&#xa;", "\x0A");
    text.replace("    ", "\t"); // NOTE может менять только началострок
    return text;
}

bool Serializer::save() {
    if(QFile file{fileName}; file.open(QFile::WriteOnly)) {
        file.write(toString().toUtf8());
        return true;
    } else
        qWarning() << file.errorString();
    return false;
}

void Serializer::save(const QString& dir) {
    fileName = dir;
    save();
}

void Serializer::debugNode() const {
    QDomDocument outDoc{""};
    outDoc.insertBefore(node.cloneNode(), outDoc.firstChild());
    QString text = outDoc.toString(4);
    text.replace("<![CDATA[", "");
    text.replace("]]>", "");
    text.replace("&#xd;", "\x0D");
    text.replace("&#xa;", "\x0A");
    // text.replace("    ", "\t");
    qInfo() << node.lineNumber() << '\n'
            << text.toUtf8().data();
}

} // namespace Xml
