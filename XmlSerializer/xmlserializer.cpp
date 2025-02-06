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

        QString errorMsg{};
        int errorLine{};
        int errorColumn{};
        if(!doc.setContent(&file, &errorMsg, &errorLine, &errorColumn)) {
            qWarning() << errorMsg << errorLine << errorColumn;
            break;
        }

        file.close();
        return true;
    } while(false);
    return false;
}

bool Serializer::save() {
    QDomNode xmlNode = outDoc.createProcessingInstruction("xml", R"(version='1.0' encoding='UTF-8')");
    outDoc.insertBefore(xmlNode, outDoc.firstChild());
    QString text = outDoc.toString(4);
    text.replace("<![CDATA[", "");
    text.replace("]]>", "");
    text.replace("&#xd;", "\x0D");
    text.replace("&#xa;", "\x0A");
    if(QFile file{fileName}; file.open(QFile::WriteOnly)) {
        file.write(text.toUtf8());
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
    qInfo() << node.lineNumber() << '\n'
            << text.toUtf8().data();
}

} // namespace Xml
