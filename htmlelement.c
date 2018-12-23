#include "htmlelement.h"

HTMLElement::HTMLElement(std::string tag) : tagName(tag), id("") {
    m_attributes["id"] = "";
    m_attributes["class"] = "";
}

HTMLElement::HTMLElement(HTMLElement *parent) : m_parent(parent) {}

HTMLElement *HTMLElement::appendChild(std::unique_ptr<HTMLElement> && newNode){
    newNode->m_parent = this;
    childrens.emplace_back(std::move(newNode));
    return newNode.get();
}

HTMLElement *HTMLElement::firstChild(){
    return children(0);
}

HTMLElement *HTMLElement::lastChild(){
    return children(-1);
}

HTMLElement *HTMLElement::nextSibling(){
    if(m_parent == NULL) {
        return nullptr;
    }
    size_t index = 0;
    size_t count = childrens.size();
    while(index < count && this != m_parent->childrens[index].get()) {
        ++index;
    }
    if(++index >= count) {
        return nullptr;
    }
    return m_parent->childrens[index].get();
}

HTMLElement *HTMLElement::prevSibling(){
    if (m_parent == NULL) {
        return nullptr;
    }
    size_t index = 0;
    size_t count = childrens.size();
    while(index < count && this != m_parent->childrens[index].get()) {
        ++index;
    }
    if (--index < 0) {
        return nullptr;
    }
    return m_parent->childrens[index].get();
}

bool HTMLElement::hasClass(std::string className) const {
    const auto &names = m_attributes.at("class");
    return names.find(className) != std::string::npos;
}

void HTMLElement::addClass(std::string &className) {
    if(!hasClass(className)) {
        std::string classes = m_attributes.at("class");
        classes += " " + className;
        m_attributes["class"] = classes;
    }
}

void HTMLElement::setAttribute(std::string &name, std::string val) {
    m_attributes[name] = val;
}

void HTMLElement::removeAttribute(std::string name) {
    m_attributes.erase(std::string(name));
}

std::string HTMLElement::getAttribute(const std::string &name) {
    const auto it = m_attributes.find(name);
    if (it != m_attributes.end()){
        return it->second;
    }
    return "";
}

bool HTMLElement::hasAttribute(const std::string &name) const {
    return m_attributes.find(name) != m_attributes.end();
}

HTMLElement *HTMLElement::children(size_t index) {
    if (childrens.size() == 0) {
        return nullptr;
    }
    if (index < 0) {
        index = childrens.size() + index;
    }
    if (index >= childrens.size()) {
        return nullptr;
    }
    return childrens[index].get();
}

HTMLElement *HTMLElement::getElementById(std::string id) {
    std::vector<HTMLElement*> queue(1, this);
    while(queue.size()) {
        std::vector<HTMLElement*> next;
        for(auto &node : queue) {
            if (node->id == id) {
                return node;
            }
            for(auto &i : node->childrens) {
                next.push_back(i.get());
            }
        }
        queue = next;
    }
    return nullptr;
}

std::vector<HTMLElement*> HTMLElement::getElementByClassName(std::string name) {
    std::vector<HTMLElement*> retVal;
    std::vector<HTMLElement*> queue(1, this);
    while (queue.size()) {
        std::vector<HTMLElement*> next;
        for(auto &node : queue) {
            if (node->hasClass(name)){
                retVal.push_back(node);
            }
            for(auto &i : node->childrens) {
                next.push_back(i.get());
            }
        }
        queue = next;
    }
    return retVal;
}

std::vector<HTMLElement*> HTMLElement::getElementByTagName(std::string tagName) {
    std::vector<HTMLElement*> retVal;
    std::vector<HTMLElement*> queue(1, this);
    while(queue.size()) {
        std::vector<HTMLElement*> next;
        for(auto &node : queue) {
            if(node->tagName == tagName) {
                retVal.push_back(node);
            }
            for(auto &i : node->childrens) {
                next.push_back(i.get());
            }
        }
        queue = next;
    }
    return retVal;
}

std::vector<HTMLElement*> HTMLElement::querySelectorAll(const std::string &selector){
    std::vector<HTMLElement*> retVal;
    std::vector<HTMLElement*> queue(1, this);
    while(queue.size()) {
        std::vector<HTMLElement*> next;
        for(auto &node : queue) {
            if(node->matchesSelector(selector)) {
                retVal.push_back(node);
            }
            for(auto &i : node->childrens) {
                next.push_back(i.get());
            }
        }
        queue = next;
    }
    return retVal;
}

HTMLElement *HTMLElement::querySelector(const std::string &selector){
    std::vector<HTMLElement*> retVal;
    std::vector<HTMLElement*> queue(1, this);
    while(queue.size()){
        std::vector<HTMLElement*> next;
        for(auto &node : queue) {
            if(node->matchesSelector(selector)){
                return node;
            }
            for(auto &i : node->childrens){
                next.push_back(i.get());
            }
        }
        queue = next;
    }
    return nullptr;
}
bool HTMLElement::matchesSelector(const std::string &selector) const {
    const auto temp = selector.substr(1, selector.size() - 1);
    return tagName == selector || m_attributes.at("id") == temp && selector[0] == '#' || hasClass(std::string(temp)) && selector[0] == '.';
}
