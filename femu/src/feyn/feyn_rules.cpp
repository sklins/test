#include "feyn_rules.h"
#include <QtXml>

void XmlFail(const QString &msg) {
    QTextStream(stderr) << "Xml parsing error: " << msg << "\n";
    exit(1);
}

void XmlVerify(bool val, const QString &msg) {
    if (!val)
        XmlFail(msg);
}

void XmlVerify(bool val) {
    XmlVerify(val, "");
}

bool XmlBoolean(const QString &val) {
    if (val == "yes" || val == "true") return true;
    else if (val == "no" || val == "false") return false;
    else XmlFail("Invalid boolean: " + val + "; expected yes/true or no/false");
    throw 0; // To eliminate compiler warnings
}

void TFeynRules::ImportFromXml(const QString &xmlFileName) {
    qDebug() << "Importing xml from" << xmlFileName;

    QFile file(xmlFileName);

    QDomDocument doc;
    doc.setContent(&file);

    QDomElement e_doc = doc.documentElement();
    XmlVerify(e_doc.tagName() == "feynman-rules", "Document tag must be <feynman-rules> instead of " + e_doc.tagName());

    XmlVerify(e_doc.hasAttribute("name"), "Feynman rule collection name attribute is missing");
    Name = e_doc.attribute("name");

    QDomElement e_particles, e_interactions;
    ASSERT(e_particles.isNull() && e_interactions.isNull());

    for (QDomElement i = e_doc.firstChildElement(); !i.isNull(); i = i.nextSiblingElement()) {
        if (i.tagName() == "particles") {
            XmlVerify(e_particles.isNull(), "Duplicate particles block");
            e_particles = i;
        } else if (i.tagName() == "interactions") {
            XmlVerify(e_interactions.isNull(), "Duplicate interactions block");
            e_interactions = i;
        } else XmlFail("Unsupported block id: " + i.tagName());
    }

    XmlVerify(!e_particles.isNull(), "No particles block found");
    XmlVerify(!e_interactions.isNull(), "No interactions block found");

    QHash<QString, TParticle*> knownParticles;

    for (QDomElement i = e_particles.firstChildElement(); !i.isNull(); i = i.nextSiblingElement()) {
        XmlVerify(i.tagName() == "particle", "Particles block must consist of <particle> tags");

        XmlVerify(i.hasAttribute("name"), "Particle name attribute is missing");
        QString name = i.attribute("name");

        XmlVerify(i.hasAttribute("line-style"), "Particle line-style attribute is missing");
        QString lineStyleStr = i.attribute("line-style");
        ELineStyle lineStyle = LS_NORMAL;
        if (lineStyleStr == "normal") lineStyle = LS_NORMAL;
        else if (lineStyleStr == "dashed") lineStyle = LS_DASHED;
        else if (lineStyleStr == "dotted") lineStyle = LS_DOTTED;
        else if (lineStyleStr == "wave") XmlFail("We don't support wave propagators yet :(");
        else XmlFail("Unknown line style: " + lineStyleStr);

        TParticle *p = new TParticle(name, lineStyle);
        knownParticles.insert(name, p);
        Particles << p;
    }

    for (QDomElement i = e_interactions.firstChildElement(); !i.isNull(); i = i.nextSiblingElement()) {
        XmlVerify(i.tagName() == "interaction", "Interactions block must consist of <interaction> tags");

        XmlVerify(i.hasAttribute("name"), "Interaction name attribute is missing");
        QString name = i.attribute("name");

        XmlVerify(i.hasAttribute("allow-simple-loops"), "Interaction allow-simple-loops attribute is missing");
        bool allowSimpleLoops = XmlBoolean(i.attribute("allow-simple-loops"));

        TInteraction *in = new TInteraction(name, allowSimpleLoops);

        for (QDomElement p = i.firstChildElement(); !p.isNull(); p = p.nextSiblingElement()) {
            XmlVerify(p.tagName() == "participant", "Interaction participant tag must be <participant>");
            XmlVerify(p.hasAttribute("particle"), "Interaction participant 'particle' attribute is missing");
            QString particle = p.attribute("particle");
            if (knownParticles.contains(particle))
                in->Participants << knownParticles.value(particle);
            else XmlFail("Unknown particle " + particle + " is supposed to participate in interaction " + name);
        }

        Interactions << in;
    }

    qDebug() << "Done. " << Particles.size() << " particles & " << Interactions.size() << " interactions";
}

bool TFeynRules::CheckLimitations(const TLimitations& limitations) const {
    if (limitations.TotalInteractionsLimit.HasValue())
        return true;

    // TODO: fixed LoopsLimit also renders diagrams amount finite.
    // In this case we have to iterate through all (infinite) sets
    // of interactions until the diagrams appear to have more loops than allowed.

    for (QSet<TInteraction*>::ConstIterator i = Interactions.begin();
            i != Interactions.end(); i++)
        if (!limitations.InteractionLimits.contains(*i)) return false;

    return true;
}

