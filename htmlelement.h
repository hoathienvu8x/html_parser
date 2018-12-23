#ifndef HTMLELEMENT_H
#define HTMLELEMENT_H

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

class HTMLElement {
    public:
        HTMLElement(std::string);
        HTMLElement *appendChild(std::unique_ptr<HTMLElement> &&);
        HTMLElement *firstChild();
        HTMLElement *lastChild();
        HTMLElement *nextSibling();
        HTMLElement *prevSibling();
        bool hasClass(std::string) const;
        void addClass(std::string &);
        void setAttribute(std::string &, std::string);
        void removeAttribute(std::string);
        std::string getAttribute(const std::string &);
        bool hasAttribute(const std::string &) const;
        HTMLElement *children(size_t index);
        HTMLElement *getElementById(std::string);
        std::vector<HTMLElement*> getElementByClassName(std::string);
        std::vector<HTMLElement*> getElementByTagName(std::string);
        std::vector<HTMLElement*> querySelectorAll(const std::string &);
        HTMLElement *querySelector(const std::string &);
        HTMLElement *parent() {
            return m_parent;
        }
        std::vector<std::unique_ptr<HTMLElement>> childrens = {};
        std::string id = "";
        std::string tagName = "";
    private:
        bool matchesSelector(const std::string &) const;
        std::unordered_map<std::string, std::string> m_attributes;
        HTMLElement *m_parent;
};

#endif
