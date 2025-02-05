#include "xmlserializer.h"

#include <QFile>

QTextStream& operator<<(QTextStream& d, std::string_view sv) {
    return d << QByteArray{sv.data(), static_cast<int>(sv.size())};
}

QDebug operator<<(QDebug d, std::string_view sv) {
    return d.noquote() << QByteArray{sv.data(), static_cast<int>(sv.size())};
}

QDebug operator<<(QDebug d, std::set<QString> c) {
    const bool oldSetting = d.autoInsertSpaces();
    d.nospace() << "set" << '(';
    auto it = c.begin(), end = c.end();
    if(it != end) d << *it++;
    while(it != end) d << ", " << *it++;
    d << ')';
    d.setAutoInsertSpaces(oldSetting);
    return d.maybeSpace();
}

Xml::Xml(const QString& name) {
    // buffer.open(QIODevice::WriteOnly);
    item->itemData[TreeItem::NameType] = "Name (Type)";
    item->itemData[TreeItem::Value] = "Value";
    item->itemData[TreeItem::IsAttr] = "IsAttr";
    item->itemData[TreeItem::FLine] = "Line #";
    QFile file{name};
    if(!file.open(QIODevice::ReadOnly)) {
        qWarning() << file.errorString();
        return;
    }

    QString errorMsg{};
    int errorLine{};
    int errorColumn{};
    if(!doc.setContent(&file, &errorMsg, &errorLine, &errorColumn)) {
        qWarning() << errorMsg << errorLine << errorColumn;
        return;
    }

    // std::function<void(const QDomNode&)> func = [&func](const QDomNode& node) {
    //     static int i;
    //     switch(node.nodeType()) {
    //     case QDomNode::ElementNode:
    //     case QDomNode::AttributeNode:
    //     case QDomNode::TextNode:
    //     case QDomNode::CDATASectionNode:
    //     case QDomNode::EntityReferenceNode:
    //     case QDomNode::EntityNode:
    //     case QDomNode::ProcessingInstructionNode:
    //     case QDomNode::CommentNode:
    //     case QDomNode::DocumentNode:
    //     case QDomNode::DocumentTypeNode:
    //     case QDomNode::DocumentFragmentNode:
    //     case QDomNode::NotationNode:
    //     case QDomNode::BaseNode:
    //     case QDomNode::CharacterDataNode:
    //         break;
    //     }
    //     QByteArray str;
    //     str.fill(' ', i++ * 4);
    //     qInfo() << str.data() << node.nodeType() << node.nodeName() << node.nodeValue() << node.lineNumber();
    //     auto childNodes = node.childNodes();
    //     for(int i{}; i < childNodes.size(); ++i) {
    //         func(childNodes.at(i));
    //     }
    //     --i;
    // };
    // func(doc.firstChildElement());
    // exit(0);

    file.close();

    /*

    QDomDocument doc;
    QDomElement root = doc.createElement("MyML");
    doc.appendChild(root);

    QDomElement tag = doc.createElement("Greeting");
    root.appendChild(tag);

    QDomText t = doc.createTextNode("Hello World");
    tag.appendChild(t);

    tag.setAttribute("Attr", "Value");

    QString xml = doc.toString();
    ui->plainTextEdit->setPlainText(xml);
*/

    // return;

    file.setFileName("in.fst");
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

void Xml::save(const QString& dir) {
    QDomNode xmlNode = outDoc.createProcessingInstruction("xml", R"(version="1.0" encoding="UTF-8")");
    outDoc.insertBefore(xmlNode, outDoc.firstChild());
    QString text = outDoc.toString(4);
    text.replace("<![CDATA[", "");
    text.replace("]]>", "");
    text.replace("&#xd;", "\x0D");
    text.replace("&#xa;", "\x0A");
    if(QFile file{dir}; file.open(QFile::WriteOnly)) {
        file.write(text.toUtf8());
        // QTextStream out(&file);
        // outDoc.save(out, 4);
    }
}

void Xml::debugNode() const {
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
