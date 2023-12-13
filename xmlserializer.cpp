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
    if (it != end) d << *it++;
    while (it != end) d << ", " << *it++;
    d << ')';
    d.setAutoInsertSpaces(oldSetting);
    return d.maybeSpace();
}

Xml::Xml(const QString& name) {
    // buffer.open(QIODevice::WriteOnly);
    item->itemData[Name] = "Name";
    item->itemData[Value] = "Value";
    item->itemData[IsAttr] = "IsAttr";
    item->itemData[Type] = "Type";
    item->itemData[FLine] = "Line #";
    QFile file{name};
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << file.errorString();
        return;
    }

    QString errorMsg{};
    int errorLine{};
    int errorColumn{};
    if (!doc.setContent(&file, &errorMsg, &errorLine, &errorColumn)) {
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
    return;
    file.setFileName(file.fileName().replace("/", "/formated_"));
    qWarning() << file.fileName();
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << file.errorString();
        return;
    }
    file.write(doc.toString(4).toUtf8());
}
