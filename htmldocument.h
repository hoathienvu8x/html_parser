#ifndef HTMLDOCUMENT_H
#define HTMLDOCUMENT_H

#include "htmlelement.h"

class HTMLDocument {
    public:
        HTMLDocument() {
            _root = new HTMLElement("html");
        }
        HTMLDocument(HTMLElement *root) : _root(root){}
        HTMLElement *firstChild() {
            return _root->firstChild();
        }
        HTMLElement *lastChild() {
            return _root->lastChild();
        }
        HTMLElement *nextSibling() {
            return _root->nextSibling();
        }
        HTMLElement *prevSibling() {
            return _root->prevSibling();
        }
        HTMLElement *getElementById(std::string &id) {
            return _root->getElementById(id);
        }
        std::vector<HTMLElement*> getElementByClassName(std::string &name) {
            return _root->getElementByClassName(name);
        }
        std::vector<HTMLElement*> getElementByTagName(std::string &tagName){
            return _root->getElementByTagName(tagName);
        }
        HTMLElement *querySelector(const std::string &selector) {
            return _root->querySelector(selector);
        }
        std::vector<HTMLElement*> querySelectorAll(const std::string &selector) {
            return _root->querySelectorAll(selector);
        }
    private:
        HTMLElement *_root;
};

#endif
